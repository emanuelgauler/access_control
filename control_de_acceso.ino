#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd( 0x27, 16, 2 );

bool button_up { false }, button_down { false };
volatile bool is_incoming { false }
, is_outcoming { false };
int counter { 0 }
, MAX_CAPACITY { 0 }, counter_up { 0 }, counter_down { 0 };
String message ("Hay ");
void incoming();
void outcoming();

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor( 0, 0 );
  lcd. scrollDisplayLeft();
  lcd.print( "Bienvenido al sistema de control de accesso High Makers" );

  attachInterrupt( digitalPinToInterrupt( 2 ),
                   incoming, RISING );
  attachInterrupt( digitalPinToInterrupt( 3 ),
                   outcoming, RISING );
}

void loop() {
  if ( counter < MAX_CAPACITY ) {
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
  if ( is_incoming ) {
    is_incoming = false;
    if ( counter < MAX_CAPACITY ) counter++;
  }

  if ( is_outcoming ) {
    is_outcoming = false;
    if ( counter > 0 ) counter--;
  }

  if ( digitalRead( 13 ) == HIGH ) {
    button_up = true; counter_up++;
  } else {
    counter_up = 0;
  }

  if ( digitalRead( 12 ) == HIGH ) {
    button_down = true; counter_down++;
  } else {
    counter_down = 0;
  }

  if ( button_down && counter_down > 0 ) {
    button_down = false;
    MAX_CAPACITY--;
  }
  if ( button_up && counter_up > 0 ) {
    button_up = false;
    MAX_CAPACITY++;
  }
}

void incoming() {
  is_incoming = true;
}

void outcoming() {
  is_outcoming = true;
}
