#include "mode.h"
#include "copter.h"

bool ModeRawMotor::init(bool ignore_checks)
{
    // Allow switching mode only if GPS is available
    if (!ignore_checks && !AP::ahrs().home_is_set()) {
        // Home not set or GPS not ready
        return false;
    }
    return true;
}

void ModeRawMotor::run()
{
    // 1. safety: only drive motors if armed
    if (!copter.armed()) {
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
        return;
    }
    motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::THROTTLE_UNLIMITED);

    // 2. optionally send state telemetry to companion via MAVLink...

    // 3. apply raw PWM from companion
    for (uint8_t i = 0; i < copter.number_of_motors(); i++) {
        copter.output_motor_pwm(i, motor_pwms[i]);
    }
}
