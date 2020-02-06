/*
Copyright (c) 2020 PE5E

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


Credits:
Simple morse en- & decoding for Arduino 
Copyright (c) 2015 Matthias Esterl
Project code: https://gist.github.com/madc/4474559
License: (MIT)https://opensource.org/licenses/MIT

*/

//Define unit length in ms
int unit_length = 150;  // length of 1 morse unit
int frequency = 600;    // frequency played by tone()

int key_input = 4;      // key
int speaker =   5;      // speaker
int led_pin =  13;      // builtin led

String serial_string;

enum program_mode {
  play,
  record
};

program_mode p_mode = program_mode::play;

#include "morse_code.h"
#include "encode_morse.h"
#include "menu.h"
#include "play_morse.h"

bool key_pressed = false;

void setup() {
  pinMode(key_input, INPUT_PULLUP);   
  pinMode(speaker, OUTPUT);
  pinMode(led_pin, OUTPUT);

  Serial.begin(115200);
  delay(100);
  print_menu();
}

void loop() {

  if(!Serial) {
    key_pressed = !digitalRead(key_input);
    if(key_pressed) {
      tone(speaker, frequency);
    }
    else {
      noTone(speaker);
    }
    digitalWrite(led_pin, key_pressed);
    return;
  }

  serial_string = "";
  
  while (Serial.available() > 0) {
    serial_string += Serial.readString();
  } 

  if(serial_string.endsWith("\n")) {
    serial_string.remove(serial_string.length() -1);
  }
  if(serial_string.endsWith("\r")) {
    serial_string.remove(serial_string.length() -1);
  }

  if(is_menu_input(serial_string)) {
    serial_string = "";
    return;
  }

  if (p_mode == program_mode::record) {
    key_pressed = !digitalRead(key_input);
    if(key_pressed) {
      tone(speaker, frequency);
    }
    else {
      noTone(speaker);
    }
    digitalWrite(led_pin, key_pressed);
    return;
  }

  if(serial_string.length() == 0) {
    return;
  }

  Serial.print("Text: ");
  Serial.print(serial_string);
  Serial.print(". Morse: ");
  
  String morseWord = encode_morse(serial_string);
    
  play_morse(morseWord);
}
