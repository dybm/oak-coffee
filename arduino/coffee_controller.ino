//oak relay shield pin
const int relay = 5;
//brewing status - an integer is used instead of a boolean
//due to Particle's limitations on allowed data types for 
//an exposed cloud variable (INT, DOUBLE, or STRING only)
int brewing = 0;
//max allowable brew time (6 minutes)
unsigned long brew_max = 360000;
//time brewing began
unsigned long brew_start;

//define Particle function
int coffee(String cmd);

void setup() {
  //setup relay pin
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  
  //register Particle cloud functions
  Particle.function("coffee", coffee);
  Particle.variable("brewing", brewing);
}

void loop() {
  //check if a new brewing cycle has started
  if (!brewing && digitalRead(relay)) {
    //record the start time
    brew_start = millis();
    //set brewing status
    brewing = 1;
  } else if (brewing) {
    //check brew time
    if (millis() - brew_start > brew_max) {
      //turn off the coffee pot
      digitalWrite(relay, LOW);
      //set brewing status
      brewing = 0;
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
