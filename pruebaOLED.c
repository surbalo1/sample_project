/****************************************************************************************
 * Nombre: pruebaOLED
 * Precondiciones: --
 * Función: usar pantalla oled
 * parametros: --
**************************************************************************************/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "ssd1306.h"

#define SDA_PIN 21
#define SCL_PIN 22

void app_main() {
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
