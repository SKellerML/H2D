#pragma once

#include "OpenGLH.h"
#include <Box2D\Box2D.h>

bool SortVector(b2Vec3 i, b2Vec3 j)	{ return (i.z < j.z) && (-b2_pi >(i.z - j.z) < b2_pi); }	// b2_pi > (i.z - j.z) < b2_pi;
bool CompareVectorZ(b2Vec3 i, b2Vec3 j)	{ return (i.z == j.z); }