// C++ code
//

#define PI 3.14159f
int keyVal;
int potVal;
float angle;


void setup()
{
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  keyVal = analogRead(A0);
  Serial.print("K: ");
  Serial.println(keyVal);
  potVal = analogRead(A2);
  angle = (float) map(potVal, 0, 1023, 0, 359) * (PI / 180.f);
  Serial.print("A: ");
  Serial.println(angle);
}