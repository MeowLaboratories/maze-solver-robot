
void follow_the_damn_line()
{  
    P = 3500 - positionn;
       
    I += P;
    if(I > 255) I = 255;
    if(I < -255) I = -255;
    
    PID =  P/Kp + Kd * (P - lastError) +I/Ki ;
    lastError = P;

   RMS = rightBaseSpeed + PID;
   LMS = leftBaseSpeed - PID;
  
  if (RMS > RFS ) RMS = RFS; // prevent the motor from going beyond max speed
  if (LMS > LFS ) LMS = LFS; // prevent the motor from going beyond max speed
  if (RMS < 0) RMS = 0; // keep the motor speed positive
  if (LMS < 0) LMS = 0; // keep the motor speed positive


//  lcd.clear();
//  lcd.print(LMS);
//  lcd.setCursor(10,0);
//  lcd.print(RMS);
//  lcd.setCursor(0,1);
//  lcd.print(positionn);
//  lcd.setCursor(10,1);
//  lcd.print(PID);

  robot_forward(LMS,RMS);
}


void line_status()
{
  left = 0;
  right = 0;
  LN = 0;
  
  int i, a = 0 ;

  if(color == 'B')
  {
        positionn = qtrrc.readLine(p_val);

      if(analogRead(A8) >= thres[8] ) n_bit[0] = 0;
      else n_bit[0] = 1;
      if(analogRead(A9) >= thres[9] ) n_bit[1] = 0;
      else n_bit[1] = 1;  
  }

  else
  {
        positionn = qtrrc.readLine(p_val,1,1);
         

      if(analogRead(A8) <= thres[8] ) n_bit[0] = 0;
      else n_bit[0] = 1;
      if(analogRead(A9) <= thres[9] ) n_bit[1] = 0;
      else n_bit[1] = 1;
  }
  node = 2*n_bit[0] + n_bit[1];
}


void cal()
{
  robot_rotate_left(LHS,RHS);
  
  int i,val,a;
  
   for( i = 0 ; i < 10 ; i++)
  {
    thres[i] = 0 ;
    thres_max[i] = 0;
    thres_min[i] = 1023;
  }

  unsigned long current_time = millis();
  unsigned long end_time = current_time + 5000;
  
  while (current_time < end_time)
  {
    // now update the current time
    current_time = millis();

   for ( i = 8; i < 10; i++)
    {
      int val = analogRead(i);
       if( thres_max[i] < val )
       {
         thres_max[i] = val;
       }

       if( thres_min[i] > val )
       {
         thres_min[i] = val;
       }
    }  
  }

  robot_stop();

  for( i = 8 ; i < 10 ; i++)
  {
    thres[i] = ( ( thres_max[i] + thres_min[i] )  /  2 ) / 5 ;
  }
  
  for( a = 500,i = 8 ; i < 10 ; i++,a++)
  {
        EEPROM.write(a, thres[i]);
  }
}


void thres_read()
{
    int i,a;
    for(a =  500 , i = 8 ; i < 10 ; i++,a++)
    {
       thres[i] = 5 *  EEPROM.read(a);  
    }

    color = EEPROM.read(1);
}


