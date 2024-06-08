
int ir1=9;
int X;

int ir2=8;
int Y;

void setup() {
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
 
 
}

void loop() {
  X=digitalRead(ir1);
  Y=digitalRead(ir2);
  Serial.println(X);
  delay(300);
  if(X==1)
  {
      digitalWrite(11,LOW);
}
else
{
      digitalWrite(11,HIGH);
}

if (Y==1) {
      digitalWrite(10,LOW);
}
else {
      digitalWrite(10,HIGH);
}
}