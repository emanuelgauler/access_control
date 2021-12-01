#include <LiquidCrystal.h>
int rs { 9 }, en { 8 },
	d4 { 7 }, d5 { 6 },
	d6 { 5 }, d7 { 4 };
	
LiquidCrystal lcd( rs, en, d4, d5, d6, d7 );
volatile bool is_incoming { false }
, is_outcoming { false };
int counter { 0 }
, MAX_CAPACITY { 3 };
String message ("Hay ");
void incoming();
void outcoming();
void setup() {
	lcd.begin( 16, 2 );
	pinMode( 11, OUTPUT );
	pinMode( 10, OUTPUT );
	pinMode( 2, INPUT );
	pinMode( 3, INPUT );
	attachInterrupt( digitalPinToInterrupt( 2 ), 
		incoming, RISING );
	attachInterrupt( digitalPinToInterrupt( 3 ), 
		outcoming, RISING );
}

void loop() {
	if( counter < MAX_CAPACITY ) {
		lcd.setCursor( 0, 0 );
		lcd.print( "Ingrese   " );
		digitalWrite( 10, HIGH );
		digitalWrite( 11, LOW );
	} else {
		lcd.setCursor( 0, 0 );
		lcd.print( "No Ingrese" );
		digitalWrite( 10, LOW );
		digitalWrite( 11, HIGH );
	}
	
	lcd.setCursor( 0, 1 );
	lcd.print( message + counter + " de " + MAX_CAPACITY );
	if( is_incoming ) {
		is_incoming = false;
		if( counter < MAX_CAPACITY ) counter++;
	}
	
	if( is_outcoming ) {
		is_outcoming = false;
		if( counter > 0 ) counter--;
	}
	
}

void incoming() {
	is_incoming = true;
}

void outcoming() {
	is_outcoming = true;
}