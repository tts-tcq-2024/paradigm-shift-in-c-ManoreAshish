#include <stdio.h>
#include <assert.h>

float temperature=0;
float soc=0;
float chargeRate=0;
int SOCupperlimit=80;
int SOClowerlimit=20;
int isTempWithinRange( float temperature);
int isSOCWithinRange (float soc);
int isChargeRateValid (float chargeRate);

int batteryIsOk(float temperature, float soc, float chargeRate) 
{
  if(isTempWithinRange(temperature))
   return 1; 
  else
   return 0;
}

int isTempWithinRange( float temperature)
{
  if((temperature>0 ) && (temperature<45))
    return isSOCWithinRange(soc);
  else
    return 0;
}

int isSOCWithinRange (float soc)
{
  if((soc<20) && (soc<SOCupperlimit))
  {
    SOCWarningIndicator();
    return isChargeRateValid(chargeRate);
  }
  else 
    return 0;
}

int isChargeRateValid (float chargeRate)
{
  if(chargeRate<0.8)
    return 1;
  else 
    return 0;
}

void SOCWarningIndicator()
{
  int SOCTolerance=0;
  SOCTolerance=(SOCupperlimit *5)/100;
  
  if((SOCupperlimit-SOCTolerance)  <soc< (SOCupperlimit))
    printf("Approaching charge-peak");
  if((SOClowerlimit)<soc<(SOClowerlimit+SOCTolerance))
    printf("Approaching discharge");
  
}


int main() 
{
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
