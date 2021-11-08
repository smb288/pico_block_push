#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"

const int MOTOR1_FW = 12, 
          MOTOR1_BW = 13,
          TRIG_PIN1 = 0,
          ECHO_PIN1 = 1,
          TRIG_PIN2 = 2,
          ECHO_PIN2 = 3,
          TRIG_PIN3 = 4,
          ECHO_PIN3 = 5,
          IR1_PIN = 6,
          IR2_PIN = 7,
          MOTOR2_FW = 14,
          MOTOR2_BW = 15,
          LED_STATUS = 25;

bool TOO_CLOSE1 = false, TOO_CLOSE2 = false, TOO_CLOSE3 = false,
     START_CYCLE = true;



void motorPinInit(uint firstMotorF, uint firstMotorB, uint secondMotorF, uint secondMotorB) {
    gpio_init(firstMotorF);
    gpio_init(firstMotorB);
    gpio_init(secondMotorF);
    gpio_init(secondMotorB);

    gpio_set_dir(firstMotorF, GPIO_OUT);
    gpio_set_dir(firstMotorB, GPIO_OUT);
    gpio_set_dir(secondMotorF, GPIO_OUT);
    gpio_set_dir(secondMotorB, GPIO_OUT);
}

void ultrasonicSensorPinInit(uint trigPin1, uint echoPin1, uint trigPin2, uint echoPin2, uint trigPin3, uint echoPin3) {
    gpio_init(trigPin1);
    gpio_init(echoPin1);
    gpio_init(trigPin2);
    gpio_init(echoPin2);
    gpio_init(trigPin3);
    gpio_init(echoPin3);

    gpio_set_dir(trigPin1, GPIO_OUT);
    gpio_set_dir(echoPin1, GPIO_IN);
    gpio_set_dir(trigPin2, GPIO_OUT);
    gpio_set_dir(echoPin2, GPIO_IN);
    gpio_set_dir(trigPin3, GPIO_OUT);
    gpio_set_dir(echoPin3, GPIO_IN);
}

void startUp(uint ledPin) {
    gpio_init(ledPin);
    gpio_set_dir(ledPin, GPIO_OUT);
    
    gpio_put(ledPin, 1);
    sleep_ms(1000);
    gpio_put(ledPin, 0);
    sleep_ms(1000);
    gpio_put(ledPin, 1);
    sleep_ms(1000);
    gpio_put(ledPin, 0);
    sleep_ms(1000);
    gpio_put(ledPin, 1);
    sleep_ms(1000);
    gpio_put(ledPin, 0);
}

void forwards() {
    gpio_put(MOTOR1_FW, 1);
    gpio_put(MOTOR1_BW, 0);
    gpio_put(MOTOR2_FW, 1);
    gpio_put(MOTOR2_BW, 0);
}

void backwards() {
    gpio_put(MOTOR1_FW, 0);
    gpio_put(MOTOR1_BW, 1);
    gpio_put(MOTOR2_FW, 0);
    gpio_put(MOTOR2_BW, 1);
}

void stop_motors() {
    gpio_put(MOTOR1_FW, 0);
    gpio_put(MOTOR1_BW, 0);
    gpio_put(MOTOR2_FW, 0);
    gpio_put(MOTOR2_BW, 0);
}

void turn_right() {
    gpio_put(MOTOR1_FW, 1);
    gpio_put(MOTOR1_BW, 0);
    gpio_put(MOTOR2_FW, 0);
    gpio_put(MOTOR2_BW, 0);
}

void turn_left() {
    gpio_put(MOTOR1_FW, 0);
    gpio_put(MOTOR1_BW, 0);
    gpio_put(MOTOR2_FW, 1);
    gpio_put(MOTOR2_BW, 0);
}

void secondCoreCode() {
    while(1) {
        if(!START_CYCLE) {
            if(TOO_CLOSE1) turn_right();
            if(TOO_CLOSE2) turn_right();
            if(TOO_CLOSE3) turn_left();
            else forwards();
            sleep_us(10);
        }
    }
}

int main() {
    stdio_init_all();

    motorPinInit(MOTOR1_FW,MOTOR1_BW,MOTOR2_FW,MOTOR2_BW);
    ultrasonicSensorPinInit(TRIG_PIN1, ECHO_PIN1, TRIG_PIN2, ECHO_PIN2, TRIG_PIN3, ECHO_PIN3);

    set_sys_clock_khz(250000, true);
    multicore_launch_core1(secondCoreCode);

    startUp(LED_STATUS);

    while(1) {
        START_CYCLE = false;

    }
    return 0;
}