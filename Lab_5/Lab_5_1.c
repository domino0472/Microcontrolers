#ifndef F_CPU
#define F_CPU 16000000UL // ustawienie szybkości zegara 16 MHz
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> // Dodana biblioteka dla funkcji dtostrf()

#include "LCD/lcd44780.h"      // biblioteka LCD 

uint16_t pomiar(uint8_t kanal);

int main(void)
{
    uint16_t wynik_ADC;
    float napiecie;
    char bufor[10]; // Tablica znaków do przechowania przetworzonego napięcia
    
    lcd_init(); // inicjalizacja wyświetlacza LCD
    
    ADMUX |= (1<<REFS0); // wybór Vcc (5V) jako napięcia odniesienia
    ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); // włączenie ADC, preskaler na 64
    
    // Nieskończona pętla
    while(1)
    {
        lcd_cls(); // Skasowanie zawartości LCD
        
        wynik_ADC = pomiar(1); // Odczyt na kanale 1 (PA1)
        
        // Przeliczenie surowego wyniku na wolty
        napiecie = (wynik_ADC * 5.0) / 1024.0;
        
        // Konwersja liczby zmiennoprzecinkowej na stringa:
        // (zmienna_float, minimalna_szerokość_tekstu, ilość_miejsc_po_przecinku, tablica_docelowa)
        dtostrf(napiecie, 4, 2, bufor);
        
        // Wyświetlenie na LCD
        lcd_str("Napiecie: ");
        lcd_locate(1, 0); // Przejście do drugiej linii (jeśli biblioteka na to pozwala, opcjonalne)
        lcd_str(bufor);
        lcd_str(" V");
        
        _delay_ms(1000); // Odczekanie 1s	
    }
}

// Definicja funkcji do odczytu napięcia
uint16_t pomiar(uint8_t kanal) {
    ADMUX = (ADMUX & 0xF8) | kanal; // ustawienie wybranego kanału
    ADCSRA |= (1<<ADSC); // Start pomiaru
    while( ADCSRA & (1<<ADSC) ); // oczekiwanie na zakończenie
    return ADCW; 
}
