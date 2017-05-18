#include <wiringPi.h>
#include <stdio.h>
int main (void)
{
  printf("Start program\n");
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    printf("Set pin at HIGH level\n");
    digitalWrite (0,  LOW) ; delay (500) ;
    printf("Set pin at LOW level\n");
  }
  return 0 ;
}
