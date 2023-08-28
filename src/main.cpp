#include <Arduino.h>

#include<SPI.h>
#include "protocentral_Max30003.h"

MAX30003 max30003;


void setup()
{
    Serial.begin(9600); //Serial begin

    pinMode(MAX30003_CS_PIN,OUTPUT);
    digitalWrite(MAX30003_CS_PIN,HIGH); //disable device

    SPI.begin(CLK_PIN, MISO, MOSI);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);

    bool ret = max30003.max30003ReadInfo();
    if(ret){
      Serial.println("Max30003 read ID Success");
    }else{

      while(!ret){
        //stay here untill the issue is fixed.
        ret = max30003.max30003ReadInfo();
        Serial.println("Failed to read ID, please make sure all the pins are connected");
        delay(10000);
      }
    }
    max30003.max30003Begin();
    // Serial.println("Initialising the chip ...");
    // max30003.max30003Begin();   // initialize MAX30003
}

void loop()
{
    unsigned int heartRate;
    unsigned int RRinterval;
    signed long ecgdata;

    max30003.getEcgSamples();
    ecgdata = max30003.ecgdata;
    ecgdata = ecgdata/10000;

    Serial.print("$");
    Serial.print(ecgdata);
    Serial.print(";");
    // Aguarde um tempo antes de fazer a próxima leitura
    delay(8);
}