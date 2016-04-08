/****************************************************************
 * ReadSHT2x
 *  An example sketch that reads the sensor and prints the
 *  relative humidity to the PC's serial port
 *
 *  Tested with:
 *    - SHT25-Breakout Temperature Humidity sensor from Switch Science
 ***************************************************************/

#include <Wire.h>
#include <kSHT2x.h>

void setup()
{
  Wire.begin();
  Serial.begin(115200);
}

void loop()
{
  Serial.print("Humidity(%RH): ");
  Serial.print(SHT2x.GetHumidity());
  Serial.print("     Temperature(C): ");
  Serial.println(SHT2x.GetTemperature());
  
  delay(1000);
}

