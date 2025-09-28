/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>
#include <PF.h>
#include <KF.h>





// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

const int trigPin = 9;
const int echoPin = 10;

int itr=0;
float pk=0.0,res=0.0;
float duration, distance_k,distance_p;



const int rs = 8, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
KF kf(0.0,0.0,1.0,0.5,0.1,1.0);
PF pf(10,0.1,0.4);
float kalman_f(float val){
    
    Serial.println( pf.predict(val));
    return kf.KF_predict(val);
    

    
    
    
   

}



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  pinMode(echoPin, INPUT);

  pinMode(trigPin, OUTPUT);
 
  // Print a message to the LCD.
  Serial.begin(9600);
  lcd.print("Distance in cm");
  
  

}

void loop() {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(2);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin, HIGH);
    duration=pulseIn(echoPin,HIGH);
    lcd.setCursor(0, 1);
    float dis=(duration*0.0343)/2;
    Serial.println(dis);
    //res=kalman_f(dis);
      
   // Serial.println(res);
      

    
    //distance_p=pf(dis,100);
  // print the number of seconds since reset:
   // lcd.print(distance_k);
   // Serial.println(distance_k);
   // Serial.println(distance_p);
  
 
    delay(100);

  }
 
