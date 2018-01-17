#ifndef ARM_H
#define ARM_H
namespace Arm {
void Up();

void Down();

void Update();

bool IsFullyUp();

bool IsFullyDown();

bool IsHeldOut();

void HoldAt(int i);

void Hold();
}
#endif
