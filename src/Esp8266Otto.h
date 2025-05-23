#ifndef EspOtto_h
#define EspOtto_h

#include "ServoDriver.h"

//-- Constants
#define FORWARD 1
#define BACKWARD -1
#define LEFT 1
#define RIGHT -1
#define SMALL 5
#define MEDIUM 15
#define BIG 30

// -- Servo delta limit default. degree / sec
#define SERVO_LIMIT_DEFAULT 240

class EspOtto
{
public:
  void init();
  void attachServos();
  void detachServos();
  void driveServos(int a[4], double phase[4], float cycle);
  void moveServos(int time, int servo_target[4]);
  void home();
  void walk(float steps, int direction);
  void turn(float steps, int direction);
  void execute(int a[4], double phase[4], float steps);

  // -- Servo limiter
  void enableServoLimit(int speed_limit_degree_per_sec = SERVO_LIMIT_DEFAULT);
  void disableServoLimit();

private:
  ServoDriver _servoDrivers[4];
  int _servoPins[4];
  unsigned long _finalTime;
  unsigned long _partialTime;
  float _increment[4];
};

#endif