#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver (2000, 11 ,9,10); // (uint16_t speed=2000, uint8_t rxPin=11, uint8_t txPin=12, uint8_t pttPin=10, bool pttInverted=false)

#define buzz 9

int32_t i=0;
int32_t tresh = 750000; // 30s 

void setup()
{
    Serial.begin(9600);
    if (!driver.init()){
         Serial.println("init failed");}
    pinMode(buzz, OUTPUT);
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN] = {};
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      Serial.print("Message: ");
      Serial.println((char*)buf);
      i=0;
      if (strstr((char*)buf,"smoke") != NULL ){
        while(1){
          digitalWrite(buzz, LOW); 
          delay(50);
          digitalWrite(buzz, HIGH);
          delay(50);
        }
      }
    } else{
      /* count iterations to detect faulty connection */
      i++; // core is 16 Mhz so it should repeat 16 times during 1 µs
    }
    if (i>tresh){
      // Run warning until reset
    while(2){
        digitalWrite(buzz, LOW); 
        delay(400);
        digitalWrite(buzz, HIGH);
        delay(1000);
      } 
    }
}
