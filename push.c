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


int main() {
    stdio_init_all();

    while(1) {

    }
    return 0;
}