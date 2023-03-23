#include <Arduino.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

#define CANint 2
#define LED2 8
#define LED3 7

unsigned char len = 0;
unsigned char buf[8];
unsigned long ID = 0;
unsigned long line = 0;

MCP_CAN CAN0(17); // Set CS to pin 17

unsigned long time;
void setup() {
  Serial.begin(115200);
  
  while (!Serial) {
    Serial.print("I will wait here forever...");
      delay(1000);
  };
  
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(CANint, INPUT);
  digitalWrite(LED2, LOW);
  
  Serial.println("CAN init:");

  if (CAN0.begin(CAN_500KBPS) == CAN_OK) {
    Serial.println("Can Init Success");
  } else {
    Serial.println("Can Init Failed");
    while (1) {
      Serial.print("I will wait here forever...");
      delay(1000);
    }
  }

  Serial.println("Good to go!");
}

void loop() {
  time = millis();
  
  if(CAN_MSGAVAIL == CAN0.checkReceive() && line < 10000) {          // Check to see whether data is read
    CAN0.readMsgBufID(&ID, &len, buf);    // Read data

// probably not
// 520
// 521
// 528
// 628
// 629
// 630
// 631
// 1280
// 1281
// 1283
// 1304
// 1328
// 1344
// 1360
// 1381
// 1383
// 1385
// 1392
// 1417
// 1536
// 1539
// 1888
// 1889
// 1890
// 1891

//Add this line back in if you want to filter traffic    if(ID == 1201) { //39
    // if(ID != 520 &&
    //    ID != 521 &&
    //    ID != 528 &&
    //    ID != 628 &&
    //    ID != 629 &&
    //    ID != 630 &&
    //    ID != 631 &&
    //    ID != 1280 &&
    //    ID != 1281 &&
    //    ID != 1283 &&
    //    ID != 1304 &&
    //    ID != 1328 &&
    //    ID != 1344 &&
    //    ID != 1360 &&
    //    ID != 1381 &&
    //    ID != 1383 &&
    //    ID != 1385 &&
    //    ID != 1392 &&
    //    ID != 1417 &&
    //    ID != 1536 &&
    //    ID != 1539 &&
    //    ID != 1888 &&
    //    ID != 1889 &&
    //    ID != 1890 &&
    //    ID != 1891) {
    if(ID == 1891) {
      line = line + 1;
      
      Serial.print(ID,DEC);
      Serial.print("\t");
      Serial.print(ID,HEX); // Output HEX Header
      Serial.print("\t");
      
      for(int i = 0; i<len; i++) { // Output 8 Bytes of data in Dec
        Serial.print(buf[i]);
        Serial.print("\t");
      }
      
      Serial.print(time); // Timestamp
      Serial.print("\t");
      Serial.println(line); // Line Number
   }
  }
  delay(10);
}