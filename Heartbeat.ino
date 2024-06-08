int led_Pin = 7;
int output_Pin = A0;
double alpha = 0.75;
int period = 50;
double change = 0.0;

void setup() {
 
 pinMode(led_Pin,OUTPUT);
 Serial.begin(9600);
}

void loop() {

static double oldValue = 0;
int rawValue = analogRead(output_Pin);
double value = alpha * oldValue + (1-alpha)*rawValue;
Serial.println(value);
oldValue = value;
if(value>=979)
{
  digitalWrite(13,HIGH);
}
 else{
   digitalWrite(13,LOW);
 }
 delay(period);
}
