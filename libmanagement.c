#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TITLE 1
#define AUTHOR 2
#define SUBJECT 3
#define CODE 4
#define SHELF_NO 5

#define MAXSIZE 1028
#define MIS 0
#define BOOKCODE 1
#define BORROW 2

typedef struct book
{
	char title[64];
	char author[32];
	char subject[16];	
	int code;
	int price;
	int shelf_num;
	int avail_copies;
}book;

typedef struct date
{
	short date;
	short month;
	short year;
}date;

typedef struct timing
{
	short hours;
	short mins;
}timing;

typedef struct student
{
	struct borrow
	{
		date bor_date;
		timing bor_timing;
		char status[16];		/* Whether issued or returned */
		date ret_date;
		timing ret_timing;
	}record;
	char name[32];
	int mis;
	int bookcode;
}student;

/* Book record managing functions */
void addbook(book *p);
void searchbook(short key, char *str);
void display(book *p);
void editcopies(int code, int number);
void sortbook(int key);

/* Book record utility functions */
int myfprintf(FILE *fp, book *p);
int mysscanf(char *s, book *p);
void swapbook(book *b, int i, int j);

/* Student book issue record managing functions */
void addissue(student *s);
void returned(int mis, int code);
void search_record(int key, int state);
void displayrec(student *s);
void sortstud(int key);

/* Student record utility functions */
int myfprintf2(FILE *fp, student *s);
int mysscanf2(char *st, student *s);
void swapstud(student *s, int i, int j);

int main()
{
	book *p;
	char ch, ch2, str[64];
	int choice, code, number, mis, key;
	student *s;
	
	printf("Welcome to library management\n");
	while(1)
	{
		Label_1:
		printf("\nEnter the record which is to be managed\n");
		printf("1. Book record\t2. Student record\t3. End the session\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				while(1)
				{
					Label_2:
					printf("\nx. Add new book record\ty. Search book\tz. Edit number of copies of existing book\t");
					printf("u. Sort book records\n\t v. Go to library management stage\tw.End session\n");
					scanf(" %c", &ch);
					switch(ch)
					{	
						case 'x' :	p = (book *) malloc(sizeof(book));
								printf("Enter title\n");
								scanf(" %[^\n]s", p->title);
								printf("Enter author name\n");
								scanf(" %[^\n]s", p->author);
								printf("Enter subject category\n");
								scanf(" %[^\n]s", p->subject);
								printf("Enter book code, price, shelf number and available copies\n");
								scanf("%d%d%d%d", &(p->code), &(p->price), &(p->shelf_num),&(p->avail_copies));
								addbook(p);
								free(p);
								break;
				
						case 'y' :	printf("Search according to:\n");
								printf("a. Title\tb. Author\tc. Subject Category\td. Code\t");
								printf("e. Go to book record managing\tf. Go to library management\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a' :	printf("Enter title\n");
											scanf(" %[^\n]s", str);
											searchbook(TITLE, str);
											break;

									case 'b' :	printf("Enter author\n");
											scanf(" %[^\n]s", str);
											searchbook(AUTHOR, str);
											break;

									case 'c' :	printf("Enter Subject category\n");
											scanf(" %[^\n]s", str);
											searchbook(SUBJECT, str);
											break;

									case 'd' :	printf("Enter book code\n");
											scanf("%s", str);
											searchbook(CODE, str);
											break;

									case 'e' :	/* goto book record managing */
											goto Label_2;
											break;

									case 'f' :	/* goto library managing */
											goto Label_1;
											break;
								}
								break;
						
						case 'z' :	printf("Enter book code\n");
								scanf("%d", &code);
								printf("Enter number of new copies of this book purchased\n");
								scanf("%d", &number);
								editcopies(code, number);
								break;

						case 'u' : 	printf("Sort according to:\n");
								printf("a. Book code\tb. Subject\tc. Author\td. Shelf number\n");
								scanf(" %c", &ch2);	
								switch(ch2)
								{
									case 'a':	sortbook(CODE);
											break;
									case 'b':	sortbook(SUBJECT);
											break;
									case 'c':	sortbook(AUTHOR);
											break;
									case 'd':	sortbook(SHELF_NO);
											break;
								}
								break;

						case 'v' :	/* goto library managing */
								goto Label_1;
								break;

						case 'w':	return 0;
								break;
					
					}
				}
				break;

			case 2:
				while(1)
				{
					printf("x. Add new issue record\ty. Search an issue record\t");
					printf("z. Edit issued book record on returning\tu. Sort issue records\n");
					printf("\tv. Go to library managing\tw. End session\n");
					scanf(" %c", &ch);
					switch(ch)
					{
						case 'x':	s = (student *) malloc(sizeof(student));
								printf("Enter first name of student\n");
								scanf("%s", s->name);
								printf("Enter student mis\n");
								scanf("%d", &(s->mis));
								printf("Enter book code\n");
								scanf("%d", &(s->bookcode));
								addissue(s);
								free(s);
								break;

						case 'y':	printf("Search according to: a. book code\tb. student mis\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a':	printf("Enter book code\n");
											scanf("%d", &key);
											search_record(key, BOOKCODE);
											break;

									case 'b':	printf("Enter student mis\n");
											scanf("%d", &key);
											search_record(key, MIS);
											break;
								}
								break;

						case 'z':	printf("Enter student mis\n");
								scanf("%d", &mis);
								printf("Enter book code\n"); 
								scanf("%d", &code);
								returned(mis, code);
								break; 

						case 'u' :	printf("Sort according to:\n");
								printf("a. Student MIS\tb. Book code\tc. Borrow date-time\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a' :	sortstud(MIS);
											break;
									case 'b' :	sortstud(BOOKCODE);
											break;
									case 'c' :	sortstud(BORROW);
											break;
								}
								break;
		
						case 'v' :	goto Label_1;
								break;

						case 'w':	return 0;
								break;
					}
				}
				break;

			case 3:
				return 0;
		}
	}
	return 0;
}

/* Book record managing functions */
void addbook(book *p)					/* To add a new book record */
{	
	FILE *fp;
	fp = fopen("bookrecord.txt", "a");
	myfprintf(fp, p);
	fclose(fp);
	return;
}

void searchbook(short key, char *str)			/* To search book according to title, author, subject or code */
{
	int i = 0;
	char s[1028];
	book *p = (book *) malloc(sizeof(book));
	
	FILE *fp = fopen("bookrecord.txt", "r");
	if(fp == NULL)
	{
		printf("No records exist\n");
		return;
	}

	while(fgets(s, 1028, fp) != NULL)
	{
		mysscanf(s, p);
		if(key == TITLE)
		{
			if(strstr(p->title, str))
			{
				display(p);
				printf("\n");
				i++;
			}
						
		}	
		if(key == AUTHOR)
		{
			if(strstr(p->author, str))
			{
				display(p);
				printf("\n");
				i++;
			}
		}
		if(key == SUBJECT)
		{
			if(strstr(p->subject, str))
			{
				display(p);
				printf("\n");
				i++;
			}
		}
		if(key == CODE)
		{
			if(atoi(str) == p->code)
			{
				display(p);
				printf("\n");
				i++;
				break;
			}
		}
	}
	if(i == 0)
		printf("No records found\n");
	free(p);
	fclose(fp);
}

void display(book *p)					/* To display a book record on screen */
{
	printf("Code\tTitle\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);	
}

void editcopies(int code, int number)			/* To edit number of copies of an existing book */
{
	FILE *fp;
	int n = 0, i = 0, index = -1;
	book b[MAXSIZE];
	char s[1028];

	fp = fopen("bookrecord.txt", "r");
	if(!fp)
	{
		printf("No records exist\n");
		return;
	}

	while(fgets(s, 1028, fp) != NULL)
	{
		mysscanf(s, &b[i]);
		if(b[i].code == code)
			index = i;
		i++;
		n++;
	}
	fclose(fp);

	if(index == -1)
	{
		printf("No book of matching code found\n");
		return;
	}
	b[index].avail_copies += number;
	fp = fopen("bookrecord.txt", "w");

	for(i = 0; i < n; i++)
		myfprintf(fp, &b[i]);
	fclose(fp);
	return;
}

void sortbook(int key)					/* To sort book records according to code, subject, author or shelf number */
{
	book b[MAXSIZE];
	int cnt = 0, i = 0, j = 0, n = 0;
	FILE *fp;
	char s[1028];

	fp = fopen("bookrecord.txt", "r");
	if(!fp)
	{
		printf("No records exist\n");
		return;
	}
	while((fgets(s, 1028, fp)) != NULL)
	{
		mysscanf(s, &b[i]);
		n++;
		i++;
	}
	fclose(fp);
	
	if(key == CODE)
	{
		for(i = 0; i < n-1; i++)				/* Bubble sort */
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(b[j].code > b[j+1].code)
				{
					swapbook(b, j, j+1);
					cnt++;
				}
			}
			if(cnt == 0)
				break;
		}
	}

	else if(key == SUBJECT)
	{
		for(i = 0; i < n-1; i++)
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(strcmp(b[j].subject, b[j+1].subject) > 0)
				{
					swapbook(b, j, j+1);
					cnt++;
				}
			}
			if(cnt == 0)
				break;
		}
	}

	else if(key == AUTHOR)
	{
		for(i = 0; i < n-1; i++)
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(strcmp(b[j].author, b[j+1].author) > 0)
				{
					swapbook(b, j, j+1);					
					cnt++;
				}
			}
			if(cnt == 0)
				break;
		}
	}

	else if(key == SHELF_NO)
	{
		for(i = 0; i < n-1; i++)
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(b[j].shelf_num > b[j+1].shelf_num)
				{
					swapbook(b, j, j+1);
					cnt++;
				}
			}
			if(cnt == 0)
				break;
		}
	}
	
	fp = fopen("bookrecord.txt", "w");
	for(i = 0; i < n; i++)
		myfprintf(fp, &b[i]);
	fclose(fp);				
}

int myfprintf(FILE *fp, book *p)		/* To write a book record into book records' file */
{
	int m;
	m = fprintf(fp, "%d\t%s\t%s\t%s\t%d\t%d\t%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);
	return m;
}

int mysscanf(char *s, book *p)			/* To read from char array containing a line red from file into book variable pointed by p */
{
	int m;
	char str[7][128];
	
	m = sscanf(s, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", str[0], str[1], str[2], str[3], str[4], str[5], str[6]);
	p->code = atoi(str[0]);
	strcpy(p->title, str[1]);
	strcpy(p->author, str[2]);
	strcpy(p->subject, str[3]);
	p->price = atoi(str[4]);
	p->shelf_num = atoi(str[5]);
	p->avail_copies = atoi(str[6]);

	return m;
}

void swapbook(book *b, int i, int j)		/* To swap two books in array.. used in sorting */
{
	book tmp;
	tmp = b[i];
	b[i] = b[j];
	b[j] = tmp;
}

/* Student book issue record managing functions */
void addissue(student *s)				/* To add new book issue record from student */
{
	struct tm *t;
	time_t rawtime;
	FILE *fp, *fpr;
	int i = 0, index = -1;
	char st[1028];
	book b[MAXSIZE];

	fpr = fopen("bookrecord.txt", "r");
	if(!fpr)
	{
		printf("No book records exist\n");
		return;
	}
	while(fgets(st, 1028, fpr) != NULL)
	{
		mysscanf(st, &b[i]); 
		if(b[i].code == s->bookcode)
		{
			index = i;
			break;
		}
		i++;
	}
	fclose(fpr);

	if(index == -1)
	{
		printf("Book code does not exist\n");
		return;
	}

	strcpy(s->record.status, "issued");
	time(&rawtime);
	t = localtime(&rawtime);
	s->record.bor_date.date = t->tm_mday;
	s->record.bor_date.month = t->tm_mon + 1;
	s->record.bor_date.year = t->tm_year + 1900;
	s->record.bor_timing.hours = t->tm_hour;
	s->record.bor_timing.mins = t->tm_min;

	s->record.ret_date.date = 0;
	s->record.ret_date.month = 0;
	s->record.ret_date.year = 0;
	s->record.ret_timing.hours = 0;
	s->record.ret_timing.mins = 0;

	fp = fopen("studentrecord.txt", "a");
	myfprintf2(fp, s);
	fclose(fp);
	editcopies(s->bookcode, -1);
	return;
}

void returned(int mis, int code)			/* To edit status of existing issue record on returning of book */
{
	struct tm *t;
	time_t rawtime;
	char st[1028];
	FILE *fp;
	int i = 0, n = 0;
	student s[MAXSIZE];

	fp = fopen("studentrecord.txt", "r");
	if(!fp)
	{
		printf("No record exists\n");
		return;
	}
	while(fgets(st, 1028, fp) != NULL)
	{
		mysscanf2(st, &s[i++]); 
		n++;
	}
	fclose(fp);
	for(i = 0; i < n; i++)
	{
		if(s[i].mis == mis && s[i].bookcode == code)
			break;
	}
	if(i == n)
	{
		printf("No matching issue record found\n");
		return;
	}
	editcopies(code, 1);
	strcpy(s[i].record.status, "returned");
	time(&rawtime);
	t = localtime(&rawtime);
	s[i].record.ret_date.date = t->tm_mday;
	s[i].record.ret_date.month = t->tm_mon + 1;
	s[i].record.ret_date.year = t->tm_year + 1900;
	s[i].record.ret_timing.hours = t->tm_hour;
	s[i].record.ret_timing.mins = t->tm_min;
	
	fp = fopen("studentrecord.txt", "w");
	for(i = 0; i < n; i++)
		myfprintf2(fp, &s[i]);
	fclose(fp);

	return;
}

void search_record(int key, int state)			/* To search issue record according to student mis or book code */
{
	student *s;
	char st[1028];
	FILE *fp;
	int cnt = 0;

	s = (student *) malloc(sizeof(student));
	fp = fopen("studentrecord.txt", "r");
	if(!fp)
	{
		printf("No issue records exist\n");
		return;
	}

	while(fgets(st, 1028, fp) != NULL)	
	{
		mysscanf2(st, s);
		if(state == MIS)
		{
			if(s->mis == key)
			{
				displayrec(s);
				cnt++;
			}
		}
		else if(state == BOOKCODE)
		{
			if(s->bookcode == key)
			{
				displayrec(s);
				cnt++;
			}
		}
	}
	fclose(fp);
	if(cnt == 0)
		printf("No matching issue record found\n");
	free(s);	
	return;
}

void displayrec(student *s)			/* To display a student record on screen */
{
	printf("MIS\tName\tBookcode\tBorrow Date\tTime\tStatus\tReturn Date\tTime\n");
	printf("%d\t%s\t%d\t%d %d %d\t%d:%d\t%s\t%d %d %d\t%d:%d\n", s->mis, s->name, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.bor_timing.hours, s->record.bor_timing.mins, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year, s->record.ret_timing.hours, s->record.ret_timing.mins);
	return;
}

void sortstud(int key)				/* To sort student records according to student mis, book code or borrow date & time */
{
	student s[MAXSIZE];
	int cnt = 0, i = 0, j = 0, n = 0;
	FILE *fp;
	char str[1028];
	
	fp = fopen("studentrecord.txt", "r");
	if(!fp)
	{
		printf("No records exist\n");
		return;
	}
	while((fgets(str, 1028, fp)) != NULL)
	{
		mysscanf2(str, &s[i]);
		i++;
		n++;
	}
	fclose(fp);

	if(key == MIS)
	{
		for(i = 0; i < n-1; i++)
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(s[j].mis > s[j+1].mis)
				{
					swapstud(s, j, j+1);
					cnt++;
				}
			}
			if(cnt == 0)
				break;
		}
	}

	if(key == BOOKCODE)
	{
		for(i = 0; i < n-1; i++)
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(s[j].bookcode > s[j+1].bookcode)
				{
					swapstud(s, j, j+1);
					cnt++;
				}
			}
			if(cnt == 0)
				break;
		}
	}

	if(key == BORROW)
	{
		for(i = 0; i < n-1; i++)
		{
			cnt = 0;
			for(j = 0; j < n-1; j++)
			{
				if(s[j].record.bor_date.year > s[j+1].record.bor_date.year)
				{
					swapstud(s, j, j+1);
					cnt++;
				}
				else if(s[j].record.bor_date.year == s[j+1].record.bor_date.year)
				{
					if(s[j].record.bor_date.month > s[j+1].record.bor_date.month)
					{
						swapstud(s, j, j+1);
						cnt++;
					}
					else if(s[j].record.bor_date.month == s[j+1].record.bor_date.month)
					{
						if(s[j].record.bor_date.date > s[j+1].record.bor_date.date)
						{
							swapstud(s, j, j+1);
							cnt++;
						}
						else if(s[j].record.bor_date.date == s[j+1].record.bor_date.date)
						{
							if(s[j].record.bor_timing.hours > s[j+1].record.bor_timing.hours)
							{
								swapstud(s, j, j+1);
								cnt++;
							}
							else if(s[j].record.bor_timing.hours == s[j+1].record.bor_timing.hours)
							{
								if(s[j].record.bor_timing.mins > s[j+1].record.bor_timing.mins)
								{
									swapstud(s, j, j+1);
									cnt++;
								}
							}
						}
					}
				}
			}
			if(cnt == 0)
				break;
		}
	}

	fp = fopen("studentrecord.txt", "w");
	for(i = 0; i < n; i++)
		myfprintf2(fp, &s[i]);
	fclose(fp);				
}

int myfprintf2(FILE *fp, student *s)		/* To write student record in student records' file */
{
	int m;
	m = fprintf(fp, "%d\t%s\t%d\t%d %d %d\t%d:%d\t%s\t%d %d %d\t%d:%d\n", s->mis, s->name, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.bor_timing.hours, s->record.bor_timing.mins, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year, s->record.ret_timing.hours, s->record.ret_timing.mins);
	return m;
}

int mysscanf2(char *st, student *s)		/*To read from char array containing a line red from file into student variable pointed by s*/
{
	int m;
	char *str[14];
	char *strnew = (char *) malloc(128);
	char *strnew2 = (char *) malloc(128);
	for(m = 0; m < 13; m++)
		str[m] = (char *) malloc(128);
	
	m = sscanf(st, "%[^\t]\t%[^\t]\t%[^\t]\t%s%s%s\t%[^\t]\t%[^\t]\t%s%s%s\t%[^\n]\n", str[0], str[1], str[2], str[3], str[4], str[5], strnew, str[8], str[9], str[10], str[11], strnew2);
	
	str[6] = strtok(strnew, ":");
	str[7] = strtok(NULL, "\0");
	str[12] = strtok(strnew2, ":");
	str[13] = strtok(NULL, "\0");

	s->mis = atoi(str[0]);
	strcpy(s->name, str[1]);
	s->bookcode = atoi(str[2]);
	s->record.bor_date.date = atoi(str[3]);
	s->record.bor_date.month = atoi(str[4]);
	s->record.bor_date.year = atoi(str[5]);
	s->record.bor_timing.hours = atoi(str[6]);
	s->record.bor_timing.mins = atoi(str[7]);
	strcpy(s->record.status, str[8]);
	s->record.ret_date.date = atoi(str[9]);
	s->record.ret_date.month = atoi(str[10]);
	s->record.ret_date.year = atoi(str[11]);
	s->record.ret_timing.hours = atoi(str[12]);
	s->record.ret_timing.mins = atoi(str[13]);

	free(strnew);
	free(strnew2);
	return m;
}

void swapstud(student *s, int i, int j)			/* To swap two student records in an array.. Used in sorting */
{
	student tmp;
	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}
