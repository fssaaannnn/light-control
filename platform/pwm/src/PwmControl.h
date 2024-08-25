
#ifndef LC_PWM_CONTROL_H_
#define LC_PWM_CONTROL_H_

#include <cstdint>
#include <memory>
#include <vector>

namespace LC {

struct PwmParameter {
    uint32_t m_gpio;
    uint32_t m_freq;
    uint32_t m_duty;
    PwmParameter() : m_gpio(0), m_freq(), m_duty(0) {}
    PwmParameter(uint32_t gpio, uint32_t freq, uint32_t duty)
        : m_gpio(gpio), m_freq(freq), m_duty(duty) {}
};

class PwmControl {
   public:
    PwmControl();
    virtual ~PwmControl() = 0;

    virtual void set(const std::vector<PwmParameter>& params) = 0;
};

class PwmFactory {
   public:
    PwmFactory();

    std::unique_ptr<PwmControl> createPwmControl();
};

}  // namespace LC

#endif  // LC_PWM_CONTROL_H_
