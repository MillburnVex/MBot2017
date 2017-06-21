#include "main.h"
#include <math.h>

//INSERT MATH FUNCTIONS HERE
//REMEMBER TO ADD ANY METHODS HERE TO FASTMATH.H FOR EXTERNAL USE

static const float NANOTOSEC = 1 / 1000000000;

static const float FLOATERROR = 0.0001f;
static const float PI = 3.1415927f;
static const float PI2 = PI * 2;
static const float PIHALF = PI / 2;
static const float E = 2.7182818f;

static const float MAXRAD = PI * 2;
static const float MAXDEG = 360;
static const float RADDEG = 180 / PI;
static const float DEGRAD = PI / 180;

static const int8_t SINBITS = 12;
static const int16_t SINMASK = ~(-1 << SINBITS);
static const int16_t SINCOUNT = SINMASK + 1;
static const float RADTOINDEX = SINCOUNT / MAXRAD;
static const float DEGTOINDEX = SINCOUNT / MAXDEG;

static int* table;

void genSinTable(){
  table = new int[SINCOUNT];
  for(int i = 0; i < SINCOUNT; i++)
    table[i] = sin((i + 0.5f) / SINCOUNT * MAXRAD);
  for (int i = 0; i < 360; i += 90)
    table[(int)(i * DEGTOINDEX) & SINMASK] = sin(i * DEGRAD);
}

float sin(float radians){
  return table[(int)(radians * RADTOINDEX) & SINMASK];
}

float cos(float radians){
  return table[(int)((radians + PI / 2) * RADTOINDEX) & SINMASK];
}

float tan(float radians){
  return sin(radians)/cos(radians);
}

float sindeg(float degrees){
  return sin(degrees * DEGRAD);
}

float cosdeg(float degrees){
  return cos(degrees * DEGRAD);
}

float tandeg(float degrees){
  return sindeg(degrees)/cosdeg(degrees);
}

float fastatan2(float d1, float d2){
  return atan2(d1,d2);
}

float fasthypot(float x, float y){
  return hypot(x,y);
}

float lerp(float p1, float p2, float progress){
  return p1 + (p2 - p1) * progress;
}

float lerpangle(float fromrad, float torad, float progress) {
  float delta = fmod(torad - fromrad + PI2 + PI, PI2) - PI;
  return fmod(fromrad + delta * progress + PI2, PI2);
}

float lerpangledeg(float fromdeg, float todeg, float progress) {
  return RADDEG * lerpangle(fromdeg * DEGRAD, todeg * DEGRAD, progress);
}

bool fequal(float a, float b){
  return abs(a - b) <= FLOATERROR;
}

bool iszero(float a){
  return abs(a) <= FLOATERROR;
}

float log(float a, float value) {
  return log(value) / log(a);
}

float log2(float value) {
  return log(2, value);
}

float to100(float from){
  return (from * 100)/127;
}

float to127(float from){
  return (from * 127)/100;
}
