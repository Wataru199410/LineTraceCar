#include "carFunc.h"

void sensorSetup(void){
  DDRB &= 0b00000000;
}

//モーターをPWM制御するための関数
void timer0PWMInit(void){
  bitSet(TCCR0A, COM0A1);
  bitClear(TCCR0A, COM0A0);
  bitSet(TCCR0A, COM0B1);
  bitClear(TCCR0A, COM0B0);
  bitSet(TCCR0A, WGM01);
  bitSet(TCCR0A, WGM00);
  bitClear(TCCR0A, WGM02);
  bitClear(TCCR0B, CS02);
  bitSet(TCCR0B, CS01);
  bitSet(TCCR0B, CS00);
}

boolean swRead(int swNum){/*押されたら「0」、それ以外の時は「1」*/
    return (PIND >> swNum) & 0x01 ? OFF : ON;
}

void delayMs(unsigned int ms){
  volatile unsigned long cnt;
  for(cnt =0;cnt<(COUNT * ms); cnt++);
}
