#include <wiringPi.h>
#include <stdio.h>
int main (void)
{
  const int pressed = 1;
  const int realised = 0;
  int status, stsButton;
  int valueNew, valueOld;
  valueNew = 0;
  valueOld = 0;
  stsButton = 0;
  //printf("Start program\n");
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  pinMode (1, INPUT ) ;
  for (;;)
  {
    valueNew = digitalRead(1);
    delay(50);
    if(valueNew != valueOld)
    {
      switch(valueNew)
	{
	  case(1):
	    status = pressed;
	    break;
	  case(0):
            if(status == pressed)
	    {
		if(stsButton == 0)
		{
		  digitalWrite(0,HIGH);
		  stsButton = 1;
		}
		else if(stsButton == 1)
		{
		  digitalWrite(0,LOW);
		  stsButton = 0;
		}
	    }
	    status = realised;
	    break;
	}
	valueOld = valueNew;
    }
  }
  return 0 ;
}
