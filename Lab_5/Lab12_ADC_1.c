 

#ifndef F_CPU
#define F_CPU 16000000UL // ustawienie szybkoœci zegara 16 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "LCD/lcd44780.h"      //biblioteka LCD 


uint16_t pomiar(uint8_t kanal);

int main(void)
{
	uint16_t wynik_ADC;
	
	lcd_init(); // inicjalizacja wyœwietlacza LCD
	
	ADMUX |= (1<<REFS0); //wybór Vcc jako napiêcia odniesienia
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); //w³¹czenie modu³u ADC i ustawienie preskalera na 64
	
	//nieskoñczona pêtla w której wykonywany bêdzie pomiar i wyœwietlany na LCD
    while(1)
    {
        lcd_cls(); // skasowanie zawartoœci LCD
		wynik_ADC = pomiar(1);
		lcd_int( wynik_ADC ); // pomiar napiêcia na wejœciu ADC1 i wyœwietlenie zawartoœci na LCD
		_delay_ms(1000); // odczekanie 1s	
    }
	
	
	
}

//definicja funkcji do odczytu napiêcia na wybranym kanale

uint16_t pomiar(uint8_t kanal) {
	ADMUX=(ADMUX & 0xF8) | kanal ; // ustawienie wybranego kana³u w rejestrze ADMUX
	ADCSRA |= (1<<ADSC); //Start pomiaru przez ustawienie bitu ADSC
	while( ADCSRA & (1<<ADSC) ); // oczekiwanie na zakoñczenie pomiaru (dopóki bit ADSC=1)
	// po zakoñczeniu pomiaru, gdy bit ADSC=0, zwrócenie wyniku w postaci 16bitowej wartoœci z rejestrów ADCH i ADCL
	return ADCW; // ADCW to para rejestrów ADCH i ADCL
	
}