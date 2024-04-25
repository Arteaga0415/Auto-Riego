// Pin Definitions
const int relayPin = 7;          // Relay control pin
const int manualSwitchPin = 8;   // Manual override switch pin
const int stopButtonPin = 9;     // Stop button pin
const int resetButtonPin = 10;     // Stop button pin

// Timing Constants
const unsigned long wateringInterval = 86400000; // 1 day in milliseconds
const unsigned long wateringDuration = 420000;    // 7 minutes in milliseconds
// const unsigned long wateringInterval = 20000;
// const unsigned long wateringDuration = 5000;   

// Timing Variables
unsigned long previousMillis = 0;
unsigned long loopMillis = 0;
unsigned long currentMillis;

// State Variables
bool isWatering = false;
bool manualOverride = false;
bool IterationONE = true;
bool stop = false;
bool prendidaManual = false;
int state = 0;

void setup() {
  // Initialize the relay pin as an output and set to OFF
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Initialize the manual switch and stop button pins as input pull-up
  pinMode(manualSwitchPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //Set the timer
  currentMillis = millis();
  
  if (digitalRead(manualSwitchPin) == HIGH) {
    state = 1;
    Serial.println("Switch to state 1");
  } else if (digitalRead(stopButtonPin) == LOW) {
    Serial.println("Tried to stop");
    //Implement a logic so that the button must be pressed for 1 second to stop
    loopMillis = currentMillis;
    while ((currentMillis - loopMillis) < 1000) {
      if (digitalRead(stopButtonPin) == LOW) {
        stop = true;
        state = 2; // Turn OFF the relay
        Serial.println("Switch to state 2");
      } else {
        //Stay in state 3
        state = 3;
        Serial.println("Stay in current state");
      }
    }

  } else if (digitalRead(resetButtonPin) == LOW) {
    Serial.println("Tried to Reset");
    loopMillis = currentMillis;
    while ((currentMillis - loopMillis) < 1000) {
      if (digitalRead(resetButtonPin) == LOW) {
        stop = false;
        state = 3;
        Serial.println("Switch to state 3");
        //previousMillis = currentMillis; // Reset the timer
        IterationONE = true;
      } else {
        //Stay in state 3
        state = 3;
        Serial.println("Stay in current state");
        Serial.println(currentMillis - loopMillis);
      }
    }
    
  }

  // Switch case to handle different states
  switch (state) {
    case 1: // Manual watering
      digitalWrite(relayPin, LOW); // Turn ON the relay
      isWatering = true;
      Serial.println("Watering started (Manual)");
      //Check to see if the swith was turned of 
      if (digitalRead(manualSwitchPin) == LOW) {
        state = 2;
        Serial.println("Switch to state 2");
      }
      break;
      
    case 2: // Stop button pressed
      digitalWrite(relayPin, HIGH); // Turn OFF the relay
      isWatering = false;
      Serial.println("Watering stopped (Stop button)");
      break;
    
    case 3: 
      //Logic for the loop to constatly turn on the watering for 7 minutes everyday 
      // Automated daily watering
      if (stop == false) {
        if (currentMillis - previousMillis >= wateringInterval || IterationONE) {
          IterationONE = false;
          digitalWrite(relayPin, LOW); // Turn ON the relay
          isWatering = true;
          Serial.println("Watering started (Automated)");
          previousMillis = currentMillis; // Reset the timer
        } else if (currentMillis - previousMillis >= wateringDuration) {
          digitalWrite(relayPin, HIGH); // Turn OFF the relay
          isWatering = false;
          Serial.println("Watering stopped (Automated)");
        }
      }
      break;

    default:
      Serial.println("In default state");
      break;
  }
  // Additional logic or functions can be added here
}


