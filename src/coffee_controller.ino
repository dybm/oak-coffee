//define pin to use with Oak relay shield
const int relay = 5;

//initialize boolean to keep track of if the brewing cycle has started
bool brewing = false;
//define max allowable brew time
unsigned long brew_max = 360000; //6 minutes
//define variable to hold the time the brewing cycle started
unsigned long brew_start;

//define Particle function
int coffee(String cmd);

void setup() {
  //setup relay pin
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  
  //register Particle function
  Particle.function("coffee", coffee);
}

void loop() {
  //check if a new brewing cycle has started
  if (!brewing && digitalRead(relay)) {
    //a new brewing cycle has started
    //record the start time
    brew_start = millis();
    //toggle the brewing boolean
    brewing = true;
  } else if (brewing) {
    //check that the max brewing time has not been exceeded
    if (millis() - brew_start > brew_max) {
      //turn off the coffee pot
      digitalWrite(relay, LOW);
      //toggle the brewing boolean
      brewing = false;
    }
  }
}

int coffee(String cmd) {
  if (cmd == "on") {
    //turn on the coffee pot and return success
    digitalWrite(relay, HIGH);
    return 1;
  } else if (cmd == "off") {
    //turn off the coffee pot and return success
    digitalWrite(relay, LOW);
    return 1;
  } else {
    //turn off the coffee pot and return failure
    digitalWrite(relay, LOW);
    return -1;
  }
}
