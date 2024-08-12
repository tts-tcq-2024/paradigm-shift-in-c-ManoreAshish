#include <stdio.h>
#include <assert.h>

float temperature=0;
float soc=0;
float chargeRate=0;

float Tempupperlimit=45;
float Templowerlimit=0;
float SOCupperlimit=80;
float SOClowerlimit=20;
float ChargeRateUpperlimit=0.8

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
  if((temperature>Templowerlimit) && (temperature<Tempupperlimit))
  {
    TempWarningIndicator();
    return isSOCWithinRange(soc);
  }
  else
    return 0;
}

int isSOCWithinRange (float soc)
{
  if((soc<SOClowerlimit) && (soc<SOCupperlimit))
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
  {
    ChargeRateWarningIndicator();
    return 1;
  }
  else 
    return 0;
}

void TempWarningIndicator()
{
  float TempTolerance=0;
  TempTolerance=(Tempupperlimit *5)/100;
  if((Tempupperlimit-TempTolerance) < temperature < (Tempupperlimit))
    printf("High Temp Detected");
  if((Templowerlimit) < temperature < (Templowerlimit+TempTolerance))
    printf("Low Temp detected"); 
}

void SOCWarningIndicator()
{
  float SOCTolerance=0;
  SOCTolerance=(SOCupperlimit *5)/100;
  if((SOCupperlimit-SOCTolerance) < soc < (SOCupperlimit))
    printf("Approaching charge-peak");
  if((SOClowerlimit) < soc < (SOClowerlimit+SOCTolerance))
    printf("Approaching discharge"); 
}

void ChargeRateWarningIndicator()
{
  float ChargeRateTolerance=0;
  ChargeRateTolerance=(ChargeRateUpperlimit *5)/100;
  if((ChargeRateUpperlimit-SOCTolerance) < chargeRate < (ChargeRateUpperlimit))
    printf("Approaching threshold of Valid charge rate");
}


int main() 
{
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
