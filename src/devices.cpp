#include "main.h"
#include "subsystems.hpp"

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
