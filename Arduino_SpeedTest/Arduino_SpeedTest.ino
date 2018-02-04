/*
   This sketch runs a artificial load on both cores to measure maximum compute power of the ESP32
*/


unsigned long loops1 = 1000;
unsigned long loops2 = 1000;


float t1;
int t2;
int t3;



unsigned long qq = 0;


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

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
}

void loop() {
  long start = millis();

  artificialLoad();

  Serial.print("Finish Loop Task ");
  Serial.print(" Time ");
  Serial.println(millis() - start);
  delay(10);
}
