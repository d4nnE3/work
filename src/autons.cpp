#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

bool sorting = true;

void w()
{
    chassis.pid_wait();
}

void holdRing()
{
    pros::Task([=] {
        intake.move(127);
        bool a = true;
        while (a)
        {
            if (colorSens.get_hue() < 20 || colorSens.get_hue() > 330)
            {
                // red ring
                a = false;
            }
            else if (colorSens.get_hue() > 200 && colorSens.get_hue() < 230)
            {
                // blue ring
                a = false;
            }
            else
            {
                pros::delay(10);
            }
        }
        intake.move(0);
    });
}

// 1 = red side, 2 = blue side
void colorSort(int side)
{
    pros::Task([=] {
        while (1)
        {
            if (!sorting)
            {
                break;
            }
            if (colorSens.get_hue() < 20 || colorSens.get_hue() > 330)
            {
                // detected red ring
                if (side == 2)
                {
                    bool a = true;
                    while (a)
                    {
                        if (distanceSensor.get() < 25)
                        {
                            a = false;
                            pros::delay(50);
                            intake.brake();
                            pros::delay(200);
                            intake.move(127);
                        }
                        pros::delay(5);
                    }
                };
            }
            else if (colorSens.get_hue() > 200 && colorSens.get_hue() < 230)
            {
                // detected blue ring
                if (side == 1)
                {
                    bool a = true;
                    while (a)
                    {
                        if (distanceSensor.get() < 25)
                        {
                            a = false;
                            pros::delay(50);
                            intake.brake();
                            pros::delay(200);
                            intake.move(127);
                        }
                        pros::delay(5);
                    }
                };
            }
            pros::delay(20);
        }
    });
}

///
// Constants
///
void default_constants()
{
    // P, I, D, and Start I
    chassis.pid_drive_constants_forward_set(8.5, 0.0, 15.0);
    chassis.pid_drive_constants_backward_set(10.0, 0.0, 17.0);
    // chassis.pid_drive_constants_set(8.5, 0.0, 15.0);         // Fwd/rev constants, used for odom and non odom motions
    chassis.pid_heading_constants_set(6.0, 0.0, 13.0);     // Holds the robot straight while going forward without odom
    chassis.pid_turn_constants_set(5.5, 0.05, 35.0, 15.0); // Turn in place constants
    chassis.pid_swing_constants_set(4.5, 0.0, 45.0);       // Swing constants
    chassis.pid_odom_angular_constants_set(1.2, 0.0, 5.5); // Angular control for odom motions
    chassis.pid_odom_boomerang_constants_set(1.0, 0.0, 20.0); // Angular control for boomerang motions

    // Exit conditions
    chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
    chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
    chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
    chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
    chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
    chassis.pid_turn_chain_constant_set(3_deg);
    chassis.pid_swing_chain_constant_set(5_deg);
    chassis.pid_drive_chain_constant_set(3_in);

    // Slew constants
    chassis.slew_turn_constants_set(3_deg, 70);
    chassis.slew_drive_constants_set(3_in, 70);
    chassis.slew_swing_constants_set(3_in, 80);

    // The amount that turns are prioritized over driving in odom motions
    // - if you have tracking wheels, you can run this higher.  1.0 is the max
    chassis.odom_turn_bias_set(0.5);

    chassis.odom_look_ahead_set(7_in); // This is how far ahead in the path the robot looks at
    chassis.odom_boomerang_distance_set(
        16_in); // This sets the maximum distance away from target that the carrot point can be
    chassis.odom_boomerang_dlead_set(0.625); // This handles how aggressive the end of boomerang motions are

    chassis.pid_angle_behavior_set(
        ez::shortest); // Changes the default behavior for turning, this defaults it to the shortest path there
}

void baker_blue()
{
    default_constants();
    chassis.odom_xyt_set(0_in, 0_in, 180_deg);

    pros::Task([=] {
        pros::delay(15000);
        master.rumble("---");
    });
    chassis.pid_odom_set(-25_in, 110);
    chassis.pid_wait_until(-24_in);
    clampPis.set_value(true);
    w();
    pros::Task([=] {
        pros::delay(400);
        intake.move_relative(600, 127);
    });
    chassis.pid_turn_set(44_deg, 90);
    w();
    intakePis.set_value(true);
    chassis.pid_odom_set({{14.3_in, 37.8_in}, fwd, 110});
    w();
    lDoinkerPis.set_value(true);
    pros::delay(150);
    chassis.pid_turn_set(18_deg, 90);
    w();
    chassis.pid_odom_set({{18.2_in, 41.7_in}, fwd, 110});
    w();
    rDoinkerPis.set_value(true);
    pros::delay(150);

    chassis.pid_swing_set(ez::RIGHT_SWING, 55_deg, 110);
    chassis.pid_wait_quick_chain();
    chassis.pid_odom_set({{-30_in, 5_in}, rev, 110});
    w();
    lDoinkerPis.set_value(false);
    rDoinkerPis.set_value(false);
    intakePis.set_value(false);
    pros::delay(400);
    intake.move(127);
    chassis.pid_turn_set(70_deg, 90);
    w();
    chassis.pid_odom_set(24_in, 110);
    chassis.pid_wait_quick_chain();
    chassis.pid_swing_set(ez::LEFT_SWING, -25_deg, 110);
    chassis.pid_wait_quick_chain();
    w();
    chassis.pid_odom_set({{-14.9_in, 27.7_in}, fwd, 110});
    w();

    chassis.pid_turn_set(-154.3_deg, 110);
    w();
    rDoinkerPis.set_value(true);
    chassis.pid_odom_set({{-26.2_in, -1.7_in}, fwd, 110});
    chassis.pid_wait_quick_chain();
    clampPis.set_value(false);
    chassis.pid_turn_set(90_deg, 90);
    w();
    rDoinkerPis.set_value(false);
    chassis.pid_odom_set(45_in, 110);
    w();
    chassis.pid_turn_set(-90_deg, 90);
    w();
}
void baker_red()
{
}

void ring_base()
{
    default_constants();
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);

    pros::Task redirectTask([=] {
        while (true)
        {
            float pos = intake.get_position();
            pros::delay(100);
            if (intake.get_position() == pos)
            {
                intake.move(-127);
                pros::delay(200);
                intake.move(127);
            }
            pros::delay(20);
        }
    });
    redirectTask.suspend();

    chassis.pid_turn_set(20, 90);
    w();
    if (chassis.odom_x_direction_get() == false)
    {
        // if red side
        rDoinkerPis.set_value(true);
    }
    else
    {
        // if blue side
        lDoinkerPis.set_value(true);
    }
    holdRing();

    chassis.pid_drive_constants_forward_set(8.5, 0, 0);
    chassis.pid_odom_set(47_in, 127);
    chassis.pid_wait_quick();
    default_constants();
    chassis.pid_odom_set(-4.5_in, 110);
    w();
    chassis.pid_turn_set(60_deg, 90);
    w();
    chassis.pid_odom_set(-18_in, 110);
    chassis.pid_wait_until(-16_in);
    clampPis.set_value(true);
    w();
    intake.move(127);
    redirectTask.resume();
    chassis.pid_turn_set(82_deg, 90);
    chassis.pid_wait_quick();
    if (chassis.odom_x_direction_get() == false)
    {
        // if red side
        rDoinkerPis.set_value(false);
    }
    else
    {
        // if blue side
        lDoinkerPis.set_value(false);
    }
    pros::delay(200);
    chassis.pid_turn_set(93_deg, 90);
    w();
    chassis.pid_odom_set(15_in, 90);
    w();
    chassis.pid_odom_set(10_in, 110);
    w();
    chassis.pid_turn_set(150_deg, 90);
    w();
    chassis.pid_odom_set({{39.6_in, 0_in}, fwd, 110});
    w();
    chassis.pid_odom_set(-6_in, 110);
    chassis.pid_wait_quick_chain();
    chassis.pid_odom_set(4_in, 110);
    w();
    chassis.pid_odom_set(-5_in, 110);
    w();
    chassis.pid_turn_set(-90_deg, 90);
    w();
    chassis.pid_odom_set({{-25_in, 4.3_in}, fwd, 110});
    chassis.pid_wait_quick();
    armTarget = 210;
    w();
    chassis.pid_odom_set({{-14.8_in, 4.3_in}, rev, 110});
    w();
    chassis.pid_turn_set(180_deg, 90);
    w();
    redirectTask.suspend();
    intake.move_relative(-50, 127);
    chassis.pid_odom_set(6_in, 110);
    w();
    armTarget = 1400;

    sorting = false;
}

void ring_blue()
{
    colorSort(2);
    ring_base();
}
void ring_red()
{
    colorSort(1);
    chassis.odom_x_flip();
    chassis.odom_theta_flip();
    ring_base();
}

void solo_base()
{
    default_constants();
    chassis.odom_xyt_set(0_in, 0_in, 180_deg);

    chassis.pid_turn_set(210, 90);
    w();
    chassis.pid_odom_set(3_in, 110);
    w();
    armTarget = 1400;
    pros::delay(500);
    chassis.pid_odom_set(-6_in, 110);
    w();
    chassis.pid_turn_set(203.3, 90);
    w();
    chassis.pid_odom_set(-32_in, 110);
    chassis.pid_wait_until(-26_in);
    armTarget = 0;
    clampPis.set_value(true);
    w();
    chassis.pid_turn_set(105, 90);
    w();
    intake.move(127);
    chassis.pid_odom_set({{30.3_in, 27.9_in}, fwd, 110});
    w();
    chassis.pid_turn_set(215, 90);
    w();
    chassis.pid_odom_set({{8.8_in, 2_in}, fwd, 110});
    w();
    chassis.pid_turn_set(-90, 90);
    w();
}

void solo_red()
{
    chassis.odom_x_flip();
    chassis.odom_theta_flip();
    solo_base();
}

void solo_blue()
{
    solo_base();
}