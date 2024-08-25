#include "PigpioPwmControl.h"

#ifdef LC_PIGPIO_AVAILABLE_ENV

#include <iostream>

#include "pigpio.h"

namespace LC {

class PigpioInitializer {
   public:
    PigpioInitializer() {
        gpioCfgInterfaces(PI_DISABLE_SOCK_IF | PI_DISABLE_SOCK_IF |
                          PI_DISABLE_ALERT);
        auto e = gpioInitialise();
        if (e < 0) {
            std::cerr << "Failed to initialize pigpio, error: " << e
                      << std::endl;
            exit(1);
        }
    }

    ~PigpioInitializer() { gpioTerminate(); }
};

static const PigpioInitializer PIGPIO_INITIALIZER;

PigpioPwmControl::PigpioPwmControl() {}

PigpioPwmControl::~PigpioPwmControl() {}

void PigpioPwmControl::set(const std::vector<PwmParameter>& params) {
    for (auto& param : params) {
        auto e = gpioHardwarePWM(param.m_gpio, param.m_freq, param.m_duty);
        if (e != 0) {
            std::cerr << "gpioHardwarePWM() error: " << e << std::endl;
        }
    }
}

}  // namespace LC

#endif  // LC_PIGPIO_AVAILABLE_ENV
