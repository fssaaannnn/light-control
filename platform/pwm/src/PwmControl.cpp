
#include "PwmControl.h"

#include "NullPwmControl.h"
#include "PigpioPwmControl.h"

namespace LC {

PwmControl::PwmControl() {}
PwmControl::~PwmControl() {}

PwmFactory::PwmFactory() {}

std::unique_ptr<PwmControl> PwmFactory::createPwmControl() {
#ifdef LC_PIGPIO_AVAILABLE_ENV
    return std::make_unique<PigpioPwmControl>();
#else
    return std::make_unique<NullPwmControl>();
#endif
}

}  // namespace LC
