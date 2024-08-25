
#ifndef LC_NULL_PWM_CONTROL_H_
#define LC_NULL_PWM_CONTROL_H_

#include "PwmControl.h"

namespace LC {

class NullPwmControl : public PwmControl {
   public:
    NullPwmControl();
    virtual ~NullPwmControl();

    void set(const std::vector<PwmParameter>& params) override;
};

}  // namespace LC

#endif  // LC_NULL_PWM_CONTROL_H_
