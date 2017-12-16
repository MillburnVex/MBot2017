#ifndef QUICKMATHS
#define QUICKMATHS
#include "main.h"
#include "Quickmaths.h"

int Math::Abs(int a) {
	if(a < 0)
		return -a;
	return a;
}

int Math::Sign(int s) {
	if(s < 0)
		return -1;
	if(s == 0)
		return 0;
	return 1;
}

int Math::Max(int a, int b) {
	if(a > b)
		return a;
	return b;
}

int Math::Min(int a, int b) {
	if(a < b)
		return a;
	return b;
}

#endif
