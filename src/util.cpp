#include "main.h"

//INSERT UTILITIES HERE
//REMEMBER TO ADD ANY METHODS HERE TO UTIL.H FOR EXTERNAL USE

float to100(float from){
  return (from * 100)/127;
}

float to127(float from){
  return (from * 127)/100;
}
