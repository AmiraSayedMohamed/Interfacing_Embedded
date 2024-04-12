#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdlib.h>

#define enable            5
#define registerselection 6

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);

int main(void) {
	
    DDRB = 0xFF;   // Define port B as output
    DDRA = 0;
	DDRD = 0xFF;   // Define Port D as output
	_delay_ms(50);
	ADMUX |=(1<<REFS0)|(1<<REFS1);
	ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

    int16_t COUNTA = 0;
	char SHOWA [3];

    send_a_command(0x0C); //Clear Screen 0x01 = 00000001
	_delay_ms(50);
	send_a_command("Temp(C)= ");
	send_a_command(0x80 + 0x40 + 8); // Set cursor to second line, 8th position

    while(1) {
		ADCSRA |=(1<<ADSC);  // Start ADC conversion
		while(ADCSRA & (1<<ADSC)); // Wait for conversion complete
		
        COUNTA = ADC/4;     // Convert ADC value (adjust scaling factor if needed)
		itoa(COUNTA,SHOWA,10);
		send_a_string(SHOWA);
		send_a_string ("      "); // Clear remaining digits
    }    

}

void send_a_command(unsigned char command) {

    PORTB = command;
	PORTD &= ~ (1<<registerselection);
	PORTD |= 1<<enable;
	_delay_ms(20);
	PORTD &= ~1<<enable;
	PORTB = 0;
}

void send_a_character(unsigned char character) {

    PORTB = character;
	PORTD |= 1<<registerselection;
	PORTD |= 1<<enable;
	_delay_ms(20);
	PORTD &= ~1<<enable;
	PORTB = 0;
}

void send_a_string(char *string_of_characters) {

    while(*string_of_characters > 0) {

        send_a_character(*string_of_characters++);

    }

}


