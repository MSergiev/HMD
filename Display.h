 #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Common.h"

Adafruit_SSD1306 display(4);

struct Point {
  
  char x, y;  
  Point( char x, char y ) : x(x), y(y) {}; 

  void rotate( Point c, double a ) {
    short rX = c.x - x;
    short rY = c.y - y;
    double r = sqrt( rX*rX + rY*rY );
    
    x = c.x + cos(atan2(rY,rX)+a) * r;
    y = c.y + sin(atan2(rY,rX)+a) * r;
  }
  
};

void drawBattery( unsigned val ) {
  
  // Params
  #define BATT_TOP 1
  #define BATT_W 4
  #define BATT_H 32
  #define BATT_X 124
  #define BATT_Y 0

  unsigned char CAP = map( val, 0, BATT_MAX, 0, BATT_H-BATT_TOP );
  
  // Frame
  display.fillRect(BATT_X+BATT_TOP, BATT_Y, 2*BATT_TOP, BATT_Y+BATT_TOP, WHITE);
  display.drawRect(BATT_X, BATT_Y+BATT_TOP, BATT_W, BATT_H, WHITE);
  // Filling
  display.fillRect(BATT_X, BATT_Y+BATT_TOP+CAP, BATT_W, BATT_H, WHITE);
  
}

void drawClock() {  
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(6,6);
  display.println("10:23");
  //display.print(analogRead(BATT_PIN));
  
}

void drawCompass() { 
  
  #define ARR_IN 4
  #define ARR_W 16
  #define ARR_H 24
  #define ARR_X 16
  #define ARR_Y 16

  Point POS[] = {
    Point( ARR_X, ARR_Y/2 ),
    Point( ARR_X, ARR_Y + ARR_H/2 - ARR_IN ),
    Point( ARR_X - ARR_W/2, ARR_Y + ARR_H/2 ),
    Point( ARR_X + ARR_W/2, ARR_Y + ARR_H/2 ),
  };

  Point c( ARR_X, ARR_Y );

  for( unsigned char i = 0; i < 4; ++i ) {
    POS[i].rotate( c, heading );
  }

  display.fillTriangle(POS[0].x, POS[0].y,
                       POS[1].x, POS[1].y,
                       POS[2].x, POS[2].y, WHITE);
  display.drawTriangle(POS[0].x, POS[0].y,
                       POS[1].x, POS[1].y,
                       POS[3].x, POS[3].y, WHITE);
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45,8);
  display.println(heading * 180/PI);
  
}

void drawAngles() { 
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("X:");
  display.println(look[0]);
  display.setCursor(0,10);
  display.print("Y:");
  display.println(look[1]);
  display.setCursor(0,20);
  display.print("Z:");
  display.println(look[2]);
  
}

void drawLocator() {
  
  //const float HALF_FOV = 0.029; //0.058; //3.34;
  const float FOVDEG = 3.34;
  const float HALF_FOV = 3.34 / 2;
  const short SCR = 21;
  
  double destAngle = atan2(dest[2],dest[0]) * RAD_TO_DEG;
  double diffAngle = kalAngleZ - destAngle;
  double rad = (pos-dest).length();

  
  double r = 1;
    
  if( diffAngle > HALF_FOV ) {
    display.fillTriangle(124, 0,
                         128, 8,
                         124, 16, 
                         WHITE);
  } else if( diffAngle < -HALF_FOV ) {
    display.fillTriangle(4, 0,
                         0, 8,
                         4, 16, 
                         WHITE);
  } else {

    //const byte w = 32;
    const float pFactor = 0.8f;
    short w = WIDTH/2 - (WIDTH/2)*pFactor;
    short x = mapTo(diffAngle, -HALF_FOV, HALF_FOV, 0, 128);
    short perspective = x*pFactor + w; //32;
    float r = (rad < 1000000 ) ? mapTo( (short)(rad/1000), 0, 1000, w, 3 ) : 3;
    
//    display.fillTriangle(58, 22,
//                         x, 10,
//                         70, 22, 
//                         WHITE);

    display.drawRect( x-r, 10-r, 2*r+2, 2*r+2, WHITE );
    display.fillCircle( x, 10, r-1, WHITE );

    display.drawLine( perspective - (w+10), 0, x-r, 10-r, WHITE );
    display.drawLine( perspective + (w+10), 0, x+r, 10-r, WHITE );
    
    display.drawLine( perspective - (w+10), 22, x-r, 10+r, WHITE );
    display.drawLine( perspective + (w+10), 22, x+r, 10+r, WHITE );

    display.drawRect( perspective - (w+10), 0, 2*(w+10) + 1, 23, WHITE );
    
  }
    
  display.fillRect( 0, 23, 128, 10, WHITE );

  char dist[10] = "";
  if( rad >= 1000000 ) sprintf( dist, "%dkm", (short)(rad/1000000) );
  else sprintf( dist, "%dm", (short)(rad/1000) );
  
  display.setTextSize( 1 );
  display.setTextColor( BLACK, WHITE );
  display.setCursor( 0, 24 );
  display.print( " D:" );
  display.print( dist );
  display.print( " A:" );
  display.print( diffAngle );
  display.print( " " );
  display.print( (rad < 1000000 ) ? mapTo( (short)(rad/10000), 0, 1000, 10, 1 ) : 1 );
  
}




void initDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
}

void clearDisplay() {
  display.clearDisplay();
}

void draw() {
  display.display();
}
