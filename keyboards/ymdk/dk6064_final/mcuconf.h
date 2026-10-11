#pragma once

#include_next <mcuconf.h>

// With a 16 MHz HSE the default PLLM (4) puts the PLL input out of range.
// PLLM = 8 -> 2 MHz PLL input; the board's default N/P/Q (168/4/7)
// then give 84 MHz SYSCLK and 48 MHz for USB.
#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8
