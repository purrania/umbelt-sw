#include <haptics.h>

void
init_haptics() {
  // Initialize Motor Pins
  for (int i = 0; i < N_MOTORS; i++) {
    // Setup EN pin and set to low
    pinMode(MOTOR_PINS[i] + EN_OFFSET, OUTPUT);
    digitalWrite(MOTOR_PINS[i] + EN_OFFSET, LOW);
    pinMode(MOTOR_PINS[i], OUTPUT);
  }
}

/* Vibrates specified motors for given intensity and duration.
 *
 * @param motor_pin	specified motor to vibrate
 * @param duration	length time of vibration in ms
 * @param percent_motor percent of haptic vibration capacity to vibrate at,
 * 			not to exceed 0.85
 */
void actuate_motor(int motor_pin, int duration, double percent_motor, int frequency) {
  digitalWrite(MOTOR_PINS[motor_pin] + EN_OFFSET, HIGH);  // enable
  if (percent_motor > 0.85) {
    Serial.println("Motor percentage above 85%. Using 85%");
    percent_motor = 0.85;
  }
  int numCycles = duration / (frequency * 2);
  for (int j = 0; j < numCycles; j++) {  // do J_MAX * TODAL_DELAY = 16 * 6 = 96ms of vibration
    analogWrite(MOTOR_PINS[motor_pin], 512 + percent_motor * 512);
    delay(frequency);
    analogWrite(MOTOR_PINS[motor_pin], 512 - percent_motor * 512);
    delay(frequency);
  }
  digitalWrite(MOTOR_PINS[motor_pin] + EN_OFFSET, LOW);  // disable
} 



void play_note(int duration, double percent_motor, int chosen_note) {
  int maxMotors = 2;
  double noteFrequencies[9] {110, 123, 131, 147, 165, 175, 196, 220, 247}; // A2 --> B3
  double period = (1 / noteFrequencies[chosen_note]) * 1000000;
  
  for (int i = 0; i < maxMotors; i++) {
    digitalWrite(MOTOR_PINS[i] + EN_OFFSET, HIGH);  // enable
  }

  if (percent_motor > 0.85) {
    Serial.println("Motor percentage above 85%. Using 85%");
    percent_motor = 0.85;
  }

  int numCycles = duration / period;
  Serial.println("Num Cycles: " + String(numCycles));
  for (int j = 0; j < numCycles; j++) {  // do J_MAX * TODAL_DELAY = 16 * 6 = 96ms of vibration
    for (int i = 0; i < maxMotors; i++) {
      analogWrite(MOTOR_PINS[i], 512 + percent_motor * 512);
    }
    delayMicroseconds(period / 2);
    for (int i = 0; i < maxMotors; i++) {
      analogWrite(MOTOR_PINS[i], 512 - percent_motor * 512);
    }
    delayMicroseconds(period / 2);
    }
    for (int i = 0; i < maxMotors; i++) {
      digitalWrite(MOTOR_PINS[i] + EN_OFFSET, LOW);  // enable
    }
}


void jackhammer_actuate(int motor_pin, double intensity, int reps) {
  for (int i = 0; i < reps; i++) {
    actuate_motor(motor_pin, 10, intensity, 3);
    delay(100);
  }
}

/* Triple vibrate */
void triple_vibrate(int duration, double percent_motor) {
  actuate_motor(0, duration, percent_motor, 3);
  delay(250);
  actuate_motor(1, duration, percent_motor, 3);
  delay(250);
  actuate_motor(2, duration, percent_motor, 3);
  delay(250);
}

/* Repeats vibration mode for given duration
 * @param motor_pin	specified motor to vibrate
 * @param duration_on	length time of vibration in ms
 * @param percent_motor percent of haptic vibration capacity to vibrate at,
 * 			not to exceed 0.85
 * @param duration_off length of delay time between vibration cycle 
 */

void repeat_motor(int motor_pin, int repeat, int duration_on, int duration_off, double percent_motor) {
  for(int i = 0; i  < repeat; i++){
    actuate_motor(motor_pin, duration_on, percent_motor, 3);
    delay(duration_off);
  }  
}


/* Test & debug functions */
void
haptics_test() {

  for (int i = 0; i < N_MOTORS; i++) {
    actuate_motor(i, 64, 0.85, 3);
    delay(50);
  }
}

void
cascade_motors(int duration, double percent_motor, int num_cycles) {
  for (int cycle = 0; cycle < num_cycles; cycle++) {
    for (int i = 0; i < N_MOTORS; i++) {
      actuate_motor(i, duration, percent_motor, 3);
      delay(50);
    }
  }
}

