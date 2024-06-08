char Incoming_Value = 0;/+,
int relayPin=3;
void setup () 
{
	   Serial.begin(9600);
    pinMode(relayPin,OUTPUT);
} 
     void loop () 
     {     
    
if(Serial.available ()> 0)
    
     {
        Incoming_Value = Serial.read ();	 
	      Serial.print(Incoming_Value);
	      Serial.print("\n");
	      if(Incoming_Value == '1'){
        digitalWrite(13,LOW);
        }
	      else if(Incoming_Value == '0'){   
        digitalWrite(13,HIGH);
        }
	 }
	}