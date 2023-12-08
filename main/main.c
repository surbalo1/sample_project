
#include "gpio_JRL/gpio.h"
#include "gpio_JRL/gpio.c"
#include <stdio.h>
#include "freertos/FreeRTOS.h"  //para la funcion del retardo
#include "freertos/task.h"
#include "freertos/portmacro.h"
#include "freertos/FreeRTOSConfig.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/adc.h"
#include <math.h>

//#include "ssd1306.h"

#define SDA_PIN 21
#define SCL_PIN 22
#define RED PIN14
#define GREEN PIN13
#define BLUE PIN12
void app_main(void)
{
 /***configurar adc***/
/**/

   
//  Definir el número de pin GPIO que deseas configurar
    uint8_t pinout = PIN4;  // Por ejemplo, configurando el pin GPIO5
    uint8_t pinON = PIN18;   //SW1
    uint8_t pinOFF = PIN19;  //SW2

float tv, tr, y, temp;

    gpio_pinMode(pinout, OUTPUT);
    gpio_pinMode(RED, OUTPUT);
    gpio_pinMode(GREEN, OUTPUT);
    gpio_pinMode(BLUE, OUTPUT);
    gpio_pinMode(pinON, INPUT_PULLUP);
    gpio_pinMode(pinOFF, INPUT_PULLUP);
    gpio_write(RED, HIGH);
    gpio_write(GREEN, HIGH);
    gpio_write(BLUE, HIGH);
    int adc_read = 0;
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc_read = adc1_get_raw(ADC1_CHANNEL_0);

    while(1){
        //printf("HIGH");

        if(gpio_read(pinON) == 0X00){
         gpio_write(pinout, HIGH);
         gpio_write(RED, LOW);
         vTaskDelay(1000/ (( TickType_t ) 1000 / 100));
         gpio_write(RED, HIGH);
         gpio_write(GREEN, LOW);
         vTaskDelay(1000/ (( TickType_t ) 1000 / 100));
         gpio_write(GREEN, HIGH);
         gpio_write(BLUE, LOW);
         vTaskDelay(1000/ (( TickType_t ) 1000 / 100));
         gpio_write(BLUE, HIGH);
         printf("HIGH\n");
        tv = 3.3 * adc_read / 4095.0;
        tr = tv * 10000.0 / (3.3 - tv);
        y = log(tr/10000.0);
        y = (1.0/298.15) + (y *(1.0/4050.0));
        temp = 1.0/y;
        temp = temp -273.15;
         printf("Temperature in %f.2 °C\n", temp);
         vTaskDelay(10/ (( TickType_t ) 1000 / 100));
        }
        if(gpio_read(pinOFF) == 0X00){
          gpio_write(pinout, LOW);
          gpio_write(RED, HIGH);
          gpio_write(GREEN, HIGH);
          gpio_write(BLUE, HIGH);
        //vTaskDelay(1000/ (( TickType_t ) 1000 / 100));
        }
     }


  
    //int bit =  GPIO_IN_ADDR & (1 << 14)? 1: 0;
    //printf("%d", bit);

   
    return;
}
