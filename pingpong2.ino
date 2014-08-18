/// @dir pingPong
/// Demo of a sketch which sends and receives packets.
// 2010-05-17 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// with thanks to Peter G for creating a test sketch and pointing out the issue
// see http://jeelabs.org/2010/05/20/a-subtle-rf12-detail/

#include <JeeLib.h>

MilliTimer sendTimer;
//char payload[] = "Hello!";
byte needToSend;
typedef struct // create structure - a neat way of packaging data for RF comms
{ 
  int flat2, flon2, flat3, flon3;
} 
payload;      
payload test, test2;  
float flat4 = 7.49899;
float flon4 = 9.000789;

void setup () {
    Serial.begin(57600);
    Serial.println(57600);
    Serial.println("Send and Receive");
    rf12_initialize(1, RF12_433MHZ, 33);

}

void loop () {
  test2.flat3= flat4+0.0000001;
  test2.flon3= flon4+0.0000002;
    if (rf12_recvDone() && rf12_crc == 0) {
        Serial.print("OK ");
        for (byte i = 0; i < rf12_len; ++i)
            Serial.print(rf12_data[i]);
            Serial.print("Lat1: ");
            Serial.print(test.flat2);
            Serial.print(" Long1: ");
            Serial.print(test.flon2);
        Serial.println();
        delay(100); // otherwise led blinking isn't visible
    }
    
    if (sendTimer.poll(3000))
        needToSend = 1;

    if (needToSend && rf12_canSend()) {
        needToSend = 0;
        
        rf12_sendStart(0, &test2, sizeof test2);
        delay(100); // otherwise led blinking isn't visible

    }
}
