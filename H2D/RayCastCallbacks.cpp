#include "RayCastCallbacks.h"


LaserRayCastCallback::LaserRayCastCallback(void)
{
		impactPoint=b2Vec2(0.f,0.f);
		hitObject=NULL;
}


LaserRayCastCallback::~LaserRayCastCallback(void)
{
}
