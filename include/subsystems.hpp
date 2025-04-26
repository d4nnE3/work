#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(17);
inline pros::Motor arm1(18);
inline pros::Motor arm2(19);

inline pros::adi::DigitalOut clampPis('A');
inline pros::adi::DigitalOut lDoinkerPis('B');
inline pros::adi::DigitalOut rDoinkerPis('C');
inline pros::adi::DigitalOut ptoPis('D');
inline pros::adi::DigitalOut intakePis('E');

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');