#include "Arduboy.h";

static Arduboy arduboy;

float ship_x = 10;
float ship_y = 10;
float ship_ax = 0;
float ship_ay = 0.1;
float ship_vx = 5;
float ship_vy = 0;
int ship_height = 5;
int ship_width = 5;
bool debug = false;
bool gamePaused = false;
bool zoom = false;


void draw() {
  if (debug) {
    arduboy.setCursor((0),(0));
    arduboy.print(("x:"));
    arduboy.print((ship_x));
    arduboy.print(("ax:"));
    arduboy.print((ship_ax));
    arduboy.print(("vx:"));
    arduboy.println((ship_vx));
    arduboy.print(("y:"));
    arduboy.print((ship_y));
    arduboy.print(("ay:"));
    arduboy.print((ship_ay));
    arduboy.print(("vy:"));
    arduboy.println((ship_vy));
    }
  if (!zoom) {
  arduboy.drawFastHLine((0),(63),(128), WHITE);
  arduboy.drawPixel((ship_x), (ship_y), WHITE);
  arduboy.drawPixel((ship_x+1), (ship_y+1), WHITE);
  arduboy.drawPixel((ship_x-1), (ship_y+1), WHITE);
  } else {
  arduboy.drawFastHLine((0),(63),(128), WHITE);
  arduboy.drawRect((ship_x), (ship_y), ship_width, ship_width, WHITE);
  }
  arduboy.display();
};

void updateGame() {
  if (ship_vx>0) {
    ship_vx -= 0.0005;
  } else if (ship_vx<0) {
    ship_vx += 0.0005;
  }
  ship_vx += ship_ax/360;
  ship_vy += ship_ay/360;
  ship_x += ship_vx/360;
  ship_y += ship_vy/360;

  if (63-ship_y < 10) {
    zoom = true;
    }
};

void pause() {
  if (gamePaused) {
    gamePaused = false;
    } else {
    gamePaused = true;
    }
  }

void checkKeys() {
  if (arduboy.pressed(DOWN_BUTTON)) {
     ship_ay = -1;
   } else {
     ship_ay = 0.1;
    }
  if (arduboy.pressed(B_BUTTON)) {
     debug = true;
   } else {
    debug = false;
    }
};

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(60);
};

void loop() {
  if (!gamePaused) {
  checkKeys();
  updateGame();
  arduboy.clear();
  draw();
  }
};
