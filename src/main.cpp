#include <iostream>
#include "Timer.h"
#include "Peripherals.h"

int main()
{
    STM32F407::enable(STM32F407::GPIO_D);
    const uint32_t GPIO_D_ADDRESS = 0x40020C00;
    
    static volatile uint32_t* const GPIO_D_MODER { reinterpret_cast<uint32_t*>(GPIO_D_ADDRESS + 0x00) };
    static volatile uint32_t* const GPIO_D_IDR { reinterpret_cast<uint32_t*>(GPIO_D_ADDRESS + 0x10) };
    static volatile uint32_t* const GPIO_D_ODR { reinterpret_cast<uint32_t*>(GPIO_D_ADDRESS + 0x14) };
    auto value = *GPIO_D_MODER;
    value &= ~(0x11 << 16);
    value |= (0x01 << 16);
    *GPIO_D_MODER = value;
    //*GPIO_D_IDR = *GPIO_D_IDR | 0x01;
    //*GPIO_D_ODR = *GPIO_D_ODR | 0x01;

    while(true) {

        *GPIO_D_ODR &= ~0x00'00'11'11;
        sleep(1000);
        *GPIO_D_ODR |= 0x00'00'00'01;
    }
}