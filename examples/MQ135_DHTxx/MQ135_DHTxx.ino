/*-data-type------size---------description----------------------
  boolean        (8 bit)   -  [true/false]
  byte           (8 bit)   -  [0-255] unsigned number
  char           (8 bit)   -  [-128 to 127] signed number
  unsigned char  (8 bit)   -  [-128 to 127] signed number
  word           (16 bit)  -  [0-65535] unsigned number
  unsigned int   (16 bit)  -  [0-65535] unsigned number
  int            (16 bit)  -  [-32768 to 32767] signed number
  unsigned long  (32 bit)  -  [0-4,294,967,295] unsigned number usually for millis
  long           (32 bit)  -  [-2,147,483,648 to 2,147,483,647] signed number
  float          (32 bit)  -  [-3.4028235E38 to 3.4028235E38] signed number
  uint8_t        (8 bit)   -  [0-255] unsigned number
  int8_t         (8 bit)   -  [-127 - 127] signed number
  uint16_t       (16 bit)  -  [0-65,535] unsigned number
  int16_t        (16 bit)  -  [-32,768 - 32,767] signed number
  uint32_t       (32 bit)  -  [0-4,294,967,295] unsigned number
  int32_t        (32 bit)  -  [-2,147,483,648 - 2,147,483,647] signed number
  uint64_t       (64 bit)  -  [0-18,446,744,073,709,551,615] unsigned number
  int64_t        (64 bit)  -  [−9,223,372,036,854,775,808 - 9,223,372,036,854,775,807] signed number
  --------------------------------------------------------------
  camelCase                -  anything that changes
  snake_case               -  variable's that are exclusive in a function
  Snake_Case               -  CLASS/struct exclusave varables/functions
  iNVERTEDcAMELcASE        -  outside code that is being accessed [database]
  SNake_CAse               -  duplicate varables inside the case function [frequently used in library names]
  ALL_CAPS                 -  const varable names or defines
  ------------- by jediRick & RefreshMyMind --------------------
*/

#include <Arduino.h>
#include <MQ135.h>
#include "DHT.h"  // Lib used https://github.com/adafruit/DHT-sensor-library.git 
 #include <Adafruit_Sensor.h>
#define mq135read A0 //  Initialization of the pin A0
#define dhtpin 2

// Uncomment whatever module you're using!
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// #define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(dhtpin, DHTTYPE); // Initialize DHT sensor.
MQ135 mq135(mq135read);   // Initialize MQ135 sensor.

void setup()
{
    Serial.begin(9600); // Setting baud rate
}

void loop()
{

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    float rzero = mq135.getRZero();
    float correctedRZero = mq135.getCorrectedRZero(temperature, humidity); // Passing the t and h values.
    float resistance = mq135.getResistance();
    float ppm = mq135.getPPM();
    float correctedPPM = mq135.getCorrectedPPM(temperature, humidity); // Passing the t and h values.

    Serial.print("Temperature: ");
    Serial.println(temperature); // printing temperature data from dhtxx.
    Serial.print("Humidity: ");
    Serial.println(humidity); // printing humidity data from dhtxx.

    Serial.print("PPM: ");
    Serial.print(correctedPPM); // printing the current PPM values it will take few min to settle.
    Serial.println("ppm");

    delay(1000); // Delay of 1Sec.
}