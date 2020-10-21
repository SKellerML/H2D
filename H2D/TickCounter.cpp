#include "TickCounter.h"

double TickCounter::engineTime=glfwGetTime();

void TickCounter::pauseTime()
{
	engineTime=glfwGetTime();
}

void TickCounter::resumeTime()
{
	glfwSetTime(engineTime);
}

double TickCounter::getEngineTime()
{
	return engineTime;
}
void TickCounter::updateEngineTime()
{
	engineTime=glfwGetTime();
}

TickCounter::TickCounter(void)
{
	startTime=0;
}


TickCounter::~TickCounter(void)
{
}

void TickCounter::start()
{
	startTime=engineTime;//glfwGetTime();
}
double TickCounter::getTime()
{
	return (engineTime-startTime);
}
bool TickCounter::hasPassed(GLdouble time)
{
	return ((engineTime-startTime) >= time);
}

bool TickCounter::hasPassedMS(GLdouble timeInMS)
{
	timeInMS/=1000;
	return (timeInMS <= (engineTime-startTime));
}

void TickCounter::reset()
{
	startTime=engineTime;
}
bool TickCounter::isRunning()
{
	return startTime!=0;
}
void TickCounter::deactivate()
{
	startTime=0;
}
