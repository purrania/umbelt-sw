#include <haptics.h>

void
vibrate_single_motor(int loc, int dur) {

    // If the motor lies on the back, then increase intensity
    if (loc >= 5 && loc <= 8) dur = 200;

    digitalWrite(MOTOR_PINS[loc], HIGH);
    delay(dur);
    digitalWrite(MOTOR_PINS[loc], LOW);
    delay(50);
    digitalWrite(MOTOR_PINS[loc], HIGH);
    delay(dur / 2);
    digitalWrite(MOTOR_PINS[loc], LOW);
}

void
analog_test() {

    int val_max = 40;
    // Test analog output at 5 different levels
    for (int i = val_max / 2; i <= val_max; i++) {
        int value = (i / (float)val_max) * 255;
        analogWrite(MOTOR_PINS[5], value);
        Serial.print("Index: ");
        Serial.println(i);
        delay(100);
        analogWrite(MOTOR_PINS[5], 0);
        delay(300);
    }

}

void
haptics_test() {
    // Tests each haptic motor: vibrates each once, goes in a circle.
    for (int i = 0; i < 12; i++) {
        digitalWrite(MOTOR_PINS[i], HIGH);
        delay(100);
        digitalWrite(MOTOR_PINS[i], LOW);
        delay(50);
        digitalWrite(MOTOR_PINS[i], HIGH);
        delay(50);
        digitalWrite(MOTOR_PINS[i], LOW);
        delay(50);

        delay(500);
    }
}

void
haptics_test_multi() {
    // Tests each haptic motor: vibrates each once, goes in a circle.
    for (int i = 0; i < 24; i++) {
        int mot_1 = (i / 2) % 12;
        int mot_2 = (int) ceil(i / 2.0) % 12;

        int dur = 150;
        Serial.print("Mot 1: ");
        Serial.print(mot_1);
        Serial.print(" mot 2: ");
        Serial.print(mot_2);
        Serial.println("");

        if (mot_1 != mot_2) dur = 2 * dur / 3;

        digitalWrite(MOTOR_PINS[mot_1], HIGH);
        digitalWrite(MOTOR_PINS[mot_2], HIGH);
        delay(dur);
        digitalWrite(MOTOR_PINS[mot_1], LOW);
        digitalWrite(MOTOR_PINS[mot_2], LOW);
        // delay(50);

        delay(500);
    }
}