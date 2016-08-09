#include "s3e.h"
#include "Iw2D.h"
#include "stdio.h"

	
int Map[10][10],manX=0,manY=0;
CIw2DImage *grass;
CIw2DImage *three;
CIw2DImage *man;
	

void GameInit()
{
	Iw2DInit();
	grass = Iw2DCreateImage("0.png");
	three = Iw2DCreateImage("1.png");
	man = Iw2DCreateImage("2.png");
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			Map[i][j]=0;
		}
	}
	Map[0][0]=2;
	Map[3][0]=1;
	Map[3][2]=1;
	Map[5][1]=1;
}

void DrawMap()
{
	Iw2DSurfaceClear(0x11550030);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			switch(Map[i][j])
			{
			case 0: Iw2DDrawImage(grass,CIwFVec2((i-j+9)*16,(i+j)*8)); break;
			case 1: Iw2DDrawImage(three,CIwFVec2((i-j+9)*16,(i+j)*8)); break;
			case 2: Iw2DDrawImage(grass,CIwFVec2((i-j+9)*16,(i+j)*8));
					Iw2DDrawImage(man,CIwFVec2((i-j+9)*16,(i+j)*8));
					break;
			}
		}
	}
	Iw2DSurfaceShow();
}
void DrawMap(int x,int y)
{
	for(int i=x-1;i<x+1;i++)
	{
		if(i<0) i++;
 
		for(int j=y-1;j<y+1;j++)
		{
			if(j<0) j++;

			switch(Map[i][j])
			{
				case 0: Iw2DDrawImage(grass,CIwFVec2((i-j+9)*16,(i+j)*8)); break;
				case 1: Iw2DDrawImage(three,CIwFVec2((i-j+9)*16,(i+j)*8)); break;
				case 2: 
					Iw2DDrawImage(grass,CIwFVec2((i-j+9)*16,(i+j)*8));
					Iw2DDrawImage(man,CIwFVec2((i-j+9)*16,(i+j)*8));
					break;
				default:break;
			}
		}
	}
}


void DrawXp(int x)
{
	float j=(manX+manY)*8;
	for(int i=(manX-manY+9)*16;i<=(x-manY+9)*16;i++)
	{
		DrawMap(manX,manY);
		Iw2DDrawImage(man,CIwFVec2(i,j));
		Iw2DSurfaceShow();
		j=j+0.5;
	}
}

void DrawXm(int x)
{	
	float j=(manX+manY)*8;
	for(int i=(manX-manY+9)*16;i>=(x-manY+9)*16;i--)
	{
		DrawMap(manX,manY);
		Iw2DDrawImage(man,CIwFVec2(i,j));
		Iw2DSurfaceShow();
		j=j-0.5;
	}
}

void DrawYp(int y)
{
	int i=(manX-manY+9)*16;
	for(float j=(manX+manY)*8;j<=(manX+y)*8;j++)
	{
		j=j-0.5;
		DrawMap(manX,manY);
		Iw2DDrawImage(man,CIwFVec2(i,j));
		Iw2DSurfaceShow();
		i--;
	}
}
void DrawYm(int y)
{
	int i=(manX-manY+9)*16;
	for(float j=(manX+manY)*8;j>=(manX+y)*8;j--)
	{
		j=j+0.5;
		DrawMap(manX,manY);
		Iw2DDrawImage(man,CIwFVec2(i,j));
		Iw2DSurfaceShow();
		i++;
	}
}

void Move(int x,int y)
{
	if(manX<x)
	{
		for(int i=manX+1;i<=x;i++)
		{
			if(Map[i][manY]==0)
			{
				Map[manX][manY]=0;
				DrawXp(i);
				Map[i][manY]=2;
				manX=i;
			}
			else
			{
				if(Map[manX][manY+1]==0 && y>=manY)
				{
					Map[manX][manY]=0;
					DrawYp(manY+1);
					Map[manX][manY+1]=2;
					manY=manY+1;
					i--;
				}		
				else
				{
					if(Map[manX][manY-1]==0 && y<manY)
					{
						Map[manX][manY]=0;
						DrawYm(manY-1);
						Map[manX][manY-1]=2;
						manY=manY-1;
						i--;
					}
				}
			}
		}	
	}
	if(manX>x)
	{
		for(int i=manX-1;i>=x;i--)
		{
			if(Map[i][manY]==0)
			{
				Map[manX][manY]=0;
				DrawXm(i);
				Map[i][manY]=2;
				manX=i;
			}
			else
			{
				if(Map[manX][manY+1]==0 && y>=manY)
				{
					Map[manX][manY]=0;
					Map[manX][manY+1]=2;
					DrawYp(manY+1);
					manY=manY+1;
					i--;
				}		
				else
				{
					if(Map[manX][manY-1]==0 && y<manY)
					{
						Map[manX][manY]=0;
						Map[manX][manY-1]=2;
						DrawYm(manY-1);
						manY=manY-1;
						i--;
					}
				}
			}
		}
	}
	if(manY<y)
	{
		for(int i=manY+1;i<=y;i++)
		{
			if(Map[manX][i]==0)
			{
				Map[manX][manY]=0;
				DrawYp(i);
				Map[manX][i]=2;
				manY=i;
			}
			else if(Map[manX+1][manY]==0 && x>=manX)
			{
				Map[manX][manY]=0;
				Map[manX+1][manY]=2;
				DrawXp(manX+1);
				manX=manX+1;
				i--;
			}
			else if(Map[manX-1][manY]==0 && x<manX)
			{
				Map[manX][manY]=0;
				Map[manX-1][manY]=2;
				DrawXm(manX-1);
				manX=manX-1;
				i--;
			}
		}
	}
	if(manY>y)
		{
			for(int i=manY-1;i>=y;i--)
			{
				if(Map[manX][i]==0)
				{
				Map[manX][manY]=0;
				DrawYm(i);
				Map[manX][i]=2;
				manY=i;
				}
				else if(Map[manX+1][manY]==0 && x>=manX)
				{
					Map[manX][manY]=0;
					Map[manX+1][manY]=2;
					DrawXp(manX+1);
					manX=manX+1;
					i--;
				}
			else if(Map[manX-1][manY]==0 && x<manX)
				{
					Map[manX][manY]=0;
					Map[manX-1][manY]=2;
					DrawXm(manX-1);
					manX=manX-1;	
					i--;
				}
			}
		}
		DrawMap();
	}

void Go(float x,float y)
{
	int i,j;
	i=0;//(x-156)/16;
	j=(y+(156-x))/8;//(x-(160-y*2))/16;
//	i=(x/0.8944)/17.89;
//	j=(y/0.4472)/17.89;
	if(i<10 && i>=0 && j<10 && j>=0) Move(i,j);
}

int main()
{
	GameInit();
	DrawMap();
	
//	DrawMap();
    while(!s3eDeviceCheckQuitRequest())
    {
		s3ePointerUpdate();
		s3eKeyboardUpdate();
		if(s3ePointerGetState(S3E_POINTER_BUTTON_SELECT))
		{
			Go(s3ePointerGetX(),s3ePointerGetY());
		}
        // S3E applications should yield frequently
        s3eDeviceYield();
    }


    return 0;
}


