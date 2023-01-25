#include <stdlib.h>
// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
static const uint8_t length = 20;
static const uint8_t led0 = 25;
static int ledDelay = 500;
unsigned int startTime, startTime2;
void ledBlink(void *parameter)
{
    startTime = millis();
    while (1)
    {
        digitalWrite(led0, HIGH);
        vTaskDelay(ledDelay / portTICK_PERIOD_MS);
        digitalWrite(led0, LOW);
        vTaskDelay(ledDelay / portTICK_PERIOD_MS);
        /*
        if (millis() - startTime >= 5000)
        {
            unsigned int temp1 = uxTaskGetStackHighWaterMark(NULL);
            Serial.print("ledBlink Stack Free:");
            Serial.print(temp1);
            Serial.print("\n");
            startTime = millis();
        }
        */
    }
}
void readSerial(void *parameter)
{
    startTime2 = millis();
    char c, buffer[length];
    uint8_t index = 0;
    memset(buffer, 0, length); // Clears the buffer
    while (1)
    {
        if (Serial.available() > 0)
        {
            c = Serial.read();
            // Update delay variable and reset buffer if we get a newline character
            if (c == '\n')
            {
                ledDelay = atoi(buffer);
                Serial.print("Delay updated to: ");
                Serial.print(ledDelay);
                Serial.print("\n");
                memset(buffer, 0, length);
                index = 0;
            }
            else
            {
                // Only append if index is not over message limit
                if (index < length - 1)
                {
                    buffer[index] = c;
                    index++;
                }
            }
        }
        /*
        if (millis() - startTime2 >= 5000)
        {
            unsigned int temp1 = uxTaskGetStackHighWaterMark(NULL);
            Serial.print("ReadSerial Stack Free:");
            Serial.print(temp1);
            Serial.print("\n");
            startTime2 = millis();
        }
        */
    }
}
void setup()
{
    Serial.begin(115200);
    pinMode(led0, OUTPUT);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    Serial.println("Enter delay Time: ");
    xTaskCreatePinnedToCore(
        ledBlink, // Function to be called
        "task0",  // Name of task
        1024,     // Statck Size
        NULL,     // Parameter
        1,        // Priority
        NULL,     // Task handle
        app_cpu   // core
    );
    xTaskCreatePinnedToCore(
        readSerial, // Function to be called
        "task1",    // Name of task
        1024,       // Statck Size
        NULL,       // Parameter
        1,          // Priority
        NULL,       // Task handle
        app_cpu     // core
    );
    // Delete "setup and loop" task
    // To delete the own task we should pass NULL as parameter
    vTaskDelete(NULL);
}
void loop()
{
}
