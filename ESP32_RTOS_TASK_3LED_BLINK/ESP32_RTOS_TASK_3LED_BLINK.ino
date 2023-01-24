// FreeRTOS task
// ESP32 with 3 different tasks running concurrently.(Like multitasking)
// Arduino framework

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
// Use only core 1 for demo purposes

const int output[3] = {25, 26, 27};
const int delayTime[3] = {500, 1000, 1500};

void output0(void *parameter)
{
    while (1)
    {
        digitalWrite(output[0], HIGH);
        vTaskDelay(delayTime[0] / portTICK_PERIOD_MS);
        // delay(delayTime[0]);

        digitalWrite(output[0], LOW);
        vTaskDelay(delayTime[0] / portTICK_PERIOD_MS);
        // delay(delayTime[0]);
    }
}

void output1(void *parameter)
{
    while (1)
    {
        digitalWrite(output[1], HIGH);
        vTaskDelay(delayTime[1] / portTICK_PERIOD_MS);
        // delay(delayTime[1]);

        digitalWrite(output[1], LOW);
        vTaskDelay(delayTime[1] / portTICK_PERIOD_MS);
        // delay(delayTime[1]);
    }
}

void output2(void *parameter)
{
    digitalWrite(output[2], HIGH);
    vTaskDelay(delayTime[2] / portTICK_PERIOD_MS);
    // delay(delayTime[2]);

    digitalWrite(output[2], LOW);
    vTaskDelay(delayTime[2] / portTICK_PERIOD_MS);
    // delay(delayTime[2]);
}
void setup()
{

    Serial.begin(115200);
    for (int i = 0; i < 3; i++)
    {
        pinMode(output[i], OUTPUT);
    }

    xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
        output0,             // Function to be called
        "Task0",             // Name of task
        2048,                // Stack size(bytes in ESP32, words in FreeRTOS)
        NULL,                // Parameter to pass to function
        1,                   // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                // Task handle
        app_cpu              // Run on one core for demo purposes (ESP32 only)
    );
    xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
        output1,             // Function to be called
        "Task1",             // Name of task
        2048,                // Stack size(bytes in ESP32, words in FreeRTOS)
        NULL,                // Parameter to pass to function
        1,                   // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                // Task handle
        app_cpu              // Run on one core for demo purposes (ESP32 only)
    );
    xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
        output2,             // Function to be called
        "Task2",             // Name of task
        2048,                // Stack size(bytes in ESP32, words in FreeRTOS)
        NULL,                // Parameter to pass to function
        1,                   // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                // Task handle
        app_cpu              // Run on one core for demo purposes (ESP32 only)
    );
}

void loop()
{
}