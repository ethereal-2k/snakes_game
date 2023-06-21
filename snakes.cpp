#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
bool gameOver;
const int height=20;
const int width=20;

int x,y,fx,fy,score=0,tailx[100],taily[100],ntail;
enum edirections {STOP=0,UP,DOWN,LEFT,RIGHT};
edirections dir;

void Setup()
{
	gameOver=false;
	dir=STOP;
	x=width/2;
	y=height/2;
	fx=rand()%width;
	fy=rand()%height;
}
void Draw()
{
	system("CLS");
	cout<<"Score: "<<score<<endl;
	for(int i=0;i<width;i++)
		cout<<"#";
	cout<<endl;

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(j==0||j==width-1)
				cout<<"#";
			else if(i==y && j==x)
				cout<<"*";
			else if(i==fy && j==fx)
				cout<<"o";
			else
			{
				bool print=false;
				for(int k=0;k<ntail;k++)
					if(i==taily[k] && j==tailx[k])
					{
						cout<<"*";
						print=true;
					}
				if(!print)
					cout<<" ";
			}
		}
		cout<<endl;
	}

	for(int i=0;i<width;i++)
		cout<<"#";
	cout<<endl;
}
void Input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'w':
			dir=UP;
			break;
			case 'a':
			dir=LEFT;
			break;
			case 's':
			dir=DOWN;
			break;
			case 'd':
			dir=RIGHT;
			break;
			default:
			break;
		}
	}
}
void Logic()
{
	int prevx=tailx[0],prevy=taily[0];
	tailx[0]=x;
	taily[0]=y;
	int prev2x,prev2y;
	for(int i=1;i<ntail;i++)
	{
		prev2x=tailx[i];
		prev2y=taily[i];
		tailx[i]=prevx;
		taily[i]=prevy;
		prevx=prev2x;
		prevy=prev2y;
	}
	switch(dir)
	{
		case UP:
		y--;
		break;
		case DOWN:
		y++;
		break;
		case LEFT:
		x--;
		break;
		case RIGHT:
		x++;
		break;
	}
	if(x<0||x>width||y<0||y>height)
		gameOver=true;

	for(int i=0;i<ntail;i++)
	{
		if(x==tailx[i] && y==taily[i])
			gameOver=true;
	}

	if(x==fx && y==fy)
	{
		score+=10;
		fx=rand()%width;
		fy=rand()%height;
		ntail++;
	}
}
int main()
{
	Setup();
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(40);
	}
	cout<<endl<<"Game Over!"<<endl<<"Your Score: "<<score;
}