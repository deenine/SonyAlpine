/*
            resistance	voltage
src      	2200	4.1
att	        4400	3.47
off	        35	4.98
vol down	23850	1.47
vol up	        17000	1.85
seek down	12000	2.25
seek up	        8800	2.65
back	        6660	3
front	        33940	1.13
bottom	        48800	0.84
*/

/** General Config                                                            **/
const int sonyPin = A0;
const int ledPin = 13;
const int alpPin = 2;
const int arrowDelay = 250; //repeat rate for arrow key presses
const int enterDelay = 350; //repeat rate for enter/esc key presses

boolean headunit = true; //True if stalk is controlling HU, false if emulating kb

/** Alpine Codes                                                              **/
char alpVolUp[] = "110101111101101110101011110110111101011011010101";
char alpVolDown[] = "110101111101101110101011011011011111011011010101";
char alpAtt[] = "110101111101101110101011101011011110111011010101";
char alpSource[] = "110101111101101110101011101101111101101101010101";
char alpOff[] = "110101111101101110101011011101111110101101010101";
char alpTrackUp[] = "110101111101101110101011101110111101101011010101";
char alpTrackDown[] = "110101111101101110101011010111011111101011010101";
char alpPstUp[] = "110101111101101110101011101010111110111101010101";
char alpPstDown[] = "110101111101101110101011010101011111111101010101";

/** Sony Voltages                                                             **/
const int sonySrc = 41; //4.1v
const int sonyAtt = 34;
const int sonyOff = 49;
const int sonyVolDown = 14;
const int sonyVolUp = 18;
const int sonySeekDown = 26;
const int sonySeekUp = 22;
const int sonyBack = 29;
const int sonyFront = 11;
const int sonyBottom = 8;


/** Setup                                                                    **/

void setup() {
  pinMode(alpPin,OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(2,LOW);
  Keyboard.begin();
}

/** Main program loop                                                        **/
void loop() {
  float sonyPress = analogRead(sonyPin);
  float voltage = (sonyPress / 1024) * 5.0;
  if (voltage > 0.01) {
    delay(10); //filter out the initial flutter in voltage
    //take a second reading
    sonyPress = analogRead(sonyPin);
    voltage = (sonyPress / 1024) * 5.0;
    checkVoltage(int((voltage) * 10));
  }

  if(headunit == true) 
    digitalWrite(ledPin,HIGH);
  else
    digitalWrite(ledPin,LOW);
}

void checkVoltage(int voltage) {
  Serial.print(voltage);
  switch (voltage) {
    case sonySrc:
      sendCode(alpSource);
      return;
    case sonyVolDown:
      sendCode(alpVolDown);
      return;
    case sonyVolUp:
      sendCode(alpVolUp);
      return;
    case sonyBottom:
      if (headunit == true)
        headunit = false;
      else
        headunit = true;  
      delay(500);
      return;      


    case sonyAtt:
      if (headunit)
        sendCode(alpAtt);
      else
        sendKey(KEY_RETURN);
      return;
    case sonyOff:
      if (headunit)
        sendCode(alpOff);
      else
        sendKey(KEY_ESC);
      return;
    case sonySeekUp:
      if (headunit)
        sendCode(alpTrackUp);
      else
        sendKey(KEY_RIGHT_ARROW);
      return;
    case sonySeekDown:
      if (headunit)
        sendCode(alpTrackDown);
      else
        sendKey(KEY_LEFT_ARROW);
      return;
    case sonyBack:
      if (headunit)
        sendCode(alpPstDown);
      else
        sendKey(KEY_DOWN_ARROW);
      return;
    case sonyFront:
      if (headunit)
        sendCode(alpPstUp);
      else
        sendKey(KEY_UP_ARROW);
      return;
    default:
      break;
  }
}

void sendKey(int key){
  Keyboard.write(key);
  //longer delay between enter/return than arrow keys.
  if (key == KEY_RETURN || key == KEY_ESC)
    delay(enterDelay);
  else
    delay(arrowDelay);
  return;
  
}

void sendCode(char *code) {
  const int alpCodeLength = 47;
  const int alpRate = 500; //microseconds
  const int alpInterval = 41; //milliseconds
  
  //Innit  
  digitalWrite(alpPin,HIGH);
  delay(8); // 8 ms high init
  digitalWrite(alpPin,LOW);
  delayMicroseconds(4500); // 4.5 ms low init
  
  //Send command
  for (int i = 0; i <= alpCodeLength; i++) {
    if (code[i] == '1') {
      digitalWrite(alpPin,HIGH);
    } else {
      digitalWrite(alpPin,LOW);
    }
      delayMicroseconds(alpRate);
      digitalWrite(alpPin,LOW);
      delayMicroseconds(alpRate);
  }
  digitalWrite(alpPin,LOW);
  delay(41); //41ms interval between commands  
}
