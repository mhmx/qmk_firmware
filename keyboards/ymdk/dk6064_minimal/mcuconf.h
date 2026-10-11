#pragma once

#include_next <mcuconf.h>

// 16 MHz crystal (board default: 8 MHz). PLLM=8 -> 2 MHz PLL input,
// board defaults N/P/Q (168/4/7) -> 84 MHz SYSCLK, 48 MHz USB.
#undef  STM32_HSECLK
#define STM32_HSECLK 16000000
#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 8
