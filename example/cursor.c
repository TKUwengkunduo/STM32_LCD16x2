/* USER CODE BEGIN Includes */
#include "lcd_16x2.h"
/* USER CODE END Includes */


/* USER CODE BEGIN 2 */
LCD16_Init(&hi2c1);
const char *text = "  STM32 LCD Demo  ";
char padded[64] = {0};
char display[17] = {0};
/* USER CODE END 2 */


/* USER CODE BEGIN WHILE */
while (1)
{
    sprintf(padded, "                %s                ", text);  // 16 spaces padding

    for (int i = 0; i <= strlen(padded) - 16; i++) {
        strncpy(display, &padded[i], 16);
        display[16] = '\0';

        LCD16_SetCursor(0, 0);
        LCD16_PrintStr(display);

        HAL_Delay(200);
    }
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
}