#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TITLE 1
#define AUTHOR 2
#define SUBJECT 3
#define CODE 4

#define MAXSIZE 1028
#define MIS 0
#define BOOKCODE 1

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

typedef struct student
{
	struct borrow
	{
		date bor_date;
		char status[16];		/* Whether returned, issued or damaged */
		date ret_date;
	}record;
	char name[32];
	int mis;
	int bookcode;
}student;

//Book record managing functions :-
void addbook(book *p);
void searchbook(short key, char *str);
void display(book *p);
void editcopies(int code, int number);

int myfprintf(FILE *fp, book *p);
int myfscanf(FILE *fp, book *p);
int mysscanf(char *s, book *p);

int myfprintf2(FILE *fp, student *s);
int mysscanf2(char *st, student *s);

//Student book issue record managing functions :-
//void addissue(student *s, int code);
void addissue(student *s);
void returned(int mis, int code);
void search_record(int key, int state);
void displayrec(student *s);

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
					printf("v. Go to library management stage\tw.End session\n");
					scanf(" %c", &ch);
					switch(ch)
					{	
						case 'x' :	 
								p = (book *) malloc(sizeof(book));
								/* Code number for new book is automatically generated as the next 
										available code number */	
								printf("Enter title\n");
								scanf(" %[^\n]s", p->title);
								printf("Enter author name\n");
								scanf(" %[^\n]s", p->author);
								printf("Enter subject category\n");
								scanf(" %[^\n]s", p->subject);
								printf("Enter price, shelf number and available copies\n");
								scanf("%d%d%d", &(p->price), &(p->shelf_num), &(p->avail_copies));
								addbook(p);
								break;
				
						case 'y' :	
								p = (book *) malloc(sizeof(book));
								printf("Search according to:\n");
								printf("a. Title\tb. Author\tc. Subject Category\td. Code\t");
								printf("e. Go to book record managing\tf. Go to library management\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a' :	
											printf("Enter title\n");
											scanf(" %[^\n]s", str);
											searchbook(TITLE, str);
											break;
									case 'b' :	
											printf("Enter author\n");
											scanf(" %[^\n]s", str);
											searchbook(AUTHOR, str);
											break;
									case 'c' :	
											printf("Enter Subject category\n");
											scanf(" %[^\n]s", str);
											searchbook(SUBJECT, str);
											break;
									case 'd' :
											printf("Enter book code\n");
											scanf("%s", str);
											searchbook(CODE, str);
											break;
									case 'e' :
											/* goto book record managing */
											goto Label_2;
											break;
									case 'f' :
											/* goto library managing */
											goto Label_1;
											break;
								}
								break;
						
						case 'v' :
								/* goto library managing */
								goto Label_1;
								break;

						case 'z' :
								printf("Enter book code\n");
								scanf("%d", &code);
								printf("Enter number of new copies of this book purchased\n");
								scanf("%d", &number);
								editcopies(code, number);
								break;

						case 'w':
								return 0;
								break;
					
					}
				}
				break;

			case 2:
				while(1)
				{
					//Label_3 :
					printf("x. Add new issue record\ty. Search an issue record\t");
					printf("z. Edit issued book record on returning\tv. Go to library managing\t");
					printf("w. End session\n");
					scanf(" %c", &ch);
					switch(ch)
					{
						case 'x':
								/* Adding new book issue record of student */
								s = (student *) malloc(sizeof(student));
								printf("Enter first name of student\n");
								scanf("%s", s->name);
								printf("Enter student mis\n");
								scanf("%d", &(s->mis));
								printf("Enter book code\n");
								scanf("%d", &(s->bookcode));
								addissue(s);
								break;

						case 'y':
								/* Searching a student record */
								printf("Search according to: a. book code\tb. student mis\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a':
											printf("Enter book code\n");
											scanf("%d", &key);
											search_record(key, BOOKCODE);
											break;
									case 'b':
											printf("Enter student mis\n");
											scanf("%d", &key);
											search_record(key, MIS);
											break;
								}
								break;

						case 'z':
								printf("Enter student mis\n");
								scanf("%d", &mis);
								printf("Enter book code\n"); 
								scanf("%d", &code);
								returned(mis, code);
								break; 
		
						case 'v' :
								goto Label_1;
								break;

						case 'w':
								return 0;
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

void addbook(book *p)
{	
//	book *b = (book *) malloc(sizeof(book));
	int code = 1;
	char s[1028];
	FILE *fp = fopen("bookrecord1.txt", "r");
	if(fp == NULL)
		p->code = 1;
	else
	{
//		while((fread(b, sizeof(book), 1, fp1)))
//		while((myfscanf(fp1, b)))
		while(fgets(s, 1028, fp) != NULL)
			code++;
	//	if(n == 0)
	//		p->code = 1;
	//	else
	//		p->code = b->code + 1;			// sometimes problematic.. works in libmanagement_new.c file
		p->code = code;
		fclose(fp);
	}

	fp = fopen("bookrecord1.txt", "a");
//	myfprintf(fp, p);
//	fwrite(p, sizeof(book), 1, fp2);	
	myfprintf(fp, p);
	fclose(fp);
	return;
}

void searchbook(short key, char *str)
{
	int i = 0;
	char s[1028];
	book *p = (book *) malloc(sizeof(book));
	
	FILE *fp = fopen("bookrecord1.txt", "r");
	if(fp == NULL)
	{
		printf("No records exist\n");
		return;
	}

//	while(myfscanf(fp, p))
//	while(fread(p, sizeof(book), 1, fp))
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
	fclose(fp);
}

void display(book *p)
{
	printf("Code\tTitle\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);	
	/*printf("Code=%d\tTitle-%s\tAuth-%s\tSub-%s\tRs %d\tShelf %d\tCopies=%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);*/
}

void editcopies(int code, int number)
{
	FILE *fp;
	int n = 0, i = 0;
	book b[MAXSIZE];
	char s[1028];

	fp = fopen("bookrecord1.txt", "r");
	if(!fp)
	{
		printf("No records exist\n");
		return;
	}
//	while(fread(&b[i], sizeof(book), 1, fp))
	while(fgets(s, 1028, fp) != NULL)
	{
		mysscanf(s, &b[i++]); 
		n++;
	}
//	printf("n = %d\n", n);
//	n = i;
	fclose(fp);

	if(code <= 0 || code > n)
	{
		printf("Code does not exist\n");
		return;
	}
	
	b[code-1].avail_copies += number;
	fp = fopen("bookrecord1.txt", "w");
//	fwrite(b, sizeof(book), n, fp);
	for(i = 0; i < n; i++)
		myfprintf(fp, &b[i]);
	fclose(fp);
	return;
}

int myfprintf(FILE *fp, book *p)
{
	int m;
	m = fprintf(fp, "%d\t%s\t%s\t%s\t%d\t%d\t%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);
	return m;
}

int myfscanf(FILE *fp, book *p)
{
	int m;
	m = fscanf(fp, "%d\t%s\t%s\t%s\t%d\t%d\t%d\n", &(p->code), p->title, p->author, p->subject, &(p->price), &(p->shelf_num), &(p->avail_copies));
	return m;
}

int mysscanf(char *s, book *p)
{
	int m;
	char str[7][128];
	/*m = sscanf(s, "[^\t]s[^\t]s[^\t]s[^\t]s[^\t]s[^\t]s[^\t]s\t\n", &(p->code), p->title, p->author, p->subject, &(p->price), &(p->shelf_num), &(p->avail_copies));*/
//	m = sscanf(s, "%s%s%s%s%s%s%s\n", str[0], str[1], str[2], str[3], str[4], str[5], str[6]);
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

int myfprintf2(FILE *fp, student *s)
{
	int m;
	m = fprintf(fp, "%d\t%s\t%d\t%d %d %d\t%s\t%d %d %d\n", s->mis, s->name, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year);
	return m;
}

int mysscanf2(char *st, student *s)
{
	int m;
	char str[10][128];
//	m = sscanf(st, "%[^\t]\t%[^\t]\t%[^\t]\t%s%s%[^\t]\t%[^\t]\t%s%s%[^\n]\n", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8], str[9]);
	m = sscanf(st, "%[^\t]\t%[^\t]\t%[^\t]\t%s%s%s\t%[^\t]\t%s%s%[^\n]\n", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8], str[9]);
	s->mis = atoi(str[0]);
	strcpy(s->name, str[1]);
	s->bookcode = atoi(str[2]);
	s->record.bor_date.date = atoi(str[3]);
	s->record.bor_date.month = atoi(str[4]);
	s->record.bor_date.year = atoi(str[5]);
	strcpy(s->record.status, str[6]);
	s->record.ret_date.date = atoi(str[7]);
	s->record.ret_date.month = atoi(str[8]);
	s->record.ret_date.year = atoi(str[9]);

	return m;
}

void addissue(student *s)
{
	struct tm *t;
	time_t rawtime;
	FILE *fp, *fpr;
	int i = 0, n = 0;
	char st[1028];
	book b[MAXSIZE];

	fpr = fopen("bookrecord1.txt", "r");
	if(!fpr)
	{
		printf("No book records exist\n");
		return;
	}
//	while(fread(&b[i], sizeof(book), 1, fpr))
//		i++;
//	n = i;
	while(fgets(st, 1028, fpr) != NULL)
	{
		mysscanf(st, &b[i++]); 
		n++;
	}
	fclose(fpr);

	if(s->bookcode <= 0 || s->bookcode > n)				// Sometimes problematic
	{
		printf("Code does not exist\n");
		return;
	}

	strcpy(s->record.status, "issued");
	time(&rawtime);
	t = localtime(&rawtime);
	s->record.bor_date.date = t->tm_mday;
	s->record.bor_date.month = t->tm_mon + 1;
	s->record.bor_date.year = t->tm_year + 1900;
	s->record.ret_date.date = 0;
	s->record.ret_date.month = 0;
	s->record.ret_date.year = 0;

	fp = fopen("studentrecord1.txt", "a");
	//rewind(fp);
//	fwrite(s, sizeof(student), 1, fp);
	myfprintf2(fp, s);
	fclose(fp);
	editcopies(s->bookcode, -1);		
	return;
}

void returned(int mis, int code)
{
	struct tm *t;
	time_t rawtime;
	char st[1028];
	FILE *fp;
	int i = 0, n = 0;
	student s[MAXSIZE];

	fp = fopen("studentrecord1.txt", "r");
	if(!fp)
	{
		printf("No record exists\n");
		return;
	}
//	while(fread(&s[i], sizeof(student), 1, fp))
//		i++;
//	n = i;
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
	
	fp = fopen("studentrecord1.txt", "w");

//	fwrite(s, sizeof(student), n, fp);
	for(i = 0; i < n; i++)
		myfprintf2(fp, &s[i]);
	fclose(fp);

	return;
}

void search_record(int key, int state)
{
	student *s;
	char st[1028];
	FILE *fp;
	int cnt = 0;

	s = (student *) malloc(sizeof(student));
	fp = fopen("studentrecord1.txt", "r");
	if(!fp)
	{
		printf("No issue records exist\n");
		return;
	}
//	while(fread(s, sizeof(student), 1, fp))
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
	return;
}

void displayrec(student *s)
{
	printf("MIS\tName\tBookcode\tBorrow Date\tStatus\tReturn Date\n");
	printf("%d\t%s\t%d\t%d %d %d\t%s\t%d %d %d\n", s->mis, s->name, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year);
	return;
}