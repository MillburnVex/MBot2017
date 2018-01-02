#ifndef MOTOR_H
#define MOTOR_H
enum MotorID {
	DRIVE_LEFT = 2, DRIVE_RIGHT = 3,
	MOBILE_GOAL_LIFT = 4,
	CLAW,
	LIFT_LEFT_1 = 6, LIFT_LEFT_2 = 7, LIFT_RIGHT_1, LIFT_RIGHT_2,
	ARM_LEFT, ARM_RIGHT
};
namespace Motors {
void SetSpeed(MotorID id, int speed);
void Stop(MotorID id);
}
#endif
