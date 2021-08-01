#include <LiquidCrystal.h>
#define numOfValsRec 5
#define digitsPerValRec 1

int valsRec[numOfValsRec];
int stringLength = numOfValsRec*digitsPerValRec+1; //$00000
int counter = 0;
bool counterStart = false;
String receivedString;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Hand Motion");
  
}

void receivedData(){
  while (Serial.available())
  {
    char c = Serial.read();

    if (c=='$')
    {
      counterStart = true;
    }
    if (counterStart)
    {
      if (counterStart < stringLength)
      {
        receivedString = String(receivedString + c);
        counter++; 
      }
      if (counter >= stringLength)
      {
        for (int i = 0; i < numOfValsRec; i++)
        {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}


void loop() {
    lcd.setCursor(0, 1);
    receivedData();
    // Print 5
    if (valsRec[0] == 1 and valsRec[1] == 1 and valsRec[2] == 1 and valsRec[3] == 1 and valsRec[4] == 1 ){lcd.print("5");}else{lcd.print("");}
    // Print 1
    if (valsRec[0] == 0 and valsRec[1] == 1 and valsRec[2] == 0 and valsRec[3] == 0 and valsRec[4] == 0){lcd.print("1");}else{lcd.print("");}
    // Print 2
    if (valsRec[0] == 0 and valsRec[1] == 1 and valsRec[2] == 1 and valsRec[3] == 0 and valsRec[4] == 0){lcd.print("2");}else{lcd.print("");}
    // Print 3
    if (valsRec[0] == 0 and valsRec[1] == 1 and valsRec[2] == 1 and valsRec[3] == 1 and valsRec[4] == 0){lcd.print("3");}else{lcd.print("");}
    // Print 4
    if (valsRec[0] == 0 and valsRec[1] == 1 and valsRec[2] == 1 and valsRec[3] == 1 and valsRec[4] == 1){lcd.print("4");}else{lcd.print("");}
    
}
