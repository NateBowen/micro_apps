#include "main.h"

#define BUZZER_LOW_TONE         3000
#define BUZZER_PERIOD_LOW       1000000 / BUZZER_LOW_TONE
#define BUZZER_HIGH_TONE        5000
#define BUZZER_PERIOD_HIGH      1000000 / BUZZER_HIGH_TONE

#define BUZZER_CLOCK_PRESCALAR  168


void Buzzer_Config(void);
void BuzzerOnLow(void);
void BuzzerOnHigh(void);
void BuzzerOff(void);