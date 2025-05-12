// Dawson College - EET
// Course: Introduction to IoT
// Description: PBL - Parking Availability System
// Author: Rosalie Drouin & Rochelle George-Webonga
// Date: 2025/05/12


// includs the librabriees needd for using an LCD screen
#include <LiquidCrystal.h>
#include <NewPing.h>

// Pins for the RED and GREEN LEDS plus the ultrasonic sensor's trigger and echo
const int REDpin = 4;
const int GREENpin = 5;
const int TRIGpin = 2;
const int ECHOpin = 3;

// LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



// Parameters
const int totalSpots = 1;     // total spots available (1 because 1 ultrasonic sensor)
int availableSpots = 1;     // keps track of how many are available
const int distanceThreshold = 5;  // distance in cm to decide if thee spot is considred occupied or not


// set the pin modes
void setup() {
  pinMode(TRIGpin, OUTPUT);
  pinMode(ECHOpin, INPUT);
  pinMode(REDpin, OUTPUT);
  pinMode(GREENpin, OUTPUT);



  Serial.begin(9600);     // for debugging output



// bascically initializes the LCD, turns on th backlight, display "what it is" before cleearing the screen
  lcd.begin(16, 2);          
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  delay(2000);
  lcd.clear();
}


void loop() {
  delay(2000);

  int distance = getDistance();  // finds the current distance measuremnt using the ultrasonic sensor
 

    // Check if car is present
  if (getDistance() < distanceThreshold) {
    availableSpots = 0;
  } else {
    availableSpots = 1;
  }


   updateDisplay(availableSpots);  // Custom output function


// plus prints the distance on the serial monitor (to debug if neecessery)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
}
   
 

// Custom function #1
// triggers the ultrasonic sensor
int getDistance() {
  digitalWrite(TRIGpin, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGpin, HIGH);
  delay(1000);
  digitalWrite(TRIGpin, LOW);

// converts distance into cm using that formula: duration * speed_of_sound / 2  
  long duration = pulseIn(ECHOpin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}


// Custom function #2
void updateDisplay(int spots) {
  if (getDistance() < distanceThreshold) {
    digitalWrite(GREENpin, LOW);
    digitalWrite(REDpin, HIGH);
  } else {
    digitalWrite(GREENpin, HIGH);
    digitalWrite(REDpin, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print("Available Space: ");
  lcd.setCursor(0, 1);
  lcd.print("Spots:   ");
  lcd.print(spots);
  lcd.print("   ");  // Clear old characters
}
