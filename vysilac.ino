//vysílač

#include <VirtualWire.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void)
{
sensor_t sensor;
accel.getSensor(&sensor);
}

void setup()
{

  Serial.begin(9600);
  Serial.println("Test Gyroskopu"); 
  Serial.println("");
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  if(!accel.begin()) //inicializace senzoru
  {
    Serial.println("gyroskop neni rozpoznán");
    while(1);
  }
}

void loop()
{
  sensors_event_t event; 
  accel.getEvent(&event);
  send((int)(event.acceleration.x*3*M_PI));
  posli((int)(event.acceleration.y*3*M_PI));
  delay(200);
}

void send (int polohaX)
{
  //Serial.println(cislo);
  char znakX[22];
  sprintf(znakX, "%i", polohaX);
  vw_send(znakX, strlen(znakX));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println(znakX);
}
void posli (int polohaY)
{
  char znakY[22];
  sprintf(znakY, "%i", polohaY);
  vw_send(znakY, strlen(znakY));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println(znakY);
}



