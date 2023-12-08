
#include "gpio_JRL/gpio.h"
#include "gpio_JRL/gpio.c"

#include "freertos/FreeRTOS.h"  //para la funcion del retardo
#include "freertos/task.h"
#include "freertos/portmacro.h"
#include "freertos/FreeRTOSConfig.h"
void app_main(void)
{
 // Definir el número de pin GPIO que deseas configurar
    uint8_t pinout = PIN5;  // Por ejemplo, configurando el pin GPIO5
    uint8_t pinON = PIN21;
    uint8_t pinOFF = PIN19;
    gpio_pinMode(pinout, OUTPUT);
    gpio_pinMode(pinON, INPUT_PULLUP);
    gpio_pinMode(pinOFF, INPUT_PULLUP);
    for(int j = 0; j <= 39; ++j){
        if(j!=PIN18 && j !=PIN19)
            gpio_pinMode(j, OUTPUT);
    }
    while(1){

        if(gpio_read(pinON) == 0X00){
         gpio_write(pinout, LOW);

        }
        if(gpio_read(pinOFF) == 0X00)
          gpio_write(pinout, HIGH);

        //vTaskDelay(1000/ (( TickType_t ) 1000 / 100));
    }

    return;
}
