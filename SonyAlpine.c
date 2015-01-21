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
const int alpPin = 2;

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
const int sonySeekDown = 22;
const int sonySeekUp = 26;
const int sonyBack = 29;
const int sonyFront = 11;
const int sonyBottom = 8;



void setup() {
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  Serial.begin(9600);
  Serial.println("hello world");
}

void loop() {
  float sonyPress = analogRead(sonyPin);
  float voltage = (sonyPress / 1024) * 5.0;
  if (voltage > 0.01) {
    checkVoltage(int((voltage) * 10));
  }
}

void checkVoltage(int voltage) {
  Serial.print(voltage);
  switch (voltage) {
    case sonySrc:
      sendCode(alpSource);
      return;
    case sonyAtt:
      sendCode(alpAtt);
      return;
    case sonyOff:
      sendCode(alpOff);
      return;
    case sonyVolDown:
      sendCode(alpVolDown);
      return;
    case sonyVolUp:
      sendCode(alpVolUp);
      return;
    case sonySeekUp:
      sendCode(alpTrackUp);
      return;
    case sonySeekDown:
      sendCode(alpTrackDown);
      return;
    case sonyBack:
      sendCode(alpPstDown);
      return;
    case sonyFront:
      sendCode(alpPstUp);
      return;
    case sonyBottom:
      break;      
    default:
      break;
  }
}


void sendCode(char *code) {
  const int ALPINELENGTH = 47;
  const int ALPINERATE = 500; //microseconds
  const int ALPINEINTERVAL = 41; //milliseconds
  const int alpineHighInnit = 8000; //microseconds
  const int alpineLowInnit = 4500; //microseconds
  
  //Innit  
  digitalWrite(2,HIGH);
  delay(8); // 8 ms high init
  digitalWrite(2,LOW);
  delayMicroseconds(4500); // 4.5 ms low init
  
  for (int i = 0; i <= 47; i++) {
    if (code[i] == '1') {
      digitalWrite(2,HIGH);
    } else {
      digitalWrite(2,LOW);
    }
      delayMicroseconds(500);
      digitalWrite(2,LOW);
      delayMicroseconds(500);
  }
  digitalWrite(2,LOW);
  delay(41);  
}
