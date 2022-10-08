// ���������� RGB �����������. ����������� ���
#include <avr/interrupt.h>
#include <avr/io.h>

volatile unsigned char pwm_r, pwm_g, pwm_b;
#define RED PORTD6
#define GREEN PORTD5
#define BLUE PORTD7

// ���������� �� ������������ �0
ISR(TIMER0_OVF_vect) {
	static unsigned char pwm_counter;
	
	// ���� ������m ������ �������� �������� - �������� �����, ����� ���������
	if(pwm_counter < pwm_r) PORTD |= (1 << RED);
	else PORTD &= ~(1 << RED);
	if(pwm_counter < pwm_g) PORTD |= (1 << GREEN);
	else PORTD &= ~(1 << GREEN);
	if(pwm_counter < pwm_b) PORTD |= (1 << BLUE);
	else PORTD &= ~(1 << BLUE);
	
	pwm_counter++;	// �������������� �������
}

// ��������� �������� � �������������
void delay_us(unsigned char time_us) {
	register unsigned char i;
	for(i = 0; i < time_us; i++) {
		asm (" PUSH  R0 ");       // 2 �����
		asm (" POP   R0 ");       // 2 �����
	}
}
// ��������� �������� � �������������
void delay_ms(unsigned int time_ms) {
	register unsigned int i;
	for(i = 0; i < time_ms; i++) {
 		delay_us(250); delay_us(250); delay_us(250); delay_us(250);
 		delay_us(250); delay_us(250); delay_us(250); delay_us(250);
	}
}

// ������� ����
void red (unsigned char time) {
	for(unsigned char a = 0; a < 255; a++) {
		pwm_r = a; pwm_g = 0; pwm_b = 0;
		delay_ms(time);
	}
	for(unsigned char a = 255; a > 0; a--) {
		pwm_r = a; pwm_g = 0; pwm_b = 0;
		delay_ms(time);
	}
}

// ������� ����
void green (unsigned char time) {
	for(unsigned char a = 0; a < 255; a++) {
		pwm_r = 0; pwm_g = a; pwm_b = 0;
		delay_ms(time);
	}
	for(unsigned char a = 255; a > 0; a--) {
		pwm_r = 0; pwm_g = a; pwm_b = 0;
		delay_ms(time);
	}
}

// ����� ����
void blue (unsigned char time) {
	for(unsigned char a = 0; a < 255; a++) {
		pwm_r = 0; pwm_g = 0; pwm_b = a;
		delay_ms(time);
	}
	for(unsigned char a = 255; a > 0; a--) {
		pwm_r = 0; pwm_g = 0; pwm_b = a;
		delay_ms(time);
	}
}

// ����� ����
void white (unsigned char time) {
	for(unsigned char a = 0; a < 255; a++) {
		pwm_r = a; pwm_g = a; pwm_b = a;
		delay_ms(time);
	}
	for(unsigned char a = 255; a > 0; a--) {
		pwm_r = a; pwm_g = a; pwm_b = a;
		delay_ms(time);
	}
}

// ������� ������
void rgb (unsigned char time) {
	for(unsigned char a = 0; a < 255; a++) {
		pwm_r = a; pwm_g = 255 - a;
		delay_ms(time);
	}
	for(unsigned char a = 0; a < 255; a++) {
		pwm_b = a; pwm_r = 255 - a;
		delay_ms(time);
	}
	for(unsigned char a = 0; a < 255; a++) {
		pwm_g = a; pwm_b = 255 - a;
		delay_ms(time);
	}
}

int main (void) {
	DDRD = 0b11100000;
	PORTD = 0x00;
	TCCR0A |= (0<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(0<<COM0B0)|(0<<WGM01)|(1<<WGM00);
	TCCR0B |= (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
	TIMSK0 |= (1 << TOIE0);		// ��������� ���������� �� ������������ �0
	
	sei(); // ��������� ���������� ���������
	
	while(1) {
		red(1);
 		green(1);
		blue(1);
		white(1);
		for(int i = 0; i < 4; i++) {
			rgb(1);
		}
	}
}
