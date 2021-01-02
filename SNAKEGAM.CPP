#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<iostream.h>
#include<process.h>
#include<stdlib.h>
int x,y,h=460,w=640,fx,fy,tlen,farea[25][2],tailX[100],tailY[100],s,frame=0;
char score;
enum direction{STOP=0,UP,DOWN,LEFT,RIGHT};
direction dir;
void start();
void logic();
void draw();

void eat();

void start()
{
s=0;
score='0';
tlen=5;
x=w/2;
y=h/2;
fx= rand() %w;
fy= rand() %h;
dir=STOP;
eat();
}


void input()
{
if(kbhit())
 {
  switch(getch())
  {
  case 72:
	  if(dir!=DOWN)
	  dir= UP;
	  break;
  case 80:if(dir!=UP)
	  dir = DOWN;
	  break;
  case 77: if(dir!=LEFT)
	   dir = RIGHT;
	   break;
  case 75: if(dir!=RIGHT)
	    dir = LEFT;
	   break;
  case 'x': exit(1);
	  break;
  };
 }
}
void eat()
{
int c=1;
 for(int i=fx;i<fx+5;i++)
 {
  for(int j=fy;j<fy+5;j++)
  {
   farea[c][0]=j;
   farea[c][1]=i;
   c++;
  }
 }
}

void logic()
{

tailX[0]=x;
tailY[0]=y;

int prevX=tailX[0],prevY=tailY[0],prev2X,prev2Y;
if(s%5==0)
{

for(int t=tlen;t>0;t--)
{
//prev2X=tailX[t];
//prev2Y=tailY[t];
tailX[t]=tailX[t-1];
tailY[t]=tailY[t-1];

//prevX=prev2X;
//prevY=prev2Y;
}
}
if(x==5 || y==5 || x==(w-5) || y==(h-5) )
{
cleardevice();
outtextxy(w/2,h/2,"GAME OVER :(");
delay(1000);
exit(1);
}
if(x==fx || y==fy)
{
int f=0;
for(int i=0;i<25;i++)
{
  if(x+2==farea[i][1] && y+2==farea[i][0])
  {
  f++;
  }
}
  if(f>0)
  {
  int d=dir;
  fx= rand() %w;
  fy= rand() %h;
  eat();
  score++;
  tlen+=2;
  dir=d;
  }
}

switch(dir)
{

case UP: y--;    break;
case DOWN: y++;  break;
case LEFT: x--;  break;
case RIGHT: x++; break;
}
s++;
}

void draw()
{
cleardevice();
setbkcolor(BLACK);
setfillstyle(SOLID_FILL,RED);
setcolor(YELLOW);

//outer boundary:
bar(0,0,w,5);
bar(0,0,5,h-5);
bar(w-5,5,w,h-5);
bar(0,h-5,w,h);
//snake:
setfillstyle(SOLID_FILL,GREEN);
bar(x,y,x+6,y+6);
//SNAKE TAIL

for(int t=0;t<tlen;t++)
{
bar(tailX[t],tailY[t],tailX[t]+6,tailY[t]+6);
}
setfillstyle(SOLID_FILL,YELLOW);
//fruit :
//setcolor(GREEN);
bar(fx,fy,fx+6,fy+6);
//floodfill(fx,fy,GREEN);

//outtextxy(0,470,"SCORE :"+score);
//gotoxy(8,30);
//cout<<score;
//outtextxy(30,470,score);
}
//MAIN FUNCTION:
int main()
{
int gd=DETECT,gm,page=0;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
start();
while(1)
{
draw();
input();
logic();
delay(10);
//frame++;
}
closegraph();
return 0;
}