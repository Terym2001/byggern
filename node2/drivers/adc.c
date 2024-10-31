#include "adc.h"
#include "sam.h"

void  adc_init(){
    //reset ADC, might drop this
    REG_ADC_CR |= ADC_CR_SWRST; 
    
    //enable clock and set clock frequency with prescaler
    REG_PMC_PCER1 |= PMC_PCER1_PID37; //enable ADC clock, ADC has Peripheral ID (PID) 37
    REG_ADC_MR    |= ADC_MR_PRESCAL(32); //ADCClock = MCK / ( (PRESCAL+1) * 2 )

    //Enable analog input on channel 1
    REG_ADC_CHER |= ADC_CHER_CH1;
    
    //enable hardware triggers, 
    REG_ADC_MR |= ADC_MR_TRGEN_EN;
    //ADC doesnt sleep between conversions, Use 12 bit resolution
    REG_ADC_MR &= ~(ADC_MR_TRGEN | ADC_MR_SLEEP | ADC_MR_LOWRES);  

    REG_ADC_MR |=  ADC_MR_FREERUN_ON; //set freerun mode on: always do ADC conversions continually
     

    //Comparison Event Interrupt Enable for channel 1
    REG_ADC_IER |= ADC_IER_COMPE | ADC_IER_EOC1;

    //Set CMPMODE to low: Generates an event when the converted data is lower than the low threshold of the window.
    REG_ADC_EMR &= ~(ADC_EMR_CMPMODE_Msk);
    REG_ADC_EMR |= ADC_EMR_CMPSEL(1); // Generate event only for channel 1

    //todo: check what format it takes the threshold in as.
    REG_ADC_CWR |= ADC_CWR_LOWTHRES(2); 
}   


//This will now get called since interrupts are enabled for comparisons with sampled value below threshold
ADC_Handler(){
    printf("sampled ADC value has gone below threshold");
}