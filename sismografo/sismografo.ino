#include <Wire.h> 
 
const int MPU = 0x68;   //Default address of I2C for MPU 6050 
const int TransistorPin = 13; 
int16_t AcX, AcY, AcZ; 
 
 
int giallo = 11; 
int verde = 10; 
 
void setup() { 
  pinMode(13, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(TransistorPin, OUTPUT); 
  Wire.begin();                   // Wire library initialization 
  Wire.beginTransmission(MPU);    // Begin transmission to MPU 
  Wire.write(0x6B);               // PWR_MGMT_1 register 
  Wire.write(20);                  // MPU-6050 to start mode 
  Wire.endTransmission(true); 
  Serial.begin(9600); 
  digitalWrite(TransistorPin, LOW); 
} 
 
void loop() { 
 
  Wire.beginTransmission(MPU);      // Start transfer 
  Wire.write(0x3B);                 // register 0x3B (ACCEL_XOUT_H), records data in queue 
  Wire.endTransmission(false);      // Maintain connection 
  Wire.requestFrom(MPU, 30, true);  // Request data to MPU 
  //Reads byte by byte 
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_ 1\XOUT_H) & 0x3C (ACCEL_XOUT_L) 
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L) 
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
 
  //Prints values on Serial 
    Serial.print(AcX); 
    Serial.print(","); 
    Serial.print(AcY); 
    Serial.print(","); 
    Serial.println(AcZ); 
 
 
  if (AcX > 100) { 
    Serial.println("Innescato"); 
    digitalWrite(TransistorPin, HIGH); 
  } 
  else {   
    digitalWrite(TransistorPin, LOW); 
  } 
   
  if (AcY > 100) { 
    Serial.println("Innescato"); 
    digitalWrite(TransistorPin, HIGH); 
  } 
  else {   
    digitalWrite(TransistorPin, LOW); 
  } 
   
  if (AcX > -100) { 
    Serial.println("Innescato"); 
    digitalWrite(verde, HIGH); 
  } 
  else { 
    digitalWrite(verde, LOW); 
  } 
   
  delay(20); 
 }