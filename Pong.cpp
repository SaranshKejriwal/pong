#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
#include <stdlib.h>//for rand
#include<stdio.h>//for sprintf
//#include<conio.h>
using namespace cv;
using namespace std;
Mat img(500,1000,CV_8U,Scalar(120,120,120));//global for mouse callback
int paddle1_h=250;
int paddle2_h=250;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
   
	  if ( event == EVENT_MOUSEMOVE )
     {

       
	paddle1_h=y;	
	if(y>460)
	{
		paddle1_h=460;//whole paddle stays on screen
	}	
	if(y<40)
	{
		paddle1_h=40;//whole paddle stays on screen
	}		

     }
}

int main()
{
	
	
	namedWindow("pong");//for mousecallback
	moveWindow("pong",200,200);
        int event;
	int x=40;//initial x coord of ball
	int y=250;//initial y coord of ball
	int slope= 10 + (rand() % (int)(60 - 10 + 1));//random slope here, between 10 and 60
	float m=slope/10;//initial slope
	int c=250;//initial y-intercept
	int score1=0,score2=0;
	bool x_head=0;//toggle to decide heading of ball
	for(;;)
		{
			Mat field(500,1000,CV_8U,Scalar(120,120,120));//blank field
			img=field.clone();//remove old ball trajectory
			putText(img,"Pong!",Point(400,60),FONT_HERSHEY_DUPLEX,2,Scalar(255),4);
			line(img,Point(500,80),Point(500,500),Scalar(60),5);//net
			if(x_head==0)
			{
				x++;//move rightwards
			}
			if(x_head==1)
			{
				x--;//move leftwards
			}

			y=m*x+c;//equation of trajectory
			if(y==10)//ball reached top
			{
				m=m*(-1);//m=(-m) for reflection
				c=y-m*x;//calculate new intercept based on last location and new slope
			}
			if(x==10)//ball reached left; no paddle
			{
				x_head=0;//prompt ball to move right
				m=m*(-1);//m=(-m) for reflection; this affects first trajectory
				score1-=10;//cut 10 points if paddle1 miss
				c=y-m*x;
			}
			if(x<50 && x>45 && paddle1_h-y<=87 && paddle1_h-y>=-87)//nested condition; ball reached left; paddle1 there
			{
				putText(img,"O",Point(x,y),FONT_HERSHEY_DUPLEX,2,Scalar(255),3);
				x_head=0;//prompt ball to move right
				score1+=10;//add 10 points if paddle hit
				//m=m*(-1);//m=(-m) for reflection; this affects first trajectory
				//c=y-m*x;
			}
			if(x>955 && x<960 && paddle2_h-y<=87 && paddle2_h-y>=-87)//nested condition; ball reached left; paddle2 there
			{
				putText(img,"O",Point(x,y),FONT_HERSHEY_DUPLEX,2,Scalar(255),3);//collision effect
				x_head=1;//prompt ball to move left
				score2+=10;//add 10 points if paddle hit
				//m=m*(-1);//m=(-m) for reflection; this affects first trajectory
				//c=y-m*x;
			}

			if(y==490)//ball reached bottom
			{
				m=m*(-1);//m=(-m) for reflection
				c=y-m*x;//calculate new intercept based on last location and new slope
			}
			if(x==990)//ball reached right
			{
				x_head=1;//prompt ball to move left now
				m=m*(-1);//m=(-m) for reflection
				c=y-m*x;
				score2-=10;//cut 10 points if paddle1 miss
			}

			ellipse(img,Point(x,y),Size(1,1),90,0,360,Scalar(250),30);//ball
			setMouseCallback("pong", CallBackFunc, NULL);
			ellipse(img,Point(20,paddle1_h),Size(40,1),90,0,360,Scalar(60),30);//paddle 1
			ellipse(img,Point(980,paddle2_h),Size(40,1),90,0,360,Scalar(60),30);//paddle 2
			putText(img,"w",Point(970,paddle2_h-25),FONT_HERSHEY_DUPLEX,1,Scalar(255),1);//place paddle2 markers
			putText(img,"s",Point(970,paddle2_h+50),FONT_HERSHEY_DUPLEX,1,Scalar(255),1);
			//putText(img,"mouse",Point(20,paddle1_h-25),FONT_HERSHEY_DUPLEX,1,Scalar(255),0.5);
			
			char s1[50];
	 		sprintf(s1,"Player 1:%d",score1);
	 		putText(img,s1,Point(300,100),FONT_HERSHEY_DUPLEX,1,Scalar(255),1);//display score
			char s2[50];
	 		sprintf(s2,"Player 2:%d",score2);
	 		putText(img,s2,Point(510,100),FONT_HERSHEY_DUPLEX,1,Scalar(255),1);

			if(score1>=50 && score1>score2)
			{
				putText(img,"Player 1 wins",Point(270,200),FONT_HERSHEY_DUPLEX,2,Scalar(255),4);
				
			}
			if(score2>=50 && score2>score1)
			{
				putText(img,"Player 2 wins",Point(270,400),FONT_HERSHEY_DUPLEX,2,Scalar(255),4);
				
			}




			imshow("pong",img);
			
			
			char c=waitKey(3);//this controls the speed of ball
			if(c=='b')
				{
					break;
				}
			//paddle 2 keyboard control
			if(c=='w')//press w to move paddle 2 up
				{
					paddle2_h-=30;
					if(paddle2_h<40)
						{
							paddle2_h=40;				
						}
				}
			if(c=='s')//press s to move paddle 2 down
				{
					paddle2_h+=30;
					if(paddle2_h>460)
						{
							paddle2_h=460;				
						}
				}
		}
	
	return 1;
}
