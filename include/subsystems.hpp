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

inline pros::adi::DigitalIn clampPis('A');
inline pros::adi::DigitalIn lDoinkerPis('B');
inline pros::adi::DigitalIn rDoinkerPis('C');
inline pros::adi::DigitalIn ptoPis('D');
inline pros::adi::DigitalIn intakePis('E');

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');