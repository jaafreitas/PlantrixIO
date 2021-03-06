//************************** Libraries Needed To Compile The Script [See Read me In Download] ***************//
// Both below Library are custom ones [ SEE READ ME In Downloaded Zip If You Dont Know how To install] Use them or add a pull up resistor to the temp probe

#include "settings.h"

#include <OneWire.h>
#include <DallasTemperature.h>

//************************* User Defined Variables ********************************************************//


//##################################################################################
//-----------  Do not Replace R1 with a resistor lower than 300 ohms    ------------
//##################################################################################

int R1 = 300;
int Ra = 25; //Resistance of powering Pins
float calib = 0.555;

//*********** Converting to ppm [Learn to use EC it is much better**************//
// Hana      [USA]        PPMconverion:  0.5
// Eutech    [EU]          PPMconversion:  0.64
//Tranchen  [Australia]  PPMconversion:  0.7
// Why didnt anyone standardise this?

float PPMconversion = 0.7;

//*************Compensating for temperature ************************************//
//The value below will change depending on what chemical solution we are measuring
//0.019 is generaly considered the standard for plant nutrients [google "Temperature compensation EC" for more info
float TemperatureCoef = 0.019; //this changes depending on what chemical we are measuring

//********************** Cell Constant For Ec Measurements *********************//
//Mine was around 2.9 with plugs being a standard size they should all be around the same
//But If you get bad readings you can use the calibration script and fluid to get a better estimate for K
float K = 1.23;


//***************************** END Of Recomended User Inputs *****************************************************************//

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(DS18B20OneWireBus);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensorDS18B20(&oneWire);

float Temperature = 10;
float EC = 0;
float EC25 = 0;
int ppm = 0;


float raw = 0;
float Vin = 5;
float Vdrop = 0;
float Rc = 0;
float buffer = 0;

bool canReadSensorDS18B20 = false;

unsigned long previousMillisSensorDS18B20 = 0;
// Measurments at 5's Second intervals (Dont read Ec morre than once every 5 seconds).  
const long intervalSensorDS18B20 = 5000;

void GetEC();

void PrintReadings();

void setupSensorDS18B20() {
  Serial.print("DS18B20 ");

  pinMode(DS18B20TempGround , OUTPUT ); //seting ground pin as output for tmp probe
  digitalWrite(DS18B20TempGround , LOW );//Seting it to ground so it can sink current
  pinMode(DS18B20TempPower , OUTPUT );//ditto but for positive
  digitalWrite(DS18B20TempPower , HIGH );
  pinMode(DS18B20Pin, INPUT);
  pinMode(DS18B20Power, OUTPUT); //Setting pin for sourcing current
  pinMode(DS18B20Ground, OUTPUT); //setting pin for sinking current
  digitalWrite(DS18B20Ground, LOW); //We can leave the ground connected permanantly

  delay(100);// gives sensor time to settle
  sensorDS18B20.begin();
  delay(100);
  //** Adding Digital Pin Resistance to [25 ohm] to the static Resistor *********//
  // Consule Read-Me for Why, or just accept it as true
  // Taking into acount Powering Pin Resitance
  R1 = (R1 + Ra);

  Serial.println(" done.");
  canReadSensorDS18B20 = true;
}

void loopSensorDS18B20() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensorDS18B20 >= intervalSensorDS18B20) {
    previousMillisSensorDS18B20 = currentMillis;
    
    if (canReadSensorDS18B20) {
      //Calls Code to Go into GetEC() Loop [Below Main Loop] dont call this more that 1/5 hhz [once every five seconds] or you will polarise the water
      GetEC();
  
      // Cals Print routine [below main loop]
      PrintReadings();
  
    } else {
      Serial.println("DS18B20 ignored");
    }
  }
}


//************ This Loop Is called From Main Loop************************//
void GetEC() {
  //*********Reading Temperature Of Solution *******************//
  sensorDS18B20.requestTemperatures();// Send the command to get temperatures
  Temperature = sensorDS18B20.getTempCByIndex(0); //Stores Value in Variable

  //************Estimates Resistance of Liquid ****************//
  digitalWrite(DS18B20Power, HIGH);
  raw = analogRead(DS18B20Pin);
  raw = analogRead(DS18B20Pin); // This is not a mistake, First reading will be low beause if charged a capacitor
  digitalWrite(DS18B20Power, LOW);

  //***************** Converts to EC **************************//
  Vdrop = (Vin * raw) / 1024.0;
  Rc = (Vdrop * R1) / (Vin - Vdrop);
  Rc = Rc - Ra; //acounting for Digital Pin Resitance
  EC = 1000 / (Rc * K);
  //EC = 1000/(Rc*K)*calib;

  //*************Compensating For Temperaure********************//
  EC25  =  EC / (1 + TemperatureCoef * (Temperature - 25.0));
  ppm = (EC25) * (PPMconversion * 1000);
}

void PrintReadings() {
  Serial.print("DS18B20 Rc: ");
  Serial.println(Rc);
  
  Serial.print("DS18B20 EC: ");
  Serial.println(EC25);
  
  Serial.print("DS18B20 ppm:  ");
  Serial.println(ppm);
  
  Serial.print("DS18B20 *C: ");
  Serial.println(Temperature);

  /*
    //********** Usued for Debugging ************
    Serial.print("Vdrop: ");
    Serial.println(Vdrop);
    Serial.print("Rc: ");
    Serial.println(Rc);
    Serial.print(EC);
    Serial.println("Siemens");
    //********** end of Debugging Prints *********
  */
};
