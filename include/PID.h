#ifndef PID_H
#define PID_H

class PID
{

	float P,I,D,IMAX,IMIN,sum,last;
public:
	PID(float, float, float, float, float);

	int GetValue(int value, int error);
	
};
#endif