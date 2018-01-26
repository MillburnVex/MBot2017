#ifndef LIFT_H
#define LIFT_H
namespace Lift {
void LeftSide(int speed);
void RightSide(int speed);
void Up();
void Down();
void Hold();
void HoldAt(int pos);
void UpdateControls();
void Update();
bool SideOutOfBounds(int value);
int GetCurrentHeight();

bool IsResting();
}
#endif
