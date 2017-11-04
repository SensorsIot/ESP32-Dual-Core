/*
 * This blinks two LEDs independently and not synchronized. Both have other blink frequencies. 
 * The blink sketches run in two tasks and on two cores.
 */
 
#define LED1 13
#define LED2 14

TaskHandle_t Task1, Task2;


int counter = 0;

void blink(byte pin, int duration) {

  digitalWrite(pin, HIGH);
  delay(duration);
  digitalWrite(pin, LOW);
  delay(duration);
}

void codeForTask1( void * parameter )
{
  for (;;) {
    blink(LED1, 1000);
    delay(50);
    Serial.println("Task 1: ");
  }
}

void codeForTask2( void * parameter )
{
  for (;;) {
    blink(LED2, 1200);
    delay(50);
    Serial.println("             Task 2: ");
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  // initialize digital pin LED_BUILTIN as an output.

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

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
