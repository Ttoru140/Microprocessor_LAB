#define RCC_BASE 0x40021000
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define RCC_APB1ENR (*(volatile unsigned int *)(RCC_BASE + 0x1C))

#define GPIOC_BASE 0x40011000
#define GPIOC_CRH  (*(volatile unsigned int *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR  (*(volatile unsigned int *)(GPIOC_BASE + 0x0C))

#define TIMER2_BASE 0x40000000
#define TIM2_CR1 (*(volatile unsigned int *)(TIMER2_BASE +  0x00))
#define TIM2_SR (*(volatile unsigned int *)(TIMER2_BASE +  0x10))
#define TIM2_PSC (*(volatile unsigned int *)(TIMER2_BASE +  0x28))
#define TIM2_ARR (*(volatile unsigned int *)(TIMER2_BASE +  0x2C))


int main(){

	RCC_APB2ENR |=(1u << 4);
	RCC_APB1ENR |=(1u << 0);


	GPIOC_CRH &=~(0xF << 20);
	GPIOC_CRH |=(1u << 21);

	TIM2_PSC = 7999;
	TIM2_ARR = 999;
	TIM2_CR1 |= (1u << 0);



	while(1){
//		GPIOC_ODR ^=(1u << 13);
//		for(volatile int i =0; i<100000;i++);

		if(TIM2_SR &(1u << 0)){
			TIM2_SR &=~(1u<<0);
			GPIOC_ODR ^=(1u << 13);
		}

	}
}
