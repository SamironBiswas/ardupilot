#include "mode.h"
#include "copter.h"

bool ModePPOC::init(bool ignore_checks)
{
    // Allow switching mode only if GPS is available
    if (!ignore_checks && !AP::ahrs().home_is_set()) {
        // Home not set or GPS not ready
        return false;
    }
    return true;
}

void ModePPOC::run()
{
    // 1. safety: only drive motors if armed
    if (!copter.armed()) {
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
        return;
    }
    motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::THROTTLE_UNLIMITED);
}
