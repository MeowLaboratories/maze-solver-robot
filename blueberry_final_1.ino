#include <EEPROM.h>
#include <QTRSensors.h>
#include <LiquidCrystal.h>

#define LEFTMOTORA 52
#define LEFTMOTORB 53
#define RIGHTMOTORA 50
#define RIGHTMOTORB 51

#define left_speed_pin   3
#define right_speed_pin  2

#define green_bulb  27
#define red_bulb    26
#define yellow_bulb 25

#define switch_1 24
#define switch_2 23
#define switch_3 22

#define rightBaseSpeed 200
#define leftBaseSpeed  200 //174

int LFS = 255; //220;
int RFS = 255;
int LHS = 125; //110;
int RHS = 125;


int left, right, p_bit[10], dif, LN, thres_min[15], thres_max[15], thres[15], n_val[2], n_bit[2], node;
char color;

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   12

QTRSensorsRC qtrrc((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, A6, A7
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int p_val[NUM_SENSORS], positionn;

LiquidCrystal lcd(7, 6, 11, 10, 9, 8);

int Kp = 50;//200
int Kd = 5;//5
int Ki = 5;
int lastError = 0;
int PID, P, RMS, LMS;
int I = 0;

int maze[1000], proto[1000];

void setup()
{
  //motor
  pinMode(LEFTMOTORA, OUTPUT);
  pinMode(LEFTMOTORB, OUTPUT);
  pinMode(RIGHTMOTORA, OUTPUT);
  pinMode(RIGHTMOTORB, OUTPUT);

  pinMode(left_speed_pin, OUTPUT);
  pinMode(right_speed_pin, OUTPUT);

  //debugging light

  pinMode(yellow_bulb, OUTPUT);
  pinMode(red_bulb, OUTPUT);
  pinMode(green_bulb, OUTPUT);

  //switch
  pinMode(switch_1, INPUT);
  pinMode(switch_2, INPUT);
  pinMode(switch_3, INPUT);

  //lcd screen
  lcd.begin(16, 2);

  //calibration
  if (digitalRead(switch_1) == HIGH && digitalRead(switch_2) == HIGH && digitalRead(switch_3) == LOW)
  {
    lcd.clear();
    lcd.print("calibrartion");
    robot_stop();
    delay(2000);

    bulb(1, 1, 1);

    cal();
    while (1)
    {
      lcd.clear();
      lcd.print("press s1 for W line");
      lcd.setCursor(0, 1);
      lcd.print("press s2 for B line");
      robot_stop();

      if (digitalRead(switch_1) == HIGH && digitalRead(switch_2) == LOW)
      {
        EEPROM.write(1, 'W');
        break;
      }
      if (digitalRead(switch_1) == LOW && digitalRead(switch_2) == HIGH)
      {
        EEPROM.write(1, 'B');
        break;
      }
    }

    while (1)
    {
      bulb(1, 0, 0);
      lcd.clear();
      lcd.print("MEOW");
    }
  }

  else thres_read();

  //proto

}

void loop()
{
  lcd.clear();
  lcd.print("S1 for L");
  lcd.setCursor(0,1);
  lcd.print("S2 for R");
  

  if(digitalRead(switch_1) == HIGH && digitalRead(switch_2) == LOW)
  {
    main_run_L(); 
  }
  
  if(digitalRead(switch_1) == LOW && digitalRead(switch_2) == HIGH)
  {
    main_run_R(); 
  }
  delay(100);
 // main_run();
  // return_to_start();
  //bulb(1,1,1);
  //debug();
  //line_status();
  //robot_180();
  //delay(2000);
}

void delay_follow_line(unsigned long n)
{
  unsigned long current_time = millis();
  unsigned long end_time = current_time + n;

  while (current_time < end_time)
  {
    follow_the_damn_line();
    current_time = millis();
  }
}

void bulb(byte n1, byte n2 , byte n3)
{
  if ( n1 == 1)
    digitalWrite(green_bulb, HIGH);
  else
    digitalWrite(green_bulb, LOW);

  if (n2 == 1)
    digitalWrite(yellow_bulb, HIGH);
  else
    digitalWrite(yellow_bulb, LOW);

  if (n3 == 1)
    digitalWrite(red_bulb, HIGH);
  else
    digitalWrite(red_bulb, LOW);

}
