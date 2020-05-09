// killOnSW.cpp

#include "bzfsAPI.h"

class killOnSW : public bz_Plugin
{
public:
    virtual const char* Name () {return "killOnSW";}
    virtual void Init(const char* config);
    virtual void Event(bz_EventData *eventData);
};

BZ_PLUGIN(killOnSW)

void killOnSW::Init( const char* /*commandLine*/ ) {
    bz_debugMessage(2, "killOnSW plugin loaded.");
    if (bz_getBZDBDouble("_shockAdLife") > bz_getBZDBDouble("_explodeTime")) {
        bz_debugMessage(2,"WARNING: Players may be killed and spawn into Shockwave.");
    }
    Register(bz_eShotFiredEvent);
}

void killOnSW::Event ( bz_EventData *eventData ) {
    if (eventData->eventType != bz_eShotFiredEvent)
        return;
    bz_ShotFiredEventData_V1* shotData = (bz_ShotFiredEventData_V1*)eventData;
    
    int shotFiredFrom = shotData->playerID;
    if ((shotFiredFrom >= 0) && (shotFiredFrom <= 199) && (strcmp(shotData->type.c_str(), "SW") == 0)) {
        bz_killPlayer(shotData->playerID, false, BZ_SERVER);
        bz_incrementPlayerLosses(shotData->playerID, -1);
    }
}
