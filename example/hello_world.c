/* USER CODE BEGIN Includes */
#include "lcd_16x2.h"
/* USER CODE END Includes */



/* USER CODE BEGIN 2 */
LCD16_Init(&hi2c1);

LCD16_SetCursor(0, 0);
LCD16_PrintStr("Hello");

LCD16_SetCursor(0, 1);
LCD16_PrintStr("World!");
/* USER CODE END 2 */