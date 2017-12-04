#ifndef QUICKMATH_H

#define QUICKMATH_H

namespace Math {

const float PI = 3.1415927f;

void genSinTable();

float sin(float radians);

float cos(float radians);

float tan(float radians);

float sindeg(float degrees);

float cosdeg(float degrees);

float tandeg(float degrees);

float fastatan2(float d1, float d2);

float fasthypot(float x, float y);

float lerp(float p1, float p2, float progress);

float lerpangle(float fromrad, float torad, float progress);

float lerpangledeg(float fromdeg, float todeg, float progress);

bool fequals(float a, float b);

bool iszero(float a);

float log(float a, float value);

float log2(float value);

float to100(float from);

float to127(float from);

}
#endif
