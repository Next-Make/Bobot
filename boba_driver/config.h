// Pumps
#define MILK_TO_TEA 0
#define TEA_TO_BOBA 1
#define WATER_TO_TEA 2
#define WATER_TO_BOBA 3
#define BOBA_TO_WASTE 4

// Teabag motor
#define TEABAG_MOTOR 5
#define BOBA_DROP_SERVO 11 // needs to be pwm

// Temp sensor
#define TEA_TEMP_SENSOR 6
#define BOBA_TEMP_SENSOR 7

// Heater
#define TEA_HEATER 8
#define BOBA_HEATER 9

// Timing
#define BOBA_COOK_TIME 100000
#define TEA_COOK_TIME 100000
#define BOBA_WATER_FILL_TIME 1000 
#define TEA_WATER_FILL_TIME 1000

// User Input
#define START_COOK_BTN 10

// States
#define S_IDLE 0
#define S_COOK 1
#define S_DISPENSE 3
#define S_CLEAN 2

// Cook boba substates
#define SS_FILL_BOBA_WATER 0
#define SS_HEAT_BOBA_WATER 1
#define SS_COOK_BOBA 2
#define SS_BOBA_IDLE 3

// Cook tea substates
#define SS_TEA_IDLE 0
#define SS_FILL_TEA_WATER 1
#define SS_HEAT_TEA_WATER 2
#define SS_COOK_TEA 3


// Temps 
#define BOBA_COOK_TEMP 120 // TODO: change these values for the sensor later
#define DROP_BOBA_TEMP 120
#define TEA_COOK_TEMP 120