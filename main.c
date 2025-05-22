#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))  //Controls clock for GPIO
#define RCC_APB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x1C))  //Controls clock for Timer2.

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH  (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR  (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

#define TIMER2_BASE 0x40000000
#define TIM2_CR1 (*(volatile unsigned int *)(TIMER2_BASE +  0x00))
#define TIM2_SR (*(volatile unsigned int *)(TIMER2_BASE +  0x10))
#define TIM2_PSC (*(volatile unsigned int *)(TIMER2_BASE +  0x28))
#define TIM2_ARR (*(volatile unsigned int *)(TIMER2_BASE +  0x2C))


int main(){

	RCC_APB2ENR |=(1u << 4);    // Enable clock for GPIOC
	RCC_APB1ENR |=(1u << 0);     // Enable clock for TIM2


	GPIOC_CRH &=~(0xF << 20);   // Clear CNF13[1:0] and MODE13[1:0]
	GPIOC_CRH |=(1u << 21);    // Set MODE13 = 0b01 (Output mode, max speed 10 MHz)

	TIM2_PSC = 7999;        // Prescaler: divide clock by 8000 (assuming 8 MHz -> 1 kHz)      Divides the system clock down to slow the timer.
	TIM2_ARR = 999;          // Auto-reload value: 999 + 1 = 1000 (1 Hz)     Sets the value at which the timer overflows (resets to 0 and sets the update flag UIF).
	TIM2_CR1 |= (1u << 0);    // Enable counter



	while(1){
//		GPIOC_ODR ^=(1u << 13);
//		for(volatile int i =0; i<100000;i++);

		if(TIM2_SR &(1u << 0)){       // If UIF (update interrupt flag) is set
			TIM2_SR &=~(1u<<0);         // Clear the UIF flag
			GPIOC_ODR ^=(1u << 13);            // Toggle PC13
		}

	}
}
