#ifndef F_CPU
# define F_CPU 16000000UL // clock speed is 16MHz
#endif

#include<avr/io.h> // AVR header
#include<util/delay.h> // delay header

//******************LCD PROGRAM STARTS*********************//

#define LCD_DATA PORTB // port B is selected as LCD data port
#define ctrl PORTD // port D is selected as LCD command port

#define en PD7 // enable signal is connected to port D pin 7
#define rw PD6 // read/write signal is connected to port D pin 6
#define rs PD5 // register select signal is connected to port D pin 5

void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);

int main(void)
{
	DDRB = 0xFF; // set LCD data port as output
	DDRD = 0xE0; // set LCD signals (RS, RW, E) as out put

	init_LCD(); // initialize LCD
	_delay_ms(100); // delay of 100 Milli seconds

	LCD_cmd(0x0C); // display on, cursor off
	_delay_ms(100);

	LCD_write('T'); // call a function to display space on LCD
	_delay_ms(1);

	LCD_write('e'); // call a function to display space on LCD
	_delay_ms(1);

	LCD_write('m'); // call a function to display space on LCD
	_delay_ms(1);

	LCD_write('p'); // call a function to display space on LCD
	_delay_ms(1);

	LCD_write('e'); // call a function to display space on LCD
	_delay_ms(1);

	LCD_write('r'); // call a function to display "A" on LCD
	_delay_ms(1);

	LCD_write('a'); // call a function to display "V" on LCD
	_delay_ms(1);

	LCD_write('t'); // call a function to display "R" on LCD
	_delay_ms(1);
	
	LCD_write('u');
	_delay_ms(1);
	
	LCD_write('r');
	_delay_ms(1);
	
	LCD_write('e');
	_delay_ms(1);

	LCD_cmd(0xC0); // move cursor to the start of 2nd line
	_delay_ms(1);

	LCD_cmd(0x0C); // display on, cursor off
	_delay_ms(1);

	LCD_write(' '); // call a function to display space on LCD
	_delay_ms(1);

	LCD_write(' ');
	_delay_ms(1);

	LCD_write(' ');
	_delay_ms(1);

	LCD_write('i'); // call a function to display "A" on LCD
	_delay_ms(1);

	LCD_write('s'); // call a function to display "t" on LCD
	_delay_ms(1);

	LCD_write(' '); // call a function to display "m" on LCD
	_delay_ms(1);

	LCD_write('N'); // call a function to display "e" on LCD
	_delay_ms(1);

	LCD_write('o'); // call a function to display "g" on LCD
	_delay_ms(100);

	LCD_write('W'); // call a function to display "a" on LCD
	_delay_ms(1);

	LCD_write(' '); // call a function to display "3" on LCD
	_delay_ms(1);

	LCD_write(':'); // call a function to display "2" on LCD
	_delay_ms(1);

	LCD_cmd(0x0E); // make display ON, cursor ON
	_delay_ms(1);

	return 0;
}

void init_LCD(void)
{
	LCD_cmd(0x38); // initialization in 8bit mode of 16X2 LCD
	_delay_ms(1);

	LCD_cmd(0x01); // make clear LCD
	_delay_ms(1);

	LCD_cmd(0x02); // return home
	_delay_ms(1);

	LCD_cmd(0x06); // make increment in cursor
	_delay_ms(1);

	LCD_cmd(0x80); // "8" go to first line and "0" is for 0th position
	_delay_ms(1);

	return;
}

//**************sending command on LCD***************//

void LCD_cmd(unsigned char cmd)
{
	LCD_DATA = cmd; // data lines are set to send command
	
	PORTD &= ~(1 << rs); // RS sets 0, for command data
	PORTD &= ~(1 << rw); // RW sets 0, to write data
	PORTD |= (1 << en); // make enable from high to low
	
	_delay_ms(100);
	PORTD &= ~(1 << en); // make enable low

	return;
}

//*****************write data on LCD*****************//

void LCD_write(unsigned char data)
{
	LCD_DATA = data; // data lines are set to send command
	PORTD |= (1 << rs); // RS sets 1, for command data
	PORTD &= ~(1 << rw); // RW sets 0, to write data
	PORTD |= (1 << en); // make enable from high to low

	_delay_ms(100);
	PORTD &= ~(1 << en); // make enable low

	return;
}
