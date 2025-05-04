#include "main.h"
#include "subsystems.hpp"

float clamp(float min, float val, float max)
{
    return (min > ((val < max) ? val : max) ? min : ((val < max) ? val : max));
}

// ----------------------
// |      Intake        |
// ----------------------

int intakeState = 0;

void runIntake()
{
    if (intakeState != 1)
    {
        intake.move(127);
        intakeState = 1;
    }
    else
    {
        intake.move(0);
        intakeState = 0;
    }
}

void reverseIntake()
{
    if (intakeState != -1)
    {
        intake.move(-127);
        intakeState = -1;
    }
    else
    {
        intake.move(0);
        intakeState = 0;
    }
}

// ----------------------
// |        Arm         |
// ----------------------
float armPos[] = {0, 210, 1079};
int numOfArmPos = sizeof(armPos) / sizeof(armPos[0]);
int armState = 0;
float armTarget = 0;
float armPrevErr = 0;
bool autoArm = true;

void armMode()
{
    autoArm = !autoArm;
    if (autoArm)
    {
        armState = 0;
        armTarget = armPos[armState];
    }
}

void armControlTask()
{
    arm1.set_zero_position(0);
    armTarget = 0;
    while (1)
    {
        float kP = 0.3;
        float kD = 0;
        float armMotPos = arm1.get_position();
        float err = armTarget - armMotPos;
        float output = kP * err + kD * (err - armPrevErr);
        armPrevErr = err;
        output = clamp(-127, output, 127);

        if (autoArm)
        {
            arm1.move(output);
            arm2.move(output);
        }

        pros::delay(10);
    }
}

void armUp()
{
    if (autoArm)
    {
        if (armState < numOfArmPos - 1)
        {
            armState++;
            armTarget = armPos[armState];
        }
    }
    else
    {
        arm1.move(127);
        arm2.move(127);
    }
}

void armDown()
{
    if (autoArm)
    {
        if (armState > 0)
        {
            armState--;
            armTarget = armPos[armState];
        }
    }
    else
    {
        arm1.move(-127);
        arm2.move(-127);
    }
}

void armReleased()
{
    if (!autoArm)
    {
        arm1.set_brake_mode(MOTOR_BRAKE_HOLD);
        arm1.brake();
        arm2.set_brake_mode(MOTOR_BRAKE_HOLD);
        arm2.brake();
    }
}

// ----------------------
// |       Clamp        |
// ----------------------

bool clampState = false;
void clamp()
{
    clampState = !clampState;
    clampPis.set_value(clampState);
}

// ----------------------
// |      Doinker       |
// ----------------------

bool lDoinkerState = false;
bool rDoinkerState = false;
void lDoinker()
{
    lDoinkerState = !lDoinkerState;
    lDoinkerPis.set_value(lDoinkerState);
}
void rDoinker()
{
    rDoinkerState = !rDoinkerState;
    rDoinkerPis.set_value(rDoinkerState);
}