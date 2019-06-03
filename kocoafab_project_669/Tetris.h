#include "Stone.h"
#include "Sound.h"

#define BUTTON_LEFT 13
#define BUTTON_RIGHT 12
#define BUTTON_ROT 11
#define BUTTON_DOWN 10

bool BUTTON_LEFT_LAST = false;
bool BUTTON_RIGHT_LAST = false;
bool BUTTON_ROT_LAST = false;
bool BUTTON_DOWN_LAST = false;
long points = 0;
long points2 = 0;
int i=4;
const int SPKER=9; //
const int LED2=8; //
Stone currentStone;
bool debounce(bool last , int BUTTON){
  bool current = digitalRead(BUTTON);
  if(last ==current){
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;
}
  


void Te_Init()
{

  currentStone = St_InitStone();
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_ROT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);//
}

void Te_Draw()
{
  St_Print(currentStone, true);
  Dp_Draw();
  St_Print(currentStone, false);
}

void Te_AddPoints(long p)
{
  int j=0;
  pinMode(SPKER,OUTPUT);
  pinMode(LED2,OUTPUT);
  points += p;
  lcd.setCursor(10, 0);
  lcd.print(points);
   if(points / 100 > i){//
    for(j=0;j<3;j++){
     digitalWrite(SPKER,HIGH);
     digitalWrite(LED2,LOW);
     delay(400);
     digitalWrite(SPKER,LOW);
     digitalWrite(LED2,HIGH);
     delay(400);
    }
      digitalWrite(SPKER,LOW);
      digitalWrite(LED2,LOW);
    for(j=0;j<(((((points/500)+1)*500)-(((points2/500)+1)*500))/500);j++){
    i +=5;
    }     
  }//
  points2 = points;
}

void Te_DeleteRow(int row) // 한줄 삭제시 처리되는 함수
{
  bool sw = true;
  for (int i = 0; i < 15; i++)
  {
    Dp_DrawLine(1, row, 8, true, sw);
    Dp_DrawLine(0,0,10,true,!sw); // Linie Oben H
    Dp_DrawLine(0,15,10,true,!sw); // Linie Unten H
    Dp_DrawLine(0,0,16,false,!sw); // Linie Links V
    Dp_DrawLine(9,0,16,false,!sw); // Linie Rechts V
    Dp_Draw();
    delay(90);
    sw = sw ? false : true;
  }
  Dp_DrawLine(1, row, 8, true, false);
  Dp_DrawLine(0,0,10,true,true); // Linie Oben H
  Dp_DrawLine(0,15,10,true,true); // Linie Unten H
  Dp_DrawLine(0,0,16,false,true); // Linie Links V
  Dp_DrawLine(9,0,16,false,true); // Linie Rechts V
  Dp_Draw();
  for (int zeile = row; zeile > 2; zeile--)
  {
    for (int x = 1; x < TE_WIDTH + 1; x++)
    {
      Dp_SetPixel(x, zeile, Dp_GetPixel(x, zeile - 1));
    }
  }
}

void Te_CheckRows() // 한줄을 검사하는 함수
{
  byte rowWins = 0;
  for (int zeile = TE_HEIGHT; zeile > 0; zeile--)
  {
    bool zeileVoll = true;
    for (int x = 1; x < TE_WIDTH; x++)
    {
      if (!Dp_GetPixel(x, zeile)) 
      {
        zeileVoll = false;
        break;
      }
    }
    if (zeileVoll) 
    {
      rowWins++;
      Te_DeleteRow(zeile);
      zeile++;
    }
  }
  if (rowWins > 0) 
    Te_AddPoints(random(9, 15) * (10 + pow(3,rowWins) * 10));

}

void Te_Reload()
{
  for (int row = 1; row < TE_HEIGHT + 1; row++)
  {
    Dp_DrawLine(1, row, 8, true, true);
    Dp_Draw();
    delay(60);
  }
  delay(400);
  for (int row = TE_HEIGHT; row >= 1 ; row--)
  {
    Dp_DrawLine(1, row, 8, true, false);
    Dp_Draw();
    delay(60);
  }
  currentStone = St_InitStone();
  points = 0;
  lcd.setCursor(10, 0);
  lcd.print("0     ");
  lcd.setCursor(3, 1);
  lcd.print("             ");
}

void Te_Update(long frameCount)
{
  if (frameCount % 40  == 0)
  {
    currentStone.y++;
    if (St_HitTest(currentStone)) 
    {
      currentStone.y--;
      for(int i = 0; i < 5; i++)
      {
        St_Print(currentStone, true);
        Dp_Draw();
        delay(60);
        St_Print(currentStone, false); // 블록 바닥에 닿을때
        Dp_Draw();
        delay(60);
      }
      St_Print(currentStone, true);
      currentStone = St_InitStone();
      Dp_Draw();
      if (St_HitTest(currentStone))
      {
        gameOverSing();//Gameover 시 노래
        lcd.setCursor(3, 1);
        lcd.write("Game Over!");
        delay(1000);
        while (!digitalRead(BUTTON_LEFT) || !digitalRead(BUTTON_RIGHT));//게임 종료시 처리
        Te_Reload();
      }
      Te_AddPoints(random(1, 4) * 10);
      Te_CheckRows();
      return;
    }
  }

  if(frameCount % 10) 
  {
    BUTTON_DOWN_LAST=false;
  }
/*각 버튼을 눌렀을 경우 처리하는 단계*/
 bool LEFT =!debounce(BUTTON_LEFT_LAST ,  BUTTON_LEFT);
 bool RIGHT = !debounce(BUTTON_RIGHT_LAST ,  BUTTON_RIGHT);
 bool LOWER = !debounce(BUTTON_DOWN_LAST ,  BUTTON_DOWN);
 bool ROT =!debounce(BUTTON_ROT_LAST ,  BUTTON_ROT);
  if ( !LEFT )
  {
    if (!BUTTON_LEFT_LAST)
    {
      BUTTON_LEFT_LAST = true;

      
      currentStone.x--;
      if (St_HitTest(currentStone))
        currentStone.x++;
    }
  }
  else BUTTON_LEFT_LAST = false;

  if (!RIGHT)
  {
    if (!BUTTON_RIGHT_LAST)
    {
      BUTTON_RIGHT_LAST = true;

      
      currentStone.x++;
      if (St_HitTest(currentStone))
        currentStone.x--;
    }
  }
  else BUTTON_RIGHT_LAST = false;

  if (!ROT)
  {
    if (!BUTTON_ROT_LAST)
    {
      BUTTON_ROT_LAST = true;

      // Versuche Stein zu verschieben
      St_Rotate(&currentStone);
      if (St_HitTest(currentStone))
        St_BackRotate(&currentStone);
    }
  }
  else BUTTON_ROT_LAST = false;

  if (LOWER)
  {
    if (!BUTTON_DOWN_LAST)
    {
      BUTTON_DOWN_LAST = true;

      // Versuche Stein zu verschieben
      currentStone.y++;
      if (St_HitTest(currentStone))
        currentStone.y--;
    }
  }
  else BUTTON_DOWN_LAST = false;
}
