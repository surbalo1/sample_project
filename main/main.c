#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "ssd1306.h"
#include "gpio_JRL/gpio.h"
#include "gpio_JRL/gpio.c"


#define RED PIN14
#define GREEN PIN13
#define BLUE PIN12

#define SDA_PIN 21
#define SCL_PIN 22

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

    //FUNCION OLED
    void OLED() {
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = SCL_PIN,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    i2c_param_config(I2C_NUM_0, &i2c_config);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    ssd1306_set_i2c_address(0, 0x3C);
    ssd1306_set_i2c_port(0);
    ssd1306_set_screen(&screen);
    ssd1306_clear_screen(&screen, false);
    ssd1306_refresh(&screen, true);

    // Agregar el mensaje de bienvenida en la pantalla OLED
    ssd1306_write_string(&screen, 1, 1, "Hola, mundo!");
    ssd1306_refresh(&screen, true);
}

   
    return;
}
