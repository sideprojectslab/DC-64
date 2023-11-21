//----------------------------------------------------------------------------//
//         .XXXXXXXXXXXXXXXX.  .XXXXXXXXXXXXXXXX.  .XX.                       //
//         XXXXXXXXXXXXXXXXX'  XXXXXXXXXXXXXXXXXX  XXXX                       //
//         XXXX                XXXX          XXXX  XXXX                       //
//         XXXXXXXXXXXXXXXXX.  XXXXXXXXXXXXXXXXXX  XXXX                       //
//         'XXXXXXXXXXXXXXXXX  XXXXXXXXXXXXXXXXX'  XXXX                       //
//                       XXXX  XXXX                XXXX                       //
//         .XXXXXXXXXXXXXXXXX  XXXX                XXXXXXXXXXXXXXXXX.         //
//         'XXXXXXXXXXXXXXXX'  'XX'                'XXXXXXXXXXXXXXXX'         //
//----------------------------------------------------------------------------//
//             Copyright 2023 Vittorio Pascucci (SideProjectsLab)             //
//                   Software licensed under CC BY-NC-SA 4.0.                 //
//                    To view a copy of this license, visit                   //
//               http://creativecommons.org/licenses/by-nc-sa/4.0/            //
//----------------------------------------------------------------------------//

#include <xc.h>

#define CORE_CLK_FREQ     8000000
#define SYS_CLK_PRESCALER 8
#define SYS_CLOCK_FREQ    (CORE_CLK_FREQ / SYS_CLK_PRESCALER)
#define PWM_PRESCALER     1
#define OCR_60Hz          (uint16_t)(SYS_CLOCK_FREQ / PWM_PRESCALER / 60 / 1.03f / 2)
#define OCR_50Hz          (uint16_t)(SYS_CLOCK_FREQ / PWM_PRESCALER / 50 / 1.03f / 2)

void set_pwm_freq()
{
	if(PINB & 1)
	{
		ICR0H = OCR_60Hz >> 8;
		ICR0L = OCR_60Hz & 0xff;
	}
	else
	{
		ICR0H = OCR_50Hz >> 8;
		ICR0L = OCR_50Hz & 0xff;
	}
}

int main(void)
{
	// setting core clock prescaker to 8 (default)
	CLKPSR = 0b00000011;
	// setting up IO
	DDRB  = 1 << PINB1; // TOD output
	PORTB = 0;

	for(uint32_t i = 0; i < 100000; ++i){}

	// PWM frequency is set at startup and never changes until power cycle
	set_pwm_freq();

	// setting up PWM:
	// - toggle OC0B on compare match
	// - Clear Timer on compare match
	// - Clock prescaler = 1
	//
	TCCR0A = 0b00010000;
	TCCR0B = 0b00011001;

    while(1){}

}
