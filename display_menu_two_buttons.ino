// This is an open souce code for public use, you can copy, change und adapt it for you purpuses,
// if you damage your hardware or some body with this code, then, it's only your problem.
//
//  created by Mr.Buton, planet Earth(Fri Sep 20, 2024)
//

#include "header_display_menu.h"

void setup() {
  u8g2.begin();
  Serial.begin(9600);
  pinMode(buttonPin7, INPUT); pinMode(buttonPin8, INPUT);
  pinMode(A9, OUTPUT); pinMode(A10, OUTPUT); //led's
}

void loop() {
  if (digitalRead(buttonPin8)) { // CLOSE operation
    cancel_all();
    display_controll(2);
    led_controll(2);
    check_button_time("do_close_2x");
  }
  else if (digitalRead(buttonPin7)) {// OPEN operation
    cancel_all();
    display_controll(1);
    led_controll(1);
    check_button_time("do_open_2x");
  }
  else if (close_state_complex or open_state_complex) { // this section is for complex/automatic working operation
    condition_checking();
    Serial.print("state_open_complex: "); Serial.println(open_state_complex); Serial.print("state_close_complex: "); Serial.println(close_state_complex);
  }
  else { // plot to display, if no one button is active and states are not active.
    display_controll(5);
    led_controll(5);
    Serial.println("nothing happens"); Serial.println(open_state_complex); Serial.println(close_state_complex);
  }
}

// this function change display states
void display_controll(int display_case) {
  switch (display_case) {
    case 1://"1xUp"
      u8g2.clearBuffer();          // clear the internal memory
      //u8g2.setFont(u8g2_font_IPAandRUSLCD_tf);
      u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(16, 10, "1xUP");// u8g2.drawStr(16, 25, "MANUAL");
      u8g2.drawFrame(0, 20, DisplayWidth, 11);
      // DRAW_LOADLINE
      poi_t_p = &time_pressed; // get address fron var [time_pressed_condition]
      val_load_line = map(*poi_t_p, 0, time_set, 0, 64);
      u8g2.drawBox(0, 20, val_load_line, 11); // third parameter for [drawBox] is depending on pressed time.

      u8g2.sendBuffer(); // transfer internal memory to the display
      break;
    case 2://"1xDown"
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(16, 10, "1xDOWN");// u8g2.drawStr(16, 25, "MANUAL");
      u8g2.drawFrame(0, 20, DisplayWidth, 11);
      // DRAW_LOADLINE
      poi_t_p = &time_pressed; // get address fron var [time_pressed_condition]
      val_load_line = map(*poi_t_p, 0, time_set, 0, 64);
      u8g2.drawBox(0, 20, val_load_line, 11); // third parameter for [drawBox] is depending on pressed time.

      u8g2.sendBuffer(); // transfer internal memory to the display
      break;
    case 3://"2xUp"
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(22, 10, "2xUP"); u8g2.drawStr(6, 25, "AUTOMATIC");
      u8g2.sendBuffer();          // transfer internal memory to the display
      break;
    case 4://"2xDown"
      u8g2.clearBuffer(); // clear the internal memory
      u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(16, 10, "2xDOWN"); u8g2.drawStr(6, 25, "AUTOMATIC");
      u8g2.sendBuffer(); // transfer internal memory to the display
      break;
    case 5:// "smile_eyes"
      u8g2.firstPage();//this function is to print image on the display
      do {
        u8g2.drawXBMP(0, 0, SmileyBreite, SmileyHoehe, Smiley);
      }
      while (u8g2.nextPage());
      break;
    case 6:// "WORKING PROCESS"  this is only example
      display_time_max = millis();
      if ((display_time_max - display_time_min) >= display_time_sequence and !display_state_cond) {
        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_t0_14_tf); u8g2.drawStr(10, 10, "WORKING");
        u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(12, 25, "PROCESS");
        display_time_min = millis();
        display_state_cond = true;
        u8g2.sendBuffer(); // transfer internal memory to the display
      }
      else if ((display_time_max - display_time_min) >= display_time_sequence and display_state_cond) {
        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(12, 10, "WORKING");
        u8g2.setFont(u8g2_font_t0_14_tf); u8g2.drawStr(10, 25, "PROCESS");
        display_time_min = millis();
        display_state_cond = false;
        u8g2.sendBuffer(); // transfer internal memory to the display
      }
      break;
    default:
      Serial.println("DISPLAY_OFF");
      u8g2.clearBuffer(); // clear the internal memory
      u8g2.setFont(u8g2_font_t0_11_tf); u8g2.drawStr(16, 10, "DISPLAY"); u8g2.drawStr(2, 25, "FUNCTION_ERROR");
      u8g2.sendBuffer(); // transfer internal memory to the display
      delay(5000);
  }
}

void led_controll(int led_case) {
  switch (led_case) {
    case 1://"1xUp"
      analogWrite(A9, 0);
      break;
    case 2://"1xDown"
      analogWrite(A10, 0);
      break;
    case 3://"2xUp"
      analogWrite(A9, 0); analogWrite(A10, 255);
      break;
    case 4://"2xDown"
      analogWrite(A9, 255); analogWrite(A10, 0);
      break;
    case 5:// "smile_eyes"
      analogWrite(A9, 255); analogWrite(A10, 255);
      break;
    case 6:// "WORKING PROCESS" this is only example what can be done
      // blinking led's depending on setted time sequence and setted condition
      led_time_max = millis();
      if ((led_time_max - led_time_min) >= led_time_sequence and !led_state_cond) {
        analogWrite(A9, 0); analogWrite(A10, 255);
        led_time_min = millis();
        led_state_cond = true;
      }
      else if ((led_time_max - led_time_min) >= led_time_sequence and led_state_cond) {
        analogWrite(A9, 255); analogWrite(A10, 0);
        led_time_min = millis();
        led_state_cond = false;
      }
      break;
    default:
      Serial.println("LED_OFF");
  }
}

// calcel all activities
void cancel_all() {
  close_state_complex = false;
  open_state_complex = false;
  time_last = 0;
  time_last_condition = 0;
  led_time_min = 0;
  led_time_min = 0;
  led_state_cond = false;
  display_time_min = 0;
  display_time_min = 0;
  display_state_cond = false;
  Serial.println("cancel_function, all conditions are brought to initial state");
}

// checking if button is pressed continiously for more then {time_set}
void check_button_time(String action_to_do) {
  time_last = millis();
  while (digitalRead(buttonPin7) or digitalRead(buttonPin8)) {

    time_now = millis();
    time_pressed = time_now - time_last;
    Serial.println("check_button_time_function"); Serial.print("time_last: "); Serial.println(time_last);
    Serial.print("time_now: "); Serial.println(time_now); Serial.print("time_pressed: "); Serial.println(time_pressed);
    if (time_pressed > time_set) {
      if (action_to_do == "do_close_2x") {
        close_state_complex = true;
        display_controll(4);
        led_controll(4);
      }
      else if (action_to_do == "do_open_2x") {
        open_state_complex = true;
        display_controll(3);
        led_controll(3);
      }
    }
    else if (time_pressed < time_set) {
      // this part is only for display_load_line{
      if (action_to_do == "do_close_2x") {
        display_controll(2);
      }
      else if (action_to_do == "do_open_2x") {
        display_controll(1);
      }
      //ends}
      Serial.println("button pressed but not long enought");
    }
  }//while
}//main


// this function is to simulate periphery,digital or analog input signals
// or some other signals, in this case this is time out counter.
void condition_checking() {
  if (time_last_condition == 0) {
    time_last_condition = millis();
  }
  time_now_condition = millis();
  time_pressed_condition = time_now_condition - time_last_condition;
  Serial.println("condition_checking_function"); Serial.print("time_last_condition: "); Serial.println(time_last_condition);
  Serial.print("time_now_condition: "); Serial.println(time_now_condition); Serial.print("time_now_condition: "); Serial.println(time_pressed_condition);
  if ((time_pressed_condition > time_set_condition) and (close_state_complex or open_state_complex)) {
    cancel_all();
  }
  else if ((time_pressed_condition < time_set_condition) and (close_state_complex or open_state_complex)) {
    display_controll(6);
    led_controll(6);
    Serial.println("WORKING PROCESS");
  }
}
