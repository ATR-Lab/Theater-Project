//pinmap.h
//12/8/21

//This pin map is for version 0.1.1/0.1.2 of the Theater Control Board.
//Use these macros for best results and compatibility with future versions.

///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///*********************************MOTOR PIN MAP***************************///
///                                                                         ///
///////////////////////////////////////////////////////////////////////////////
//Gear Motor 1 Pins
#define GEAR_MOTOR_1_DIR        23
#define GEAR_MOTOR_1_SPEED      2
#define GEAR_MOTOR_1_E1         16
#define GEAR_MOTOR_1_E2         17
//Gear Motor 2 Pins
#define GEAR_MOTOR_2_DIR        22
#define GEAR_MOTOR_2_SPEED      3
#define GEAR_MOTOR_2_E1         14
#define GEAR_MOTOR_2_E2         15

//Stepper Motor 1 Pins
#define STEPPER_MOTOR_1_DIR     57
#define STEPPER_MOTOR_1_STEP    12
//Stepper Motor 2 Pins
#define STEPPER_MOTOR_2_DIR     56
#define STEPPER_MOTOR_2_STEP    11
//Stepper Motor 3 Pins
#define STEPPER_MOTOR_3_DIR     55
#define STEPPER_MOTOR_3_STEP    13
//Stepper Motor 4 Pins
#define STEPPER_MOTOR_4_DIR     54
#define STEPPER_MOTOR_4_STEP    10

//Servo Pins
#define SERVO_1   9
#define SERVO_2   8
#define SERVO_3   7
#define SERVO_4   6
#define SERVO_5   5
#define SERVO_6   4


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///******************************CONTROLS PIN MAP***************************///
///                                                                         ///
///////////////////////////////////////////////////////////////////////////////
//Joystick Pins
#define JOYSTICK_X    A8
#define JOYSTICK_Y    A9
//Button Pins
#define SW1   53
#define SW2   65
#define SW3   64
#define SW4   61
#define SW5   60
#define SW6   59
#define SW7   58


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///******************************I/O PIN MAP********************************///
///                                                                         ///
///////////////////////////////////////////////////////////////////////////////
//Analog Input Pins
#define ANALOG_1    A12
#define ANALOG_2    A13
#define ANALOG_3    A14
#define ANALOG_4    A15

//Digital I/O - Bank 1
#define BANK_1_PIN_1    24
#define BANK_1_PIN_2    25
#define BANK_1_PIN_3    26
#define BANK_1_PIN_4    27
#define BANK_1_PIN_5    28
#define BANK_1_PIN_6    29
#define BANK_1_PIN_7    30  //CAN BE ANALOG INPUT - A15
#define BANK_1_PIN_8    31  //CAN BE ANALOG INPUT - A14
#define BANK_1_PIN_9    32  //CAN BE ANALOG INPUT - A13
#define BANK_1_PIN_10   33  //CAN BE ANALOG INPUT - A12
//Digital I/O - Bank 2
#define BANK_2_PIN_1    38
#define BANK_2_PIN_2    39
#define BANK_2_PIN_3    40
#define BANK_2_PIN_4    41
#define BANK_2_PIN_5    46  //PWM
#define BANK_2_PIN_6    47
#define BANK_2_PIN_7    48  
#define BANK_2_PIN_8    49  
#define BANK_2_PIN_9    51 
#define BANK_2_PIN_10   52 
