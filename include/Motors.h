#ifndef MOTOR_H
#define MOTOR_H
enum MotorID {
	DRIVE_LEFT = 2, DRIVE_RIGHT = 9,
	MOBILE_GOAL_LIFT = 10,
	CLAW = 6,
	LIFT_LEFT_1 = 3, LIFT_LEFT_2 = 4, LIFT_RIGHT_1 = 8, LIFT_RIGHT_2 = 7,
	ARM = 5
};
namespace Motors {
void SetSpeed(MotorID id, int speed);
void Stop(MotorID id);
void ToggleAll();
}
#endif
