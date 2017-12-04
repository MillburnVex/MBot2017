#ifndef QUICKMATH
#define QUICKMATH
#include "main.h"
#include <math.h>
#include "Quickmaths.h"

//INSERT MATH FUNCTIONS HERE
//REMEMBER TO ADD ANY METHODS HERE TO FASTMATH.H FOR EXTERNAL USE

namespace Math {

const float NANOTOSEC = 1 / 1000000000;

const float FLOATERROR = 0.0001f;
const float PI2 = PI * 2;
const float PIHALF = PI / 2;
const float E = 2.7182818f;

const float MAXRAD = PI * 2;
const float MAXDEG = 360;
const float RADDEG = 180 / PI;
const float DEGRAD = PI / 180;

const int8_t SINBITS = 12;
const int16_t SINMASK = ~(-1 << SINBITS);
const int16_t SINCOUNT = SINMASK + 1;
const float RADTOINDEX = SINCOUNT / MAXRAD;
const float DEGTOINDEX = SINCOUNT / MAXDEG;

}

static int* table;

void Math::genSinTable(){
        table = new int[SINCOUNT];
        for(int i = 0; i < SINCOUNT; i++)
                table[i] = sin((i + 0.5f) / SINCOUNT * MAXRAD);
        for (int i = 0; i < 360; i += 90)
                table[(int)(i * DEGTOINDEX) & SINMASK] = sin(i * DEGRAD);
}

float Math::sin(float radians){
        return table[(int)(radians * RADTOINDEX) & SINMASK];
}

float Math::cos(float radians){
        return table[(int)((radians + PI / 2) * RADTOINDEX) & SINMASK];
}

float Math::tan(float radians){
        return sin(radians)/cos(radians);
}

float Math::sindeg(float degrees){
        return sin(degrees * DEGRAD);
}

float Math::cosdeg(float degrees){
        return cos(degrees * DEGRAD);
}

float Math::tandeg(float degrees){
        return sindeg(degrees)/cosdeg(degrees);
}

float Math::fastatan2(float d1, float d2){
        return atan2(d1,d2);
}

float Math::fasthypot(float x, float y){
        return hypot(x,y);
}

float Math::lerp(float p1, float p2, float progress){
        return p1 + (p2 - p1) * progress;
}

float Math::lerpangle(float fromrad, float torad, float progress) {
        float delta = fmod(torad - fromrad + PI2 + PI, PI2) - PI;
        return fmod(fromrad + delta * progress + PI2, PI2);
}

float Math::lerpangledeg(float fromdeg, float todeg, float progress) {
        return RADDEG * lerpangle(fromdeg * DEGRAD, todeg * DEGRAD, progress);
}

bool Math::fequals(float a, float b){
        return abs(a - b) <= FLOATERROR;
}

bool Math::iszero(float a){
        return abs(a) <= FLOATERROR;
}

float Math::log(float a, float value) {
        return std::log(value) / std::log(a);
}

float Math::log2(float value) {
        return log(2, value);
}

float Math::to100(float from){
        return (from * 100)/127;
}

float Math::to127(float from){
        return (from * 127)/100;
}
#endif
