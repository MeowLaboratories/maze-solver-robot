void debug()
{
  Serial.begin(9600);
  while (1)
  { 
   debug_scan();
    //debug_lcd_qtr();
   //check_motor();
//   Serial.print(analogRead(A8));
//   Serial.print('\t');
//   Serial.println(analogRead(A9));
//   delay(200);
  }
}

void debug_p_val()
{
  qtrrc.read(p_val);

  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(p_val[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  
  delay(250);
}

void debug_lcd_qtr()
{
  delay(2000);
  robot_rotate_right(LHS,RHS);
   for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }

  robot_stop();

while(1)
{
  positionn = qtrrc.readLine(p_val);

  line_status();
  
  lcd.clear();
  lcd.print(positionn);
  lcd.setCursor(0,1);
  lcd.print(LN,2);
  delay(200);
 }  
}

void debug_p_bit()
{
  line_status();

//  for(int i = 0 ; i < 8 ; i++)
//  {
//    Serial.print(p_bit[i]);
//    Serial.print('\t');
//  }
//
//  Serial.print(" LN = ");
//  Serial.print(LN);
//  Serial.print('\t');

  Serial.print("node = ");
  Serial.println(node);
  Serial.print('\t');

//  Serial.print("left = ");
//  Serial.print(left);
//  Serial.print('\t');
//
//  Serial.print("right = ");
//  Serial.print(right);
//  Serial.println();

  delay(250);
  
}

void debug_scan()
{
  for ( int i = 2000; i < 2100 ; i++ )
  {
    Serial.println( EEPROM.read(i) );
  } 

  while(1)
  {
    
  }
}

void debug_cal()
{
  for ( int i = 8; i < 10 ; i++ )
  {
    Serial.print( thres[i] );
    Serial.print("   ");
  }
  Serial.println();
  
  while(1)
  {
    
  }
}

void debug_path()
{
  
}

void check_motor()
{
  robot_forward(150,150);
  delay(1500);
  robot_backward(150,150);
  delay(1500);
  robot_right(150, 150);
  delay(1500);
  robot_left(150, 150);
  delay(1500);
  robot_rotate_right(150,150);
  delay(1500);
  robot_rotate_left(150, 150);
  delay(1500);
  robot_stop();
  delay(8000);
}
