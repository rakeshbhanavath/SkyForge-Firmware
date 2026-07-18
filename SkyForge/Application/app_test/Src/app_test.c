#include "app_test.h"
#include "app_test_uart.h"
#include "app_test_i2c.h"
//#include "app_test_gpio.h"
//#include "app_test_i2c.h"

void APP_Test_Run(void)
{
	APP_Test_I2C();
   // APP_Test_UART();

    // APP_Test_GPIO();
    // APP_Test_I2C();
}
