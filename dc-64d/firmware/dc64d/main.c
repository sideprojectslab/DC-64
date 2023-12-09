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

#define CORE_CLK_FREQ     6000000
#define SYS_CLK_PRESCALER 4
#define SYS_CLOCK_FREQ    (CORE_CLK_FREQ / SYS_CLK_PRESCALER)
#define PWM_PRESCALER     1
#define OCR_60Hz          (uint16_t)(SYS_CLOCK_FREQ / PWM_PRESCALER / 60 / 2)
#define OCR_50Hz          (uint16_t)(SYS_CLOCK_FREQ / PWM_PRESCALER / 50 / 2)

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
	// setting core clock prescaler to 8 (default)
	CCP    = 0xD8;
	CLKPSR = 0b0000010;

	// selecting external clock
	CCP    = 0xD8;
	CLKMSR = 0b00000010;
	
	// setting up IO
	DDRB  = 1 << PINB2; // TOD output
	PORTB = 0;

	// waiting for voltages to settle (cautionary measure)
	for(uint32_t i = 0; i < 1000; ++i){}

	// PWM frequency is set at startup and never changes until power cycle
	set_pwm_freq();

	// setting up PWM:
	// - toggle OC0B on compare match
	// - Clear Timer on compare match
	// - Clock prescaler = 1
	//
	TCCR0A = 0b00000000;
	TCCR0B = 0b00011001;

    while(1){
		
		// this little trick here is to fix the fact that I
		// swapped PB0 and PB22 in hardware, anyway a few clock
		// cycles at 1.5MHz are negligible compared to the
		// generated 50-60Hz wave
		
		if(TIFR0 & 2)
		{
			PORTB = ~PORTB;
			TIFR0 = 2;
		}
	}

}
