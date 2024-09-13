#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>


Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int buzzer=13;
int sw1=8;
int sw2=9;
int relay=6;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  Serial.begin(9600);
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  lcd.begin(16, 2);
  while (!Serial);

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
}

void loop() 
{
  Serial.print("Temperature= "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  delay(500);
  if(mlx.readObjectTempC()>38)
  {
    digitalWrite(buzzer,1);
    Serial.println("Temperature is too high");
    lcd.setCursor(0, 0);
    lcd.print("Temp is HIGH   ");
    lcd.setCursor(0, 1);
    lcd.print("Please take care");
    
  }

  else
  {
    digitalWrite(buzzer,0);
    Serial.println("Temperature is Normal");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp is NORMAL");
    int var1=digitalRead(sw1);
    if(var1==0)
    {
      Serial.println("Please Stand here and hold the hand for sanitization");
      lcd.setCursor(0, 0);
      lcd.print("Quick Sanitizati  ");
      lcd.setCursor(0, 1);
      lcd.print("on of your hands");
      delay(1000);
      digitalWrite(relay,0);
      delay(2000);
      digitalWrite(relay,1);
    }

    else
    {
       digitalWrite(relay,1);
    }

    int var2=digitalRead(sw2);
    if(var2==0)
    {
      Serial.println("Please Wear the Mask");
      lcd.setCursor(0, 0);
      lcd.print("Please Wear the ");
      lcd.setCursor(0, 1);
       lcd.print("      MASK      ");
        delay(2000);
    }
    
  }

  
}
