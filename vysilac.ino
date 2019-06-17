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
  double* message = new double(event.acceleration.x*3*M_PI);
  send(message);
  delay(1000);
}

void send (double *message)
{
  
  //const char *zprava = "";
  //char znaky [128];
//  snprintf(znaky, sizeof(znaky), "%ld", message);
  Serial.println(*message);
  vw_send((uint8_t *)message, sizeof(message));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println(*message);
}
