#ifndef MOTOR_H
#define MOTOR_H
enum MotorID {
	DRIVE_LEFT = 2, DRIVE_RIGHT = 3,
	MOBILE_GOAL_LIFT = 4,
	CLAW = 5,
	LIFT_LEFT_1 = 6, LIFT_LEFT_2 = 7, LIFT_RIGHT_1 = 8, LIFT_RIGHT_2 = 9,
	ARM = 10
};
namespace Motors {
void SetSpeed(MotorID id, int speed);
void Stop(MotorID id);
void ToggleAll();
}
#endif
