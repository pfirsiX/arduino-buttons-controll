// This is an open souce code for public use, you can copy, change und adapt it for you purpuses, 
// if you damage your hardware or some body with this code, then, it's only your problem.
//
//  created by Mr.Buton, planet Earth(Fri Sep 20, 2024)
//
#ifndef HEADER_DISPLAY_MENU  //protection from included twice ore more
#define HEADER_DISPLAY_MENU // declaration start

// used lib's
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// create object for display activity
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int DisplayWidth = u8g2.getDisplayWidth();
int DisplayHight = u8g2.getDisplayHeight(); 
// this two things are the same bellow and ubove, use what best for you.
# define SmileyBreite 64
# define SmileyHoehe 32

// links below are for use to create image that you like.
// to create and check BitMap https://xbm.jazzychad.net/
// https://javl.github.io/image2cpp/
// https://convert-my-image.com/ImageConverter
// https://www.pixilart.com/draw/96x64-bitmap-3f8f52032f

static const unsigned char Smiley[] PROGMEM = {
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B11111100,B00000001,B00000000,B00000000,B11111110,B00000000,B00000000,
  B00000000,B11111111,B00000111,B00000000,B10000000,B11111111,B00000011,B00000000,
  B10000000,B11111111,B00001111,B00000000,B11000000,B11111111,B00000111,B00000000,
  B10000000,B11111111,B00001111,B00000000,B11000000,B11111111,B00000111,B00000000,
  B11000000,B11111111,B00011111,B00000000,B11100000,B11111111,B00001111,B00000000,
  B11000000,B11111111,B00011111,B00000000,B11100000,B11111111,B00001111,B00000000,
  B11000000,B11111111,B00011111,B00000000,B11100000,B11111111,B00001111,B00000000,
  B11100000,B11111111,B00111111,B00000000,B11110000,B11111111,B00011111,B00000000,
  B11100000,B11111111,B00111111,B00000000,B11110000,B11111111,B00011111,B00000000,
  B11100000,B11111111,B00111111,B00000000,B11110000,B11111111,B00011111,B00000000,
  B11100000,B00000011,B00111110,B00000000,B11110000,B00000001,B00011111,B00000000,
  B01100000,B00000000,B00110000,B00000000,B00110000,B00000000,B00011000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};




// constants won't change. They're used here to set pin numbers:
const int buttonPin7 = 7;     // the number of the pushbutton pin is used to open 1x.
const int buttonPin8 = 8;     // used to close 1x.

// var's are used to set working state ON/OFF, can be used for control the peripherie.
bool close_state_complex = false;
bool open_state_complex = false;



// variables beneath used to change state automaticaly
unsigned long time_now; // set actual time.
unsigned long time_last;  // last time that function run. 
unsigned long time_pressed; // calculated time from two above
unsigned long time_set = 750;// this variable is for time range automatic work, if needed.

// var to playng with conditions, 
unsigned long time_now_condition;
unsigned long time_last_condition;
unsigned long time_pressed_condition; // is for simulating working process
unsigned long time_set_condition = 10000;

// display controll, depending on state_condition and time 
int display_time_sequence = 300; // here you can change the display layout change time sequence
unsigned long display_time_min = 0;
unsigned long display_time_max = display_time_sequence; // in each {display_time_sequence} seconds change the collor  
bool display_state_cond = false;

//is for display representatioin load line and processline {only for optical reason}
int val_load_line = 0;
int val_proces_line = 0;
long unsigned *poi_t_p;// pointer to {time_pressed_condition}

// led controll to change the collor, depending on state_condition and time 
int led_time_sequence = 133; // here you can change the led's change time sequence
unsigned long led_time_min = 0;
unsigned long led_time_max = led_time_sequence; // in each {led_time_sequence} seconds change the collor  
bool led_state_cond = false;


//function declaration, parameter are without names only datatype.
void condition_checking();
void check_button_time(String);
void cancel_all();
void led_controll(int);
void display_controll(int);

#endif  // declaration end

