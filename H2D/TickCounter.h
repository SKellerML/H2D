#pragma once

#include "OpenGLH.h"

class TickCounter
{
public:
	TickCounter(void);
	~TickCounter(void);

	void start();
	double getTime();
	bool hasPassed(GLdouble time);
	bool hasPassedMS(GLdouble timeInMS);
	void reset();
	bool isRunning();
	void deactivate();

	static void updateEngineTime();
	static void pauseTime();
	static void resumeTime();
	static double getEngineTime();

private:
	static double engineTime;

	GLdouble startTime;

};

