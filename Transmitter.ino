#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver (2000, 10,9,10); // (uint16_t speed=2000, uint8_t rxPin=11, uint8_t txPin=12, uint8_t pttPin=10, bool pttInverted=false)

#define MQ_2 A1
uint8_t Sensor = 0; // sensor read
uint8_t Tresh = 250; // activation treshold
const char *check = "check"; // check conncetion
const char *smoke = "smoke"; // smoke detection

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init()){
         Serial.println("init failed");
         }
    pinMode(MQ_2, INPUT); // set A1 pin as input

}

void loop()
{
    Sensor = analogRead(MQ_2);
    Serial.print("Detector read host: ");
    Serial.println(Sensor);
    
    if (Sensor>Tresh){
      driver.send((uint8_t *)smoke, strlen(smoke));
      driver.waitPacketSent();
    } else {
      driver.send((uint8_t *)check, strlen(check));
      driver.waitPacketSent();     
    }
    
    delay(200);
}
