#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

/*
0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
*/

int main()
{
	uint16_t a[8][8];
	for(uint8_t i=0;i<8;i++)
		for(uint8_t j=0;j<8;j++)
			a[i][j]=0;
	srand(time(NULL));
	uint16_t start_x, start_y;
	start_x=rand()%8;
	start_y=rand()%8;
	bool goesDown=false,goesRight=false;
	int16_t y=start_y, x=start_x;
	a[y][x]=1;

//	cout<<"start x="<<x<<endl<<"start y="<<y<<endl;
//set position for better start
	while(!(((x==0)||(x==7))&&((y==0)||(y==7))))
	{
/*		sleep(1);
		for(uint8_t i=0;i<8;i++)
		{
			for(uint8_t j=0;j<8;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;*/
		if((x<4)&&(x>0))
		{
			if(a[y][--x]!=1)
				a[y][x]++;
		}
		else
			if((x>=4)&&(x<7))
				if(a[y][++x]!=1)
					a[y][x]++;
		//cout<<"x inside of set start pos="<<x<<endl<<"y inside of set start pos="<<y<<endl;
		if(((x==0)||(x==7))&&((y!=0)/*||*/&&(y!=7)))
			if((start_y%2!=0)&&(y>0))
			{
				if(a[--y][x]!=1)
					a[y][x]++;
			}
			else
				if((start_y%2==0)&&(y<7))
					if(a[++y][x]!=1)
						a[y][x]++;
	}
	//cout<<"x after set start pos="<<x<<endl<<"y after start pos="<<y<<endl;
	if(y==7)goesDown=true;
	//cout<<"before while"<<endl;
	//fill all position before start position
	while(y!=start_y)
/*
		sleep(1);
		for(uint8_t i=0;i<8;i++)
		{
			for(uint8_t j=0;j<8;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;*/
		//if(y<=start_y)
		{
		//	cout<<"while body y="<<y<<endl;
		//	cout<<"while body x="<<x<<endl;
			if(x==0)
			{
				//cout<<"goes right"<<endl;
				for(x=0;x<8;x++)
					if(a[y][x]!=1)
						a[y][x]++;
			}
			else
			{
				//cout<<"goes left"<<endl;
				for(x=7;x>=0;x--)
					if(a[y][x]!=1)
						a[y][x]++;
			}
			if(x>7)x=7;
			if(x<0)x=0;
			//y++;
		if(y<=start_y)
			y++;
		else
			y--;
		}
	//fill start row
	while(y==start_y)
	{
/*
		sleep(1);
		for(uint8_t i=0;i<8;i++)
		{
			for(uint8_t j=0;j<8;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;*/
		//cout<<"fill start row here"<<endl;
		//cout<<"fill start row x="<<x<<endl<<"fill start row y="<<y<<endl;
		if((a[y][x]!=1)||((y==start_y)&&(x==start_x)))
			if(x>start_x)
			{
				for(x;x>start_x;x--)
					a[y][x]++;
				goesRight=false;
			}
			else
				if(x<start_x)
				{
					for(x;x<start_x;x++)
						a[y][x]++;
					goesRight=true;
				}
				else
					if(x==0)
					{
						for(x=x+1;x<8;x++)
							a[y][x]++;
						goesRight=true;
					}
					else
					{
						for(x=x-1;x>=0;x--)
							a[y][x]++;
						goesRight=false;
					}
		else
			if(x==0)
			{
				x--;
				goesRight=false;
			}
			else
			{
				x++;
				goesRight=true;
			}
		if(goesDown)
			y--;
		else
			y++;
	}
	uint8_t count=0;
	//cout<<"x after start row="<<x<<endl<<"y after start pos="<<y<<endl;

	//fill all position before end of table
	while(true)
	{
/*		cout<<endl;
		sleep(1);
		for(uint8_t i=0;i<8;i++)
		{
			for(uint8_t j=0;j<8;j++)
				cout<<a[i][j]<<" ";
			cout<<endl;
		}*/
		//cout<<"fill all pos here"<<endl;
		//cout<<goesRight<<endl<<"continue y="<<y<<endl<<"continue x="<<x<<endl;
		if(goesRight)
		{
			for(x=x-1;x>=0;x--)
				if(x==start_x)
					break;
				else
					a[y][x]++;
			goesRight=false;
		}
		else
		{
			for(x=x+1;x<8;x++)
				if(x==start_x)
					break;
				else
					a[y][x]++;
			goesRight=true;
		}
		if(goesDown)
			y--;
		else
			y++;
		if(y==7||y==0)
			break;
	}

	//fill bottom/top of table
	if(goesRight)
		for(x=x-1;x>=0;x--)
		{
			a[y][x]++;
		/*	sleep(1);
			for(uint8_t i=0;i<8;i++)
			{
				for(uint8_t j=0;j<8;j++)
					cout<<a[i][j]<<" ";
				cout<<endl;
			}
			cout<<endl;*/
		}
	else
		for(x=x+1;x<8;x++)
		{
			a[y][x]++;
			/*sleep(1);
			for(uint8_t i=0;i<8;i++)
			{
				for(uint8_t j=0;j<8;j++)
					cout<<a[i][j]<<" ";
				cout<<endl;
			}
			cout<<endl;*/
		}
	goesRight=!goesRight;

	if(goesDown)
		y++;
	else
		y--;


	//Endspiel
	bool cont=true;
//	cout<<"preendspiel x="<<x<<endl<<"preendspiel y="<<y<<endl;

	while(cont)
	{
		sleep(1);
                for(uint8_t i=0;i<8;i++)
                {
                        for(uint8_t j=0;j<8;j++)
                                cout<<a[i][j]<<" ";
                        cout<<endl;
                }
		cout<<endl;
		if(x>7)x=7;
		if(x<0)x=0;

//		cout<<"endspiel x="<<x<<endl<<"endspiel y="<<y<<endl;
		if(x<start_x)
			if(!goesRight)
			{
				if(x>7)x=7;
				for(x;x<=start_x;x++)
				{
					a[y][x]++;
//					cout<<"Inside for:"<<endl<<"x="<<x<<endl<<"y="<<y<<endl;
					if(a[start_y][start_x]==2)
					{
						cont=!cont;
						break;
					}
				}
				x++;
			}
			else
			{
				for(x;x>=0;x--)
				{
					a[y][x]++;
//					cout<<"Inside for:"<<endl<<"x="<<x<<endl<<"y="<<y<<endl;
					if(a[start_y][start_x]==2)
					{
						cont=!cont;
						break;
					}
				}
				x--;
			}
		else
		{
			//cout<<"x>=start_x else there"<<endl;
			if(!goesRight)
			{
				//if(x<0)x=0;
				for(x;x<8;x++)
				{
					a[y][x]++;
//					cout<<"Inside for:"<<endl<<"x="<<x<<endl<<"y="<<y<<endl;
					if(a[start_y][start_x]==2)
					{
						cont=!cont;
						break;
					}
				}
				x--;
			}
			else
			{
				if(x>7)x=7;
				for(x;x>=start_x;x--)
				{
					a[y][x]++;
//					cout<<"Inside for:"<<endl<<"x="<<x<<endl<<"y="<<y<<endl;
					if(a[start_y][start_x]==2)
					{
						cont=!cont;
						break;
					}
				}
				x++;
			}
		}
		if(goesDown)
			y++;
		else
			y--;
		goesRight=!goesRight;
		cout<<endl;

	}

//	cout<<"Last x="<<x<<endl<<"Last y="<<y<<endl;
	for(uint8_t i=0;i<8;i++)
	{
		for(uint8_t j=0;j<8;j++)
			cout<<a[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
