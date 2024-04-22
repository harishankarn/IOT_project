#define IN1 6
#define IN2 5
#define IN3 4
#define IN4 3

#define ENA 7
#define ENB 2

#define ledPin 13
#define LEDB 14
#define LEDG 15
#define LEDR 16

#define Speed 200

#include <ArduinoBLE.h>

//custom 128-bit UUID, read and writable by central
BLEService MotorService("19b10000-e8f2-537e-4f6c-d104768a1214");
BLEService UltraSonicService("19b10000-e8f2-537e-4f6c-d104768a1215");

//setting read and write characteristics 
//BLEByteCharacteristic switchCharacteristic("19b10000-e8f2-537e-4f6c-d104768a1214", BLERead | BLEWrite);
BLEIntCharacteristic switchCharacteristic("19b10000-e8f2-537e-4f6c-d104768a1214", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
 
  // motor controls
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,Speed);
  analogWrite(ENB,Speed);

  
  // BLE initialization
  if (!BLE.begin()) { 
    Serial.println("Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName("IOT_Project");
  BLE.setLocalName("IOT_Project");
  BLE.setAdvertisedService(MotorService);

  // add the characteristic to the service
  MotorService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(MotorService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();
  Serial.println("BLE Peripheral");
}

void loop() {
  // wait for a Bluetooth®️ Low Energy central
  BLEDevice central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {

      Stop();
      if (switchCharacteristic.written())
      {
      int value = switchCharacteristic.value();
      //Serial.println(value);
      if (value>0)
      {
        Serial.println(value);
        switch (value){
          case 49:{
            Forward();
            Serial.println("Forward");
            delay(150);
            break;
          }
          case 50:{
            Backward();
            Serial.println("Backward");
            delay(150);
            break;
          }
          case 51:{
            Left();
            Serial.println("Left");
            delay(150);
            break;
          }
          case 52:{
            Right();
            Serial.println("Right");
            delay(150);
            break;
          }
          case 53:{
            Stop();
            Serial.println("Stop");
            break;
          }
          default:{
            Stop();
            Serial.println("Default Stop");
            break;
          }
        }
      }
      }
    }

    // the central has disconnected
    Serial.println("Disconnected from central: ");
  }
}

void Backward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Forward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void Left() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Right() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}