//else if(node == 0b10)
//     {
//       delay_follow_line(3);
//       line_status();
//
//           //cross or T or finish node
//             if(node == 0b11 )
//             {
//               bulb(1,0,0);
//               robot_forward(LHS,RHS);
//               delay(100);
//        
//               robot_stop();
//               delay(100);
//               line_status();
//        
//               if(node == 0b11)// finish
//               {
//                 maze[i] = 0;
//                 lcd.setCursor(i%15 , i / 15);
//                 lcd.print(maze[i]);
//                 i++;
//                 break;
//               }
//        
//               else // cross or T
//               {
//                 bulb(1,0,0);
//                 maze[i] = 1; //left
//                 lcd.setCursor(i%15 , i / 15);
//                 lcd.print(maze[i]);
//                 i++;
//                 robot_left_90();
//                  delay(100);
//               }
//             } 
//
//
//             //left or junction
//             else
//             {
//               robot_forward(LHS,RHS);
//               delay(100);
//        
//                 robot_stop();
//                 delay(100);
//                 line_status();
//
//               if(positionn == 0 || positionn == 7000)//left 90
//               {
//                robot_left_90();
//                delay(100);
//               }
//
//               else if(node == 0)//junction
//               {
//                 bulb(1,0,0);
//                 maze[i] = 1; //left
//                 lcd.setCursor(i%15 , i / 15);
//                 lcd.print(maze[i]);
//                 i++;
//                 robot_left_90();
//                 delay(100);
//               }
//
//               else 
//               {
//                    bulb(1,0,0);
//                     maze[i] = 0;
//                     lcd.setCursor(i%15 , i / 15);
//                     lcd.print(maze[i]);
//                     i++;
//                     break;
//               }
//             }
//     }
//
//     else if(node == 0b01)
//     {
//         delay_follow_line(3);
//         line_status();
//      
//
//           //cross or T or finish node
//             if(node == 0b11 )
//             {
//                bulb(1,0,0);
//               robot_forward(LHS,RHS);
//               delay(100);
//        
//               robot_stop();
//               delay(100);
//               line_status();
//        
//               if(node == 0b11)// finish
//               {
//                 maze[i] = 0;
//                 lcd.setCursor(i%15 , i / 15);
//                 lcd.print(maze[i]);
//                 i++;
//                 break;
//               }
//        
//               else // cross or T
//               {
//                 maze[i] = 1; //left
//                 lcd.setCursor(i%15 , i / 15);
//                 lcd.print(maze[i]);
//                 i++;
//                 robot_left_90();
//                  delay(100);
//               }
//             } 
//
//
//             //right or junction
//             else
//             {
//                robot_forward(LHS,RHS);
//                delay(100);
//        
//                 robot_stop();
//                 delay(100);
//                 line_status();
//
//               if(positionn == 0 || positionn == 7000)//left 90
//               {
//                robot_right_90();
//                delay(100);
//               }
//
//               else if(node == 0)//junction
//               {
//                bulb(1,0,0);
//                 maze[i] = 2; //straight
//                 lcd.setCursor(i%15 , i / 15);
//                 lcd.print(maze[i]);
//                 i++;
//                 delay_follow_line(30);
//                 
//               }
//
//               else 
//               {
//                bulb(1,0,0);
//                     maze[i] = 0;
//                     lcd.setCursor(i%15 , i / 15);
//                     lcd.print(maze[i]);
//                     i++;
//                     break;
//               }
//             }
//     }
