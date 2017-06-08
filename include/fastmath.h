#pragma once

#ifndef FASTMATH_H

#define FASTMATH_H

void genSinTable();

float sin(float radians);

float cos(float radians);

float tan(float radians);

float sindeg(float degrees);

float cosdeg(float degrees);

float tandeg(float degrees);

float lerp(float p1, float p2, float progress);

float lerpangle(float fromrad, float torad, float progress);

float lerpangledeg(float fromdeg, float todeg, float progress);

bool fequals(float a, float b);

bool iszero(float a);

float log(float a, float value);

float log2(float value);

float to100(float from);

float to127(float from);

#endif
