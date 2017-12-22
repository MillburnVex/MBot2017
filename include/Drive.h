#ifndef DRIVE_H
#define DRIVE_H
namespace Drive {
enum {
	ROTATE_LEFT, ROTATE_RIGHT, FORWARDS, BACKWARDS
};
void LeftSide(int speed);
void RightSide(int speed);
void Move(int dir, unsigned int speed);
void Stop();
void Update();
}
#endif
