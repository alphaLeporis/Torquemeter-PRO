#include "HX711.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



//load cell
float calibration_factor = 500; //gevonden via een kalibratie code
#define LOADCELL_DOUT_PIN  5 // verander naar 3 als er problemen zijn
#define LOADCELL_SCK_PIN  4 // verander naar 2 als er problemen zijn
HX711 scale;

int koppel;
float arm = 140; //lengte arm in mm
int vermogen;
int horsepower;
float kracht;



//rpm sensor
const int RPM_pin = 7; //pin op arduino voor RPM sensor
int triggers = 0;
unsigned long elapsedTime;
int laststate =0;
const unsigned long sampleTime = 1000;
int rpmMax=0;
int rpm = 0;


//beeld
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display



void setup() {
  Serial.begin(9600);


  //loadcell
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average();

  //scherm
  lcd.init(); // initiatie van de scherm
  lcd.backlight();

  //rpm
  pinMode(RPM_pin, INPUT);

  //knop
  pinMode(2, INPUT_PULLUP);  


}

void loop() {

  Koppel();
  Serial.print(";");
  RPM();

  vermogen = (koppel * rpmMax)/9.5488 ;
  //P = T * w
  //w = 2 * pi * n / 60 met n = RPM 
  
  horsepower = vermogen/1341.02;
  
  int knop = digitalRead(2); 
  if (knop == HIGH) { //als knop niet is ingedrukt
  
  //koppel
    lcd.setCursor(0,0); //coördinaat vanaf waar het mag printen
    lcd.print("KOPPEL= ");

    lcd.setCursor(8,0);
    lcd.print(koppel);
    if (koppel < 0) {
      lcd.setCursor(8,0);
      lcd.print("0    ");}
    else if (koppel < 10) {
      lcd.setCursor(9,0);
      lcd.print("  ");
    } else if (koppel < 100) {
      lcd.setCursor(10,0);
      lcd.print("  ");}
    
    lcd.setCursor(13,0);
    lcd.print("Nmm");

    //RPM
    lcd.setCursor(0,1);
    lcd.print("RPM   = ");

    lcd.setCursor(8,1);
    lcd.print(rpmMax);
    if (rpmMax < 10) {
      lcd.setCursor(9,1);
      lcd.print("  ");
    } else if (rpmMax < 100) {
      lcd.setCursor(10,1);
      lcd.print("  ");}
      else if (rpmMax < 1000) {
      lcd.setCursor(11,1);
      lcd.print("  ");
      }

    lcd.setCursor(13,1);
    lcd.print("rpm");  }

    
    else{            //als knop is ingedrukt
      lcd.setCursor(0,0);
      lcd.print("vermogen= ");

    lcd.setCursor(9,0);
    lcd.print(vermogen);
    if (vermogen < 10) {
      lcd.setCursor(10,0);
      lcd.print("  ");
    } else if (vermogen < 100) {
      lcd.setCursor(11,0);
      lcd.print("  ");}

    lcd.setCursor(14,0);
    lcd.print("  ");

    lcd.setCursor(13,0);
    lcd.print("W"); 
  
    lcd.setCursor(0,1);
    lcd.print("horse  = ");

    lcd.setCursor(9,1);
    lcd.print(horsepower);
    if (horsepower < 10) {
      lcd.setCursor(10,1);
      lcd.print("  ");
    } else if (horsepower < 100) {
      lcd.setCursor(11,1);
      lcd.print("  ");}
  
    lcd.setCursor(15,1);
    lcd.print("  ");

    lcd.setCursor(13,1);
    lcd.print("HP");  }

      delay(100); //add a delay

}

void Koppel()
{
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  
  kracht = ((scale.get_units())/1000 * 9.81);
  koppel = (kracht * arm) ;
  //Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
  //Serial.println(" g");
  Serial.print(koppel);
  //Serial.print(" Nmm;");


  
}


  void RPM() {
  //Serial.print(rpmMax);
  //Serial.println(" RPM");

  Serial.println(rpm);
  rpm=rpmGet();
  //if (rpm > rpmMax)
  //{
    rpmMax = rpm;
  //}
    }

int rpmGet(){
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  while (currentTime <= sampleTime)
  {
    int val = digitalRead(RPM_pin);
    if(!val)
    {
      if(laststate){
        triggers++;
        laststate=0;
        }
    }
  else {laststate = 1;}
  currentTime = millis() - startTime;
  }

  int countRpm = (triggers*60)/9;
  triggers=0;
  return countRpm;
}
