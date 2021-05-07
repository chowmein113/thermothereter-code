const int votageInputPin =A0;
const float arduinoVoltage = 5.0;//Operating voltage of Arduino. either 3.3V or 5.0V 
#include <Wire.h>
#include <Adafruit_MLX90614.h>
//int temptype = 1;
char *typeName[]={"Object","Ambient"};
//Serial Code
#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);
String str;
float sen;
String c;
//
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float tempObjecC, tempObjecF, tempAmbientC ,tempAmbientF, tempObjecK, tempAmbientK;

void setup() {
  pinMode(votageInputPin, INPUT);
  Serial.begin(115200);
  // Cereal Code
  espSerial.begin(115200);
  //
  Serial.println("Robojax MLX90614 test");  

  mlx.begin();  
delay(2000);

  
}

void loop() {
  //Robojax Example for MLX90614-DCI medical accuracy long range version
 // printTemp('C');
//  printTemp('D');
//  
  printTemp('F');  
  
//  printTemp('G'); 
 // if( getTemp('C')>40)
 // {
    //do something here
 // }
  
//  printTemp('K');   
//  printTemp('L');  
 // Serial.println("======");
  printVoltage();// this line will read the input voltage and dispalys it on serial monitor
  
  //Cereal Code
  sen=getTemp('F');
    //str=String("Coming from Arduino: ")+String(sen)
   str=String(0)+String(sen);
    //+String("\xC2\xB0")+String('F')+String('\n');
    espSerial.println(str);
   
   
    //
    delay(10);
  //Robojax Example for MLX90614-DCI medical accuracy long range version

}

/*
 * @brief returns temperature or relative humidity
 * @param "type" is character
 *     C = Object Celsius
 *     D = Ambient Celsius
 *     
 *     K = Object Keliven
 *     L = Ambient in Keilven
 *     
 *     F = Object Fahrenheit
 *     G = Ambient in Fahrenheit

 * @return returns one of the values above
 * Usage: to get Fahrenheit type: getTemp('F')
 * to print it on serial monitor Serial.println(getTemp('F'));
 * Written by Ahmad Shamshiri on Mar 30, 2020. 
 * in Ajax, Ontario, Canada
 * www.Robojax.com 
 */
float getTemp(char type)
{
   //Robojax Example for MLX90614-DCI medical accuracy long range version
  float value;
   tempObjecC = mlx.readObjectTempC();//in C object
   tempAmbientC = mlx.readAmbientTempC();

   tempObjecF = mlx.readObjectTempF(); //Fah. Object
   tempAmbientF = mlx.readAmbientTempF();//Fah Ambient

    dependencyComp();
      
   if(type =='F')
   {
    value = tempObjecF;
   }else if(type =='G')
   {
    value = tempAmbientF;
   }else if(type =='K')
   {
    value = tempObjecC + 273.15;// Object Kelvin
   }else if(type =='L')
   {
    value = tempAmbientC + 273.15;//Ambient Kelvin
   }else if(type =='C')
   {
    value = tempObjecC;
   }else if(type =='D')
   {
    value = tempAmbientC;
   }
   return value;
    //Robojax Example for MLX90614-DCI medical accuracy long range version
}//getTemp



/*
 * fixes the voltage dependancey of measurement
 * This funciton updates the reading of temperature by reading 
 * the power supply voltage and compensating it.
 * see page 37 of datasheet here: https://robojax.com/learn/arduino/robojax_MLX90614_Datasheet-Melexis.pdf
 * T=T0 - (VCC-3) *0.6
 */
void dependencyComp()
{
  //Robojax Example for MLX90614-DCI medical accuracy long range version
 // int value = analogRead(votageInputPin);// read the input
  //float voltage =  value * (arduinoVoltage / 1023.0);//get the voltage from the value above
  //Serial.println(voltage);
  double voltage=getvoltage();
  tempObjecC = tempObjecC - (voltage -3) * 0.6;
  tempAmbientC = tempAmbientC - (voltage -3) * 0.6;  

  tempObjecF = tempObjecF - (voltage -3) * 0.6;
  tempAmbientF = tempAmbientF - (voltage -3) * 0.6;    

  tempObjecK = tempObjecK - (voltage -3) * 0.6;
  tempAmbientK = tempAmbientK - (voltage -3) * 0.6;     
  //Robojax Example for MLX90614-DCI medical accuracy long range version
}//dependencyComp() ends here


/*
 * @brief nothing
 * @param "type" is character
 *     C = Object Celsius
 *     D = Ambient Celsius
 *     
 *     K = Object Keliven
 *     L = Ambient in Keilven
 *     
 *     F = Object Fahrenheit
 *     G = Ambient in Fahrenheit

 * @return prints temperature value in serial monitor
 * Usage: to get Fahrenheit type: getTemp('F')
 * to print it on serial monitor Serial.println(getTemp('F'));
 * Written by Ahmad Shamshiri on Mar 30, 2020 at 21:51
 * in Ajax, Ontario, Canada
 * www.Robojax.com 
 */
void printTemp(char type)
{
  //Robojax Example for MLX90614-DCI medical accuracy long range version
  float tmp =getTemp(type);

  if(type =='C')
  {
    Serial.print(typeName[0]);
    Serial.print(" ");    
    Serial.print(tmp);
    printDegree();     
    Serial.println("C");
  }else if(type =='D')
  {
    Serial.print(typeName[1]);
    Serial.print(" ");     
    Serial.print(tmp);
    printDegree();     
    Serial.println("C");
  }else if(type =='F')
  {
    Serial.print(typeName[0]);
    Serial.print(" ");     
    Serial.print(tmp);
    printDegree();     
    Serial.println("F");
  }else if(type =='G')
  {
    Serial.print(typeName[1]);
    Serial.print(" ");     
    Serial.print(tmp);
    printDegree();      
    Serial.println("F");
  }

  else if(type =='K')
  {
    Serial.print(typeName[0]);
    Serial.print(" ");     
    Serial.print(tmp);  
    printDegree();      
    Serial.println(" K");
  }  
  else if(type =='L')
  {
    Serial.print(typeName[1]);
    Serial.print(" ");     
    Serial.print(tmp);  
    printDegree();      
    Serial.println(" K");
  }

//Robojax Example for MLX90614-DCI medical accuracy long range version
}//printTemp(char type)

/*
 * printDegree()
 * prints degree symble on serial monitor
 * written by Ahmad Shamshiri for Robojax.com 
 * 
 */
void printDegree()
{
     Serial.print("\xC2\xB0");     
}

/*
 *  printVoltage()
 *  prints voltage at pin "voltageInputPin"
 *  on serial monitor.
 */
void printVoltage()
{
  //Robojax Example for MLX90614-DCI medical accuracy long range version
 // const int value = analogRead(votageInputPin);// read the input
// int value = getvoltage();
 // const double voltage =  value * (arduinoVoltage / 1023.0);//get the voltage from the value above
 double voltage=getvoltage();
  Serial.print("Voltage: ");
  Serial.print(voltage);  
  Serial.println("V");
  //Robojax Example for MLX90614-DCI medical accuracy long range version
}// printVoltage()
double getvoltage(){

 double value = analogRead(votageInputPin);
//String boat=String("analog:")+String(" ")+String(value);
//Serial.println(boat);
  const double voltage =  value * (arduinoVoltage / 1023.0);//get the voltage from the value above
return voltage;
}

 
