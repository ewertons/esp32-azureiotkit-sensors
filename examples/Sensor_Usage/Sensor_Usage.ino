/* Licensed under the MIT License. */

#include <stdlib.h>
#include <stdio.h>

#include "esp32_azureiotkit_sensors.h"
#include "esp_err.h"
#include "nvs_flash.h"

// Macro to help obtain the length of a string define discounting the byte used for null-terminator (\0).
#define lengthof(x)                      (sizeof(x) - 1)

#define OLED_SPLASH_MESSAGE              "Hello World!"

int last_sensor_read_time =              0;
const int sensor_read_frequency_millis = 5000;
bool led1_on = false;
bool led2_on = true;

void setup() {
    esp32_azureiotkit_initialize_sensors();

    esp32_azureiotkit_oled_clean_screen();
    esp32_azureiotkit_oled_show_message((uint8_t*)OLED_SPLASH_MESSAGE, lengthof(OLED_SPLASH_MESSAGE));
}

void loop() {
  if ((millis() - last_sensor_read_time) >= sensor_read_frequency_millis)
  {
      printf("temperature=%f C\r\n", esp32_azureiotkit_get_temperature());
      printf("humidity=%f %\r\n", esp32_azureiotkit_get_humidity());
      printf("light=%f lux\r\n", esp32_azureiotkit_get_ambientLight());

      float pressure, altitude;
      esp32_azureiotkit_get_pressure_altitude(&pressure, &altitude);
      printf("pressure=%f Pa\r\n", pressure);
      printf("altitude=%f m\r\n", altitude);

      int pitch, roll, accelX, accelY, accelZ;
      esp32_azureiotkit_get_pitch_roll_accel(&pitch, &roll, &accelX, &accelY, &accelZ);
      printf("pitch=%f\r\n", pitch);
      printf("roll=%f\r\n", roll);
      printf("acceleration X=%f\r\n", accelX);
      printf("acceleration Y=%f\r\n", accelY);
      printf("acceleration Z=%f\r\n", accelZ);

      int magnetometerX, magnetometerY, magnetometerZ;
      esp32_azureiotkit_get_magnetometer(&magnetometerX, &magnetometerY, &magnetometerZ);
      printf("magnetometer X=%f T\r\n", magnetometerX);
      printf("magnetometer Y=%f T\r\n", magnetometerY);
      printf("magnetometer Z=%f T\r\n", magnetometerZ);

      esp32_azureiotkit_led1_set_state(led1_on ? LED_STATE_ON : LED_STATE_OFF);
      esp32_azureiotkit_led2_set_state(led2_on ? LED_STATE_ON : LED_STATE_OFF);

      led1_on = !led1_on;
      led2_on = !led2_on;

      last_sensor_read_time = millis();
  }
}
