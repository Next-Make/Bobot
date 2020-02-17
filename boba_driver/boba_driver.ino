#include <config.h>

short state;
unsigned long elapsed_time;
double sugar_time;
double boba_drop_time;

void setup() {

    Serial.begin(9600);
    
    // put your setup code here, to run once:
    pinMode(MILK_TO_TEA, OUTPUT);
    pinMode(TEA_TO_BOBA, OUTPUT);
    pinmode(WATER_TO_TEA, OUTPUT);
    pinMode(WATER_TO_BOBA, OUTPUT);
    pinMode(BOBA_TO_WASTE, OUTPUT);
    pinMode(TEABAG_MOTOR, OUTPUT);
    pinmode(TEA_TEMP_SENSOR, INPUT);
    pinmode(STIR_FAN, OUTPUT);
    pinmode(BOBA_TEMP_SENSOR, INPUT);
    pinmode(TEA_HEATER, OUTPUT);
    pinmode(BOBA_HEATER, OUTPUT);
    pinMode(START_COOK_BTN, INPUT_PULLUP);

    state = S_IDLE;
}

void loop() {
    switch (state) {
        case S_IDLE:
            idleHandler();
            break;
        case S_COOK:
            cookHandler();
            break;
        case S_CLEAN:
            cleanHandler();
            break;
        default:
            Serial.println("ERROR: invalid state");
            break;
    }
    // put your main code here, to run repeatedly:

}

void idleHandler(){
    bool button = analogRead(START_COOK_BTN);
    sugar_time = get_sugar_from_pot();
    boba_drop_time = get_boba_from_pot();
    if(button){
        state = S_COOK;
    }
}

short boba_substate = SS_FILL_BOBA_WATER;
short tea_substate = SS_TEA_IDLE;

void cookHandler(){
    static unsigned long boba_start_time = millis();
    static unsigned long tea_start_time = millis();

    switch (boba_substate) {
        case SS_FILL_BOBA_WATER:
            if((millis() - boba_start_time) > BOBA_WATER_FILL_TIME) {
                digitalWrite(WATER_TO_BOBA, LOW);
                boba_substate = SS_HEAT_BOBA_WATER;
                analogWrite(STIR_FAN, STIR_LOW);
            } else {
                digitalWrite(WATER_TO_BOBA, HIGH);
                analogWrite(STIR_FAN, STIR_HIGH);
            }
            break;
        case SS_HEAT_BOBA_WATER:
            if(analogRead(BOBA_TEMP_SENSOR) >= BOBA_COOK_TEMP){
                boba_substate = SS_COOK_BOBA;
                
                // Dispense raw boba
                analogWrite(BOBA_DROP_SERVO, 50); // TODO: fix this position
                delay(boba_drop_time); // wait for boba to fall
                analogWrite(BOBA_DROP_SERVO, 200); // TODO: fix this position
                delay(20);
                boba_dropped = true;
                boba_start_time = millis();
            }
            break;
        case SS_COOK_BOBA:
            if(millis() - boba_start_time > BOBA_COOK_TIME){
                boba_substate = SS_BOBA_DONE;
            }
            break;
        case SS_BOBA_DONE:
            break;
        default:
            boba_substate = SS_FILL_WATER;
            break;
    }   

    switch (tea_substate)
    {
        case SS_TEA_IDLE:
            if(millis() - tea_start_time > BOBA_COOK_TIME - TEA_COOK_TIME) {
                water_substate = SS_FILL_TEA_WATER;
                tea_start_time = millis();
            }
            break;
        case SS_FILL_TEA_WATER:
            if((millis() - sugar_time) > TEA_WATER_FILL_TIME) {
                digitalWrite(WATER_TO_TEA, LOW);
                tea_substate = SS_HEAT_TEA_WATER;
            } else {
                digitalWrite(WATER_TO_TEA, HIGH);
            }
            break;
        case SS_HEAT_TEA_WATER:
            if(analogRead(TEA_TEMP_SENSOR) >= TEA_COOK_TEMP){
                tea_substate = SS_COOK_TEA;
                // Dispense tea
                analogWrite(TEABAG_MOTOR, 1700); // TODO: fix this position
                delay(2000); // wait for tea to fall
                analogWrite(TEABAG_MOTOR, 1500); // TODO: fix this position
                digitalWrite(MILK_TO_TEA, HIGH); // TODO: THIS IS ALEX'S WORK AND IS LIKELY WRONG
                tea_start_time = millis();
            }
            break;
        case SS_COOK_TEA:
            if(millis() - tea_start_time >= TEA_COOK_TIME) {
                digitalWrite(MILK_TO_TEA, LOW); // TODO: THIS IS ALEX'S WORK AND IS LIKELY WRONG
            }
            if(millis() - tea_start_time >= TEA_COOK_TIME) {
                // Raise teabag 
                analogWrite(TEABAG_MOTOR, 1300);
                delay(2000);
                analogWrite(TEABAG_MOTOR, 1500);
                tea_substate = SS_TEA_DONE;
            }
        case SS_TEA_DONE:
            break;
        default:
            Serial.println("Error: invalid TEA substate");
            break;
    }

    // Bang-bang controller for water temperature
    if(boba_substate == SS_BOBA_IDLE)
        digitalWrite(BOBA_HEATER, LOW);
    else
        digitalWrite(BOBA_HEATER, analogRead(BOBA_TEMP_SENSOR) < BOBA_COOK_TEMP);
    if(boba_substate == SS_TEA_IDLE)
        digitalWrite(TEA_HEATER, LOW);
    else
        digitalWrite(TEA_HEATER, analogRead(TEA_TEMP_SENSOR) < TEA_COOK_TEMP);
    
    // Both tea and boba are done cooking
    if(boba_substate == SS_BOBA_DONE && tea_substate == SS_TEA_DONE){
        state = S_DISPENSE;
    }
}

void cleanHandler(){

}

double get_sugar_from_pot(){
    // WILL NEED TO BE A CALIBRATED FUNCTION OF SOME KIND
    return analogRead(SUGAR_LEVEL);
}

double get_boba_from_pot(){
    // WILL NEED TO BE A CALIBRATED FUNCTION OF SOME KIND
    return analogRead(BOBA_LEVEL);
}