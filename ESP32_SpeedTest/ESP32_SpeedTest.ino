/* 
 * This sketch runs a artificial load on both cores to measure maximum compute power of the ESP32 
 */


unsigned long loops1 = 1000;
unsigned long loops2 = 1000;


float t1;
int t2;
int t3;



unsigned long qq = 0;

TaskHandle_t Task1, Task2;


void artificialLoad () {
  for ( long i = 0; i < loops1; i++) {
    for (long  j = 1; j < loops2; j++) {
      qq++;
      t1 = 5000.0 * i;
      t2 = 150 * 1234 * i;
      t3 = j % 554 ;
    }
  }
}

void codeForTask1( void * parameter )
{
  unsigned long i, j;
  for (;;) {
    long start = millis();

    artificialLoad();

    Serial.print("Finish Task 1 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time ");
    Serial.println(millis() - start);
    delay(10);
  }
}

void codeForTask2( void * parameter )
{
  for (;;) {
    long start = millis();

    artificialLoad();

    Serial.print("                                                        Finish Task 2 which runs on Core ");
    Serial.print( xPortGetCoreID());
    Serial.print(" Time ");
    Serial.println(millis() - start);
    delay(10);
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.

  xTaskCreatePinnedToCore(
    codeForTask1,
    "led1Task",
    1000,
    NULL,
    1,
    &Task1,
    0);
  delay(500);  // needed to start-up task1

  xTaskCreatePinnedToCore(
    codeForTask2,
    "led2Task",
    1000,
    NULL,
    1,
    &Task2,
    1);

}

void loop() {
  delay(1000);
}
