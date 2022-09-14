#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>
#include "Peripherals.h"

namespace Devices {
    class GPIO {
    public:
        explicit GPIO(STM32F407::AHB1_Device device);
        void set_input(unsigned pin);
        void set_output(unsigned pin);
        uint32_t mode() const;
        uint32_t read() const;
        void set(uint32_t pattern);
        void clear(uint32_t pattern);
    private:
        volatile struct Registers* port;
    };


} // namespace Devices

#endif // GPIO_H_