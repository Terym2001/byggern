#include "adc.h"
#include "sam.h"

void  adc_init(){
    //reset ADC, might drop this
    REG_ADC_CR |= ADC_CR_SWRST; 

    REG_PMC_PCER1 |= PMC_PCER1_PID37; //enable ADC clock, ADC has Peripheral ID (PID) 37
    REG_PIOB_PDR |= PIO_PA24X1_AD6;  // Disable PIO control
    REG_PIOB_ABSR |= PIO_PA24X1_AD6; // Select A6 peripheral D
    
    REG_ADC_WPMR = ADC_WPMR_WPKEY(0x414443); //disable write protection
    REG_ADC_WPMR &= ~(ADC_WPMR_WPEN); //enable write protection
    
    
    //enable clock and set clock frequency with prescaler
    REG_ADC_MR    |= ADC_MR_PRESCAL(32); //ADCClock = MCK / ( (PRESCAL+1) * 2 )

    //Enable analog input on channel 6
    REG_ADC_CHER |= ADC_CHER_CH6;

    //Enable the ADC interrupt
    NVIC_EnableIRQ(ADC_IRQn);

    //enable hardware triggers, 
    REG_ADC_MR |= ADC_MR_TRGEN_EN; 
    //ADC doesnt sleep between conversions, Use 12 bit resolution
    REG_ADC_MR &= ~(ADC_MR_TRGEN | ADC_MR_SLEEP | ADC_MR_LOWRES); 

    REG_ADC_MR |=  ADC_MR_FREERUN_ON; //set freerun mode on: always do ADC conversions continually 
     

    //Comparison Event Interrupt Enable for channel 6
    REG_ADC_IER |= ADC_IER_COMPE;

    //Set CMPMODE to out: Generates an event when the converted data is out of threshold window.
    REG_ADC_EMR |= (ADC_EMR_CMPMODE_Msk);
    REG_ADC_EMR |= ADC_EMR_CMPSEL(6); // Generate event only for channel 6

    //todo: check what format it takes the threshold in as.
    REG_ADC_CWR |= ADC_CWR_LOWTHRES(ADC_LOWTHRESHOLD); 
    REG_ADC_CWR |= ADC_CWR_HIGHTHRES(ADC_HIGHTHRESHOLD); 

}   


//This will now get called since interrupts are enabled for comparisons with sampled value below threshold
void ADC_Handler(void){
    if(!(REG_ADC_ISR & ADC_ISR_COMPE)){
        return;
    }
    uint16_t sampledValue = REG_ADC_LCDR;
    // printf("Sampled value: %d\n\r", sampledValue);
    // printf("sampled ADC value has gone below threshold \n\r");
    // uint32_t flag2 = NVIC_GetPendingIRQ(ADC_IRQn);
    // printf("ADC interrupt flag BEFORE: %d\n\r", flag2);
    // //Read interrupt flag
    // uint32_t flag = NVIC_GetPendingIRQ(ADC_IRQn);
    // printf("ADC interrupt flag AFTER: %d\n\r", flag);
    static int shouldCountMiss  = 1;
    if(sampledValue < ADC_LOWTHRESHOLD && shouldCountMiss){
        printf("Sampled value: %d\n\r", sampledValue);
        printf("Ball missed \r\n");
        shouldCountMiss = 0;
    }
    else if(sampledValue > ADC_HIGHTHRESHOLD){
        shouldCountMiss = 1;
    }
    NVIC_ClearPendingIRQ(ADC_IRQn);
}