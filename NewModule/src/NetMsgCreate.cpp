#include "NetMsgCreate.h"

#include "ManagerGLView.h"
#include "WorldContainer.h"
#include "GLView.h"
#include "Model.h"
#include "WOFTGLString.h"
#include "MGLFTGLString.h"

using namespace Aftr;
using namespace std;

NetMsgMacroDefinition(NetMsgCreate);

NetMsgCreate::NetMsgCreate() {
	this->setCamPos(Vector(0, 0, 0));
	this->setStringPos(Vector(0, 0, 0));
	this->setCamLookDir(Vector(0, 0, 0));
	this->setStringRotateZ(0.0f);
	this->setStringContent("");
	this->setLabel("");
}

bool NetMsgCreate::toStream(NetMessengerStreamBuffer& os) const {
	os << this->camPos.x << this->camPos.y << this->camPos.z << this->camLookDir.x << this->camLookDir.y << this->camLookDir.z << this->stringPos.x
		<< this->stringPos.y << this->stringPos.z << this->stringRotateZ << this->stringContent << this->label;

	return true;
}

bool NetMsgCreate::fromStream(NetMessengerStreamBuffer& is) {
	is >> this->camPos.x >> this->camPos.y >> this->camPos.z>> this->camLookDir.x >> this->camLookDir.y >> this->camLookDir.z >> this->stringPos.x 
		>> this->stringPos.y >> this->stringPos.z >> this->stringRotateZ >> this->stringContent >> this->label;

	return true;
}

void NetMsgCreate::onMessageArrived() {
	if (this->label == "")
	{
		ManagerGLView::getGLView()->getCamera()->setPosition(this->getCamPos());
		ManagerGLView::getGLView()->getCamera()->setCameraLookDirection(this->getCamLookDir());
		return;
	}

	WorldContainer* actorList = ManagerGLView::getGLView()->getActorLst();

	if (actorList != nullptr && actorList->size() > 0) {
		WOFTGLString* wo = (WOFTGLString*)ManagerGLView::getGLView()->getActorLst()->at(0);
		if (this->stringRotateZ != 0.0f) {
			wo->rotateAboutGlobalZ(this->stringRotateZ);
		}
		wo->setPosition(this->stringPos);
		wo->setText(this->stringContent);
		ManagerGLView::getGLView()->getCamera()->setPosition(this->getCamPos());
		ManagerGLView::getGLView()->getCamera()->setCameraLookDirection(this->getCamLookDir());
	}
	else {
		WOFTGLString* string = WOFTGLString::New(ManagerEnvironmentConfiguration::getSMM() + "/fonts/COMIC.TTF", 30);
		string->getModelT<MGLFTGLString>()->setFontColor(aftrColor4f(1.0f, 0.5f, 1.5f, 1.0f));
		string->getModelT<MGLFTGLString>()->setSize(50, 15);
		string->getModelT<MGLFTGLString>()->setText(this->stringContent);
		string->rotateAboutGlobalX(PI / 2);
		string->rotateAboutGlobalZ(-PI / 2);
		string->setPosition(50, 15, 15);
		string->setLabel(this->label);
		ManagerGLView::getGLView()->getWorldContainer()->push_back(string);
		ManagerGLView::getGLView()->getActorLst()->push_back(string);
	}
}

string NetMsgCreate::toString() const {
	stringstream ss;
	ss << NetMsg::toString();
	ss << "Payload is: String Position: " << this->stringPos << "...\nCamera Position: " << this->camPos << "...\nString Content: " << this->stringContent
		<< "....\nString RotateZ: " << this->stringRotateZ << "....\nCamera Look Direction: " << this->camLookDir << "...\nLabel: " << this->label << endl;

	return ss.str();
}

void NetMsgCreate::setStringPos(Vector v) {
	this->stringPos = v;
}


Vector NetMsgCreate::getCamPos() {
	return this->camPos;
}

void NetMsgCreate::setCamPos(Vector v) {
	this->camPos = v;
}

Vector NetMsgCreate::getCamLookDir() {
	return this->camLookDir;
}

void NetMsgCreate::setCamLookDir(Vector dir) {
	this->camLookDir = dir;
}

void NetMsgCreate::setStringRotateZ(float rotate) {
	this->stringRotateZ = rotate;
}

void NetMsgCreate:: setStringContent(string s) {
	this->stringContent = s;
}

void NetMsgCreate::setLabel(string l) {
	this->label = l;
}

