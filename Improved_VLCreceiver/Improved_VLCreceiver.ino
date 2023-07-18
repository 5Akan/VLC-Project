#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12;

#define DELAY 2000
#define sensorPin A0
#define ID 180
//#define S1 4
#define BITLENGTH 8
int middleValue, middleValue1;
int sensorValue = 0;
float temperature;
int count = 0;
int inputByte;
long Timer = millis();

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(115200);
  //pinMode(S1, INPUT);
  pinMode(sensorPin, INPUT);
  Serial.print("RECEIVER");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RECEIVER");
  delay(1000);

  /*int r1 = readPin();
  delay(2000);
  int r2 = readPin();
  middleValue1 = (r1 + r2)/2;
  middleValue = middleValue1 + 10;
  Serial.println("The threshold is ");
  Serial.print(middleValue);
*/
  calibration_func();

}

void loop() {
  
  // put your main code here, to run repeatedly:
  //abstract into calibration_func()
  
  
  if (readPin() > middleValue){

    //delay(500);
    if (getID()){
     while(1)
    {
     mainProg();
    }
    }
  }
    
    }
 
   
    



void mainProg()
{
  
  //lcd.print("Start Receiving");
    

      
      readTemp();
    
    

    if (count > 256)
    {
      count = 0;
    }
  }

bool getID()
{
  if (readByte() == ID) {
      lcd.setCursor(0, 0);
      Serial.print("ID Detected");
      lcd.print("ID Detected");
      delay(2000);

      
      return true;
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Transmitter");
      lcd.setCursor(0, 1);
      lcd.print(" not seen.");
      Serial.println("Transmitter not seen");
      delay(1000);
    }

}
  
int readPin(){
  sensorValue = analogRead(sensorPin);
  lcd.setCursor(0, 1);
  //lcd.print(sensorValue);
  lcd.print("Await ID for 10S");
  Serial.println(sensorValue);
  return sensorValue;
  } 

int readByte()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Getting ID/Temp");
  lcd.setCursor(0, 1);
  int i, input = 0;
  for (i = 0; i < BITLENGTH; i++)
  { //Repeat for each bit
    sensorValue = analogRead(sensorPin); //Read the sensor Value
    Serial.println(sensorValue);

    if (sensorValue > middleValue)
    {

      input++;
      lcd.print("1");
      Serial.println("1");
    }
    else
    {
      lcd.print("0");
      Serial.println("0");
    }
    //Binary shift to store another bit
    input = input << 1;
    delay(DELAY);
  }
  //Return the value if input
  input = input >> 1;
  lcd.clear();
  lcd.print(input);
  Serial.println(input);
  return input;
}
void readBit()
{
  sensorValue = analogRead(sensorPin);
  lcd.print(sensorValue);
  Serial.print(sensorValue);
  if (sensorValue < 1000) {

    lcd.print("1");
    Serial.print("1");
  }
  else {

    lcd.print("0");
    Serial.print("0");
  }
  delay(DELAY);
}
void readTemp() {


  inputByte = readByte(); //Reading 1 Byte
  //Calculating temperature
  temperature = (float)inputByte * 5 / 1023;
  temperature = (temperature) * 100;
  lcd.clear();
  lcd.setCursor(0, 0);
//  lcd.print(++count); // Sending the value of temperature
  lcd.print ("Temperature is");
  lcd.setCursor(0, 1);
  lcd.print(temperature); // Sending the value of temperature
  lcd.print(" 'C");

  Serial.print(++count); // Sending the value of temperature
  Serial.print (".temperature is");
  Serial.print(temperature); // Sending the value of temperature
  Serial.println(" 'C");
  delay(1000);
  //might uncomment later delay(2000); // transmitter delay
}

int calibration_func(){
  
  /*middleValue1 = readPin();
  if((millis()-Timer)<1000){
  delay(500);  
  middleValue1 = max(readPin(),middleValue1);

  }
  */
  middleValue= getMaxValue() + 25;

  Serial.print("The threshold is ");
  Serial.println(middleValue);
  return middleValue;
}

int getMaxValue(){
  r1 = readPin();
  delay(500);
  r2 = readPin();
  delay(500);
  r3 = readPin();
  delay(500);
  r4 = readPin();
  delay(500);
  r5 = readPin();
  delay(500);
  r6 = readPin();
  delay(500);
  r7 = readPin();
  delay(500);
  r8 = readPin();
  delay(500);
  r9 = readPin();
  delay(500);
  r10 = readPin();
  delay(500);
  r11 = readPin();
  delay(500);
  r12 = readPin();
  delay(500);

  int pinValue[12] = {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12};

  int maxVal = pinValue[0];

  for (int i=0; i<(sizeof(pinValue)/sizeof(pinValue[0])); i++ ){
    maxVal = max(pinValue[i],maxVal);
  }
  


  return maxVal;


}
