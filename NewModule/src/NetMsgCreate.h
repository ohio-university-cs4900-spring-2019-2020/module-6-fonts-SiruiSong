#pragma once
#include "NetMsg.h"
#include "Vector.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {

	class NetMsgCreate : public NetMsg {
	public:
		NetMsgMacroDeclaration(NetMsgCreate);

		NetMsgCreate();
		//virtual ~NetMsgCreate();
		virtual bool toStream(NetMessengerStreamBuffer& os) const;
		virtual bool fromStream(NetMessengerStreamBuffer& is);
		virtual void onMessageArrived();
		virtual std::string toString() const;

		//getters and setters
		Vector getCamPos();
		void setCamPos(Vector v);
		Vector getCamLookDir();
		void setCamLookDir(Vector dir);
		void setStringPos(Vector v);
		void setStringRotateZ(float rotate);
		void setStringContent(std::string s);
		void setLabel(std::string l);

	protected:
		Vector camPos; //camera position
		Vector camLookDir; //camera look direction
		Vector stringPos;
		float stringRotateZ;
		std::string stringContent;
		std::string label;
	};
}

#endif
