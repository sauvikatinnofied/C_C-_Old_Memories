//Game for 15-puzzle problem when i was so much angry againt her
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>


int x1=300,y1=60,x2=600,y2=420;
int rect_dimention[]={x1,y1,x2,y1,x2,y2,x1,y2};
int numbers[4][4]={
		    {15,1,8,13},
		    {9,10,12,2},
		    {3,7,4,0},
		    {5,11,6,14}
		  };
int step_no=0;
int to_mv_x=1000,to_mv_y=1000;
int blank_x,blank_y;
int num_change=0;
clock_t start,end;


void create_sound()
{
  sound(440);
  delay(100);
  nosound();
}
void draw_blank()
{
   int setblack[]={to_mv_x-3,to_mv_y-3,  to_mv_x+63,to_mv_y-3,
		   to_mv_x+63,to_mv_y+78, to_mv_x-3,to_mv_y+77};
   setcolor(BLACK);
   setfillstyle(CLOSE_DOT_FILL,LIGHTGREEN);
   fillpoly(4,setblack);
}
void animate()
{
   /*int setblack[]={to_mv_x-3,to_mv_y-3,  to_mv_x+63,to_mv_y-3,
		   to_mv_x+63,to_mv_y+78, to_mv_x-3,to_mv_y+77};
   setcolor(BLACK);
   setfillstyle(CLOSE_DOT_FILL,LIGHTGREEN);
   fillpoly(4,setblack);*/
   draw_blank();


   int x=blank_x;
   int y=blank_y;
   int draw_box[]={x,y,x+60,y,x+60,y+75,x,y+75};
   char c[3];
   setfillstyle(SOLID_FILL,BLACK);
   setcolor(LIGHTRED);
   fillpoly(4,draw_box);
   sprintf(c,"%d",num_change);
   setcolor(CYAN);
   settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
   if(num_change<10)
      outtextxy(x+22,y+15,c);
   else
      outtextxy(x+10,y+14,c);
     setcolor(RED);

}

int find_blank()
{
    int i=0,j=0;
    int position;
    for(i=0;i<4;i++)
      for(j=0;j<4;j++)
      if(numbers[i][j]==0)
      {
	blank_x=x1+12+j*72;
	blank_y=y1+10+i*85;
	position=10*i+j;//will return 32 for position numbers[3][2]
      }
      return position;
}

int draw_frame()
{
   //printing the outer rectangle
   start=clock();
   setcolor(BLUE);
   setfillstyle(CLOSE_DOT_FILL,LIGHTGREEN);
   fillpoly(4,rect_dimention);
   return 0;
}
int getkey()
{
   union REGS i,o;


   while(!kbhit())
	;
  i.h.ah=0;
  int86(22,&i,&o);
  return(o.h.ah);
 }

void show_step()
{
  char steps[3];
  setcolor(BLACK);
  sprintf(steps,"%d",step_no-1);
  outtextxy(20+textwidth("Steps Taken="),90,steps);
  sprintf(steps,"%d",step_no);
  setcolor(LIGHTGREEN);
  outtextxy(20,90,"Steps Taken=");
  setcolor(RED);
  outtextxy(20+textwidth("Steps Taken="),90,steps);

}
int draw_rectangles()
{
    //printing individual rectangles
   int i=0,j=0;
   for(int x=x1+12;x<x2;x+=72)
   {
     for(int y=y1+10;y<y2-10;y+=85)//-10 to avoid lower rectangles
     {
	 int rct_dmntn[]={x,y,x+60,y,x+60,y+75,x,y+75};
	 setcolor(RED);

	       //printf("%d %d ",i,j);
	       if(numbers[j][i]==0)
		draw_blank();
	       else
	       {
		   char c[3];
		   setfillstyle(SOLID_FILL,BLACK);
		   setcolor(LIGHTRED);
		   fillpoly(4,rct_dmntn);

		   sprintf(c,"%d",numbers[j][i]);//to make in reverse direction
		   setcolor(CYAN);
		   settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
		   if(numbers[j][i]<10)
		     outtextxy(x+22,y+15,c);
		   else
		     outtextxy(x+10,y+14,c);
		   setcolor(RED);
	       }
	  j++;if(j==4){j=0;i++;}
       }
     }
  return 0;
}

int test()//returns 0 if arranged properly else 1
{
  int i,j;
  int flag=1;
  for(i=0;i<4;i++)
     for(j=0;j<4;j++)
     {
       int x=i*4+j+1;
       if(i==3 && j==3) x=0;
       if(numbers[i][j]!=x)
	     flag=0;
     }
  return flag;
}

int change(int b_x,int b_y)
{
    fflush(stdin);
    int c=getkey();
    int temp;
    int ignore=0;
    if(c==80 && b_x==0)ignore=1;
    if(c==72 && b_x==3)ignore=1;
    if(c==75 && b_y==3)ignore=1;
    if(c==77 && b_y==0)ignore=1;
    if(!ignore)
    switch(c)
    {
       case 75://left key
	      {
	       step_no++;
	       show_step();
	       create_sound();
	       temp=numbers[b_x][b_y+1];
	       num_change=temp;
	       numbers[b_x][b_y+1]=0;
	       numbers[b_x][b_y]=temp;
	       to_mv_x=blank_x+72;
	       to_mv_y=blank_y;

	       break;
		}
       case 77://right key
	      {
	       step_no++;
	       show_step();
	       create_sound();

	       temp=numbers[b_x][b_y-1];
	       num_change=temp;
	       numbers[b_x][b_y-1]=0;
	       numbers[b_x][b_y]=temp;
	       to_mv_x=blank_x-72;
	       to_mv_y=blank_y;

		break;
		}

       case 80: //down key
	       {
		step_no++;
		show_step();
		create_sound();

		temp=numbers[b_x-1][b_y];
		num_change=temp;
		numbers[b_x-1][b_y]=0;
		numbers[b_x][b_y]=temp;
		to_mv_x=blank_x;
		to_mv_y=blank_y-85;

		break;
		}
       case 72://up key
	       {
		 step_no++;
		 show_step();
		 create_sound();


		 temp=numbers[b_x+1][b_y];
		 num_change=temp;
		 numbers[b_x+1][b_y]=0;
		 numbers[b_x][b_y]=temp;
		 to_mv_x=blank_x;
		 to_mv_y=blank_y+85;

		 break;

	       }
	       default:exit(0);
     }

    return 0;
}

int main(void)
{
  int i,j;
  int gdriver=DETECT,gmode,errorcode;

  initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
  errorcode=graphresult();
  if(errorcode!=grOk) //cosidering an error
  {
       printf("Graphics ERROR:%s",grapherrormsg(errorcode));
       printf("Program will be terminated");
       printf("Enter any key...");
       getch();
   }

  setlinestyle(SOLID_LINE,1,3);
  draw_frame();
  draw_rectangles();
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
  setcolor(YELLOW);
  outtextxy(20,44,"Use proper arrow keys ");
  outtextxy(20,60,"to nevigate the boxes...");
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
  setcolor(RED);
  rectangle(160,4,textwidth("15-Puzzle Game")+190,45);
  setcolor(LIGHTMAGENTA);
  outtextxy(180,6,"15-Puzzle Game");
  setcolor(BLUE);
  outtextxy(40,320,"Developed By");
  setcolor(YELLOW);
  outtextxy(80,360,"SOCKET");
  setcolor(CYAN);
  outtextxy(15,390,"GCETTS-March'12");
 // rectangle()
  int test_value=0;
  while(!test_value)
  {
     int b_postn=find_blank();
     int  b_postn_x=b_postn/10;
     int b_postn_y=b_postn%10;
     change(b_postn_x,b_postn_y);
     //draw_rectangles();
     animate();

     test_value=test();
     if(test_value==1)
     {
	end=clock();
	char tym[6];
	sprintf(tym,"%0.2f",(end-start)/CLK_TCK);
	for(int i=0;i<10;i++) create_sound();
	setcolor(CYAN);
	outtextxy(50,130,"Time Taken");
	setcolor(RED);
	outtextxy(70,160,tym);
	setcolor(GREEN);
	outtextxy(70+textwidth(tym),160,"Sec");
	setcolor(RED);
	outtextxy(2,200,"!CONGRATULATIONS!");
	setcolor(LIGHTMAGENTA);
	outtextxy(70,240,"YOU WIN");
     }
   }
   getch();
   closegraph();
   return 0;
}