#include "buttons.h"
#include "LPC17xx.h"

void BTNs_Init(void)
{
    // Enabling EINT[0..2] in PINSEL4. In the table, these PINS behave
    // like EINTs when set to 01.
    LPC_PINCON->PINSEL4 |= (0b010101 << 20);

    // EITs mapped to PINs 2.[10..12]. Need to set them to 0, i.e. input.
    LPC_GPIO2->FIODIR &= ~(0b111 << 10);

    // Setting how EINTs are raised using EXTMODE in SC. Setting 1 to the
    // bottom 3 bits to set interrupt edge sensitive. Since we're not modifying
    // EXTPOLAR in SC, ints are raised on FALLING EDGE.
    LPC_SC->EXTMODE = 0x7;
    LPC_SC->EXTPOLAR = 0x0;

    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
    NVIC_EnableIRQ(EINT2_IRQn);

    // Change priorities here.
    NVIC_SetPriority(EINT0_IRQn, 0);
    NVIC_SetPriority(EINT1_IRQn, 0);
    NVIC_SetPriority(EINT2_IRQn, 0);
}