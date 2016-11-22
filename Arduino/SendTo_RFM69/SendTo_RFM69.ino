/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/
#include <RFM69.h>
#include <SPI.h>

#define NODEID      99
#define NETWORKID   100
#define GATEWAYID   98
#define FREQUENCY   RF69_868MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "sampleEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200
#define ACK_TIME    30  // # of ms to wait for an ack

int TRANSMITPERIOD = 300; //transmit a packet to gateway so often (in ms)
byte sendSize=0;
boolean requestACK = false;

RFM69 radio;

typedef struct {
  int           nodeId; //store this nodeId
  unsigned long uptime; //uptime in ms
  float         temp;   //temperature maybe?
} Payload;
Payload theData;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(9, OUTPUT);
  Serial.begin(SERIAL_BAUD);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Init complete ready for RFM69");
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  Serial.println("Radio initialised");
//  radio.setHighPower(); //uncomment only for RFM69HW!
  Serial.println("Radio High Power");
  radio.encrypt(KEY);
  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
  Serial.println("Radio init complete.");
  
}

void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second


  //check for any received packets
  if (radio.receiveDone())
  {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.readRSSI());Serial.print("]");

    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.print(" - ACK sent");
      delay(10);
    }
    Blink(LED,5);
    Serial.println();
  }

  char input = Serial.read();

  switch(input) {
    case -1:
      break;
    case 'r':
      radio.readAllRegs();
      break;
    case 'c':
      if(radio.canSend()) {
        Serial.println("CAN send");
      } else {
        Serial.println("CANNOT send");
      }
      break;
    case 's':
      Serial.println("Sending message");
      //fill in the struct with new values
      theData.nodeId = NODEID;
      theData.uptime = millis();
      theData.temp = 91.23; //it's hot!
    
      Serial.print("Sending struct (");
      Serial.print(sizeof(theData));
      Serial.print(" bytes) ... ");
//      radio.sendFrame(GATEWAYID, (const void*)(&theData), sizeof(theData));
      digitalWrite(9, HIGH);
      radio.send(GATEWAYID, (const void*)(&theData), sizeof(theData));
      digitalWrite(9, LOW);
  //    if (radio.sendWithRetry(GATEWAYID, (const void*)(&theData), sizeof(theData)))
  //      Serial.print(" ok!");
  //    else Serial.print(" nothing...");
      Serial.println();
      break;
    default:
      Serial.print("Got char:");
      Serial.print(int(input));
      Serial.println("");
      break;
  }
}
