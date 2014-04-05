//------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------------//
//---                                                           CYBROS PROJECT 1.0                                                                         ---//
//---                                                           $   LIFE LINE   $                                                                          ---//
//---														 MEDICAL STOCK MANAGEMENT                                                                      ---//
//---						GAUTAM ANGHORE        HARSHIT THUKRAL          TANUJ SHRIVASTAV          SATRAJIT SAHANI                                       ---//
//------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------------//

//DS PROJECT
//DATE : 10/5/2013

//------------------------------------------------------------------------------------------------------------------------------------------------------------
// 																HEADER FILES
//------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>
#include <time.h>
#include <dos.h>

//<time.h> : for time_t , time(&t) , ctime(&t)
//<dos.h> : for struct date, getdate()


//USER DEFINED HEADER FILE
//INCLUDE MEDTEXT.H IN MEDGRAPH.H
//GRAPHIC AND TEXT FUNCTION DEFINATIONS
#include <medgraph.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------------------------
// 																STRUCTURES
//------------------------------------------------------------------------------------------------------------------------------------------------------------

// DATE STRUCTURE
struct mdate
{
	int dd;//date
	int mm;//month
	int yy;//year
}currentDate;


// USER ACCOUNTS STRUCTURE
struct userAcc
{
	char userName[30];	//name of user ->not used for login
	char userId[10];	//id used for login
	char userPass[30];	//password
	int level;	// level of authority
	
	//	3-root
	//	2-admin
	//	1-management
	//	0-sales
	
	struct userAcc *link;

}*userA,*user,userCurrent,root;

// for medical stock
struct medicine
{
	int key;
	char medName[30];
	char medId[10];
	int medNo;//number of items
	int medmrp;//mrp per item
	char batchId[10];
	int shelfRow,shelfCol;
	struct mdate addDate;
	struct mdate expDate;
	
	struct medicine *next;
	struct medicine *pre;
}*medA,*med,*medexA,*medex;

// for medical list
struct medId
{
	char medName[30];
	char medId[10];
	int key;
}medAcc;

// for medical multi linked list
struct medHead
{
	struct medHead *link;
	struct medicine *next;
	
	char medName[30];
	char medId[10];
	int expDays; 
}*medHeadA,*medHead;

struct transection
{
	int key;
	char pName[30];
	char userId[10];
	time_t t;
	struct mdate tDate;
	int amount;
	
	struct transection *next;
	struct transection *pre;
}*transA,*trans,*last;


//------------------------------------------------------------------------------------------------------------------------------------------------------------
// 															GLOBAL VARIABLES
//------------------------------------------------------------------------------------------------------------------------------------------------------------

int logout=0,esc=0;

//------------------------------------------------------------------------------------------------------------------------------------------------------------
// 															FUNCTION DECLARATION
//------------------------------------------------------------------------------------------------------------------------------------------------------------

//############## INTRO SCREEN ##################
void rx(int,int);
void fortis1(int,int);
void fortis2(int,int);
void bars(int,int);
void loading(int,int);
void load(int,int,int);
void iload(int,int,int);

void intro_screen();

//############## USER FUNCTIONS ################

// root user initialisation
void root_init(FILE *uin);

//user register screen
void user_register_window();

// user registration
void user_register(FILE *uin);

//user table <list with all details :traverse>
void user_display(FILE *uout);

//creates linked list of user data from uppf.swf
void user_llist(FILE *uout);

void user_login_window(int color);

//user login check
int user_login_check(FILE *uout,struct userAcc *userCurrent,int color);

//user login screen
int user_login_screen(FILE * uout,struct userAcc *userCurrent);

//################# DATE FUNCTIONS #########################

int digits(int n);	//tells the number of digits
char int_to_char(int i);	//converts number to char;
void date_input(struct mdate *d,int x,int y,int bcolor,int fcolor);
void date_output(struct mdate *d,int x,int y,int bcolor,int fcolor);
void get_currentDate(struct mdate *currentDate);
int days_month(int x);// number of days till month x
int date_substract(struct mdate d2,struct mdate d1);//considering d2>d1
int date_compare(struct mdate d1,struct mdate d2);//return 1 if 1st is greater and 2 if 2nd is greater
int date_equal(struct mdate d1,struct mdate d2);

//################# MEDICINE #########################
void id_creater(char name[],char id[],int n,int serial);//creates id for any name

void med_register(FILE *min);
int med_id_search(FILE *mid,struct medId *);//0 - search succesfull else last serial number
int med_stock_last();
void med_id_register(FILE *mid,struct medId *,int serial);// register the med name with id

// display and creates report of medical stock file data /* rstock.txt */
void med_stock_file_display();

// multi list of medical stock according to the expiry date
void med_multi_list();
void med_multi_list_display();

// creates single linked list in increasing order of expiry date
void med_expiry_list();
// creates and display report /* rexpire.txt */
void med_expiry_report();

//################# TRANSECTION #########################
int transection_last();
void transection();
void transection_log_currentuser();

void transection_log_user(struct userAcc *);
void transection_log_all();
void transection_log_today();
//################ MENU DISPLAY #######################
//main menu according to level returns the choice
char main_menu(int level);

char user_account_screen();
void user_account_window();


char stock_management_screen();
void stock_management_window();

char report_screen();
void report_window();

char user_profile_log_screen_1();
void user_profile_log_window_1();

char user_profile_log_screen_2();
void user_profile_log_window_2();

char user_profile_log_screen_3();
void user_profile_log_window_3();

void user_register_window();

void user_display_screen();

void user_display_window();

void med_register_screen();
void med_register_window();

void sales_transection();
void sales_transection_window();
//------------------------------------------------------------------------------------------------------------------------------------------------------------
// 															   	 MAIN
//------------------------------------------------------------------------------------------------------------------------------------------------------------

void main()
{
	// VARIABLES
	
	int gd=DETECT,gm,errorcode;
	int login=0;
	char option;
	
	//USER FILE POINTERS
	FILE *uin,*uout;
	//STOCK FILE POINTERS
	FILE *min,*mout;
	//FUNCTIONS
	
	get_currentDate(&currentDate);
	//************ INTRO SCREEN ***************
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	
	if((errorcode=graphresult())==grOk)
		intro_screen();
	closegraph();
	
	//************* LOGIN ********************
	clearS(0);
	esc=0;
		root_init(uin);	//root initialised
	login=user_login_screen(uin,&userCurrent);
	
	while(!esc)
	{
		option=main_menu(login);
		if(!esc)
		{
		switch(option)
		{
			case 'a':
			case 'A':option=user_account_screen();
						if(!esc)
						{
							switch(option)
							{
								case 'a':
								case 'A':user_register(uin);
										getch();
										break;
								case 'b':
								case 'B':user_display(uin);
										//	user_display_screen();
										getch();
										break;
								
							}
						}
					break;
			case 'b':
			case 'B':option=stock_management_screen();
						if(!esc)
						{
							switch(option)
							{
								case 'a':
								case 'A':med_register(min);
										break;
								case 'b':
								case 'B':break;
								case 'c':
								case 'C':med_stock_file_display();
											getch();
										break;
								
							}
						}
					break;
					
			case 'c':
			case 'C'://clearS(1);
					//gotoxy(1,1);
					transection();
					getch();
					break;
			case 'd':
			case 'D':option=report_screen();
						if(!esc)
						{
							switch(option)
							{
								case 'a':
								case 'A':med_expiry_report();
										getch();
										break;
								case 'b':
								case 'B':transection_log_all();
										getch();
										break;
								case 'c':
								case 'C':transection_log_today();
											getch();
								case 'd':
								case 'D':break;
								
								
							}
						}
					break;
			case 'e':
			case 'E':switch(login)
					{
						case 3:
						case 2:
								option=user_profile_log_screen_3();
								switch(option)
								{
									case 'a':
									case 'A':transection_log_currentuser();
											getch();
												break;
									case 'b':
									case 'B':break;
									case 'c':
									case 'C':transection_log_all();
											getch();
											break;
									case 'd':
									case 'D':
											break;
									
								}
								break;
						case 1:
								option=user_profile_log_screen_2();
								switch(option)
								{
									case 'a':
									case 'A':transection_log_currentuser();
											getch();
												break;
									case 'b':
									case 'B':break;
									
									case 'c':
									case 'C':
											break;
									
								}
								break;
						case 0:
								option=user_profile_log_screen_1();
								switch(option)
								{
									case 'a':
									case 'A':transection_log_currentuser();
											getch();
												break;
									
									case 'b':
									case 'B':
											break;
									
								}
								break;
					}
					break;
			case 'f':
			case 'F':
						menu_box(40,9,20,8,4,15," WARNING ");
						write_middle(40,6,20,12,4,15,"Do You Want To DELETE ALL USERS");
						write_middle(40,6,20,13,4,15,"(Y|N)");
						rect(38,1,21,15,7,15);
						gotoxy(40,15);
						textcolor(4);
						textbackground(7);
						option=getch();
						cprintf("%c",option);
						if(option=='y'||option=='Y')
						{
							uin=fopen("uppf.swf","w");
							
						//	fpos_t pos;

							arr_init(root.userName,30);
							strcpy(root.userName,"gautam");

							arr_init(root.userId,10);
							strcpy(root.userId,"gautam");

							arr_init(root.userPass,30);
							strcpy(root.userPass,"vidyayaamrit");

							root.level=3;

							//deformation of text
							text_encrypt(root.userName);
							text_encrypt(root.userId);
							text_encrypt(root.userPass);
							fflush(uin);
							fwrite(&root,sizeof(root),1,uin);

							fclose(uin);
						}
					break;
		}
		}
		/*else
		{
			menu_box(40,9,20,8,4,15," WARNING ");
			write_middle(40,6,20,12,4,15,"Do You Want To Exit");
			write_middle(40,6,20,13,4,15,"(Y|N)");
			rect(38,1,21,15,7,15);
			gotoxy(40,15);
			textcolor(4);
			textbackground(7);
			option=getch();
			cprintf("%c",option);
			if(option=='y'||option=='Y')
			{
				esc=1;
			}
		}
		*/
	}
	
	//main_menu(2);
	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------
// 															FUNCTION DEFINATIONS
//------------------------------------------------------------------------------------------------------------------------------------------------------------

//##################################################### INTRO SCREEN ############################################################

void rx(int x,int y)
{       int poly1[8],poly2[8];

	//cordinate for first poly
	poly1[0]=x+30;
	poly1[1]=y+50;

	poly1[2]=x+37;
	poly1[3]=y+47;

	poly1[4]=x+70;
	poly1[5]=y+100;

	poly1[6]=x+63;
	poly1[7]=y+105;
	setfillstyle(1,4);
	//delay(500);
	bar(x,y,x+10,y+80);
	bar(x+10,y,x+40,y+10);
	bar(x+10,y+40,x+40,y+50);
	bar(x+40,y,x+50,y+50);
	delay(500);
	fillpoly(4,poly1);

	poly2[0]=x+63;
	poly2[1]=y+47;

	poly2[2]=x+70;
	poly2[3]=y+52;

	poly2[4]=x+37;
	poly2[5]=y+105;

	poly2[6]=x+30;
	poly2[7]=y+100;
	delay(500);
	fillpoly(4,poly2);

}

//left hand
void fortis1(int x,int y)
{
 
	int poly[14];
	setcolor(15);
	setfillstyle(1,15);
	poly[0]=x+15;
	poly[1]=y-10;
	poly[2]=x;
	poly[3]=y+50;
	poly[4]=x+10;
	poly[5]=y+50;
	poly[6]=x+10;
	poly[7]=y+130;
	poly[8]=x-10;
	poly[9]=y+130;
	poly[10]=x;
	poly[11]=y+100;
	poly[12]=x-20;
	poly[13]=y+50;
	fillpoly(7,poly);

}
void fortis2(int x,int y)
{
	int poly[14];
	poly[0]=x-15;
	poly[1]=y-10;
	poly[2]=x+20;
	poly[3]=y+50;
	poly[4]=x;
	poly[5]=y+100;
	poly[6]=x+10;
	poly[7]=y+130;
	poly[8]=x-10;
	poly[9]=y+130;
	poly[10]=x-10;
	poly[11]=y+50;
	poly[12]=x;
	poly[13]=y+50;
	fillpoly(7,poly);
}
void bars(int x,int y)
{
	setfillstyle(1,15);
	bar(364-x,265-y,369-x,295-y);
	bar(373-x,257-y,377-x,303-y);
	bar(381-x,243-y,385-x,317-y);
	bar(389-x,261-y,393-x,307-y);
	bar(397-x,273-y,401-x,305-y);

	setcolor(15);
	settextstyle(0,0,2);
	outtextxy(88,68,"Medical");
	outtextxy(88,88,"Store");
	outtextxy(88,108,"Management");
}

void loading(int x,int y)
{
	setfillstyle(9,3);
	bar(x-10,y-5,x+5,y+5);
	setcolor(14);
	setfillstyle(1,14);
	pieslice(x,y,0,360,5);
}

void load(int sx,int ex,int y)
{
	int temp,i,j,k,x;
	temp=sx;
	i=1;
	j=1;k=0;
	for(x=sx;x<ex;x++)
	{
		loading(x,y);
		if(x-temp>50)
		{
			temp=x;
			k=j;
			j=i;
			i=j+k;
		}
		delay(i);

	}

}

void iload(int sx,int ex,int y)
{
	int temp,i,j,k,x;
	temp=sx;
	i=2;
	j=1;k=0;
	for(x=sx;x<ex;x++)
	{
		loading(x,y);
		if(x-temp>45)
		{
			temp=x;
			k=j;
			j=i;
			i=j+k;
		}
		delay(20/i);

	}

}
void intro_screen()
{
	int time=500;
	
	setcolor(4);
	settextstyle(7,0,1);
	outtextxy(15,15,"Hello World");

	setfillstyle(9,3);
	bar(0,0,639,479);

	//medicine names
	setcolor(15);
	settextstyle(2,1,5);
	outtextxy(20,0,"paracitamol gluformin benzene amiryl codeine chlorpheniramine");
	settextstyle(2,1,4);
	outtextxy(12,0,"gluformin paracitamol amiryl benzene disprien neopropane hydrogen avil biorex methane");
	settextstyle(2,1,5);
	outtextxy(0,0,"gluformin paracitamol amiryl benzene disprien neopropane hydrogen avil biorex methane");

	//settextstyle(2,0,5);
	//outtextxy(40,20,"paracitamol gluformin benzene amiryl codeine chlorpheniramine archeopeteryx hewlttpackard");
	settextstyle(2,0,4);
	outtextxy(40,12,"gluformin paracitamol amiryl benzene disprien neopropane hydrogen avil biorex methane cyclomethane hydropropinre");
	settextstyle(2,0,5);
	outtextxy(40,0,"gluformin paracitamol amiryl benzene disprien neopropane hydrogen avil biorex methane");

	//settextstyle(2,0,5);
	//outtextxy(40,439,"paracitamol gluformin benzene amiryl codeine chlorpheniramine archeopeteryx hewlttpackard");
	settextstyle(2,0,4);
	outtextxy(40,452,"gluformin paracitamol amiryl benzene disprien neopropane hydrogen avil biorex methane cyclomethane hydropropinre");
	settextstyle(2,0,5);
	outtextxy(40,459,"gluformin paracitamol amiryl benzene disprien neopropane hydrogen avil biorex methane");

	settextstyle(2,1,5);
	outtextxy(609,10,"phenylethene gluformin benzene amiryl codeine chlorphenyl");
	settextstyle(2,1,4);
	outtextxy(622,25,"gluformin paracitamol amiryl benzene disprien neopropane hydrogenethyl");
	settextstyle(2,1,5);
	outtextxy(629,0,"gluformin paracitamol amiryl benzene disprien neopropane h");
	delay(time);

	//white vertical lines
	bars(320,205);
	//loading(230,360);
	delay(time);

	setcolor(14);
	settextstyle(0,0,10);
	outtextxy(45,202,"Life");
	delay(time);

	setfillstyle(1,2);
	bar(41,278,360,284);
	delay(time);


	//vertical lines
	bar(364,265,369,295);
	bar(373,257,377,303);
	bar(381,243,385,317);
	bar(389,261,393,307);
	bar(397,273,401,305);
	delay(time);

	bar(405,296,605,302);
	delay(time);

	settextstyle(0,0,6);
	outtextxy(420,250,"LINE");
	delay(time);

	setcolor(4);
	rx(425,120);
       //	delay(500);
	delay(time);

	fortis1(400,70);
	fortis2(510,70);
	delay(time);


	setcolor(15);
	settextstyle(0,0,2);
	outtextxy(175,380,"Cybros project 1.0");

	setcolor(14);
	settextstyle(0,0,1);
	outtextxy(40,410," Gautam Anghore   Tanuj Srivastava   Satrajit Sahani   Harshit Thukral");
	delay(time);


	load(100-50,350,350);
	load(100-50,320,350);
	load(100-50,290,350);
	iload(350,600,350);

	setfillstyle(9,3);
	bar(600-10,350-5,600+5,350+5);
	iload(320,600,350);
	setfillstyle(9,3);
	bar(600-10,350-5,600+5,350+5);
	iload(290,600,350);
	setfillstyle(9,3);
	bar(600-10,350-5,600+5,350+5);
	
	delay(500);

}
//###############################################################################################################################

//#################################################### USER FUNCTIONS ###########################################################

void root_init(FILE *uin)
{
	struct userAcc root;
//	fpos_t pos;

	arr_init(root.userName,30);
	strcpy(root.userName,"gautam");

	arr_init(root.userId,10);
	strcpy(root.userId,"gautam");

	arr_init(root.userPass,30);
	strcpy(root.userPass,"vidyayaamrit");

	root.level=3;

	//deformation of text
	text_encrypt(root.userName);
	text_encrypt(root.userId);
	text_encrypt(root.userPass);

	uin=fopen("uppf.swf","r+");

//	fgetpos(uin,&pos);
//	printf("file pos %ld",pos);

	if(uin==NULL)
	{
		uin=fopen("uppf.swf","ab+");
		fflush(uin);
		fwrite(&root,sizeof(root),1,uin);

	}

	fclose(uin);

}


void user_register(FILE *uin)
{
	char choice='y';

	int bcolor,fcolor;
	bcolor=1;
	fcolor=15;

	//user_register_window();
	//userA - linked list start node
	//user - linked list traversing pointer
	//both defined globally

	userA=user=(struct userAcc *)malloc(sizeof(struct userAcc));
	
	/*
	
	gotoxy(18,11);
	cprintf("User Name :");
	gotoxy(18,13);
	cprintf("User Id   :");
	gotoxy(18,15);
	cprintf("Password  :");
	gotoxy(18,17);
	cprintf("User Level:");
	*/

	do
	{
		user_register_window();
		//printf("user name :");
		gotoxy(30,11);
		arr_init(user->userName,30);
		text_input(user->userName,30,bcolor,fcolor);
		
		//printf("\nuser id :");
		gotoxy(30,13);
		arr_init(user->userId,10);
		text_input(user->userId,10,bcolor,fcolor);

		//printf("\nuser password :");
		gotoxy(30,15);
		arr_init(user->userPass,30);
		text_input_pass(user->userPass,30,bcolor,fcolor);

		//printf("\nuser level :");
		gotoxy(30,17);
		scanf("%d",&user->level);

		//printf("\n(y|n):");
			menu_box(40,9,20,8,6,15," OPTION ");
			write_middle(40,6,20,12,6,15,"Do You Add More ?");
			write_middle(40,6,20,13,6,15,"(Y|N)");
			rect(38,1,21,15,7,15);
			gotoxy(40,15);
			textcolor(4);
			textbackground(7);
			choice=getch();
			cprintf("%c",choice);
			

		if(choice=='y'||choice=='Y')
		{
			user->link=(struct userAcc *)malloc(sizeof(struct userAcc));
			user=user->link;
		}
		else
		{
			user->link=NULL;
			break;
		}

	}while(choice=='y');

	uin=fopen("uppf.swf","ab+");	//uppf=user password protected file//a+ : append the existing file

	user=userA;

	while(user)
	{
		fflush(uin);

		//encryption/deformation of text
		text_encrypt(user->userName);
		text_encrypt(user->userId);
		text_encrypt(user->userPass);

		fwrite(user,sizeof(*user),1,uin);
		user=user->link;
	}

	free(user);
	free(userA);

	fclose(uin);

}
// ctrl+a : get sales report
// enter : continue
// esc : exit
void user_display(FILE *uout)
{
	int bcolor,fcolor;
	int choice='y';
	int exit=0;
	bcolor=1;
	fcolor=15;

	user_display_screen();
	
	
//	user_llist(uout);

	user=userA;
	
	
	/*
	gotoxy(26,11);
	cprintf("User Name :");
	gotoxy(26,13);
	cprintf("User Id   :");
	gotoxy(26,15);
	cprintf("Password  :");
	gotoxy(26,17);
	cprintf("User Level:");
	*/
	while(user->link)
	{
		//printf("\n\nuser name :");
		gotoxy(38,11);
		text_output(user->userName,bcolor,fcolor);

		//printf("\nuser id :");
		gotoxy(38,13);
		text_output(user->userId,bcolor,fcolor);

		//printf("\nuser password :");
		gotoxy(38,15);
		text_output_pass(user->userPass,bcolor,fcolor);

		//printf("\nuser level :");
		gotoxy(38,17);
		cprintf("%d",user->level);
		choice=2;
		while(choice!=13)
		{
			if(kbhit())
			{
			choice=getch();
			switch(choice)
			{
				case 1:transection_log_user(user);
						getch();
						user_display_screen();
						break;
				
				case 27:exit=1;
						break;
			}
			}
		}
		choice='y';
		if(exit)
			break;
		
		user=user->link;
	}
//	free(user);
//	free(userA);


}

void user_llist(FILE *uout)
{
	uout=fopen("uppf.swf","rb");

	if(uout)
	{
	userA=user=(struct userAcc *)malloc(sizeof(struct userAcc));
	//printf("came here");
	do
	{
		//fflush(uout);
		//fflush(stdin);	//dont know why i did it

		if((fread(user,sizeof(*user),1,uout))&&(feof(uout)==0))
		{
			//printf("1");
			//decryption/formation of text
			text_decrypt(user->userName);
			text_decrypt(user->userId);
			text_decrypt(user->userPass);

			user->link=(struct userAcc*)malloc(sizeof(struct userAcc));
			user=user->link;
			user->link=NULL;
		}
		else
		user->link=NULL;
	}while(feof(uout)==0);
	user->link=NULL;
	fclose(uout);
	}
	//else
	//printf("file not open");
}

void user_login_window(int color)
{
	menu_box(40,9,20,8,color,14," [ USER LOGIN ] ");

	gotoxy(25,12);
	text_output(" User Id : ",color,14);
	gotoxy(25,14);
	text_output(" Password: ",color,14);

}

int user_login_check(FILE *uout,struct userAcc *userCurrent,int color)
{
	char uid[10],upass[30];
	int flag=0;
	
	int bcolor,fcolor;
	bcolor=color;
	fcolor=14;
	
	user_login_window(color);
	
	arr_init(uid,10);
	arr_init(upass,30);
	
	//user id input
	gotoxy(35,12);
	text_input(uid,10,bcolor,fcolor);
	
	//user password input
	gotoxy(35,14);
	text_input_pass(upass,30,bcolor,fcolor);

	user_llist(uout);
	
	user=userA;
	
	while(user->link)
	{
		if(text_compare(uid,user->userId,10)&&(text_compare(upass,user->userPass,30)))
		{
			//login attempt successfull
			strcpy(userCurrent->userName,user->userName);
			strcpy(userCurrent->userId,user->userId);
			strcpy(userCurrent->userPass,user->userPass);
			userCurrent->level=user->level;
			
			flag=1;
			break;
		}
		
		user=user->link;
	}
	
//	free(user);
//	free(userA);
	
	return flag;
}

int user_login_screen(FILE *uout,struct userAcc *userCurrent)
{
	char choice;
	int bcolor,fcolor;
	int level=-1;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	base_screen("","");
	rect(30,1,50,25,7,7);
	write_middle(1,1,50,25,7,0,"³");
	write_middle(5,1,53,25,7,4,"ENTER");
	write_middle(6,1,58,25,7,0,":LOGIN");
	write_middle(3,1,66,25,7,4,"ESC");
	write_middle(6,1,69,25,7,0," :EXIT");
	
	user_login_window(2);
	
	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:if(user_login_check(uout,userCurrent,bcolor))
						{
								choice=0;
								clear_base();
								
								switch(userCurrent->level)
								{
									case 3:
											level=3;
											break;
									case 2:
											level=2;
											break;
									case 1:
											level=1;
											break;
									case 0:
											level=0;
											break;
								}
						}
						
						else
						{
							bcolor=6;
							OutBox(30,5,25,11,4,15," ERROR ");
							gotoxy(27,13);
							textcolor(15);
							textbackground(4);
							cprintf("Invalid UserId or Password");
							
							getch();
							user_login_window(bcolor);
						}
						break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								user_login_window(bcolor);
							
						break;
				default:break;
			}
		}
	}
	
	return level;
}

//###############################################################################################################################

//#################################################### DATE FUNCTIONS ###########################################################

int digits(int n)
{
	int flag=0;

	while(n>0)
	{
		n=n/10;
		flag++;
	}

	return flag;
}

char int_to_char(int i)
{
	return i+48;
}

void date_input(struct mdate *d,int x,int y,int bcolor,int fcolor)
{
	int flag=0;
	
	textcolor(fcolor);
	textbackground(bcolor);

	if((x!=0)&&(y!=0))
		gotoxy(x,y);
	else
	{
		x=wherex();
		y=wherey();
	}
	cprintf("  /  /    ");
	//gotoxy(x+5,y);
	//cprintf("/");

	do
	{
		gotoxy(x,y);
		scanf("%d",&d->dd);
		if((d->dd<32)&&(d->dd>0))
			flag=1;
		else
		{
			gotoxy(x,y);
			cprintf("  ");
			flag=0;
		}
	}while(flag!=1);

	flag=0;
	do
	{
		gotoxy(x+3,y);
		scanf("%d",&d->mm);
		if((d->mm<13)&&(d->mm>0))
			flag=1;
		else
		{
			gotoxy(x+3,y);
			cprintf("  ");
			flag=0;
		}
	}while(flag!=1);

	flag=0;
	do
	{
		gotoxy(x+6,y);
		scanf("%d",&d->yy);

		if((d->yy<3000)&&(d->yy>1800))
			flag=1;
		else
		{
			gotoxy(x+6,y);
			cprintf("    ");
			flag=0;
		}
	}while(flag!=1);

}

void date_output(struct mdate *d,int x,int y,int bcolor,int fcolor)
{
	textcolor(fcolor);
	textbackground(bcolor);
	
	if((x!=0)&&(y!=0))
		gotoxy(x,y);
	
	cprintf("%d/%d/%d",d->dd,d->mm,d->yy);
}

void get_currentDate(struct mdate *currentDate)
{
	struct date d;
	getdate(&d);
	currentDate->dd=d.da_day;
	currentDate->yy=d.da_year;
	currentDate->mm=d.da_mon;
}

int days_month(int x)
{
	int y=0;
	switch(x)
	{
		case 1: y=0;
		break;
		case 2: y=31;
		break;
		case 3: y=59;
		break;
		case 4: y=90;
		break;
		case 5: y=120;
		break;
		case 6: y=151;
		break;
		case 7: y=181;
		break;
		case 8: y=212;
		break;
		case 9: y=243;
		break;
		case 10:y=273;
		break;
		case 11:y=304;
		break;
		case 12:y=334;
		break;
	}
	 return(y);
}

int date_substract(struct mdate d2,struct mdate d1)
{
	int ref,dd1,dd2,i;
	ref = d1.yy;
	if(d2.yy<d1.yy)
	{
		ref = d2.yy;
	}
	dd1=0;
	dd1=days_month(d1.mm);
	for(i=ref;i<d1.yy;i++)
	{
		if(i%4==0)
		dd1+=1;
	}
	dd1=dd1+d1.dd+(d1.yy-ref)*365;
	dd2=0;
	for(i=ref;i<d2.yy;i++)
	{
		if(i%4==0)
		dd2+=1;
	}
	dd2=days_month(d2.mm)+dd2+d2.dd+((d2.yy-ref)*365);
	
	return (dd2-dd1);
}

int date_compare(struct mdate d1,struct mdate d2)
{
	if(d1.yy>d2.yy)
		return 1;
	else if(d1.yy<d2.yy)
		return 2;
	else if(d1.yy==d2.yy)
	{	
		if(d1.mm>d2.mm)
			return 1;
		else if(d1.mm<d2.mm)
			return 2;
		else if(d1.mm==d2.mm)
		{
			if(d1.dd>d2.dd)
				return 1;
			else if(d1.dd<d2.dd)
				return 2;
			else if(d1.dd==d2.dd)
				return 1;
		}
	}
}


int date_equal(struct mdate d1,struct mdate d2)
{
	if((d1.dd==d2.dd)&&(d1.mm==d2.mm)&&(d1.yy==d2.yy))
	{
		return 1;
	}
	else
		return 0;
}
//###############################################################################################################################

//#################################################### MEDICAL FUNCTIONS ###########################################################

void id_creater(char name[],char id[],int n,int serial)
{
	int i,j,k;

	arr_init(id,n);

	j=n-digits(serial)-2;

	for(i=0,k=0;i<j;)
	{
		if(name[k+1])
		{
			if(((name[k]>=65)&&(name[k]<=90))||((name[k]>=97)&&(name[k]<=122))||((name[k]>=48)&&(name[k]<=57)))
			{	
				id[i++]=name[k++];
			}
			else
				k++;
		}
		else
		{
			id[i++]=name[k];
		}
	}
	id[j]='_';
	for(i=n-2;i>=j+1;i--)
	{
		id[i]=int_to_char(serial%10);
		serial=serial/10;
	}
	id[n-1]=NULL;
}
// naam medAcc se pass karo to id search kar deta hai
int med_id_search(FILE *mid,struct medId * medAcc)
{
	struct medId *temp;
	int flag=0;
	
	mid=fopen("medlist.swf","rb");
	
	if(mid)
	{
		temp=(struct medId *)malloc(sizeof(struct medId));
		do
		{
			fflush(mid);
			
			if((fread(temp,sizeof(*temp),1,mid))&&(feof(mid)==0))
			{
				if(text_compare(temp->medName,medAcc->medName,30))
				{
					//medicine search attempt successfull
					strcpy(medAcc->medId,temp->medId);
					flag=-1;
					break;
				}
				else
					flag=temp->key;
			}
		}while(feof(mid)==0);
		fclose(mid);
		
		return flag;
	}
	
	return 0;//file could not be opened
}

void med_id_register(FILE *mid,struct medId *medAcc,int serial)
{
	mid=fopen("medlist.swf","a+");
	
	if(mid)
	{
		id_creater(medAcc->medName,medAcc->medId,10,serial);
		medAcc->key=serial;
		fwrite(medAcc,sizeof(*medAcc),1,mid);
		fclose(mid);
	}
	
}

int med_stock_last()
{
	struct medicine temp;
	FILE *m;
	int flag;
	
	m=fopen("medstock.swf","rb");
	fflush(m);
	
	while(feof(m)==0)
	{
		fread(&temp,sizeof(temp),1,m);
	}
	
	fseek(m,-sizeof(temp),SEEK_CUR);
	fread(&temp,sizeof(temp),1,m);
	
	flag=temp.key;
	free(temp);
	fclose(m);
	return flag;
}

void med_register(FILE *min)
{
	char choice='y';
	int prekey,key;
	int flag;
	
	FILE *mid;// for id operations on medlist.swf with struct medId
	// FILE *min - for registering the medicine sturct medicine
	
	//medA - linked list start node
	//med - linked list traversing pointer
	//both defined globally
	
	/*
	gotoxy(10,9);
	cprintf("Key         :");
	gotoxy(32,9);
	cprintf("Medicine Id:");
	gotoxy(10,11);
	cprintf("Medicine Name:");
	gotoxy(10,13);
	cprintf("Quantity    :");
	gotoxy(32,13);
	cprintf("MRP/Item   :");
	gotoxy(10,15);
	cprintf("Batch Id    :");
	gotoxy(10,17);
	cprintf("Shelf Row   :");
	gotoxy(32,17);
	cprintf("Column     :");
	gotoxy(10,19);
	cprintf("Current Date:");
	gotoxy(32,19);
	cprintf("Expiry Date:");
	*/
	med_register_screen();
	prekey=med_stock_last();
	key=prekey+1;
	medA=med=(struct medicine *)malloc(sizeof(struct medicine));
	med->pre=NULL;
	
	do
	{
		gotoxy(24,9);
		med->key=key++;
		cprintf("%d\n",med->key);
		//cprintf("Medcine name :");
		gotoxy(24,11);
		arr_init(med->medName,30);
		text_input(med->medName,30,1,15);

		arr_init(medAcc.medName,30);
		arr_init(medAcc.medId,10);
		
		strcpy(medAcc.medName,med->medName);
		
		flag=med_id_search(mid,&medAcc);
		flag++;
		
		if(!flag)
		{
			strcpy(med->medId,medAcc.medId);
		}
		else
		{	
			med_id_register(mid,&medAcc,flag);
			strcpy(med->medId,medAcc.medId);
		}
		
		//cprintf("\r\n");
		gotoxy(45,9);
		text_output(med->medId,1,15);
		gotoxy(24,13);
		//cprintf("\r\nQuantity :");
		scanf("%d",&med->medNo);
		//cprintf("Medicine MRP/item :");
		gotoxy(45,13);
		scanf("%d",&med->medmrp);
		
		//cprintf("BatchId :");
		gotoxy(24,15);
		arr_init(med->batchId,10);
		text_input(med->batchId,10,1,15);

		//cprintf("\nShelf Row :");
		gotoxy(24,17);
		scanf("%d",&med->shelfRow);
		//cprintf("Shelf Column:");
		gotoxy(45,17);
		scanf("%d",&med->shelfCol);
		
		med->addDate.dd=currentDate.dd;
		med->addDate.mm=currentDate.mm;
		med->addDate.yy=currentDate.yy;
		date_output(&med->addDate,24,19,1,15);
		//cprintf("Expiry Date :");
		date_input(&med->expDate,45,19,1,15);

		//printf("\n(y|n):");
		//printf("\n(y|n):");
			menu_box(40,9,20,8,6,15," OPTION ");
			write_middle(40,6,20,12,6,15,"Do You Add More ?");
			write_middle(40,6,20,13,6,15,"(Y|N)");
			rect(38,1,21,15,7,15);
			gotoxy(40,15);
			textcolor(4);
			textbackground(7);
			choice=getch();
			cprintf("%c",choice);

		if(choice=='y')
		{
			med->next=(struct medicine *)malloc(sizeof(struct medicine));
			med->next->pre=med;
			med=med->next;
		}
		else
		{
			med->next=NULL;
			break;
		}

	}while(choice=='y');


	
//	free(med);
//	free(medA);

	fclose(min);
	
}

void med_stock_file_display()
{
	//in order of entry
	FILE *mout,*mprint;
	struct medicine temp;
	int bcolor=1,fcolor=15;
	time_t t;
	time(&t);
	
	clearS(1);
	textcolor(15);
	textbackground(1);
	gotoxy(1,1);

	mout=fopen("medstock.swf","rb");
	mprint=fopen("rStock.txt","ab+");

	cprintf("---------------------------------------------------------------------------");
	printf("\n");
	cprintf("S.NO|MEDICINE NAME              | MED_ID |QNTY|MRP|BATCH ID|ROW COL| EXPIRY");
	printf("\n");
	cprintf("---------------------------------------------------------------------------");
	printf("\n");

	fprintf(mprint,"\r\n \r\n \r\n---------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n                          PROJECT LIFELINE                               ");
	fprintf(mprint,"\r\n                          $ STOCK REPORT $                               ");
	fprintf(mprint,"\r\n---------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n                          %s",ctime(&t));
	fprintf(mprint,"\r\n---------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n---------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n");
	fprintf(mprint,"S.NO|MEDICINE NAME              | MED_ID |QNTY|MRP|BATCH ID|ROW COL |   EXPIRY");
	fprintf(mprint,"\r\n");
	fprintf(mprint,"---------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n");
	while(fread(&temp,sizeof(temp),1,mout)&&(feof(mout)==0))
	{
		cprintf("%2d. %-28s %-9s %3d %3d %-10s %2d:%-2d%d/%d/%d ",temp.key,temp.medName,temp.medId,temp.medNo,temp.medmrp,temp.batchId,temp.shelfRow,temp.shelfCol,temp.expDate.dd,temp.expDate.mm,temp.expDate.yy);
		printf("\n");
		fprintf(mprint,"%2d. %-28s %-9s %3d %3d %-10s %2d:%-2d  %d/%d/%d ",temp.key,temp.medName,temp.medId,temp.medNo,temp.medmrp,temp.batchId,temp.shelfRow,temp.shelfCol,temp.expDate.dd,temp.expDate.mm,temp.expDate.yy);
		fprintf(mprint,"\r\n");

	}

	fclose(mprint);
	fclose(mout);

}

//Multi Linked List of Medical stock arranged according to expiry date
// ********** most important and difficult function in my view ***********
void med_multi_list()
{
	FILE *mout;
	struct medHead *temp;
	int match=0;
	int exp1,exp2;
	
	mout=fopen("medstock.swf","rb");
	
	medA=(struct medicine *)malloc(sizeof(struct medicine));
	//medHeadA=medHead=(struct medHead *)malloc(sizeof(struct medHead));
	
	medHeadA=NULL;
	medHead=NULL;
	
	while(fread(medA,sizeof(*medA),1,mout)&&(feof(mout)==0)) // medicine struct data from file to medA
	{
		if(medA->medNo>0)
		{
			exp1=date_substract(medA->expDate,currentDate);	// days left for expiry

			temp=medHeadA;	//searching for id if already exits in multi list
			while((temp)&&(!match))
			{
				if(text_compare(medA->medId,temp->medId,10))
				{
					// match found
					medHead=temp;
					match=1;
					break;
				}
				else
					medHead=temp;

				temp=temp->link;
			}
			if(match)
			{
				med=medHead->next;
				while(med)	// finding and inserting at right position using criteria of days left to expire in increasing order
				{
					exp2=date_substract(med->expDate,currentDate);
					if(exp1<exp2)	// position before med
					{
						medA->pre=med->pre;
						med->pre=medA;
						medA->next=med;
						if(!medA->pre)
						{
							medHead->next=medA;
						}
						else
						{
						med=medA->pre;
						med->next=medA;
						}
						if(medHead->expDays>exp1)
							medHead->expDays=exp1;
						break;
					}
						
					if(med->next!=NULL)
						med=med->next;
					else
					{
						// last position
						med->next=medA;
						medA->pre=med;
						medA->next=NULL;
						med=NULL;
					}
				}
				match=0;
			}
			else
			{
				if(!medHeadA)	// if no node exists
					medHeadA=medHead=(struct medHead *)malloc(sizeof(struct medHead));
				else
				{
					medHead->link=(struct medHead *)malloc(sizeof(struct medHead));	//creating new head node
					medHead=medHead->link;
				}
				medHead->link=NULL;	// to complete the search with temp for next itretion
				
				// inserting node medA 
				strcpy(medHead->medName,medA->medName);
				strcpy(medHead->medId,medA->medId);
				medHead->expDays=exp1;//expiry days
				medHead->next=medA;
				medA->pre=NULL;
				medA->next=NULL;
			}
			
			medA=(struct medicine *)malloc(sizeof(struct medicine));
		}
	}

//	med_multi_list_display();

// dont free them error occurs if freed them	
//	free(medA);
//	free(temp);
//	free(med);
	
	fclose(mout);
}

void med_multi_list_display()
{	
	medHead=medHeadA;
	while(medHead)
	{
		med=medHead->next;
		printf("%s\n",medHead->medName);
		while(med)
		{
			printf("\t%d",med->key);
			med=med->next;
		}
		printf("\n");
		medHead=medHead->link;
	}
}

void med_expiry_list()
{	
	struct medicine *temp,*ptr;
	int comp,insert=0,flag=0;
	
	med_multi_list();
	
	medexA=medex=NULL;
	medHead=medHeadA;
	
	while(medHead)
	{
		temp=medHead->next;
		
		while(temp)
		{
			if(!medexA)
			{
				medexA=medex=(struct medicine *)malloc(sizeof(struct medicine));
				medex->pre=NULL;
				medex->next=NULL;
			}
			else
			{
				medex=(struct medicine *)malloc(sizeof(struct medicine));
				flag=1;
				medex->next=NULL;
				medex->pre=NULL;
			}
			
				//copy the date of temp in med
				medex->key=temp->key;
				strcpy(medex->medName,temp->medName);
				strcpy(medex->medId,temp->medId);
				medex->medNo=temp->medNo;
				medex->medmrp=temp->medmrp;
				medex->shelfRow=temp->shelfRow;
				medex->shelfCol=temp->shelfCol;
				medex->addDate=temp->addDate;
				medex->expDate=temp->expDate;
				strcpy(medex->batchId,temp->batchId);
				
				
			
			ptr=medexA;
			if(flag)
			{
				while(ptr)
				{
					comp=date_compare(ptr->expDate,temp->expDate);
					switch(comp)
					{
						case 1://ptr->expDate is greater i.e. temp will expire before
								// so insert med before ptr
								if(ptr->pre==NULL)
								{
									//insert in beginning
									ptr->pre=medex;
									medex->next=ptr;
									medex->pre=NULL;
									medexA=medex;
									insert=1;
								}
								else
								{
									// insert in between
									medex->pre=ptr->pre;
									ptr->pre=medex;
									medex->next=ptr;
									ptr=medex->pre;
									ptr->next=medex;
									insert=1;
								}
								break;
						
						case 2: // temp->expDate is greater i.e. ptr will expire before temp
								// only insertion at last is considered as it can be inserted in next itretion of ptr
								if(ptr->next==NULL)
								{
									ptr->next=medex;
									medex->pre=ptr;
									medex->next=NULL;
									insert=1;
								}
								
								break;
					}
					
					if(insert==1)
					{
						insert=0;
						break;
					}
					
					ptr=ptr->next;
				}
			}
			
		temp=temp->next;
		}
		
		medHead=medHead->link;
	}

	free(temp);
	free(ptr);
}

void med_expiry_report()
{
	FILE *mprint;

	struct medicine *temp,*ptr;
	int comp,insert=0,flag=0;
	
	int bcolor=1,fcolor=15;
	time_t t;
	time(&t);
	
	clearS(1);
	textbackground(bcolor);
	textcolor(fcolor);
	gotoxy(1,1);
	//creation single linked list of medicines according to their expiry date
	//med_expiry_list();
	//---------------------------------------------------------------------------------------------------------------------

	med_multi_list();
	
	medexA=medex=NULL;
	medHead=medHeadA;
	
	while(medHead)
	{
		temp=medHead->next;
		
		while(temp)
		{
			if(!medexA)
			{
				medexA=medex=(struct medicine *)malloc(sizeof(struct medicine));
				medex->pre=NULL;
				medex->next=NULL;
			}
			else
			{
				medex=(struct medicine *)malloc(sizeof(struct medicine));
				flag=1;
				medex->next=NULL;
				medex->pre=NULL;
			}
			
				//copy the date of temp in med
				medex->key=temp->key;
				strcpy(medex->medName,temp->medName);
				strcpy(medex->medId,temp->medId);
				medex->medNo=temp->medNo;
				medex->medmrp=temp->medmrp;
				medex->shelfRow=temp->shelfRow;
				medex->shelfCol=temp->shelfCol;
				medex->addDate=temp->addDate;
				medex->expDate=temp->expDate;
				strcpy(medex->batchId,temp->batchId);
				
				
			
			ptr=medexA;
			if(flag)
			{
				while(ptr)
				{
					comp=date_compare(ptr->expDate,temp->expDate);
					switch(comp)
					{
						case 1://ptr->expDate is greater i.e. temp will expire before
								// so insert med before ptr
								if(ptr->pre==NULL)
								{
									//insert in beginning
									ptr->pre=medex;
									medex->next=ptr;
									medex->pre=NULL;
									medexA=medex;
									insert=1;
								}
								else
								{
									// insert in between
									medex->pre=ptr->pre;
									ptr->pre=medex;
									medex->next=ptr;
									ptr=medex->pre;
									ptr->next=medex;
									insert=1;
								}
								break;
						
						case 2: // temp->expDate is greater i.e. ptr will expire before temp
								// only insertion at last is considered as it can be inserted in next itretion of ptr
								if(ptr->next==NULL)
								{
									ptr->next=medex;
									medex->pre=ptr;
									medex->next=NULL;
									insert=1;
								}
								
								break;
					}
					
					if(insert==1)
					{
						insert=0;
						break;
					}
					
					ptr=ptr->next;
				}
			}
			
		temp=temp->next;
		}
		
		medHead=medHead->link;
	}
//-----------------------------------------------------------------------------------------------------------------------------------------
//	mout=fopen("medstock.swf","rb");
	mprint=fopen("rexpire.txt","ab+");

	cprintf("---------------------------------------------------------------------------");
	printf("\n");
	cprintf(" KEY|MEDICINE NAME              | MED_ID |QNTY|MRP|BATCH ID|ROW COL| EXPIRY");
	printf("\n");
	cprintf("---------------------------------------------------------------------------");
	printf("\n");

	fprintf(mprint,"\r\n \r\n \r\n------------------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n                              PROJECT LIFELINE                               ");
	fprintf(mprint,"\r\n                              $ EXPIRY REPORT $                               ");
	fprintf(mprint,"\r\n------------------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n                              %s",ctime(&t));
	fprintf(mprint,"\r\n------------------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n------------------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n");
	fprintf(mprint," KEY|MEDICINE NAME              | MED_ID | QUANTITY |MRP|BATCH ID|ROW COL |   EXPIRE IN DAYS");
	fprintf(mprint,"\r\n");
	fprintf(mprint,"----------------------------------------------------------------------------------------------");
	fprintf(mprint,"\r\n");
	
	medex=medexA;
	
	while(medex)
	{
		cprintf("%2d. %-28s %-9s %3d %3d %-10s %2d:%-2d%d/%d/%d ",medex->key,medex->medName,medex->medId,medex->medNo,medex->medmrp,medex->batchId,medex->shelfRow,medex->shelfCol,medex->expDate.dd,medex->expDate.mm,medex->expDate.yy);
		printf("\n");
		fprintf(mprint,"%2d. %-28s %-9s %7d %5d %-10s %2d:%-2d     %d ",medex->key,medex->medName,medex->medId,medex->medNo,medex->medmrp,medex->batchId,medex->shelfRow,medex->shelfCol,date_substract(medex->expDate,currentDate));
		fprintf(mprint,"\r\n");
		medex=medex->next;
	}
	
	fclose(mprint);

}

//###############################################################################################################################

//#################################################### TRANSECTION FUNCTIONS ###########################################################

int transection_last()
{
	struct transection temp;
	FILE *t;
	int flag;
	flag=0;
	
	t=fopen("medtrans.swf","rb");
	
	if(t)
	{
	while(feof(t)==0)
	{
		fread(&temp,sizeof(temp),1,t);
	}
	
	fseek(t,-sizeof(temp),SEEK_CUR);
	fread(&temp,sizeof(temp),1,t);
	
	flag=temp.key;
	}
	free(temp);
	fclose(t);
	return flag;
}

void transection()
{
	char choice='y';
	int bcolor,fcolor;
	FILE *tin;
	int prekey;
	struct transection *temp;
	transA=trans=NULL;
	choice='y';
	
	/*
		gotoxy(26,11);
	cprintf("Patient Name :");
	gotoxy(26,13);
	cprintf("Current Date:");
	gotoxy(26,15);
	cprintf("Amount      :");
	*/
	sales_transection();
	bcolor=1;
	fcolor=15;
	prekey=transection_last();
	prekey++;
	while(choice != 27)
	{

		switch(choice)
		{
			case 'Y':
			case 'y':
					sales_transection_window();
					if(!transA)
					{
						transA=trans=last=(struct transection *)malloc(sizeof(struct transection));
						last->pre=NULL;
						last->next=NULL;
					}
					else
					{
						last->next=(struct transection *)malloc(sizeof(struct transection));
						last->next->pre=last;
						last=last->next;
						last->next=NULL;
						trans=last;
					}
					last->key=prekey++;
					//printf("PATIENT NAME :");
					gotoxy(40,11);
					text_input(last->pName,30,bcolor,fcolor);
					gotoxy(40,13);
					date_output(&currentDate,40,13,1,15);
					gotoxy(40,15);
					scanf("%d",&last->amount);
					arr_init(last->userId,10);
					strcpy(last->userId,userCurrent.userId);

					time(&last->t);
					last->tDate=currentDate;
					break;
			case 2:
					//while(choice=='a')

					//	printf("\n%s",trans->pName);
					sales_transection_window();
					//last->key=prekey++;
					//printf("PATIENT NAME :");
					gotoxy(40,11);
					text_output(trans->pName,bcolor,fcolor);
					gotoxy(40,13);
					date_output(&trans->tDate,40,13,1,15);
					gotoxy(40,15);
					cprintf("%d",&trans->amount);
					//arr_init(last->userId,10);
					//strcpy(last->userId,userCurrent.userId);
						if(trans->pre)
						trans=trans->pre;

					break;
		}

		//cprintf("\r\nChoice :");
	       while(choice!=27)
	       {
			if(kbhit())
			{
			choice=getch();
			break;
			}
		}
	}

	tin=fopen("medtrans.swf","ab+");	//medtrans= medical transection file: append the existing file

	trans=transA;

	while(trans)
	{
		fflush(tin);

		fwrite(trans,sizeof(*trans),1,tin);
		trans=trans->next;
	}
	fclose(tin);
}
//ruserlog.txt
void transection_log_currentuser()
{
	FILE *fout;
	struct transection temp;
	int x,y;
	
	time_t t;
	time(&t);
	
	clearS(1);
	gotoxy(1,1);
	textcolor(15);
	textbackground(1);
	
	fout=fopen("medtrans.swf","rb");

	transA=trans=NULL;

	while(fread(&temp,sizeof(temp),1,fout)&&feof(fout)==0)
	{
		if(text_compare(temp.userId,userCurrent.userId,10))
		{
			if(!transA)
			{
				transA=trans=(struct transection*)malloc(sizeof(struct transection));
				trans->next=NULL;
				trans->pre=NULL;
			}
			else
			{	
				trans->next=(struct transection *)malloc(sizeof(struct transection));
				trans->next->pre=trans;
				trans=trans->next;
				trans->next=NULL;
			}
			
			trans->key=temp.key;
			strcpy(trans->pName,temp.pName);
			strcpy(trans->userId,temp.userId);
			trans->t=temp.t;
			trans->tDate=temp.tDate;
			trans->amount=temp.amount;
		}
		
	}
	
	fclose(fout);
	
	trans=transA;
	
	fout=fopen("ruserlog.txt","ab+");
	
	cprintf("---------------------------------------------------------------------------");
	printf("\n");
	cprintf(" KEY  |  PATIENT NAME              |   AMOUNT   |            TIME       ");
	printf("\n");
	cprintf("---------------------------------------------------------------------------");
	printf("\n");

	fprintf(fout,"\r\n \r\n \r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n                          PROJECT LIFELINE                               ");
	fprintf(fout,"\r\n                       $ TRANSECTION REPORT $                               ");
	fprintf(fout,"\r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n        %30s , %s",userCurrent.userName,userCurrent.userId);
	fprintf(fout,"\r\n                          %s",ctime(&t));
	fprintf(fout,"\r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	fprintf(fout," KEY  |    PATIENT NAME              |   AMOUNT   |            TIME       ");
	fprintf(fout,"\r\n");
	fprintf(fout,"---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	
	x=wherex();
	y=wherey();
	while(trans)
	{
		gotoxy(x,y++);
		cprintf("%5d. %-30s %9d %28s ",trans->key,trans->pName,trans->amount,ctime(&trans->t));
		
		fprintf(fout,"%4d. %-30s %10d %30s ",trans->key,trans->pName,trans->amount,ctime(&trans->t));
		fprintf(fout,"\r\n");
		trans=trans->next;
	}
	
	fclose(fout);
}
//ruserlogid.txt
void transection_log_user(struct userAcc *userCurrent)
{

	FILE *fout;
	struct transection temp;
	int x,y;
	
	time_t t;
	time(&t);
	
	clearS(1);
	gotoxy(1,1);
	textcolor(15);
	textbackground(1);
	

	fout=fopen("medtrans.swf","rb");

	transA=trans=NULL;

	while(fread(&temp,sizeof(temp),1,fout)&&feof(fout)==0)
	{
		if(text_compare(temp.userId,userCurrent->userId,10))
		{
			if(!transA)
			{
				transA=trans=(struct transection*)malloc(sizeof(struct transection));
				trans->next=NULL;
				trans->pre=NULL;
			}
			else
			{	
				trans->next=(struct transection *)malloc(sizeof(struct transection));
				trans->next->pre=trans;
				trans=trans->next;
				trans->next=NULL;
			}
			
			trans->key=temp.key;
			strcpy(trans->pName,temp.pName);
			strcpy(trans->userId,temp.userId);
			trans->t=temp.t;
			trans->tDate=temp.tDate;
			trans->amount=temp.amount;
		}
		
	}
	
	fclose(fout);
	
	trans=transA;
	
	fout=fopen("ruserlogid.txt","ab+");
	
	cprintf("---------------------------------------------------------------------------");
	printf("\n");
	cprintf(" KEY  |  PATIENT NAME              |   AMOUNT   |            TIME       ");
	printf("\n");
	cprintf("---------------------------------------------------------------------------");
	printf("\n");

	fprintf(fout,"\r\n \r\n \r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n                             PROJECT LIFELINE                               ");
	fprintf(fout,"\r\n                          $ USER SALES REPORT $                               ");
	fprintf(fout,"\r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n      %30s , %s",userCurrent->userName,userCurrent->userId);
	fprintf(fout,"\r\n                          %s",ctime(&t));
	fprintf(fout,"\r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	fprintf(fout," KEY  |    PATIENT NAME              |   AMOUNT   |            TIME       ");
	fprintf(fout,"\r\n");
	fprintf(fout,"---------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	
	x=wherex();
	y=wherey();
	while(trans)
	{
		gotoxy(x,y++);
		cprintf("%5d. %-30s %9d %28s ",trans->key,trans->pName,trans->amount,ctime(&trans->t));
		
		fprintf(fout,"%4d. %-30s %10d %30s ",trans->key,trans->pName,trans->amount,ctime(&trans->t));
		fprintf(fout,"\r\n");
		trans=trans->next;
	}
	
	fclose(fout);
	
}
//rsales.txt
void transection_log_all()
{
	
	FILE *fout;
	struct transection temp;
	int x,y;
	
	time_t t;
	time(&t);
	clearS(1);
	gotoxy(1,1);
	textcolor(15);
	textbackground(1);

	fout=fopen("medtrans.swf","rb");

	transA=trans=NULL;

	while(fread(&temp,sizeof(temp),1,fout)&&feof(fout)==0)
	{
			if(!transA)
			{
				transA=trans=(struct transection*)malloc(sizeof(struct transection));
				trans->next=NULL;
				trans->pre=NULL;
			}
			else
			{	
				trans->next=(struct transection *)malloc(sizeof(struct transection));
				trans->next->pre=trans;
				trans=trans->next;
				trans->next=NULL;
			}
			
			trans->key=temp.key;
			strcpy(trans->pName,temp.pName);
			strcpy(trans->userId,temp.userId);
			trans->t=temp.t;
			trans->tDate=temp.tDate;
			trans->amount=temp.amount;
		
		
	}
	
	fclose(fout);
	
	trans=transA;
	
	fout=fopen("rsales.txt","ab+");
	
	cprintf("---------------------------------------------------------------------------");
	printf("\n");
	cprintf(" KEY  |  PATIENT NAME              |   AMOUNT   |            TIME       ");
	printf("\n");
	cprintf("---------------------------------------------------------------------------");
	printf("\n");

	fprintf(fout,"\r\n \r\n \r\n-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n                          PROJECT LIFELINE                               ");
	fprintf(fout,"\r\n                       $ GROSS SALES REPORT $                               ");
	fprintf(fout,"\r\n-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n                          %s",ctime(&t));
	fprintf(fout,"\r\n-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	fprintf(fout," KEY  |    PATIENT NAME              |   AMOUNT   |           TIME        | USER ID");
	fprintf(fout,"\r\n");
	fprintf(fout,"-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	
	x=wherex();
	y=wherey();
	while(trans)
	{
		gotoxy(x,y++);
		cprintf("%5d. %-30s %9d %28s ",trans->key,trans->pName,trans->amount,ctime(&trans->t));
		
		fprintf(fout,"%4d. %-30s %10d %28s %10s ",trans->key,trans->pName,trans->amount,ctime(&trans->t),trans->userId);
		fprintf(fout,"\r\n");
		trans=trans->next;
	}
	
	fclose(fout);
}
//rtoday.txt
void transection_log_today()
{	
	FILE *fout;
	struct transection temp;
	int x,y;
	
	time_t t;
	time(&t);
	clearS(1);
	gotoxy(1,1);
	textcolor(15);
	textbackground(1);

	fout=fopen("medtrans.swf","rb");

	transA=trans=NULL;

	while(fread(&temp,sizeof(temp),1,fout)&&feof(fout)==0)
	{
		if(date_equal(temp.tDate,currentDate))
		{
			if(!transA)
			{
				transA=trans=(struct transection*)malloc(sizeof(struct transection));
				trans->next=NULL;
				trans->pre=NULL;
			}
			else
			{	
				trans->next=(struct transection *)malloc(sizeof(struct transection));
				trans->next->pre=trans;
				trans=trans->next;
				trans->next=NULL;
			}
			
			trans->key=temp.key;
			strcpy(trans->pName,temp.pName);
			strcpy(trans->userId,temp.userId);
			trans->t=temp.t;
			trans->tDate=temp.tDate;
			trans->amount=temp.amount;
		
		}
	}
	
	fclose(fout);
	
	trans=transA;
	
	fout=fopen("rtoday.txt","ab+");
	
	cprintf("---------------------------------------------------------------------------");
	printf("\n");
	cprintf(" KEY  |  PATIENT NAME              |   AMOUNT   |            TIME       ");
	printf("\n");
	cprintf("---------------------------------------------------------------------------");
	printf("\n");

	fprintf(fout,"\r\n \r\n \r\n-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n                          PROJECT LIFELINE                               ");
	fprintf(fout,"\r\n                       $ TODAY'S SALES REPORT $                               ");
	fprintf(fout,"\r\n-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n                          %d/%d/%d",currentDate.dd,currentDate.mm,currentDate.yy);
	fprintf(fout,"\r\n-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	fprintf(fout," KEY  |    PATIENT NAME              |   AMOUNT   |           TIME        | USER ID");
	fprintf(fout,"\r\n");
	fprintf(fout,"-------------------------------------------------------------------------------------------");
	fprintf(fout,"\r\n");
	
	x=wherex();
	y=wherey();
	while(trans)
	{
		gotoxy(x,y++);
		cprintf("%5d. %-30s %9d %28s ",trans->key,trans->pName,trans->amount,ctime(&trans->t));
		
		fprintf(fout,"%4d. %-30s %10d %28s %10s ",trans->key,trans->pName,trans->amount,ctime(&trans->t),trans->userId);
		fprintf(fout,"\r\n");
		trans=trans->next;
	}
	
	fclose(fout);
}


//#################################################### MENU DIPLAY ##############################################################

char main_menu(int level)
{
	char choice=1;
	char option=1;
	int flag=1;
	int x,y;
	esc=0;
	
	base_screen("","a");
	rect(W,1,1,25,7,7);
	gotoxy(2,25);
	textcolor(8);
	textbackground(7);
	cprintf(" WELCOME :  ");
	text_output(userCurrent.userName,7,0);
	textcolor(8);
	cprintf(" | ");
	switch(level)
	{
		case 3:cprintf("ROOT");
				break;
		case 2:cprintf("ADMIN");
				break;
		case 1:cprintf("MANAGEMENT");
				break;
		case 0:cprintf("SALES");
				break;
	}
	
	write_middle(1,1,40,25,7,0,"³");
	write_middle(5,1,43,25,7,4,"ENTER");
	write_middle(11,1,49,25,7,0,":GOTO MENU");
	write_middle(3,1,62,25,7,4,"ESC");
	write_middle(7,1,65,25,7,0," :EXIT"); 
	
	
	switch(level)
	{
		case 3:clear_base();
				menu_box_input(50,21,5,3,1,9," MENU ");
				menu_box(20,21,55,3,7,8," HELP ");
				textcolor(15);
				textbackground(1);
				gotoxy(17,8);
				cprintf("<A> USER ACCOUNTS");
				
				gotoxy(17,10);
				cprintf("<B> STOCK MANAGEMENT");
				
				gotoxy(17,12);
				cprintf("<C> SALES DEPARTMENT");
				
				gotoxy(17,14);
				cprintf("<D> REPORTS");

				gotoxy(17,16);
				cprintf("<E> PROFILE LOGS");

				gotoxy(17,18);
				cprintf("<F> BLOCK ACCESS");
				
				textcolor(1);
				textbackground(7);
				gotoxy(7,22);
				cprintf(" ENTER THE CHOICE >");
				x=wherex();
				y=wherey();
				
				break;
		case 2:
				clear_base();
				menu_box_input(50,20,5,3,1,9," MENU ");
				menu_box(20,20,55,3,7,8," HELP ");
				textcolor(15);
				textbackground(1);
				gotoxy(17,8);
				cprintf("<A> USER ACCOUNTS");
				
				gotoxy(17,10);
				cprintf("<B> STOCK MANAGEMENT");
				
				gotoxy(17,12);
				cprintf("<C> SALES DEPARTMENT");
				
				gotoxy(17,14);
				cprintf("<D> REPORTS");

				gotoxy(17,16);
				cprintf("<E> PROFILE LOGS");

				textcolor(1);
				textbackground(7);
				gotoxy(7,21);
				cprintf(" ENTER THE CHOICE >");
				x=wherex();
				y=wherey();				
				break;
		case 1:
				clear_base();
				menu_box_input(50,19,5,3,1,9," MENU ");
				menu_box(20,19,55,3,7,8," HELP ");
				textcolor(15);
				textbackground(1);
				gotoxy(17,8);
				cprintf("<B> STOCK MANAGEMENT");
				
				gotoxy(17,10);
				cprintf("<C> SALES DEPARTMENT");
				
				gotoxy(17,12);
				cprintf("<D> REPORTS");
				
				gotoxy(17,14);
				cprintf("<E> PROFILE LOG");

				textcolor(1);
				textbackground(7);
				gotoxy(7,20);
				cprintf(" ENTER THE CHOICE >");
				x=wherex();
				y=wherey();
				break;
		case 0:clear_base();
				menu_box_input(50,17,5,5,1,9," MENU ");
				menu_box(20,17,55,5,7,8," HELP ");
				textcolor(15);
				textbackground(1);
				
				gotoxy(17,10);
				cprintf("<C> SALES DEPARTMENT");
				
				gotoxy(17,12);
				cprintf("<D> REPORTS");
				
				gotoxy(17,14);
				cprintf("<E> PROFILE LOG");

				textcolor(1);
				textbackground(7);
				gotoxy(7,20);
				cprintf(" ENTER THE CHOICE >");
				x=wherex();
				y=wherey();
				break;
	}
	
	while(choice!=27)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	rect(50,1,30,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-F");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
									if(level>=0)
									{
										if(choice=='c'||choice=='d'||choice=='e'||choice=='C'||choice=='D'||choice=='E')
										{
											option=choice;
											rect(16,1,x,y,7,1);
											gotoxy(x,y);
											cprintf("%c",choice);
										}
										else if(level>=1)
										{	
											if(choice=='b'||choice=='B')
											{
												option=choice;
												rect(16,1,x,y,7,1);
												gotoxy(x,y);
												cprintf("%c",choice);
											}
											else if(level>=2)
											{
												if(choice=='a'||choice=='A')
												{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
												}
												else if(level>=3)
												{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
												}
												else
												{
													option=0;
													gotoxy(x,y);
													cprintf(" INVALID CHOICE ");
												}
											}
											else
											{
												option=0;	
												gotoxy(x,y);
												cprintf(" INVALID CHOICE ");
											}
										}
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
										switch(choice)
										{
											case 'a':
											case 'A':	rect(18,14,56,7,7,15);
														write(18,14,56,7,8,"Maintain the usersand authorisations provided to user");
													gotoxy(58,y);
													textcolor(15+128);
													cprintf("PRESS ENTER");

													break;
											case 'b':
											case 'B':rect(18,14,56,7,7,15);
													write(18,14,56,7,8,"Add update or     check the stock of medicine");
													gotoxy(58,y);
													textcolor(15+128);
													cprintf("PRESS ENTER");

													break;
											case 'c':
											case 'C':rect(18,14,56,7,7,15);
														write(18,14,56,7,8,"Search and sell   medicine          Also generate bill");
													gotoxy(58,y);
													textcolor(15+128);
													cprintf("PRESS ENTER");

													break;
											case 'd':
											case 'D':rect(18,14,56,7,7,15);
													write(18,14,56,7,8,"Generate text     reports of stocks and sales");
													gotoxy(58,y);
													textcolor(15+128);
													cprintf("PRESS ENTER");

													break;
											case 'e':
											case 'E':
													rect(18,14,56,7,7,15);
													write(18,14,56,7,8,"View the recent   activities by the user");
													gotoxy(58,y);
													textcolor(15+128);
													cprintf("PRESS ENTER");

													break;
											case 'f':
											case 'F':
													rect(18,14,56,7,7,15);
													write(18,14,56,7,8,"Delete all user accounts");
													gotoxy(58,y);
													textcolor(15+128);
													cprintf("PRESS ENTER");

													break;

										}
										}
									}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
								}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=27;
								esc=1;
							}
							else
							{
									switch(level)
									{
										case 3:clear_base();
												menu_box_input(50,21,5,3,1,9," MENU ");
												menu_box(20,21,55,3,7,8," HELP ");
												textcolor(15);
												textbackground(1);
												gotoxy(17,8);
												cprintf("<A> USER ACCOUNTS");
												
												gotoxy(17,10);
												cprintf("<B> STOCK MANAGEMENT");
												
												gotoxy(17,12);
												cprintf("<C> SALES DEPARTMENT");
												
												gotoxy(17,14);
												cprintf("<D> REPORTS");

												gotoxy(17,16);
												cprintf("<E> PROFILE LOGS");

												gotoxy(17,18);
												cprintf("<F> BLOCK ACCESS");
												
												textcolor(1);
												textbackground(7);
												gotoxy(7,22);
												cprintf(" ENTER THE CHOICE >");
												x=wherex();
												y=wherey();
												
												break;
										case 2:
												clear_base();
												menu_box_input(50,20,5,3,1,9," MENU ");
												menu_box(20,20,55,3,7,8," HELP ");
												textcolor(15);
												textbackground(1);
												gotoxy(17,8);
												cprintf("<A> USER ACCOUNTS");
												
												gotoxy(17,10);
												cprintf("<B> STOCK MANAGEMENT");
												
												gotoxy(17,12);
												cprintf("<C> SALES DEPARTMENT");
												
												gotoxy(17,14);
												cprintf("<D> REPORTS");

												gotoxy(17,16);
												cprintf("<E> PROFILE LOGS");

												textcolor(1);
												textbackground(7);
												gotoxy(7,21);
												cprintf(" ENTER THE CHOICE >");
												x=wherex();
												y=wherey();				
												break;
										case 1:
												clear_base();
												menu_box_input(50,19,5,3,1,9," MENU ");
												menu_box(20,19,55,3,7,8," HELP ");
												textcolor(15);
												textbackground(1);
												gotoxy(17,8);
												cprintf("<B> STOCK MANAGEMENT");
												
												gotoxy(17,10);
												cprintf("<C> SALES DEPARTMENT");
												
												gotoxy(17,12);
												cprintf("<D> REPORTS");
												
												gotoxy(17,14);
												cprintf("<E> PROFILE LOG");

												textcolor(1);
												textbackground(7);
												gotoxy(7,20);
												cprintf(" ENTER THE CHOICE >");
												x=wherex();
												y=wherey();
												break;
										case 0:clear_base();
												menu_box_input(50,17,5,5,1,9," MENU ");
												menu_box(20,17,55,5,7,8," HELP ");
												textcolor(15);
												textbackground(1);
												
												gotoxy(17,10);
												cprintf("<C> SALES DEPARTMENT");
												
												gotoxy(17,12);
												cprintf("<D> REPORTS");
												
												gotoxy(17,14);
												cprintf("<E> PROFILE LOG");

												textcolor(1);
												textbackground(7);
												gotoxy(7,20);
												cprintf(" ENTER THE CHOICE >");
												x=wherex();
												y=wherey();
												break;
									}
									
							}
							break;
				default:break;
			}
			
			if(esc)
				break;
		}
	}
	
	if(esc==2)
		esc=0;
	
	return option;
	
}


char user_account_screen()
{
	char *ch;
	char choice;
	int bcolor,fcolor;
	int level=-1;
	int x,y;
	char option;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"USER ACCOUNTS");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");
	
	user_account_window();
	
	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	x=35;
							y=19;
							rect(60,1,20,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-B");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							choice=1;
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
											if(choice=='a'||choice=='b'||choice=='A'||choice=='B')
											{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
											}	
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
											switch(choice)
											{
												case 'a':
												case 'A':	//menu_box(16,15,55,6,7,8," HELP ");
															
															rect(14,11,56,9,7,8);
															write(14,12,56,10,8,"Add new users ");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'b':
												case 'B':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"View the info of users");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												
											}
										}
								}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								user_account_window(bcolor);
							
						break;
				default:break;
			}
		}
		if(esc==2)
		{
				esc=0;
				break;
		}
		else if(esc==1)
		{
			break;
		}
	
	}
	
	return option;

}


void user_account_window()
{
	menu_box_input(45,15,10,6,1,9," [ MENU ] ");
	menu_box(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	textcolor(15);
	textbackground(1);
	gotoxy(18,11);
	cprintf("<A> Add New Users");
	gotoxy(18,14);
	cprintf("<B> View Users   ");
}



char stock_management_screen()
{

	char *ch;
	
	char choice;
	int bcolor,fcolor;
	int level=-1;
	int x,y;
	char option;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"Stock Management");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");
	
	stock_management_window();
	
	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	x=35;
							y=19;
							rect(60,1,20,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-C");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							choice=1;
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
											if(choice=='a'||choice=='b'||choice=='c'||choice=='A'||choice=='B'||choice=='C')
											{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
											}	
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
											switch(choice)
											{
												case 'a':
												case 'A':	//menu_box_input(16,15,55,6,7,8," HELP ");
															
															rect(14,11,56,9,7,8);
															write(14,12,56,10,8,"Add new stock in the library ");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'b':
												case 'B':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Search any medicine in stock");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'c':
												case 'C':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Report of All medicine in stock");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
											}
										}
								}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								stock_management_window();
							
						break;
				default:break;
			}
		}
		if(esc==2)
		{
				esc=0;
				break;
		}
		else if(esc==1)
		{
			break;
		}
	
	}
	
	return option;


}



void stock_management_window()
{
	menu_box_input(45,15,10,6,1,9," [ MENU ] ");
	menu_box(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	
	textcolor(15);
	textbackground(1);
	gotoxy(18,11);
	cprintf("<A> Add New Sock");
	gotoxy(18,13);
	cprintf("<B> Search Medicines");
	gotoxy(18,15);
	cprintf("<C> All Medicines in stock");
	
}


char report_screen()
{

	char *ch;
	char choice;
	int bcolor,fcolor;
	int level=-1;
	int x,y;
	char option;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	
	
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"Reports");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");

	report_window();
	
	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	x=35;
							y=19;
							rect(60,1,20,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-D");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							choice=1;
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
											if(choice=='a'||choice=='b'||choice=='c'||choice=='d'||choice=='A'||choice=='B'||choice=='C'||choice=='D')
											{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
											}	
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
											switch(choice)
											{
												case 'a':
												case 'A':	//menu_box_input(16,15,55,6,7,8," HELP ");
															
															rect(14,11,56,9,7,8);
															write(14,12,56,10,8,"Report of Medicine Near Expiry ");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'b':
												case 'B':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Total Sales till current date");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'c':
												case 'C':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Sales of current day");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'd':
												case 'D':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Sales from last 10 Days");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
											}
										}
								}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								report_window();
							
						break;
				default:break;
			}
		}
		if(esc==2)
		{
				esc=0;
				break;
		}
		else if(esc==1)
		{
			break;
		}
	
	}
	
	return option;

}



void report_window()
{
	menu_box_input(45,15,10,6,1,9," [ MENU ] ");
	menu_box(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	textcolor(15);
	textbackground(1);
	gotoxy(18,10);
	cprintf("<A> Medicines Near Expiry");
	gotoxy(18,12);
	cprintf("<B> Gross Sales");
	gotoxy(18,14);
	cprintf("<C> Today's Sales");
	gotoxy(18,16);
	cprintf("<D> Last 10 Day's Sales");
	
}
	

char user_profile_log_screen_1()
{
	char *ch;
	char choice;
	int bcolor,fcolor;
	int level=-1;
	int x,y;
	char option;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"PROFILE LOG");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");

	user_profile_log_window_1();

	
	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	x=35;
							y=19;
							rect(60,1,20,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-D");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							choice=1;
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
											if(choice=='a'||choice=='b'||choice=='A'||choice=='B')
											{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
											}	
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
											switch(choice)
											{
												case 'a':
												case 'A':	//menu_box_input(16,15,55,6,7,8," HELP ");
															
															rect(14,11,56,9,7,8);
															write(14,12,56,10,8,"View the Transections done by you ");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												
												case 'b':
												case 'B':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Change Your Password");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
											}
										}
								}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								user_profile_log_window_1();
							
						break;
				default:break;
			}
		}
		if(esc==2)
		{
				esc=0;
				break;
		}
		else if(esc==1)
		{
			break;
		}
	
	}
	
	return option;

}



void user_profile_log_window_1()
{
	menu_box_input(45,15,10,6,1,9," [ MENU ] ");
	menu_box(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	textcolor(15);
	textbackground(1);
	gotoxy(18,11);
	cprintf("<A> My Profile Log");
	gotoxy(18,14);
	cprintf("<B> Change Password:");
}

char user_profile_log_screen_2()
{
	char *ch;
	char choice;
	int bcolor,fcolor;
	int level=-1;
	int x,y;
	char option;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"PROFILE LOG");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");

	user_profile_log_window_2();
	

	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	x=35;
							y=19;
							rect(60,1,20,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-D");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							choice=1;
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
											if(choice=='a'||choice=='b'||choice=='c'||choice=='A'||choice=='B'||choice=='C')
											{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
											}	
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
											switch(choice)
											{
												case 'a':
												case 'A':	//menu_box_input(16,15,55,6,7,8," HELP ");
															
															rect(14,11,56,9,7,8);
															write(14,12,56,10,8,"View the Transections done by you ");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'b':
												case 'B':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"View Other users transections");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												
												case 'c':
												case 'C':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Change Your Password");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
											}
										}
								}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								user_profile_log_window_2();
							
						break;
				default:break;
			}
		}
		if(esc==2)
		{
				esc=0;
				break;
		}
		else if(esc==1)
		{
			break;
		}
	
	}
	
	return option;


}



void user_profile_log_window_2()
{
	menu_box_input(45,15,10,6,1,9," [ MENU ] ");
	menu_box_input(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	textcolor(15);
	textbackground(1);
	gotoxy(18,11);
	cprintf("<A> My Profile Log");
	gotoxy(18,13);
	cprintf("<B> Other User's Log");
	gotoxy(18,15);
	cprintf("<C> Change Password :");
}

char user_profile_log_screen_3()
{
	char *ch;
	char choice;
	int bcolor,fcolor;
	int level=-1;
	int x,y;
	char option;
	
	fcolor=14;
	bcolor=2;
	choice=1;

	clearS(0);
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"PROFILE LOG");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");

	user_profile_log_window_3();
	
	
	while(choice!=0)
	{
		update_time(54,1,7,1);

		if(kbhit())
		{
			choice=getch();
			switch(choice)
			{
				case 13:	x=35;
							y=19;
							rect(60,1,20,25,7,7);
							write_middle(1,1,30,25,7,0,"³");
							write_middle(3,1,34,25,7,4,"A-D");
							write_middle(11,1,38,25,7,0,":CHOICES   ");
							write_middle(5,1,51,25,7,4,"ENTER");
							write_middle(8,1,57,25,7,0," :SELECT");
							choice=1;
							while(choice!=27)
							{
								if(kbhit())
								{
									choice=getch();
									if(choice!=27&&choice!=13)
									{
										esc=0;
											if(choice=='a'||choice=='b'||choice=='c'||choice=='d'||choice=='A'||choice=='B'||choice=='C'||choice=='D')
											{
													option=choice;
													rect(16,1,x,y,7,1);
													gotoxy(x,y);
													cprintf("%c",choice);
											}	
										else
										{
											option=0;
											gotoxy(x,y);
											cprintf(" INVALID CHOICE ");
										}
									}
										if(option!=0)
										{
											switch(choice)
											{
												case 'a':
												case 'A':	//menu_box_input(16,15,55,6,7,8," HELP ");
															
															rect(14,11,56,9,7,8);
															write(14,12,56,10,8,"View the Transections done by you ");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'b':
												case 'B':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"View Other users transections");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'c':
												case 'C':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"View transections of all users");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
												case 'd':
												case 'D':rect(14,11,56,9,7,8);
														write(14,12,56,10,8,"Change Your Password");
														gotoxy(58,y);
														textcolor(8+128);
														textbackground(7);
														cprintf("PRESS ENTER");

														break;
											}
										}
								}
									else if(choice==13&option!=0)
									{
										choice=27;
										esc=2;
									}
									else if(choice==27)
									{
										esc=1;
										option=0;
									}
							}
							break;
				case 27: 	menu_box(40,9,20,8,4,15," WARNING ");
							write_middle(40,6,20,12,4,15,"Do You Want To Exit");
							write_middle(40,6,20,13,4,15,"(Y|N)");
							rect(38,1,21,15,7,15);
							gotoxy(40,15);
							textcolor(4);
							textbackground(7);
							choice=getch();
							cprintf("%c",choice);
							getch();
							if((choice=='y')||(choice=='Y'))
							{
								choice=0;
								esc=1;
							}
							else
								user_profile_log_window_1();
							
						break;
				default:break;
			}
		}
		if(esc==2)
		{
				esc=0;
				break;
		}
		else if(esc==1)
		{
			break;
		}
	
	}
	
	return option;

}



void user_profile_log_window_3()
{
	menu_box_input(45,15,10,6,1,9," [ MENU ] ");
	menu_box(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	textcolor(15);
	textbackground(1);
	gotoxy(18,10);
	cprintf("<A> My Profile Log");
	gotoxy(18,12);
	cprintf("<B> Other User's Log");
	gotoxy(18,14);
	cprintf("<C> All User's Log");
	gotoxy(18,16);
	cprintf("<D> Change Password");
}


void user_register_window()
{
	char *ch;
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	write_middle(13,1,2,1,7,4," ADD NEW USER ");
	write_middle(3,1,14,1,7,0," ³ ");
	write_middle(35,1,16,1,7,8," MEDICAL STORE MANAGEMENT ");
	menu_box(45,15,10,6,1,9," [ ADD USER ] ");
	menu_box(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"User name :      Max 30 charUser Id :        Max 10 charPassword :       Max 30 charLevel :         3:Root        2:Admin       1:Management  0:sales");
	textcolor(15);
	textbackground(1);

	gotoxy(18,11);
	cprintf("User Name :");
	gotoxy(18,13);
	cprintf("User Id   :");
	gotoxy(18,15);
	cprintf("Password  :");
	gotoxy(18,17);
	cprintf("User Level:");
}

void user_display_screen()
{
char *ch;
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ESC:Main Menu ³ ctrl+a:Watch Profile Log");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"INFO:USER ACCOUNTS ");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");

	user_display_window();
}

void user_display_window()
{

	menu_box(45,15,18,6,1,9," [ USER INFO ] ");
	textcolor(15);
	textbackground(1);

	gotoxy(26,11);
	cprintf("User Name :");
	gotoxy(26,13);
	cprintf("User Id   :");
	gotoxy(26,15);
	cprintf("Password  :");
	gotoxy(26,17);
	cprintf("User Level:");
}


void med_register_screen()
{
	char *ch;
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ 1:Main Menu ³ 2:Logout ³ 0:Exit");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"STOCK ENTRY");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");
	//menu_box(45,15,10,6,1,9," [ ADD USER ] ");
	
	med_register_window();
}

void med_register_window()
{	
	menu_box(50,21,5,3,1,9," [ STOCK ENTRY ] ");
	menu_box(21,21,55,3,7,8," HELP ");
	write(14,11,56,9,8," Medicine Name :    max 30 characters                 shelf row : Upto 15 only             shelf column : upto 15 only");
	textcolor(15);
	textbackground(1);
	
	gotoxy(10,9);
	cprintf("Key         :");
	gotoxy(32,9);
	cprintf("Medicine Id:");
	gotoxy(10,11);
	cprintf("Medicine Name:");
	gotoxy(10,13);
	cprintf("Quantity    :");
	gotoxy(32,13);
	cprintf("MRP/Item   :");
	gotoxy(10,15);
	cprintf("Batch Id    :");
	gotoxy(10,17);
	cprintf("Shelf Row   :");
	gotoxy(32,17);
	cprintf("Column     :");
	gotoxy(10,19);
	cprintf("Current Date:");
	gotoxy(32,19);
	cprintf("Expiry Date:");

	getch();
}

void sales_transection()
{
	char *ch;
	*ch=NULL;
	strcpy(ch," WELCOME : ");
	strcat(ch,userCurrent.userName);
	strcat(ch,"  ³ ENTER:Goto Input ³ ECS:Main Menu ³ ctrl+b:Last Entry");
	base_screen("","");
	rect(W,1,1,25,7,7);
	write_middle(W,1,1,25,7,0,ch);
	rect(50,1,1,1,7,7);
	gotoxy(1,1);
	write_middle(19,1,2,1,7,4,"SALES TRANSACTION");
	write_middle(3,1,20,1,7,0," ³ ");
	write_middle(28,1,23,1,7,8," MEDICAL STORE MANAGEMENT ");

	sales_transection_window();

}



void sales_transection_window()
{
	menu_box(45,15,18,6,1,9," [ TRANSACTION ] ");
	//menu_box_input(16,15,55,6,7,8," HELP ");
	write(14,11,56,9,8,"");
	textcolor(15);
	textbackground(1);
	gotoxy(26,11);
	cprintf("Patient Name:");
	gotoxy(26,13);
	cprintf("Current Date:");
	gotoxy(26,15);

	cprintf("Amount      :");
}
