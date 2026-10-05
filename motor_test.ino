// MCU side of motor_test.py (UNO Q). Drives Cytron Maker Drive M1 channel.
//   M1A <- pin 10, M1B <- pin 11
//   A=PWM, B=LOW -> one direction;  A=LOW, B=PWM -> other;  both LOW -> brake
#include <Arduino_RouterBridge.h>

const int M1A = 10;
const int M1B = 11;

// speed: -255..255. Positive = clockwise, negative = counter-clockwise, 0 = stop.
void set_motor(int speed) {
  speed = constrain(speed, -255, 255);
  if (speed > 0) {
    analogWrite(M1A, speed);
    analogWrite(M1B, 0);
  } else if (speed < 0) {
    analogWrite(M1A, 0);
    analogWrite(M1B, -speed);
  } else {
    analogWrite(M1A, 0);
    analogWrite(M1B, 0);
  }
}

void setup() {
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  set_motor(0);

  Bridge.begin();
  Bridge.provide("set_motor", set_motor);
}

void loop() {}
