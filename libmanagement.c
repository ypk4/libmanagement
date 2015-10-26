/* Library management */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"libmanagement.h"

/* Book record managing functions :-*/
void addbook(book *p)					/* To add a new book record */
{	
	FILE *fp;
	fp = fopen("bookrecord.txt", "r");
	if(!fp)
	{
		fp = fopen("bookrecord.txt", "a");
		fprintf(fp, "Code\tTitle\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	}
	if(fp)
	{
		fclose(fp);
		fp = fopen("bookrecord.txt", "a");
	}
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
	if(!fp)
	{
		printf("No records exist\n");
		return;
	}

	fgets(s, 1028, fp);			/* To read first line of file mentioning column names and discard it */
	printf("Code\tTitle\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	while(fgets(s, 1028, fp) != NULL)
	{
		mysscanf(s, p);
		if(key == TITLE)
		{
			if(strstr(p->title, str))
			{
				display(p);
				i++;
			}
						
		}	
		if(key == AUTHOR)
		{
			if(strstr(p->author, str))
			{
				display(p);
				i++;
			}
		}
		if(key == SUBJECT)
		{
			if(strstr(p->subject, str))
			{
				display(p);
				i++;
			}
		}
		if(key == CODE)
		{
			if(atoi(str) == p->code)
			{
				display(p);
				i++;
				break;		/* Since book code is unique */
			}
		}
	}
	if(i == 0)
		printf("\nNo records found\n");
	free(p);
	fclose(fp);
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

	fgets(s, 1028, fp);			/* To read first line of file mentioning column names and discard it */
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
	fprintf(fp, "Code\tTitle\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
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
	
	fgets(s, 1028, fp);			/* To read first line of file mentioning column names and discard it */		
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
	fprintf(fp, "Code\tTitle\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	for(i = 0; i < n; i++)
		myfprintf(fp, &b[i]);
	fclose(fp);				
}

void display(book *p)					/* To display a book record on screen */
{
	printf("%d\t%s\t%s\t%s\t%d\t%d\t%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);	
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

/* Student book issue record managing functions :- */
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

	fgets(st, 1028, fpr);			/* To read first line of file mentioning column names and discard it */		
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

	/* Fetching system date and time to store it as issue date and time */
	time(&rawtime);
	t = localtime(&rawtime);
	s->record.bor_date.date = t->tm_mday;
	s->record.bor_date.month = t->tm_mon + 1;
	s->record.bor_date.year = t->tm_year + 1900;
	s->record.bor_timing.hours = t->tm_hour;
	s->record.bor_timing.mins = t->tm_min;

	rawtime += 15 * 24 * 60 * 60;			/* Day 15 days after today */
	t = localtime(&rawtime);
	s->record.ret_date.date = t->tm_mday;		/* Due date */
	s->record.ret_date.month = t->tm_mon + 1;
	s->record.ret_date.year = t->tm_year + 1900;
	s->record.ret_timing.hours = 0;
	s->record.ret_timing.mins = 0;

	fp = fopen("studentrecord.txt", "r");
	if(!fp)
	{
		fp = fopen("studentrecord.txt", "a");
		fprintf(fp, "MIS\tName\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
	}
	if(fp)
	{
		fclose(fp);
		fp = fopen("studentrecord.txt", "a");
	}
	myfprintf2(fp, s);
	fclose(fp);
	editcopies(s->bookcode, -1);		/* Decrementing number of available copies of the issued book by 1 */
	return;
}

void returned(int mis, int code)			/* To edit status of existing issue record on returning of book */
{
	struct tm *t;
	time_t rawtime;
	char st[1028];
	FILE *fp;
	int i = 0, n = 0, index = -1;
	student s[MAXSIZE];

	fp = fopen("studentrecord.txt", "r");
	if(!fp)
	{
		printf("No record exists\n");
		return;
	}
	
	fgets(st, 1028, fp);			/* To read first line of file mentioning column names and discard it */		
	while(fgets(st, 1028, fp) != NULL)
	{
		mysscanf2(st, &s[i]);
		if(s[i].mis == mis && s[i].bookcode == code)
			index = i;
		n++;
		i++;
	}
	fclose(fp);

	if(index == -1)
	{
		printf("No matching issue record found\n");
		return;
	}
	editcopies(code, 1);		/* Incrementing number of available copies of the returned book by 1 */
	strcpy(s[index].record.status, "returned");

	/* Fetching system date and time to store it as return date and time */
	time(&rawtime);
	t = localtime(&rawtime);
	s[index].record.ret_date.date = t->tm_mday;
	s[index].record.ret_date.month = t->tm_mon + 1;
	s[index].record.ret_date.year = t->tm_year + 1900;
	s[index].record.ret_timing.hours = t->tm_hour;
	s[index].record.ret_timing.mins = t->tm_min;
	
	fp = fopen("studentrecord.txt", "w");
	fprintf(fp, "MIS\tName\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
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

	printf("MIS\tName\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
	fgets(st, 1028, fp);			/* To read first line of file mentioning column names and discard it */		
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
		printf("\nNo matching issue record found\n");
	free(s);	
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

	fgets(str, 1028, fp);			/* To read first line of file mentioning column names and discard it */		
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
	fprintf(fp, "MIS\tName\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
	for(i = 0; i < n; i++)
		myfprintf2(fp, &s[i]);
	fclose(fp);				
}

void displayrec(student *s)			/* To display a student record on screen */
{
	printf("%d\t%s\t%d\t%d %d %d\t%d:%d\t%s\t%d %d %d\t%d:%d\n", s->mis, s->name, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.bor_timing.hours, s->record.bor_timing.mins, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year, s->record.ret_timing.hours, s->record.ret_timing.mins);
	return;
}
https://github.com/ypk4/libmanagement.git
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
