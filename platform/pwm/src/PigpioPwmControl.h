
#ifndef LC_PIGPIO_PWM_CONTROL_H_
#define LC_PIGPIO_PWM_CONTROL_H_

#include "PwmControl.h"

namespace LC {

class PigpioPwmControl : public PwmControl {
   public:
    PigpioPwmControl();
    virtual ~PigpioPwmControl();

    void set(const std::vector<PwmParameter>& params) override;
};

}  // namespace LC

#endif  // LC_PIGPIO_PWM_CONTROL_H_
