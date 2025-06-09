#include "mode.h"
#include "copter.h"
#include "AP_Math/AP_Math.h"  // for attitude math if needed

bool ModeRawMotor::init(bool ignore_checks)
{
    // Allow switching mode only if GPS is available
    if (!ignore_checks && !AP::ahrs().home_is_set()) {
        // Home not set or GPS not ready
        return false;
    }
    return true;
}
