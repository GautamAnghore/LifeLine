// MEDICAL STORE MANAGEMENT
// GRAPHICS FILE
// TEAM CYBROS
// MEDGRAPH.H
/* 

void rect(int width,int height,int x,int y,int bcolor,int fcolor)
		rectangle of width , height and from coordinate x,y with background color bcolor

void stdD()
		standard defaults sets standard colors black and white
		
void special_rect(int width,int height,int x,int y,int bcolor,int fcolor,char ch)
		rectangle with special character passed from ch
		
void OutBox(int width,int height,int x,int y,int bcolor,int fcolor,char *ch)
		rectangle with double boundry , and title "" passed in *ch
		
void special_OutBox(int width,int height,int x,int y,int bcolor,int fcolor,char *ch,char bk,char tleft,char left,char bleft,char bottom,char bright,char right,char tright,char top)
		special ractangle with bk passed character background *ch in heading and boundry of passed boundry characters		
		
void write_middle(int width,int height,int x,int y,int bcolor,int fcolor,char *ch)
		writes the "" *ch in the middle of the box of width "width" and at the top
		
void write(int width,int height,int x,int y,int fcolor,char *ch)
		writes the "" *ch within the height and width given // main purpose to maintain the newlines

void clearS(int bcolor)
		clearscreen with bcolor to MAXx * MAXy rectangle
*/

/*

----------------OUTPUT SCREENS----------------------------------------
void base_screen(char *head,char *foot);// main base screen i.e. background screen with *head = text to write on top *foot = text to write on bottom
										// if *head and *foot left null , prints default values
void clear_base();//base background fill

void update_time(int x,int y,int bcolor, int fcolor);// update the current time at x,y with bcolor,fcolor

void menu_box(int width, int height, int x,int y, int bcolor ,int fcolor,char *ch);// menu box with heading *ch 
void menu_box_input(int width, int height, int x,int y, int bcolor ,int fcolor,char *ch);// menu box with heading *ch and with box for taking input;

*/

#include <time.h>
#include <string.h>
//userdefined
#include <medtext.h>

#define W 79  //size of screen -> X
#define H 25 // size of screen -> Y

void rect(int width,int height,int x,int y,int bcolor,int fcolor)
{
	int yy,xx;

	textcolor(fcolor);
	textbackground(bcolor);

	for(yy=1;yy<=height;yy++)
	{
		gotoxy(x,y);
		for(xx=1;xx<=width;xx++)
		{
			cprintf(" ");

		}
		y++;

	}

}

void stdD()
{

	textcolor(15);
	textbackground(1);

}

void special_rect(int width,int height,int x,int y,int bcolor,int fcolor,char ch)
{
	int yy,xx;

	textcolor(fcolor);
	textbackground(bcolor);

	for(yy=y;yy<height+y;yy++)
	{
		for(xx=x;xx<x+width;xx++)
		{
			gotoxy(xx,yy);
			cprintf("%c",ch);
		}

	}

}


void OutBox(int width,int height,int x,int y,int bcolor,int fcolor,char *ch)
{

	int xxx=x;
	int yyy=y;

	int xx,yy;
	int l;

	rect(width,height,x,y,bcolor,fcolor);

	textcolor(fcolor);
	textbackground(bcolor);


	gotoxy(x,y);

	//side line - 1&3
	for(xx=1;xx<=width;xx++)
	{
		gotoxy(xxx,yyy);
		cprintf("Í");

		gotoxy(xxx,yyy+height-1);
		cprintf("Í");

		xxx++;
	}

	xxx=x;

	//side line - 2&4
	for(yy=1;yy<=height;yy++)
	{
		gotoxy(xxx,yyy);
		cprintf("º");

		gotoxy(xxx+width-1,yyy);
		cprintf("º");

		yyy++;
	}
	yyy=y;

	//End -1
	gotoxy(x,y);
	cprintf("É");

	//End -2
	gotoxy(x+width-1,y);
	cprintf("»");

	//End -3
	gotoxy(x,y+height-1);
	cprintf("È");

	//End -4
	gotoxy(x+width-1,y+height-1);
	cprintf("¼");


	//LABLE

	l=strlen(ch);
	xxx=x+(width/2)-(l/2);
	gotoxy(xxx,yyy);
	cprintf("%s",ch);

}

void special_OutBox(int width,int height,int x,int y,int bcolor,int fcolor,char *ch,char bk,char tleft,char left,char bleft,char bottom,char bright,char right,char tright,char top)
{

	int xxx=x;
	int yyy=y;

	int xx,yy;
	int l;

	special_rect(width,height,x,y,bcolor,fcolor,bk);

	textcolor(fcolor);
	textbackground(bcolor);


	gotoxy(x,y);

	//side line - 1&3
	for(xx=1;xx<=width;xx++)
	{
		gotoxy(xxx,yyy);
		cprintf("%c",top);

		gotoxy(xxx,yyy+height-1);
		cprintf("%c",bottom);

		xxx++;
	}

	xxx=x;

	//side line - 2&4
	for(yy=1;yy<=height;yy++)
	{
		gotoxy(xxx,yyy);
		cprintf("%c",left);

		gotoxy(xxx+width-1,yyy);
		cprintf("%c",right);

		yyy++;
	}
	yyy=y;

	//End -1
	gotoxy(x,y);
	cprintf("%c",tleft);

	//End -2
	gotoxy(x+width-1,y);
	cprintf("%c",tright);

	//End -3
	gotoxy(x,y+height-1);
	cprintf("%c",bleft);

	//End -4
	gotoxy(x+width-1,y+height-1);
	cprintf("%c",bright);


	//LABLE

	l=strlen(ch);
	xxx=x+(width/2)-(l/2);
	gotoxy(xxx,yyy);
	cprintf("%s",ch);

}

void write_middle(int width,int height,int x,int y,int bcolor,int fcolor,char *ch)
{

	int l;
	int xxx;

	textcolor(fcolor);
	textbackground(bcolor);
	//LABLE

	l=strlen(ch);
	xxx=x+(width/2)-(l/2);
	gotoxy(xxx,y);
	cprintf("%s",ch);
}

void write(int width,int height,int x,int y,int fcolor,char *ch)
{
	int w,h;
	textcolor(fcolor);
	gotoxy(x,y);

	w=0;h=0;

	while(*ch!=NULL)
	{
		if(h<=height)
		{
		printf("%c",*ch);
		ch++;
		w++;
			if(w==width)
			{
				w=0;
				h++;
				gotoxy(x,++y);
			}
		}
	}
}


void clearS(int bcolor)
{
	int x,y;
	textbackground(bcolor);
	for(x=0;x<=W;x++)
		for(y=0;y<=H;y++)
		{
			gotoxy(x,y);
			cprintf(" ");
		}
}

//----------------------------------------------- OUTPUT SCREEN FUNCTIONS -----------------------------------------------------

void menu_box(int width , int height , int x ,int y, int bcolor ,int fcolor ,char *ch)
{
	special_OutBox(width,3,x,y,bcolor,fcolor,"",'Ý','Ú','³','Æ','Í','µ','³','¿','Ä');
	special_OutBox(width,height-3,x,y+3,bcolor,fcolor,"",' ','³','³','À','Ä','Ù','³','³',' ');
	write_middle(width,3,x,y+1,bcolor,15,ch);
}

void menu_box_input(int width , int height , int x ,int y, int bcolor ,int fcolor ,char *ch)
{
	special_OutBox(width,3,x,y,bcolor,fcolor,"",'Ý','Ú','³','Æ','Í','µ','³','¿','Ä');
	special_OutBox(width,height-6,x,y+3,bcolor,fcolor,"",' ','³','³','Æ','Í','µ','³','³',' ');

	special_OutBox(width,3,x,height+y-3,bcolor,fcolor,"",'±','³','³','À','Ä','Ù','³','³','±');
	special_rect(width-2,2,x+1,height+y-3,1,7,'Û');
	gotoxy(x+2,height+y-2);
	textcolor(1);
	textbackground(7);
	fflush(stdout);
	cprintf("Enter the choice :");

	write_middle(width,3,x,y+1,bcolor,15,ch);
}

void update_time(int x, int y , int bcolor, int fcolor)
{
	time_t t;
	time(&t);
	
	textcolor(fcolor);
	textbackground(bcolor);
	
	gotoxy(x,y);
	cprintf("%s",ctime(&t));
	gotoxy(x,y);
}

void base_screen(char *head,char *foot)
{
	int l,x,y;
	
	//base
	special_rect(W,H,1,1,7,9,'°');

	//head
	special_rect(W,1,1,1,7,8,' ');

	l=strlen(head);

	if(l!=0)
	{
		x=(W/2)-(l/2);
		gotoxy(x,1);

		text_output(head,7,8);
	}
	else
	{
		gotoxy(1,1);
		text_output(" CYBROS PROJECT 1.0 ",7,4);
		gotoxy(21,1);
		text_output("³",7,0);
		text_output("   MEDICAL STORE MANAGEMENT   ",7,8);
		text_output("³ ",7,0);
		update_time(54,1,7,1);
		textcolor(8);
	}

	//foot
	special_rect(W,1,1,H,7,8,' ');

	l=strlen(foot);

	if(l!=0)
	{
		x=(W/2)-(l/2);
		gotoxy(x,H);

		text_output(foot,7,8);
	}
	else
	{
		gotoxy(1,H);
		text_output("  CREDITS | ",7,4);
		text_output("Gautam : Tanuj : Satrajit : Harshit ",7,0);
		text_output("         ³ EXIT : 0",7,8);
	}

}

void clear_base()
{
	special_rect(W,H-2,1,2,7,9,'°');
}