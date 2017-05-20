#include "Arduboy.h";

static Arduboy arduboy;

float ship_x = 10;
float ship_y = 10;
float ship_px_1 = ship_x;
float ship_py_1 = ship_y+1;
float ship_px_2 = ship_x-1;
float ship_py_2 = ship_y;
float ship_px_3 = ship_x+1;
float ship_py_3 = ship_y;
float ship_px_4 = ship_px_1;
float ship_py_4 = ship_py_1;
float ship_px_5 = ship_px_1;
float ship_py_5 = ship_py_1;
float ship_px_6 = ship_px_1;
float ship_py_6 = ship_py_1;
float ship_px_7 = ship_px_1;
float ship_py_7 = ship_py_1;
float ship_px_8 = ship_px_1;
float ship_py_8 = ship_py_1;
float ship_px_9 = ship_px_1;
float ship_py_9 = ship_py_1;
float ship_ax = 0;
float ship_ay = 0.1;
float ship_vx = 5;
float ship_vy = 0;
float ship_angle = PI/2;
float ship_altitude = 10;
float maxThrust = 10;
float thrust = 0;
float gravity = 0.1;
float fuel = 100;
float score = 0;
int minHeight = 1;
int maxHeight = 5;
bool debug = false;
bool paused = false;
bool zoom = false;
bool RB_LAST = false;
bool LB_LAST = false;
String mapString = "";
String landing = "none";
String gameStatus = "menu";
bool waiting = false;

void draw() {
  if (!zoom) {
  getShipPoints();
  arduboy.drawPixel((ship_px_1), (ship_py_1), WHITE);
  arduboy.drawPixel((ship_px_2), (ship_py_2), WHITE);
  arduboy.drawPixel((ship_px_3), (ship_py_3), WHITE);
  arduboy.drawPixel((ship_px_4), (ship_py_4), WHITE);
  arduboy.drawPixel((ship_px_5), (ship_py_5), WHITE);
  arduboy.drawPixel((ship_px_6), (ship_py_6), WHITE);
  arduboy.drawPixel((ship_px_7), (ship_py_7), WHITE);
  arduboy.drawPixel((ship_px_8), (ship_py_8), WHITE);
  arduboy.drawPixel((ship_px_9), (ship_py_9), WHITE);
  } else {
  getShipPoints();
  arduboy.drawPixel((128/2), (64/2), WHITE);
  arduboy.drawPixel((ship_px_1), (ship_py_1), WHITE);
  arduboy.drawPixel((ship_px_2), (ship_py_2), WHITE);
  arduboy.drawPixel((ship_px_3), (ship_py_3), WHITE);
  arduboy.drawPixel((ship_px_4), (ship_py_4), WHITE);
  arduboy.drawPixel((ship_px_5), (ship_py_5), WHITE);
  arduboy.drawPixel((ship_px_6), (ship_py_6), WHITE);
  arduboy.drawPixel((ship_px_7), (ship_py_7), WHITE);
  arduboy.drawPixel((ship_px_8), (ship_py_8), WHITE);
  arduboy.drawPixel((ship_px_9), (ship_py_9), WHITE);
  }
  arduboy.fillRect(126,64-((fuel/100)*64),2,fuel,WHITE);
  arduboy.setCursor(101,0);
  arduboy.print("Fuel");
  arduboy.setCursor(101,9);
  arduboy.print(round(fuel));
  arduboy.setCursor(90,20);
  arduboy.print(thrust);
  arduboy.display();
};

void resetGame() {
   ship_x = 10;
   ship_y = 10;
   ship_ax = 0;
   ship_ay = 0.1;
   ship_vx = 5;
   ship_vy = 0;
   thrust = 0;
   ship_angle = PI/2;
   ship_altitude = 10;
   fuel = 100;
   score = 0;
   debug = false;
   paused = false;
   mapString = "";
   landing = "none";
   waiting = false;
   arduboy.clear();
   gameStatus = "menu";
  }

void tryAgain() {
   ship_x = 10;
   ship_y = 10;
   ship_ax = 0;
   ship_ay = 0.1;
   ship_vx = 5;
   ship_vy = 0;
   thrust = 0;
   ship_angle = PI/2;
   ship_altitude = 10;
   zoom = false;
   landing = "none";
   waiting = false;
   arduboy.clear();
   gameStatus = "playing";
  }

void getShipPoints() {
    if (!zoom) {
      ship_px_1 = ship_x+(1*cos(ship_angle));
      ship_py_1 = ship_y-(1*sin(ship_angle));
      ship_px_2 = ship_x+(1*cos(-ship_angle+(PI/2)));
      ship_py_2 = ship_y+(1*sin(-ship_angle+(PI/2)));
      ship_px_3 = ship_x+(1*cos(-ship_angle-(PI/2)));
      ship_py_3 = ship_y+(1*sin(-ship_angle-(PI/2)));
      ship_px_4 = ship_x+(3*cos(ship_angle));
      ship_py_4 = ship_y-(3*sin(ship_angle));
      ship_px_5 = ship_x+(2*cos(-ship_angle+(PI/6)));
      ship_py_5 = ship_y+(2.3*sin(-ship_angle+(PI/6)));
      ship_px_6 = ship_x+(2*cos(-ship_angle-(PI/6)));
      ship_py_6 = ship_y+(2.3*sin(-ship_angle-(PI/6)));
      if (thrust>0 && thrust<maxThrust/3) {
        ship_px_7 = ship_x;
        ship_py_7 = ship_y;
      } else if (thrust>=maxThrust/3 && thrust<(maxThrust/3)*2) {
        ship_px_7 = ship_x;
        ship_py_7 = ship_y;
        ship_px_8 = ship_x+(1*cos(-ship_angle-(PI)));
        ship_py_8 = ship_y+(1*sin(-ship_angle-(PI)));
      } else if (thrust>(maxThrust/3)*2) {
        ship_px_7 = ship_x;
        ship_py_7 = ship_y;
        ship_px_8 = ship_x+(1*cos(-ship_angle-(PI)));
        ship_py_8 = ship_y+(1*sin(-ship_angle-(PI)));
        ship_px_9 = ship_x+(2*cos(-ship_angle-(PI)));
        ship_py_9 = ship_y+(2*sin(-ship_angle-(PI)));
      } else {
        ship_px_7 = ship_px_1;
        ship_py_7 = ship_py_1;
        ship_px_8 = ship_px_1;
        ship_py_8 = ship_py_1;
        ship_px_9 = ship_px_1;
        ship_py_9 = ship_py_1;
      }
    } else {
      ship_px_1 = (128/2)+(1*cos(ship_angle));
      ship_py_1 = (64/2)-(1*sin(ship_angle));
      ship_px_2 = (128/2)+(1*cos(-ship_angle+(PI/2)));
      ship_py_2 = (64/2)+(1*sin(-ship_angle+(PI/2)));
      ship_px_3 = (128/2)+(1*cos(-ship_angle-(PI/2)));
      ship_py_3 = (64/2)+(1*sin(-ship_angle-(PI/2)));
      ship_px_4 = (128/2)+(3*cos(ship_angle));
      ship_py_4 = (64/2)-(3*sin(ship_angle));
      ship_px_5 = (128/2)+(2*cos(-ship_angle+(PI/6)));
      ship_py_5 = (64/2)+(2.3*sin(-ship_angle+(PI/6)));
      ship_px_6 = (128/2)+(2*cos(-ship_angle-(PI/6)));
      ship_py_6 = (64/2)+(2.3*sin(-ship_angle-(PI/6)));
      if (thrust>0 && thrust<maxThrust/3) {
        ship_px_7 = (128/2);
        ship_py_7 = (64/2);
      } else if (thrust>=maxThrust/3 && thrust<(maxThrust/3)*2) {
        ship_px_7 = (128/2);
        ship_py_7 = (64/2);
        ship_px_8 = (128/2)+(1*cos(-ship_angle-(PI)));
        ship_py_8 = (64/2)+(1*sin(-ship_angle-(PI)));
      } else if (thrust>(maxThrust/3)*2) {
        ship_px_7 = (128/2);
        ship_py_7 = (64/2);
        ship_px_8 = (128/2)+(1*cos(-ship_angle-(PI)));
        ship_py_8 = (64/2)+(1*sin(-ship_angle-(PI)));
        ship_px_9 = (128/2)+(2*cos(-ship_angle-(PI)));
        ship_py_9 = (64/2)+(2*sin(-ship_angle-(PI)));
      } else {
        ship_px_7 = ship_px_1;
        ship_py_7 = ship_py_1;
        ship_px_8 = ship_px_1;
        ship_py_8 = ship_py_1;
        ship_px_9 = ship_px_1;
        ship_py_9 = ship_py_1;
      }
    }
  }

void updateGame() {
  if (ship_vx>0) {
    ship_vx -= 0.0005;
  } else if (ship_vx<0) {
    ship_vx += 0.0005;
  }
  if (ship_x<0) {
    ship_x = 128;
  }
  if (ship_x>128) {
    ship_x = 0;
  }
  ship_ax = thrust*cos(ship_angle);
  ship_ay = gravity-(thrust*sin(ship_angle));
  fuel -= 0.01*thrust;
  ship_vx += ship_ax/360;
  ship_vy += ship_ay/360;
  ship_x += ship_vx/360;
  ship_y += ship_vy/360;
  
  char character = (mapString[ship_x]);
  int groundLevel = (int)character - 48;
  groundLevel = 64-groundLevel;
  ship_altitude = groundLevel - ship_y;

  if (ship_altitude < 10) {
    zoom = true;
  } else {zoom = false;}
};

void makeMap() {
  mapString = "";
  mapString += (round(random(minHeight,maxHeight)));
  for (int i=1; i < 128; i++){
      char character = (mapString[i-1]);
      int lastHeight = (int)character - 48;
      if (lastHeight == 1) {
        mapString += lastHeight+1;
        continue;
      } else if (lastHeight == 9) {
        mapString += lastHeight-1;
        continue;
      }
      int temp = round(random(1,4));
      if (temp == 1) {
        mapString += lastHeight+1;
      } else if (temp == 2) {
        mapString += lastHeight;
      } else {
        mapString += lastHeight-1;
      }
   }
  }

void drawMap() {
  if (!zoom) {
  for (int i=0; i < mapString.length(); i++){
     char character = (mapString[i]);
     int number = (int)character - 48;
     arduboy.drawPixel((i), (64-number), WHITE);
   }
  } else {
    for (int i=0; i <= 8; i++){
      char character = (mapString[ship_x+(i-4)]);
      int number = (int)character - 48;
      float altitude = (64-(number))-ship_y;
      character = (mapString[ship_x+((i+1)-4)]);
      number = (int)character - 48;
      float altitude2 = (64-(number))-ship_y;
      arduboy.drawLine((i*16), 33+(altitude*5),((i+1)*16), 33+(altitude2*5), WHITE);
      arduboy.drawPixel((i*16), 33+(altitude*5), WHITE);
      }
    }
  }

void checkKeys() {
  if (arduboy.pressed(DOWN_BUTTON) && fuel>0) {
    if (thrust < maxThrust) {
        thrust +=0.1;
      } else {thrust = maxThrust;}
     ship_ax = thrust*cos(ship_angle);
     ship_ay = gravity-(thrust*sin(ship_angle));
     fuel -= 0.0025*thrust;
   } else {
     if (thrust>0) {thrust -= 0.1;}
     if (thrust<0) {thrust = 0;}
    }
  if (arduboy.pressed(B_BUTTON)) {
     paused=true;
   }
  if (arduboy.pressed(RIGHT_BUTTON) && RB_LAST) {
     ship_angle -= PI/4;
     RB_LAST = false;
   } else if (!arduboy.pressed(RIGHT_BUTTON)) {RB_LAST = true;};
  if (arduboy.pressed(LEFT_BUTTON) && LB_LAST) {
     ship_angle += PI/4;
     LB_LAST = false;
   } else  if (!arduboy.pressed(LEFT_BUTTON)) {LB_LAST = true;};
};

void checkLanding() {
  if (ship_altitude <= 0) {
    if (ship_vx < 0.5) {
      if (ship_vy < 5) {
        if (round(cos(ship_angle)) == 0 && round(sin(ship_angle)) == 1) {
          if (mapString[ship_x-1] == mapString[ship_x] && mapString[ship_x+1] == mapString[ship_x]) {
              landing = "perfect";
            } else {landing = "onSlope";}
          } else {landing = "fellOver";}
        } else {landing = "vyTooHigh";}
      } else {landing = "vyTooHigh";}
    } else {landing = "none";}
  }

void winScreen() {
  arduboy.fillRect(20,10,88,34,BLACK);
  arduboy.drawRect(20,10,88,34,WHITE);
  arduboy.setCursor(25,15);
  score = round(fuel*10);
  arduboy.print("YOU WINNED!!!");
  arduboy.display();
  }

void loseScreen() {
  arduboy.fillRect(20,10,88,34,BLACK);
  arduboy.drawRect(20,10,88,34,WHITE);
  arduboy.setCursor(25,15);
  arduboy.print(landing);
  arduboy.display();
  }

void menuScreen() {
  arduboy.fillRect(20,10,88,34,BLACK);
  arduboy.drawRect(20,10,88,34,WHITE);
  arduboy.setCursor(48,15);
  arduboy.print("LUNAR!");
  arduboy.setCursor(30,32);
  arduboy.print("BY: Evan M.");
  arduboy.setCursor(35,55);
  arduboy.print("A to start");
  arduboy.display();
  }

void pauseScreen() {
  arduboy.fillRect(20,10,88,34,BLACK);
  arduboy.drawRect(20,10,88,34,WHITE);
  arduboy.setCursor(25,15);
  arduboy.print("A to continue");
  arduboy.display();
  }

void waitForContinue() {
  if (arduboy.pressed(A_BUTTON)) {
    waiting = false;
    if (paused) {paused = false;} else if (fuel>0) {tryAgain();makeMap();} else  if (fuel<0) {resetGame();makeMap();} else if (gameStatus == "menu") {gameStatus = "playing";}
    } else {waiting = true;arduboy.idle();}
  }

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(60);
  if (gameStatus = "menu") {menuScreen();waitForContinue();}
  makeMap();
};

void loop() {
  if (!waiting) {
    if (landing == "none") {
      checkLanding();
      checkKeys();
      updateGame();
      arduboy.clear();
      drawMap();
      draw();
      if (paused) {
        pauseScreen();
        waitForContinue();
      }
   } else {
      if (landing == "perfect") {
        winScreen();
        waitForContinue();
      }
      if (landing != "perfect") {
        loseScreen();
        waitForContinue();
      }
    }
  } else {waitForContinue();}
};
