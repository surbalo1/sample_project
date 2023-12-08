
#include "gpio_JRL/gpio.h"
#include "gpio_JRL/gpio.c"


#define RED PIN14
#define GREEN PIN13
#define BLUE PIN12
void app_main(void)
{
//  Definir el número de pin GPIO que deseas configurar
    uint8_t pinout = PIN4;  // Por ejemplo, configurando el pin GPIO5
    uint8_t pinON = PIN18;   //SW1
    uint8_t pinOFF = PIN19;  //SW2



    gpio_pinMode(pinout, OUTPUT);
    gpio_pinMode(RED, OUTPUT);
    gpio_pinMode(GREEN, OUTPUT);
    gpio_pinMode(BLUE, OUTPUT);
    gpio_pinMode(pinON, INPUT_PULLUP);
    gpio_pinMode(pinOFF, INPUT_PULLUP);
    gpio_write(RED, HIGH);
    gpio_write(GREEN, HIGH);
    gpio_write(BLUE, HIGH);


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
