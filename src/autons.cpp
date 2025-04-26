#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

void w()
{
    chassis.pid_wait();
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

    chassis.pid_odom_set(-25_in, 110);
    w();
    clampPis.set_value(true);
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
    chassis.pid_turn_set(23_deg, 90);
    w();
    chassis.pid_odom_set({{17.2_in, 41.7_in}, fwd, 110});
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
    pros::Task([=] {
        intake.move_relative(-200, 127);
        intake.move(127);
    });
    chassis.pid_turn_set(70_deg, 90);
    w();
    chassis.pid_odom_set(25_in, 110);
    chassis.pid_wait_quick_chain();
    chassis.pid_swing_set(ez::LEFT_SWING, -25_deg, 110);
    chassis.pid_wait_quick_chain();
    chassis.pid_odom_set({{-14.8_in, 24.6_in}, fwd, 110});
    w();
    pros::delay(1000);

    chassis.pid_turn_set(-154.3_deg, 110);
    w();
    chassis.pid_odom_set(40_in, fwd, 110);
    w();

    pros::delay(5000);
    intake.brake();
}
void baker_red()
{
}
void ring_blue()
{
}
void ring_red()
{
}
void solo_awp()
{
}