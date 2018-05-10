#include <Wire.h>
#include "Display.h"
#include "Sensors.h"


void setup() {

  initSensors();
  pinMode( BATT_PIN, INPUT );
  Serial.begin(9600);
  delay(500);
  initDisplay();
  
}

void loop() {

  clearDisplay();
  //display.clearDisplay();
  Serial.println(analogRead(BATT_PIN));

  //updateSensors();
  calcAngles();
  pos[2] += 500;
  //drawBattery( analogRead(BATT_PIN) );
  //drawClock();
  //drawCompass();
  //drawAngles();
  drawLocator();
  draw();
  //display.display();
  //delay(100);

}
