// Pin Definitions
const int relayPin = 7;          // Relay control pin
const int manualSwitchPin = 6;   // Manual override switch pin
const int autoSwitchPin = 5;   // reset override switch pin


// Timing Constants
const unsigned long wateringInterval = 86400000; // 1 day in milliseconds
const unsigned long wateringDuration = 240000;    // 5 minutes in milliseconds
// const unsigned long wateringInterval = 20000;
// const unsigned long wateringDuration = 5000;   

// Timing Variables
unsigned long previousMillis = 0;
unsigned long currentMillis;

// State Variables
bool isWatering = false;
bool manualOverride = false;
bool IterationONE = true;
int state = 0;
unsigned int previouState;

void setup() {
  // Initialize the relay pin as an output and set to OFF
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Initialize the manual switch and stop button pins as input pull-up
  pinMode(manualSwitchPin, INPUT_PULLUP);
  pinMode(autoSwitchPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //Set the timer
  currentMillis = millis();
  
  if (digitalRead(manualSwitchPin) == HIGH) {
    state = 1;
    Serial.println("Switch to state 1");
  } else if (digitalRead(manualSwitchPin) == LOW && digitalRead(autoSwitchPin) == LOW) {
    previouState = state;
    previousMillis = currentMillis;
    //has to trap in a loop of 1.5sec to check if both mantain in low
    while (millis() - previousMillis <= 1500) {
      if (digitalRead(manualSwitchPin) == LOW && digitalRead(autoSwitchPin) == LOW) {
        state = 2; // Turn OFF the relay
        //If they are completly stopped iteration One may resume
        IterationONE = true;
        Serial.println("Switch to state 2");
      } else {
        state = previouState;
        Serial.println("Switch to state " + state);
      }
    }
  } else if (digitalRead(autoSwitchPin) == HIGH && digitalRead(manualSwitchPin) == LOW) {
    state = 3;
    Serial.println("Switch to state 3");
  }

  // Switch case to handle different states
  switch (state) {
    case 1: // Manual watering
      digitalWrite(relayPin, LOW); // Turn ON the relay
      isWatering = true;
      Serial.println("Watering started (Manual)");
      break;
      
    case 2: // Stop button pressed
      digitalWrite(relayPin, HIGH); // Turn OFF the relay
      isWatering = false;
      Serial.println("Watering stopped");
      break;
    
    case 3: 
      //Logic for the loop to constatly turn on the watering for 7 minutes everyday 
      // Automated daily watering
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
      break;

    default:
      Serial.println("In default state");
      break;
  }
  // Additional logic or functions can be added here
}


