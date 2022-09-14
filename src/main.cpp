#include <iostream>
#include "Timer.h"
#include "Peripherals.h"

#include "Step.h"
#include "GPIO.h"
using WMS::Step;


int main()
{
    STM32F407::enable(STM32F407::GPIO_D);
    const uint32_t GPIO_D_ADDRESS = 0x40020C00;
    
    static volatile uint32_t* const GPIO_D_MODER { reinterpret_cast<uint32_t*>(GPIO_D_ADDRESS + 0x00) };
    static volatile uint32_t* const GPIO_D_IDR { reinterpret_cast<uint32_t*>(GPIO_D_ADDRESS + 0x10) };
    static volatile uint32_t* const GPIO_D_ODR { reinterpret_cast<uint32_t*>(GPIO_D_ADDRESS + 0x14) };
    enum class LED { A=8, B, C, D };
    enum class Motor { on=12, dir };

    auto value = *GPIO_D_MODER;
    value &= ~(0x11 << int(LED::A)*2);
    value |= 0x01 << int(LED::A)*2;
    value &= ~(0xF << int(Motor::on)*2);
    value |= 0x5 << int(Motor::on)*2;
    *GPIO_D_MODER = value;
    //*GPIO_D_IDR = *GPIO_D_IDR | 0x01;
    //*GPIO_D_ODR = *GPIO_D_ODR | 0x01;

    Step fill{ Step::fill, 500 };
    Step wash{ Step::wash, 1000 };
    Step empty{ Step::empty, 2000 };

    fill.run();
    wash.run();
    empty.run();

    while(true) {

        auto outr = *GPIO_D_ODR;
        outr |= (0x1 << int(LED::A));
        outr |= (0x1 << int(Motor::on));
        outr ^= (0x1 << int(Motor::on)+1);
        *GPIO_D_ODR = outr;
        std::cout << "ON" << std::endl;
        sleep(500);
        outr &= ~(0x1 << int(LED::A));
        outr &= ~(0x1 << int(Motor::on)+1);
        *GPIO_D_ODR = outr;
        std::cout << "OFF" << std::endl;
        sleep(500);
    }
}