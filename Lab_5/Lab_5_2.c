#ifndef F_CPU
#define F_CPU 16000000UL // ustawienie szybkości zegara 16 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h> // Niezbędna biblioteka do funkcji pow()

#include "LCD/lcd44780.h"

uint16_t pomiar(uint8_t kanal);

int main(void)
{
    uint16_t wynik_ADC;
    float napiecie_uf;
    float luksy;
    char bufor[15];
    
    lcd_init();
    
    ADMUX |= (1<<REFS0); // Vcc jako napięcie odniesienia
    ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); // ADC ON, preskaler 64
    
    while(1)
    {
        lcd_cls();
        wynik_ADC = pomiar(1); // Pomiar z pinu PA1
        
        // Zabezpieczenie przed błędem dzielenia przez zero przy potęgowaniu ujemnym
        if (wynik_ADC == 0) wynik_ADC = 1; 
        
        // Obliczenie napięcia na fotorezystorze
        napiecie_uf = wynik_ADC * 0.00488;
        
        // Zastosowanie empirycznego wzoru z instrukcji przy użyciu pow()
        luksy = 108000.0 * pow(napiecie_uf, -5.0);
        
        // Konwersja wyniku (float) na tekst (string)
        dtostrf(luksy, 6, 2, bufor);
        
        // Wyświetlenie wyniku na LCD
        lcd_str("Swiatlo:");
        lcd_locate(1, 0); // Przejście do drugiego wiersza
        lcd_str(bufor);
        lcd_str(" lx");
        
        _delay_ms(1000);	
    }
}

uint16_t pomiar(uint8_t kanal) {
    ADMUX = (ADMUX & 0xF8) | kanal;
    ADCSRA |= (1<<ADSC);
    while( ADCSRA & (1<<ADSC) );
    return ADCW;
}
