#include <stdint.h>

#ifndef I2C_REGBASE_H_
#define I2C_REGBASE_H_

struct t_i2c_regs
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
};

#endif /* I2C_REGBASE_H_ */
