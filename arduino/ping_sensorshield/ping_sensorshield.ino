#include <sensorShieldLib.h>

#define pingPin 8

SensorShield board;

int ping() {
  long duration;

  pinMode( pingPin, OUTPUT );
  digitalWrite( pingPin, LOW );
  delayMicroseconds( 2 );
  digitalWrite( pingPin, HIGH );
  delayMicroseconds( 5 );
  digitalWrite( pingPin, LOW );

  pinMode( pingPin, INPUT );
  duration = pulseIn( pingPin, HIGH );
  long distance = duration / 29 / 2;

  return int(distance);
}

void setup() {
  board.init();

  board.addSensor( "ping", ping );
  board.setSensorSensitivity("ping", 2);
}

void loop() {
  board.update();
  delay(50);
}
