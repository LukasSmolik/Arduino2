//prijimac

#include <VirtualWire.h>

uint8_t message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
uint8_t messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup()
{
  Serial.begin(9600);
  Serial.println("Device is ready");
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver
  Serial.println("komunikace zapnuta");
}

void loop()
{
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++)
    {
      Serial.print(message[i]);
    }
    Serial.println();
  }
}

