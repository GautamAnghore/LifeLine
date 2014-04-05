// TEAM CYBROS : GAUTAM ANGHORE
// initiated :22/4/2013 completed:27/4/2013 
// TEXT FUNCTIONS HEADER
// MEDTEXT.H

//----------------------------------------------------------------------------------------------------------------------------------------------
/*
void arr_init(char a[],int n);

void text_input(char ch[],int n,int bcolor,int fcolor);
void text_input_pass(char ch[],int n,int bcolor,int fcolor);// do not show the characters

void text_output(char *ch,int bcolor,int fcolor);
void text_output_pass(char *ch,int bcolor,int fcolor);

//compare s1 and s2 of length n and return 1 for same and 0 for different strings -> case sensitive
int text_compare(char *s1,char *s2,int n); 

//encryption to store in file
void text_encrypt(char *ch);//key 58
void text_decrypt(char *ch);

*/
//-----------------------------------------------------------------------------------------------------------------------------------------------
void arr_init(char a[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		a[i]=NULL;
	}
}


void text_input(char ch[],int n,int bcolor,int fcolor)
{
	int i=0;
	char *c,*temp;
	char flag=1;
	
	textbackground(bcolor);
	textcolor(fcolor);
	
	temp=c;
	fflush(stdin);
	
	while(flag!=13)
	{
		if(kbhit())
		{
			fflush(stdin);
			flag=getch();
			if(flag!=13)
			{
				if((flag==8)&&(i!=0))
				{
					*c=NULL;
					c--;
					i--;
					cprintf("\b");
				}
				else if(flag!=8)
				{
					if(i<(n-1))
					{
						*c=flag;
						cprintf("%c",*c);
						c++;
						i++;
					}
					else
					{
						*c=NULL;
						break;
					}
				}	
			}
			else
			{
				*c=NULL;
				break;
			}
		}
	}
	
	c=temp;
	
	strcpy(ch,c);
}

void text_input_pass(char ch[],int n,int bcolor,int fcolor)
{
	int i=0;
	char *c,*temp;
	char flag=1;
		
	textbackground(bcolor);
	textcolor(fcolor);
	
	temp=c;
	fflush(stdin);
	
	while(flag!=13)
	{
		if(kbhit())
		{
			fflush(stdin);
			flag=getch();
			if(flag!=13)
			{
				if((flag==8)&&(i!=0))
				{
					*c=NULL;
					c--;
					i--;
					cprintf("\b");
				}
				else if(flag!=8)
				{
					if(i<(n-1))
					{
						*c=flag;
						cprintf("*");
						c++;
						i++;
					}
					else
					{
						*c=NULL;
						break;
					}
				}	
			}
			else
			{
				*c=NULL;
				break;
			}
		}
	}
	
	c=temp;
	
	strcpy(ch,c);
}

void text_output(char *ch,int bcolor,int fcolor)
{	
	textbackground(bcolor);
	textcolor(fcolor);
	
	while(*ch!=NULL)
	{
		cprintf("%c",*ch);
		ch++;
	}
}

void text_output_pass(char *ch,int bcolor,int fcolor)
{
	
	textbackground(bcolor);
	textcolor(fcolor);
	
	while(*ch!=NULL)
	{
		cprintf("*");
		ch++;
	}
}

int text_compare(char *s1,char *s2,int n)
{
	int i=1,flag=1;
	
	while((flag==1)&&(i<=n))
	{
		if(*s1==*s2)
		{
			s1+=1;
			s2+=1;
			i++;
		}
		else
		{
			flag=0;
		}
	}
	
	return flag;

}

void text_encrypt(char *ch)
{
	while(*ch!=NULL)
	{
		*ch+=58;
		ch++;
	}
}
void text_decrypt(char *ch)
{
	while(*ch!=NULL)
	{
		*ch-=58;
		ch++;
	}
}
