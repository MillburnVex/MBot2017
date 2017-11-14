#include "main.h"
#include "bot.h"
#include "fastmath.h"

//INSERT UTILITIES HERE
//REMEMBER TO ADD ANY METHODS HERE TO UTIL.H FOR EXTERNAL USE

void runDrive(int jx, int jy){
	motorSet(frdrive, -jx-jy);  //right drive front
	motorSet(brdrive, -jx-jy);  //right drive back
	motorSet(bldrive, -jx+jy);  //left drive back
	motorSet(fldrive, -jx+jy);  //left drive front
}

void setMobileLift(int power){
	if(power != 0){
		motorSet(goallift, -power);
	}else{
		if(analogReadCalibrated(gliftpotentiometer) > 350){
			motorSet(goallift, -30);  //claw stop
		}else{
			motorSet(goallift,0);
		}
	}
}

void holdArmAt(int pos, float p){

}
