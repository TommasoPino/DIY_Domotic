#include <wiringPi.h>
#include <stdio.h>
int main (void)
{
  int pressed;
  int valueNew, valueOld;
  valueNew = 0;
  valueOld = 0;
  pressed = 0;
  printf("Start program\n");
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  pinMode (1, INPUT ) ;
  for (;;)
  {
    valueNew = digitalRead(1);
    delay(50);
    if(valueNew != valueOld)
    {
      digitalWrite(0,valueNew);
      valueOld = valueNew;
    }
  }
  return 0 ;
}
