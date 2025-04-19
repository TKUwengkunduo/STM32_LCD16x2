/* USER CODE BEGIN Includes */
#include "lcd_16x2.h"
/* USER CODE END Includes */


/* USER CODE BEGIN 2 */
LCD16_Init(&hi2c1);
/* USER CODE END 2 */


/* USER CODE BEGIN WHILE */
while (1)
{
    LCD16_Clear();

    for (uint8_t row = 0; row < 2; row++) {
        for (uint8_t col = 0; col < 16; col++) {
            LCD16_SetCursor(col, row);
            LCD16_PrintStr("*");
            HAL_Delay(100);
        }
    }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}