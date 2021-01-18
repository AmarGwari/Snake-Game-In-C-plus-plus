//max width (horizontal) is 200 characters // recommended height is 55 characters.
//check for food->move->increase length
#include<iostream>
#include<stdlib.h>
#include<vector>
using namespace std;

// ONLY BORROWED PART OF THE CODE---------------------------------------------------
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}
// BORROWED PART ENDS -----------------------------------------------------------------


int speed = 0;
int isDead;
char ip = 'd';

vector<pair<long long,pair<long long, long long>>> snakebody;

char screen[55][200];

unsigned long long tick=0;
unsigned long long oldtick=0;
unsigned long long score = 0;

int foodX;
int foodY;

void renderSrc()
{
	int i,j;
	for(i=0;i<55;i++)
	{
		for(j=0;j<200;j++)
		{
			cout<<screen[i][j];
		}
		cout<<endl;
	}
}
void spawnFood()
{
	foodX = rand()%199;
	if(foodX == 0)
	{
		foodX = 1;
	}
	foodY = rand()%54;
	if(foodY == 0)
        {
                foodY = 1;
        }
	screen[foodY][foodX] = 'X';
}
bool ateFood()
{
	if(snakebody[0].second.first==foodY&&snakebody[0].second.second==foodX)
		score++;
	return(snakebody[0].second.first==foodY&&snakebody[0].second.second==foodX)?1:0; 
}

bool canmoved()
{
	return(snakebody[0].second.second+1 == snakebody[1].second.second)?false:true;
}
bool canmovea()
{
        return(snakebody[0].second.second-1 == snakebody[1].second.second)?false:true;
}
bool canmovew()
{
        return(snakebody[0].second.first-1 == snakebody[1].second.first)?false:true;
}
bool canmoves()
{
        return(snakebody[0].second.first+1 == snakebody[1].second.first)?false:true;
}

bool collision()
{
	if(snakebody[0].second.first==0||snakebody[0].second.first==54||snakebody[0].second.second==0||snakebody[0].second.second==199)
		return 1;
	for(long long i=1;i<snakebody.size();i++)
	{
		if(snakebody[0].second.first==snakebody[i].second.first&&snakebody[0].second.second==snakebody[i].second.second)
			return 1;
	}
	return 0;
}

void move()
{
	long long i,j,k,l,m,n;
	if(tick-oldtick>=speed)
	{ 
		oldtick = tick;
		k = snakebody[0].second.first;
		l = snakebody[0].second.second;
		if(kbhit())
		{	
			ip = getchar();
		}
		if(ip == 'd'&&canmoved())
		{
			snakebody[0].second.second = (snakebody[0].second.second+1);
		}
		else if(ip == 'a'&&canmovea())
		{
			snakebody[0].second.second = (snakebody[0].second.second-1);
		}
		else if(ip == 'w'&&canmovew())
                {
                        snakebody[0].second.first = (snakebody[0].second.first-1);
                }
                else if(ip == 's'&&canmoves())
                {
                        snakebody[0].second.first = (snakebody[0].second.first+1);
                }
		for(i=1;i<snakebody.size();i++)
		{
			m = snakebody[i].second.first;
			n = snakebody[i].second.second;
			snakebody[i].second.first = k;
			snakebody[i].second.second = l;
			k = m;
			l = n;
		}
		if(!ateFood())
			screen[m][n] = ' ';
		else
		{
			snakebody.push_back(make_pair(i,make_pair(m,n)));
		}
		isDead = (collision()?1:0);
	}
}
void drawSnake()
{
	for(int i=0;i<snakebody.size();i++)
	{
		screen[snakebody[i].second.first][snakebody[i].second.second] = 'O';	
	}
}
bool initialise()
{
	int i,j;
	for(i=0;i<55;i++)
	{
		screen[i][0] = '|';
		screen[i][199] = '|';
	}
	for(j=0;j<200;j++)
	{
		screen[0][j] = '-';
		screen[54][j] = '-';
	}
	for(i=1;i<54;i++)
	{
		for(j=1;j<199;j++)
		{
			screen[i][j] = ' ';
		}
	}
	snakebody.push_back(make_pair(0,make_pair(27,99)));
	snakebody.push_back(make_pair(1,make_pair(27,98)));
	drawSnake();
	return 0;
}
void renderScore()
{
	int i,j,k,l;
	unsigned long long dummy;
        for(i=0;i<snakebody.size();i++)
	{
		screen[snakebody[i].second.first][snakebody[i].second.second] = ' ';
	}
	screen[foodY][foodX] = ' ';
	char scoreChar[100];
	l=0;
	dummy = score;
	while(score>0)
	{
		k = score%10;
		scoreChar[l++] = char(k+48);
		score = score/10;
	}
	screen[27][95]='G';
	screen[27][96]='A';
	screen[27][97]='M';
	screen[27][98]='E';
	screen[27][99]=' ';
	screen[27][100]='O';
	screen[27][101]='V';
	screen[27][102]='E';
	screen[27][103]='R';
	screen[32][95]='S';
        screen[32][96]='C';
        screen[32][97]='O';
        screen[32][98]='R';
        screen[32][99]='E';
	screen[32][100]=' ';
	screen[32][101]='=';
	screen[32][102]=' ';
	if(dummy == 0)
	{
		screen[32][93] = '0';
		renderSrc();
		return;
	}
	for(i=0;i<l;i++)
	{
		screen[32][103+i] = scoreChar[l-i-1];
	}
	renderSrc();
}
int main()
{
	long long i,j,k,l,ch;
	isDead = initialise();
	while(!isDead)
	{
		if(ateFood()||tick==0)
		{
			spawnFood();
		}
		move();
		drawSnake();
		renderSrc();
		tick++;
		for(i=0;i<50000000;i++); //FrameRate regulation.
	}
	renderScore();
	return 0;
}
