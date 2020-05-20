// Start with all the variables for each set of buttons and lights

//Set1
int LED1pin = 13;
int Button1pin = 2;
int button1State;
int LED1State = LOW;
int lastbutton1State = 0;

//Set2
int LED2pin = 12;
int Button2pin = 4;
int button2State;
int LED2State = LOW;
int lastbutton2State = 0;

//Set3
int LED3pin = 27;
int Button3pin = 17;
int button3State;
int LED3State = LOW;
int lastbutton3State = 0;

//Set4
int LED4pin = 33;
int Button4pin = 19;
int button4State;
int LED4State = LOW;
int lastbutton4State = 0;

//Variables to make sure the button bounce is not seen as a switch
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 25;

//define which pins do what
void setup()
{
  pinMode(LED1pin, OUTPUT);
  pinMode(Button1pin, INPUT);
  digitalWrite(LED1pin, lastbutton1State);
  
  pinMode(LED2pin, OUTPUT);
  pinMode(Button2pin, INPUT);
  digitalWrite(LED2pin, lastbutton2State);
  
  pinMode(LED3pin, OUTPUT);
  pinMode(Button3pin, INPUT);
  digitalWrite(LED3pin, lastbutton3State);
  
  pinMode(LED4pin, OUTPUT);
  pinMode(Button4pin, INPUT);
  digitalWrite(LED4pin, lastbutton4State);
  
  Serial.begin(115200);
}

void loop()
{
  //A repeat for each Set
  //Read the button pin
  int reading = digitalRead(Button1pin);
  //if button has changed
  if (reading != lastbutton1State) {
    //how long ago was this
    lastDebounceTime = millis();
  }

  //if the button was pressed long enough
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != button1State) {
      button1State = reading;
      // if button is pressed
    if (button1State == HIGH) {
      //change LED state
        LED1State = !LED1State;
      }
    }
  }

  //send led state to led pin for actual update of the LED
  digitalWrite(LED1pin, LED1State);
  lastbutton1State = reading;

  reading = digitalRead(Button2pin);
  if (reading != lastbutton2State) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != button2State) {
      button2State = reading;
      if (button2State == HIGH) {
        LED2State = !LED2State;
      }
    }
  }
  
  digitalWrite(LED2pin, LED2State);
  lastbutton2State = reading;

  reading = digitalRead(Button3pin);
  if (reading != lastbutton3State) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != button3State) {
      button3State = reading;
      if (button3State == HIGH) {
        LED3State = !LED3State;
      }
    }
  }
  
  digitalWrite(LED3pin, LED3State);
  lastbutton3State = reading;

  reading = digitalRead(Button4pin);
  if (reading != lastbutton4State) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != button4State) {
      button4State = reading;
      if (button4State == HIGH && LED3State == LOW) {
        LED4State = !LED4State;
      }
    }
  }
  
  digitalWrite(LED4pin, LED4State);
  lastbutton4State = reading;

  delay(50); // Delay a little bit to improve simulation performance
}
