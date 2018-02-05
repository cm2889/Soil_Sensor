
/*
 * LCD CONFIGURATION
 * 
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
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sensorPin = A0;
int redLed = 9;
int greenLed = 8; 
int yellowLed = 7;

#define RED 0
#define GREEN 1
#define YELLOW 2

float Reading = 0;
float lastReading = 0;

void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(sensorPin,INPUT);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(yellowLed , OUTPUT);
}



void loop() {
  for (int i=0;i<100;i++){
    analogRead(sensorPin);
  }

  Reading = analogRead(sensorPin);
  lastReading = map(Reading, 0, 1023, 100, 0);
  

  lcd.setCursor(1,0);
  lcd.print("SOIL MOISTURE:");
  lcd.setCursor(0,1);
  lcd.print(lastReading);
  lcd.setCursor(5,1);
  lcd.print("%");
  Serial.print("last Reading of Sensor: ");
  Serial.println(lastReading);
  
  if (lastReading < 25){ 
    lcd.setCursor(7,1);
    lcd.print("(  DRY  )");
    setLED(0); 
    }
  else if (lastReading >= 25 && lastReading <75 ){
    lcd.setCursor(7,1);
    lcd.print("(PERFECT)");
    setLED(1);
    }
  else {
    lcd.setCursor(7,1);
    lcd.print("(  WET  )");
    setLED(2); 
    }
  delay(1000);
}

void setLED(int ledValue) {
  if (ledValue == RED){

  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  }

    else if (ledValue == GREEN){
  
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, LOW);

  }

  else if (ledValue == YELLOW){ 
 
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);

  } 


}
