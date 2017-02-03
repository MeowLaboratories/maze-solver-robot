void main_run_R()
{
  int i,flag, a;
  unsigned long current_time,end_time;

  lcd.print("calibrating");
  lcd.setCursor(0,1);
  lcd.print("POLOLU");
  delay(1000);
  
  robot_rotate_right(LHS,RHS);
  
  for (int i = 0; i < 250; i++)  // make the calibration take about 5 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }

  robot_stop();
  
  lcd.clear();
  lcd.print("press S1 to SCAN");
  lcd.setCursor(0,1);
  lcd.print("press S2 to SOLVE");
 
  while(1)
  {
   robot_stop();

    if(digitalRead(switch_1) == HIGH && digitalRead(switch_2) == LOW && digitalRead(switch_3) == LOW) break;
    if(digitalRead(switch_1) == LOW && digitalRead(switch_2) == HIGH && digitalRead(switch_3) == LOW) return_to_start_R();
  }

//  while(1)
//  {
//    line_status();
//    follow_the_damn_line();
//  }

  for(i = 1000; i <= 1500; i++)
  {
    EEPROM.write(i, 255);
  }

  delay(1000);
  line_status();
  while(node > 0)
  {
    robot_forward(LHS,RHS);
    line_status();
  }
  
  lcd.clear();
  i=0;
  a = 1000;
  while(1)
  {
     line_status();
     bulb(0,0,0);

     //cross or T or finish node
     if(node == 0b11 )
     {
       bulb(1,0,0);
       robot_forward(LHS,RHS);
       delay(100);
       
       robot_stop();
       delay(100);
       line_status();

       if(node == 0b11)// finish
       {
         maze[i] = 0;
         lcd.setCursor(i%15 , i / 15);
         lcd.print(maze[i]);
         i++;
         EEPROM.write(a, 0);
         a++;
         break;
       }

       else // cross or T
       {
         maze[i] = 3; //right
         lcd.setCursor(i%15 , i / 15);
         lcd.print(maze[i]);
         i++;
         EEPROM.write(a, 3);
         a++;
         
         robot_right_90();
         robot_stop();
         delay(100);
       }
     }

     // left or T or cross or finish
     else if(node == 0b10)
     {
         current_time = millis();
         end_time = current_time + 100;

          flag = 0;
          while (current_time < end_time)
          {
            robot_forward(LHS,RHS);
            current_time = millis();

            line_status();
            if(node == 0b11 || node == 0b01) flag = 1;
          }

          robot_stop();
          delay(100);

          line_status();
          if(node == 0b11) // end
          {
              bulb(1,0,0);
               maze[i] = 0;
               lcd.setCursor(i%15 , i / 15);
               lcd.print(maze[i]);
               i++;
               EEPROM.write(a, 0);
                a++;
               break;
          }

          else if(flag == 1) // T or cross
          {
                bulb(1,0,0);
               maze[i] = 3; //right
               lcd.setCursor(i%15 , i / 15);
               lcd.print(maze[i]);
               i++;
               EEPROM.write(a, 3);
               a++;
               robot_right_90();
               robot_stop();
               delay(100);
          }

          else
          {
            if(positionn == 0 || positionn == 7000) //right 90
            {
              robot_right_90();
              delay(100);
            }

            else //junction
            {
               bulb(1,0,0);
                maze[i] = 2; //straight
               lcd.setCursor(i%15 , i / 15);
               lcd.print(maze[i]);
               i++;
               EEPROM.write(a, 2);
                a++;
               robot_right_90();
               robot_stop();
               delay(100);
            }
          }
     }

     // right or T or cross or finish
     else if(node == 0b01)
     {
         current_time = millis();
         end_time = current_time + 100;

          flag = 0;
          while (current_time < end_time)
          {
            robot_forward(LHS,RHS);
            current_time = millis();

            line_status();
            if(node == 0b11 || node == 0b10) flag = 1;
          }

          robot_stop();
          delay(100);

          line_status();
          if(node == 0b11) // end
          {
               bulb(1,0,0);
               maze[i] = 0;
               lcd.setCursor(i%15 , i / 15);
               lcd.print(maze[i]);
               i++;
               EEPROM.write(a, 0);
               a++;
               break;
          }

          else if(flag == 1) // T or cross
          {
               bulb(1,0,0);
               maze[i] = 3; //right
               lcd.setCursor(i%15 , i / 15);
               lcd.print(maze[i]);
               i++;
               EEPROM.write(a, 3);
                 a++;
               robot_right_90();
               robot_stop();
               delay(100);
          }

          else
          {
            if(positionn == 0 || positionn == 7000) //right 90
            {
              robot_left_90();
              delay(100);
            }

            else //junction
            {
               bulb(1,0,0);
                maze[i] = 3; //right
               lcd.setCursor(i%15 , i / 15);
               lcd.print(maze[i]);
               i++;
               EEPROM.write(a, 3);
               a++;
               delay_follow_line(50);
            }
          }
     }

     
     else if(positionn == 0 || positionn == 7000)
     {
      robot_forward(LHS,RHS);
      delay(110);
      robot_180();
      


                 maze[i] = 4; //back
                 lcd.setCursor(i%15 , i / 15);
                 lcd.print(maze[i]);
                 i++;
                 EEPROM.write(a, 4);
                 a++;

                 delay(100);
     }

     

     else follow_the_damn_line();

  }

  



  robot_180();
 
  return_to_start_R();
}

void return_to_start_R()
{
  int i, a, len;
  unsigned long current_time,end_time;
  lcd.clear();
  lcd.print("puchi");
  lcd.setCursor(0,1);
  lcd.print("calculating");

  for(i = 1000, a = 0; ;i++, a++)
  {
    maze[a] = EEPROM.read(i);
    if(maze[a] == 0)
    {
      break; 
    }
  }
  int flag, j;
  bulb(1,0,0);

//solve
  while(1)
    {

        for( i = 0 ; maze[i] != 0 ; i++)
        {
            if(maze[i] == 4 && i != 0) //B
            {
                if(maze[i-1] == 1 && maze[i+1] == 3) //LBR = B
                {
                    maze[i-1] = 5;
                    maze[i] = 4;//
                    maze[i+1] = 5;
                }
                if(maze[i-1] == 3 && maze[i+1] == 2) // RBS = L
                {
                    maze[i-1] = 5;
                    maze[i] = 1;//L
                    maze[i+1] = 5;
                }

                if(maze[i-1] == 3 && maze[i+1] == 1) //RBL = B
                {
                    maze[i-1] = 5;
                    maze[i] = 4; //B
                    maze[i+1] = 5;
                }

                if(maze[i-1] == 2 && maze[i+1] == 3)//SBR = L
                {
                    maze[i-1] = 5;
                    maze[i] = 1; //L
                    maze[i+1] = 5;
                }
                if(maze[i-1] == 2 && maze[i+1] == 2) // SBS = B
                {
                    maze[i-1] = 5;
                    maze[i] = 4; //B
                    maze[i+1] = 5;
                }

                if(maze[i-1] == 3 && maze[i+1] == 3)//RBR = S
                {
                    maze[i-1] = 5;
                    maze[i] = 2; //S
                    maze[i+1] = 5;
                }
            }
        }

        for( i = 0,j = 0 ; maze[i] != 0  ; i++)
        {
            if(maze[i] != 5)
            {
                proto[j] = maze[i];
                j++;
            }
        }

        proto[j] = 0;

        for(i = 0 ; i <= j ; i++)
        {
            maze[i] = proto[i];
        }


        flag = 0;
        for( i = 0 ; maze[i] != 0 ; i++)
        {
            if(maze[i] == 4)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0) break;
//        lcd.clear();
//        lcd.print(flag);
//        break; 
        
    }
    bulb(0,1,0);
    
    for(i = 2000; i <= 2500; i++)
    {
      EEPROM.write(i, 255);
    }

    for(i = 2000, a = 0; i <= 2500; i++, a++)
    {
      EEPROM.write(i, maze[a]);
      if(maze[a] == 0)
      {
        break;
      }
    }
    bulb(0,0,1);
    len = a;




/// goto
  line_status();
  while(node > 0)
  {
    robot_forward(LHS,RHS);
    line_status();
  }
  
  len--;
  while( len>= 0)
  {
        line_status();
        bulb(0,0,0);

     //cross or T or finish node
     if(node == 0b11 )
     {
       if(maze[len] == 2) delay_follow_line(100);
       else if(maze[len] == 3)
       {
        robot_forward(LHS,RHS);
        delay(100);
        robot_stop();
        delay(100);
        robot_left_90();
        delay(100);
       }

       else
       {
        robot_forward(LHS,RHS);
        delay(100);
        robot_stop();
        delay(100);

        robot_right_90();
        delay(100);
       }

       len--;
     }

     // left or T or cross or finish
     else if(node == 0b10)
     {
         current_time = millis();
         end_time = current_time + 100;

          flag = 0;
          while (current_time < end_time)
          {
            robot_forward(LHS,RHS);
            current_time = millis();

            line_status();
            if(node == 0b11 || node == 0b01) flag = 1;
          }

          robot_stop();
          delay(100);

          line_status();
          if(flag == 1) // T or cross
          {
              if(maze[len] == 2) delay_follow_line(30);
             
              else if(maze[len] == 3)
               {
                robot_left_90();
                delay(100);
               }
        
               else
               {
                robot_right_90();
                delay(100);
               }
        
               len--;
          }

          else
          {
            if(positionn == 0 || positionn == 7000) //left 90
            {
              robot_left_90();
              delay(100);
            }

            else //junction
            {
               if(maze[len] == 2) delay_follow_line(30);
               else if(maze[len] == 3)
               {
                robot_left_90();
                delay(100);
               }
        
               else
               {
                robot_right_90();
                delay(100);
               }
        
               len--;
            }
          }
     }

     // right or T or cross or finish
     else if(node == 0b01)
     {
         current_time = millis();
         end_time = current_time + 100;

          flag = 0;
          while (current_time < end_time)
          {
            robot_forward(LHS,RHS);
            current_time = millis();

            line_status();
            if(node == 0b11 || node == 0b10) flag = 1;
          }

          robot_stop();
          delay(100);

          robot_stop();
          delay(100);

          line_status();
          if(flag == 1) // T or cross
          {
              if(maze[len] == 2) delay_follow_line(30);
             
              else if(maze[len] == 3)
               {
                robot_left_90();
                delay(100);
               }
        
               else
               {
                robot_right_90();
                delay(100);
               }
        
               len--;
          }

          else
          {
            if(positionn == 0 || positionn == 7000) //right 90
            {
              robot_right_90();
              delay(100);
            }

            else //junction
            {
               if(maze[len] == 2) delay_follow_line(30);
               else if(maze[len] == 3)
               {
                robot_left_90();
                delay(100);
               }
        
               else
               {
                robot_right_90();
                delay(100);
               }
        
               len--;
            }
          }
      }
     
     else follow_the_damn_line();

    }

  line_status();
  while(node == 0)
  {
    follow_the_damn_line();
    line_status();
  }

  robot_forward(LHS,RHS);
  delay(250);
  robot_stop();

    lcd.clear();
    robot_stop();
    while(1)
    {
      lcd.print("MEOWWWWWWWWWWWWW");
      delay(200);
      bulb(1,1,1);

      delay(200);
      bulb(0,0,1);

      lcd.clear();
      
    }
    
}


//
