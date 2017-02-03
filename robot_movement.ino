void robot_forward(int l , int r)
{
//  int left_speed = (int)l;
//  int right_speed = (int)r;
  
  analogWrite(left_speed_pin, l);//enB
  analogWrite(right_speed_pin, r);//enA

  digitalWrite(LEFTMOTORA, HIGH);
  digitalWrite(LEFTMOTORB, LOW);

  digitalWrite(RIGHTMOTORA, HIGH);
  digitalWrite(RIGHTMOTORB, LOW);
}

void robot_backward(int l , int r)
{
//  int left_speed = (int)l;
//  int right_speed = (int)r;
  
  analogWrite(left_speed_pin, l);
  analogWrite(right_speed_pin, r);

  digitalWrite(LEFTMOTORA, LOW);
  digitalWrite(LEFTMOTORB, HIGH);

  digitalWrite(RIGHTMOTORA, LOW);
  digitalWrite(RIGHTMOTORB, HIGH);


}

void robot_rotate_left(int l , int r)
{
//  int left_speed = (int)l;
//  int right_speed = (int)r;
  
  analogWrite(left_speed_pin, l);//enB
  analogWrite(right_speed_pin, r);//enA

  digitalWrite(LEFTMOTORA, LOW);
  digitalWrite(LEFTMOTORB, HIGH);

  digitalWrite(RIGHTMOTORA, HIGH);
  digitalWrite(RIGHTMOTORB, LOW);
}

void robot_rotate_right(int l , int r)
{
//  int left_speed = (int)l;
//  int right_speed = (int)r;
  
  analogWrite(left_speed_pin, l);//enB
  analogWrite(right_speed_pin, r);//enA

  digitalWrite(LEFTMOTORA, HIGH);
  digitalWrite(LEFTMOTORB, LOW);

  digitalWrite(RIGHTMOTORA, LOW);
  digitalWrite(RIGHTMOTORB, HIGH);
}
void robot_right(int l , int r)
{
//  int left_speed = (int)l;
//  int right_speed = (int)r;
  analogWrite(left_speed_pin, l);
  analogWrite(right_speed_pin, r);

  digitalWrite(LEFTMOTORA, HIGH);
  digitalWrite(LEFTMOTORB, LOW);

  digitalWrite(RIGHTMOTORA, LOW);
  digitalWrite(RIGHTMOTORB, LOW);

}

void robot_left(int l , int r)
{
//  int left_speed = (int)l;
//  int right_speed = (int)r;
  analogWrite(left_speed_pin, l);
  analogWrite(right_speed_pin, r);

  digitalWrite(LEFTMOTORA, LOW);
  digitalWrite(LEFTMOTORB, LOW);

  digitalWrite(RIGHTMOTORA, HIGH);
  digitalWrite(RIGHTMOTORB, LOW);

}

void robot_stop()
{
  int l = LFS ;
  int r = RFS;
  analogWrite(left_speed_pin, l);
  analogWrite(right_speed_pin, r);

  digitalWrite(LEFTMOTORA, LOW);
  digitalWrite(LEFTMOTORB, LOW);

  digitalWrite(RIGHTMOTORA, LOW);
  digitalWrite(RIGHTMOTORB, LOW);
}

void robot_right_90()
{   
  robot_rotate_right(LHS,RHS);
  delay(250);
  robot_stop();
}

void robot_left_90()
{
  robot_rotate_left(LHS,RHS);
  delay(250);
  robot_stop();
}

void robot_180()
{
  robot_stop();
  delay(500);

  //robot_rotate_right(87,95);
  robot_rotate_right(90,90);

  delay(550);
  robot_stop();
}

