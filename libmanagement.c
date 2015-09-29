/* Library management */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define TITLE 1
#define AUTHOR 2
#define SUBJECT 3

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
	char name[16];
	int mis;
}student;

void addbook(book *p);
void searchbook(short key, char *str);
void display(book *p);
int myfprintf(FILE *fp, book *p);
int myfscanf(FILE *fp, book *p);

void addissue(student *s, int code);
student *search_record( );

int main()
{
	book *p;
	char ch, ch2, str[64];
	int choice;
	
	printf("Welcome to library management\n");
	while(1)
	{
		printf("Enter the record which is to be managed\n");
		printf("1. Book record\t2. Student record\t3. End the session\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				printf("x. Add new book record\ty. Search book\tz. Go to library management stage\n");
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
							printf("a. Title\tb. Author\tc. Subject Category\t");
							printf("d. Go to book record managing\te. Go to library management\n");
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
										/* goto book record managing */
										break;
								case 'e' :
										/* goto library managing */
										break;
							}
					
					case 'z' :
							/* goto library managing */
							break;
					
				}
				break;

			case 2:
				printf("x. Add new book issue record\ty. Search a student record\n");
				scanf(" %c", &ch);
				switch(ch)
				{
					case 'x':
							/* Adding new book issue record */
							break;
					case 'y':
							/* Searching a student record */
							break;
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
	book *b = (book *) malloc(sizeof(book));
	int n = 0;
	FILE *fp1 = fopen("bookrecord.txt", "r");
	if(fp1 == NULL)
		p->code = 1;
	else
	{
		while((fread(b, sizeof(book), 1, fp1)))
//		while((myfscanf(fp1, b)))
			n++;
		if(n == 0)
			p->code = 1;
		else
			p->code = b->code + 1;
	
		fclose(fp1);
	}

	FILE *fp2 = fopen("bookrecord.txt", "a");
//	myfprintf(fp, p);
	fwrite(p, sizeof(book), 1, fp2);	
	fclose(fp2);
	return;
}

void searchbook(short key, char *str)
{
	int i = 0;
	book *p = (book *) malloc(sizeof(book));
	
	FILE *fp = fopen("bookrecord.txt", "r");
	if(fp == NULL)
	{
		printf("No records exist\n");
		return;
	}

//	while(myfscanf(fp, p))
	while(fread(p, sizeof(book), 1, fp))
	{
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
