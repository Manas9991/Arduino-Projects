/* ------------------Dodging obstacles--------------------
 * Toggle level using buttons at 9 and 8, press 10 to select.
 * Use buttons at 9 and 8 to toggle car, avoid incoming cars and walls.
 * Beat your highscore or compare with friends, Enjoy ! 
 * 
 * Algorithm:
 * First we select level in setup portion of game, using while loop.
 * There is a set of 19 cars which comes on screen turn by turn.
 * There x coordinates are fixed at first, and y coordinates are generated randomly.
 * Now these cars appear on screen and x coordinates get updated.
 * If, the coordinates of our car match with any of these cars, end game function ends it.
 * If our car goes into walls, again end game is called.
 * 
 * Created by Manas9991
 */

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pos = 0, score = 0, i, valx, lvl = 1;
const int num = 19;
int arrx[num], arry[num]; //arrays containing coordinates

void setup()
{
  lcd.begin(16, 2);
  pinMode(8, INPUT); //down
  pinMode(9, INPUT); //up
  pinMode(10, INPUT); //main
  //----------Setup game------------
  for(i = 0, valx = -51; i < num; i++, valx = valx+3)
  {
    arrx[i] = valx;
  }
  for(i = 0; i < num; i++)
  {
    arry[i] = random(0, 2);
  }
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  delay(1000);
  lcd.clear();
  select_level();
}

void loop()
{
  lcd.clear();
  //------position of our car---------
  if(digitalRead(8)==HIGH) 
  {
    if(pos == 1)
    {
      end_game();
    }
    else
    {
      pos = 1;
    }
  }
  if(digitalRead(9)==HIGH)
  {
    if(pos == 0)
    {
      end_game();
    }
    else
    {
      pos = 0;
    }
  }
  lcd.setCursor(12, pos);
  lcd.print("=");
  //---------Position of comp car----------
  for(i = 0; i < num; i++)
  {
    if((arrx[i] == 12) and (arry[i] == pos)) //check condition
    {
      end_game();
    }
    lcd.setCursor(arrx[i], arry[i]);
    lcd.print("*");
  }
  //--------Update location----------
  for(i = 0; i < num; i++)
  {
    arrx[i] = arrx[i] + 3;
    if(arrx[i] > 54)
    {
      arrx[i] = 0;
    }
  }
  //---------------------------------
  score++;  
  level(); //delays are according to level selected
}

void end_game()
{
  while(1)
  {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Crashed!");
    lcd.setCursor(4, 1);
    lcd.print("Score: ");
    lcd.setCursor(11, 1);
    lcd.print(score);
    delay(250);
  }
}

void level()
{
  if(lvl==1)
  {
    delay(700);
  }
  else if(lvl==2)
  {
    delay(450);
  }
  else if(lvl==3)
  {
    delay(300);
  }
}

void select_level()
{
  while(1)
  {
    lcd.setCursor(1, 0);
    lcd.print("Set level: ");
    lcd.setCursor(14, 0);
    lcd.print(lvl);
    if(digitalRead(9)==HIGH)
    {
      lvl++;
      if(lvl==4)
      {
        lvl = 1;
      }
    }
    if(digitalRead(8)==HIGH)
    {
      lvl--;
      if(lvl==0)
      {
        lvl = 3;
      }
    }
    if(digitalRead(10)==HIGH) //exit select level menu
    {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Get Ready! ");
      delay(750);
      break;
    }
    delay(250);
  }
}
