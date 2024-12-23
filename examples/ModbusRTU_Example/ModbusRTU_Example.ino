#include "ModbusRTU.h"

ModbusRTU::ModbusRTUClient<16> client;

unsigned short encoder = 0;
unsigned short analogOut[3];
bool digitalOut[4];
bool digitalIn[6];
unsigned short analogIn[2];

void setup()
{
  client.begin(115200);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  
  client.update();
  
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, OUTPUT);
  
  client.addCoil(&digitalOut[0],0x0000);
  client.addCoil(&digitalOut[1],0x0001);
  client.addCoil(&digitalOut[2],0x0002);
  client.addCoil(&digitalOut[3],0x0003);

  client.addDiscreteInput(&digitalIn[0], 0x1000);
  client.addDiscreteInput(&digitalIn[1], 0x1001);
  client.addDiscreteInput(&digitalIn[2], 0x1002);
  client.addDiscreteInput(&digitalIn[3], 0x1003);
  client.addDiscreteInput(&digitalIn[4], 0x1004);
  client.addDiscreteInput(&digitalIn[5], 0x1005);

  client.addInputRegister(&analogIn[0], 0x2000);
  client.addInputRegister(&analogIn[1], 0x2001);

  client.addHoldingRegister(&analogOut[0], 0x3000);
  client.addHoldingRegister(&analogOut[1], 0x3001);
  client.addHoldingRegister(&analogOut[2], 0x3002);
}

void loop() 
{
  digitalIn[0] = !digitalRead(A0);
  digitalIn[1] = !digitalRead(A1);
  digitalIn[2] = !digitalRead(A2);
  digitalIn[3] = !digitalRead(A3);
  digitalIn[4] = !digitalRead(A4);
  digitalIn[5] = !digitalRead(A5);
  
  analogIn[0] = analogRead(A7);
  analogIn[1] = analogRead(A6);
  
  client.update();
  
  analogWrite(10, analogOut[0]);
  analogWrite(9, analogOut[1]);
  analogWrite(6, analogOut[2]);
  
  digitalWrite(7, digitalOut[0]);
  digitalWrite(11, digitalOut[1]);
  digitalWrite(5, digitalOut[2]);
  digitalWrite(8, digitalOut[3]);
}
