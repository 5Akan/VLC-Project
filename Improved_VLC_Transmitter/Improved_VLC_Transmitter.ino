#include <LiquidCrystal.h>
#define DELAY 2000
 //Output pin where LED is connected
#define ID 180 //ID of Receiver
#define BITLENGTH 8 //1 Byte 
#define FIRSTBIT pow(2,(BITLENGTH-1))//MSB Value
#define TRUE 1
#define TEMPERATURE A0
//#define proDelay 1000
int LED = 2;
int i, j;
int count = 0;
long Timer = millis();
float voltage;
void writeByte(int);
int counter = 0;

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() { //Setting the LED as Output
  lcd.begin(16, 2);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
   digitalWrite(LED, LOW);
  lcd.setCursor(0,0);
  lcd.print("Transmitting ID..");
  digitalWrite(LED, LOW);
  delay(2000);
  //delay(500);
  lcd.setCursor(0, 1);
  writeByte(ID); //Sending ID of Receiver
  lcd.print("ID Sent");
  delay(2000);
  Serial.println(ID);

}

void loop() {
  if ((millis() - Timer) < 900000)
  {
    //delay(proDelay);

    i = analogRead(TEMPERATURE); //Reading the temperature(i.e. the voltage drop on the sensor)
    Serial.println(i);
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Sending Temp...");
     lcd.setCursor(0, 1);
     writeByte(i);//sending the temperature to the receiver
     lcd.print("ID Sent");
     
    float temperature = (float)i * 5 / 1023;
    temperature = (temperature) * 100;
    Serial.print(++count); // Sending the value of temperature
    Serial.print (" : The tempereature is ");
    Serial.print(temperature); // Sending the value of temperature
    Serial.println(" 'C");

    lcd.clear();
    lcd.setCursor(0, 0);
    //lcd.print(++count); // Sending the value of temperature
    lcd.print ("The temp is ");
    lcd.setCursor(0, 1);
    lcd.print(temperature); // Sending the value of temperature
    lcd.print(" 'C");
    delay(1000);
    if (count > 256) {
      count = 0;
    }
  }
}

//Sending 1byte number
void writeByte(int decimal) {
  //converting the decimal value to binary and sending 8 bit information from MSB to LSB
  int i, binary;

  for (i = 0; i < BITLENGTH; i++) {
    binary = (int)decimal / FIRSTBIT; //Getting the first binary bit value
    decimal = (decimal & ((int)FIRSTBIT - 1)); //Setting the first bit to zero
    decimal = decimal << 1; //Shift all bits by one to left
    if (binary == TRUE) {
      digitalWrite(LED, HIGH);
      lcd.print("1");
      Serial.print("1");
    } else {
      digitalWrite(LED, LOW);
      lcd.print("0");
      Serial.print("0");
    }
    delay(DELAY);
  }
  //Serial.println();
  digitalWrite(LED, LOW);
}
