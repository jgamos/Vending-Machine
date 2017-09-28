unsigned char i;
unsigned char j;
/*Port Definitions*/
int Max7219_pinCLK = 10;
int Max7219_pinCS = 9;
int Max7219_pinDIN = 8;

unsigned char disp1[38][8] = {
  {0x00, 0x7e, 0x81, 0x81, 0x81, 0x81, 0x7e, 0x00}, //0
  {0x00, 0x00, 0x01, 0x01, 0xff, 0x41, 0x01, 0x00}, //1
  {0x00, 0x00, 0x71, 0x89, 0x89, 0x89, 0x47, 0x00}, //2
  {0x00, 0x00, 0x66, 0x99, 0x89, 0x81, 0x41, 0x00}, //3
  {0x00, 0x08, 0x08, 0x9f, 0x48, 0x28, 0x18, 0x00}, //4
  {0x00, 0x00, 0x8c, 0x92, 0x91, 0x91, 0xe1, 0x00}, //5
  {0x08, 0x04, 0x62, 0x02, 0x02, 0x62, 0x04, 0x08}, //6
};

void Write_Max7219_byte(unsigned char DATA)
{
  unsigned char i;
  digitalWrite(Max7219_pinCS, LOW);
  for (i = 8; i >= 1; i--)
  {
    digitalWrite(Max7219_pinCLK, LOW);
    digitalWrite(Max7219_pinDIN, DATA & 0x80); // Extracting a bit data
    DATA = DATA << 1;
    digitalWrite(Max7219_pinCLK, HIGH);
  }
}


void Write_Max7219(unsigned char address, unsigned char dat)
{
  digitalWrite(Max7219_pinCS, LOW);
  Write_Max7219_byte(address);           //address，code of LED
  Write_Max7219_byte(dat);               //data，figure on LED
  digitalWrite(Max7219_pinCS, HIGH);
}

void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00);       //decoding ：BCD
  Write_Max7219(0x0a, 0x03);       //brightness
  Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
  Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
  Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}

byte M1[4] = {28, 26, 24, 22};
byte M2[4] = {36, 34, 32, 30};
byte M3[4] = {37, 35, 33, 31};
byte M4[4] = {44, 42, 40, 38};
byte M5[4] = {45, 43, 41, 39};
byte M6[4] = {52, 50, 48, 46};
byte M7[4] = {53, 51, 49, 47};
byte M8[4] = {29, 27, 25, 23};
byte bt1 = 21;
byte bt2 = 20;
byte bt3 = 19;
byte bt4 = 18;
byte bt5 = 17;
byte bt6 = 16;
byte bt7 = 15;
byte bt8 = 14;

float coinlight;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(bt3, INPUT_PULLUP);
  pinMode(bt4, INPUT_PULLUP);
  pinMode(bt5, INPUT_PULLUP);
  pinMode(bt6, INPUT_PULLUP);
  pinMode(bt7, INPUT_PULLUP);
  pinMode(bt8, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A7, OUTPUT);
  pinMode(A8, OUTPUT);
  LEDoff;

  for (int i = 0; i < 4; i++) {
    pinMode(M1[i], OUTPUT);
    pinMode(M2[i], OUTPUT);
    pinMode(M3[i], OUTPUT);
    pinMode(M4[i], OUTPUT);
    pinMode(M5[i], OUTPUT);
    pinMode(M6[i], OUTPUT);
    pinMode(M7[i], OUTPUT);
    pinMode(M8[i], OUTPUT);
  }

  pinMode(Max7219_pinCLK, OUTPUT);
  pinMode(Max7219_pinCS, OUTPUT);
  pinMode(Max7219_pinDIN, OUTPUT);
  delay(50);
  Init_MAX7219();


}
byte btvar = 0;
byte coin = 0;

void loop() {

  if (coin == 0) {
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, disp1[0][i - 1]);
    }
  } else if (coin == 1) {
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, disp1[1][i - 1]);
    }
  } else if (coin == 2) {
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, disp1[2][i - 1]);
    }
  } else if (coin == 3) {
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, disp1[3][i - 1]);
    }
  } else if (coin == 4) {
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, disp1[4][i - 1]);
    }
  } else if (coin == 5) {
    for (i = 1; i < 9; i++) {
      Write_Max7219(i, disp1[5][i - 1]);
    }
  }

  analogWrite(12, coinlight);
  coinlight = coinlight - 1;
  coinlight = constrain(coinlight, 0, 255);
  Serial.println(coinlight);
  if (digitalRead(13) == 0) {
    coin++;
    coinlight = 255;
    analogWrite(12, coinlight);
    delay(300);
  }

  if (coin >= 4) {              //最右邊
    digitalWrite(A1, HIGH);
    if (digitalRead(bt1) == 0) {
      btvar = 1;
      Serial.println("bt1");
      LEDoff();
      digitalWrite(A1, HIGH);
      motorON(1);
      LEDoff();
    }
  }
  if (coin >= 4) {
    digitalWrite(A2, HIGH);
    if (digitalRead(bt2) == 0) {
      btvar = 2;
      Serial.println("bt2");
      LEDoff();
      digitalWrite(A2, HIGH);
      motorON(2);
      LEDoff();
    }
  }

  if (coin >= 3) {
    digitalWrite(A3, HIGH);
    if (digitalRead(bt3) == 0) {
      btvar = 3;
      Serial.println("bt3");
      LEDoff();
      digitalWrite(A3, HIGH);
      motorON(3);
      LEDoff();
    }
  }

  if (coin >= 2) {
    digitalWrite(A4, HIGH);
    if (digitalRead(bt4) == 0) {
      btvar = 4;
      Serial.println("bt4");
      LEDoff();
      digitalWrite(A4, HIGH);
      motorON(4);
      LEDoff();
    }
  }

  if (coin >= 2) {
    digitalWrite(A5, HIGH);
    if (digitalRead(bt5) == 0) {
      btvar = 5;
      Serial.println("bt5");
      LEDoff();
      digitalWrite(A5, HIGH);
      motorON(5);
      LEDoff();
    }
  }
  if (coin >= 2) {
    digitalWrite(A6, HIGH);
    if (digitalRead(bt6) == 0) {
      btvar = 6;
      Serial.println("bt6");
      LEDoff();
      digitalWrite(A6, HIGH);
      motorON(6);
      LEDoff();
    }
  }

  if (coin >= 1) {
    digitalWrite(A7, HIGH);
    if (digitalRead(bt7) == 0) {
      btvar = 7;
      Serial.println("bt7");
      LEDoff();
      digitalWrite(A7, HIGH);
      motorON(7);
      LEDoff();
    }
  }
  if (coin >= 1) {
    digitalWrite(A8, HIGH);
    if (digitalRead(bt8) == 0) {
      btvar = 8;
      Serial.println("bt8");
      LEDoff();
      digitalWrite(A8, HIGH);
      motorON(8);
      LEDoff();
    }
  }


}

void motorON(byte motorpin) {
  byte motorPin[4];
  Serial.println("motorGO");
  if (motorpin == 1)
    for (int i = 0; i < 4; i++)  motorPin[i] = M1[i];
  if (motorpin == 2)
    for (int i = 0; i < 4; i++)  motorPin[i] = M2[i];
  if (motorpin == 3)
    for (int i = 0; i < 4; i++)  motorPin[i] = M3[i];
  if (motorpin == 4)
    for (int i = 0; i < 4; i++)  motorPin[i] = M4[i];
  if (motorpin == 5)
    for (int i = 0; i < 4; i++)  motorPin[i] = M5[i];
  if (motorpin == 6)
    for (int i = 0; i < 4; i++)  motorPin[i] = M6[i];
  if (motorpin == 7)
    for (int i = 0; i < 4; i++)  motorPin[i] = M7[i];
  if (motorpin == 8)
    for (int i = 0; i < 4; i++)  motorPin[i] = M8[i];

  for (int i = 0; i < 512; i++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(motorPin[i], HIGH);
      delay(4);
      for (int j = 0; j < 4; j++) {
        digitalWrite(motorPin[j], LOW);

      }
    }
  }
  btvar = 0;
  coin = 0;
}

void LEDoff() {
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A6, LOW);
  digitalWrite(A7, LOW);
  digitalWrite(A8, LOW);
}


