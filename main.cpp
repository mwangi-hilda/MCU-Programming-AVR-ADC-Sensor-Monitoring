/*
 * AnalogInputs_3Sensors.cpp
 *
 * Created: 03/06/2025 12:55:35
 * Author : Hilda
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint16_t adc_result[3];
volatile uint8_t channel = 0;

ISR(ADC_vect){
	adc_result[channel] = ADCL | (ADCH<<8);
	channel ++;
	if (channel > 2) channel = 0;
	ADMUX = (1<<REFS0) | (channel & 0x0F);
	_delay_us(10);
	ADCSRA |= (1<<ADSC);

}
/*
uint16_t readAdc(int channel){
	ADMUX = (1<<REFS0) | (channel & 0x0F);
	ADCSRA |= (1<<ADSC);
	return adc_result;
}
*/

int main(void)
{
	ADMUX = (1<<REFS0);
    ADCSRA |= (1<<ADEN) | (1<<ADIE) | (7<<ADPS0);
	sei();
	ADCSRA |= (1<<ADSC);
	
	DDRB = 0xFF;
	
    while (1) 
    {
		uint16_t tempADC = adc_result[0];
		uint16_t humidityADC = adc_result[1];
		uint16_t moistureADC = adc_result[2];
		
		float temp = ((tempADC * 5.0) /1024.0) * 100.0;
		float humidity = (humidityADC / 1024.0) * 100;
		float moisture = 100.0 - ((moistureADC/1024.0) * 100.0);
		
		if (temp > 30)
		{
			PORTB |= (1<<PB0);
		} else{
			PORTB &= ~(1<<PB0);
		}
		
		if (humidity > 60)
		{
			PORTB |= (1<<PB1);
		} 
		else
		{
			PORTB &= ~(1<<PB1);
		}
		
		if (moisture < 40)
		{
			PORTB |= (1<<PB2);
		} 
		else
		{
			PORTB &= ~(1<<PB2);
		}
		
		_delay_ms(500);
    }
}

