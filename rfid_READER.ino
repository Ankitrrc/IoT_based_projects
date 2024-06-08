#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>
Servo s1;

#define SS_PIN 10 // Arduino pin connected to the RFID reader's SS pin
#define RST_PIN 9 // Arduino pin connected to the RFID reader's RST pin
#define LED_PIN 6// Arduino pin connected to the LED

MFRC522 rfid(SS_PIN, RST_PIN); // Create an instance of the RFID reader

// List of allowed RFID card UIDs (add your card UIDs here)
byte allowedCards[][4] = {
  {0xF1, 0xF6, 0xC5, 0x1B}, // Replace with your card UID bytes
  {0x22, 0xE6, 0x16, 0x21}  // Replace with your card UID bytes
};

const int numAllowedCards = sizeof(allowedCards) / sizeof(allowedCards[0]);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin();        // Initialize SPI bus
  rfid.PCD_Init();    // Initialize RFID reader
  pinMode(LED_PIN, OUTPUT);
   s1.attach(8);
  Serial.println("Ready to read RFID tags!");
}

void loop() {
  // Check for RFID tags
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    Serial.print("RFID Tag UID: ");
    byte currentCardUid[4];
    memcpy(currentCardUid, rfid.uid.uidByte, 4); // Copy the UID to a temporary array
    printUid(currentCardUid, 4);
    Serial.println();

    bool isAllowed = false;
    // Compare the current card UID with the allowed cards list
    for (int i = 0; i < numAllowedCards; i++) {
      if (memcmp(currentCardUid, allowedCards[i], 4) == 0) {
        isAllowed = true;
        break;
      }
    }

    if (isAllowed) {
      Serial.println("Access granted! LED ON");
       s1.write(0);
      delay(3000);
      s1.write(180);
      delay(3000);
      s1.write(0);
      digitalWrite(LED_PIN, HIGH); // Turn on the LED
      delay(2000); // LED remains ON for 2 seconds
      digitalWrite(LED_PIN, LOW); // Turn off the LED
    } else {
      Serial.println("Access denied!");
    }

    // Halt PICC (tag/card) to stop further reading until reset
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

// Function to print the UID of the RFID tag
void printUid(byte *uid, byte uidLength) {
  for (byte i = 0; i < uidLength; i++) {
    Serial.print(uid[i] < 0x10 ? " 0" : " ");
    Serial.print(uid[i], HEX);
  }
}
