/*****************************************************************************
 * Library Management
 * Copyright (C) 2015 Kulkarni Yogiraj Purushottam
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
******************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"libmanagement.h"

/* Book record managing functions :-*/
int addbook(book *p)					/* To add a new book record */
{	
	FILE *fp;
	book *b;
	union int_or_str var;
	int num;

	var.integer = p->code;
	b = searchbook(CODE, var, &num);
	if(b)
	{
		free(b);
		return -1;
	}

	fp = fopen("bookrecord.txt", "r");
	if(!fp)
	{
		fp = fopen("bookrecord.txt", "a");
		fprintf(fp, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	}
	if(fp)
	{
		fclose(fp);
		fp = fopen("bookrecord.txt", "a");
	}
	myfprintf(fp, p);
	fclose(fp);
	return 1;
}

book* searchbook(short key, union int_or_str var, int *num)		/* To search book according to title, author, subject or code */
{
	int i = 0;
	char s[1028];
	book *b = (book *) malloc(128 * sizeof(book));
	book *p = (book *) malloc(sizeof(book));
	*num = 0;
	
	FILE *fp = fopen("bookrecord.txt", "r");
	if(!fp)
		return NULL;

	fgets(s, 1028, fp);			/* To read first line of file mentioning column names and discard it */
	while(fgets(s, 1028, fp) != NULL)
	{
		mysscanf(s, p);
		if(key == TITLE)
		{
			if(strstr(p->title, var.str))
			{
				b[(*num)++] = *p;
				i++;
			}
						
		}	
		if(key == AUTHOR)
		{
			if(strstr(p->author, var.str))
			{
				b[(*num)++] = *p;
				i++;
			}
		}
		if(key == SUBJECT)
		{
			if(strstr(p->subject, var.str))
			{
				b[(*num)++] = *p;
				i++;
			}
		}
		if(key == CODE)
		{
			if(var.integer == p->code)
			{
				b[(*num)++] = *p;
				i++;
				break;		/* Since book code is unique */
			}
		}
	}
	free(p);
	fclose(fp);
	if(i == 0)
		return NULL;
	return b;
}

int editcopies(int code, int number)			/* To edit number of copies of an existing book */
{
	FILE *fp;
	int n = 0, i = 0, index = -1;
	book b[MAXSIZE];
	char s[1028];

	fp = fopen("bookrecord.txt", "r");
	if(!fp)
		return 0;
	
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
		return 0;
	
	b[index].avail_copies += number;
	
	fp = fopen("bookrecord.txt", "w");
	fprintf(fp, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	for(i = 0; i < n; i++)
		myfprintf(fp, &b[i]);
	fclose(fp);
	return 1;
}

int deletebook(int code)				/* To delete a book record from library (Because of damage of all copies or because of 							  incorrect entry of book record or due to circumstances like ban on the book by government)*/
{
	FILE *fp;
	int n = 0, i = 0, index = -1;
	book b[MAXSIZE];
	char s[1028];

	fp = fopen("bookrecord.txt", "r");
	if(!fp)
		return 0;
	
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
		return 0;
	
	fp = fopen("bookrecord.txt", "w");
	fprintf(fp, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	for(i = 0; i < n; i++)
	{
		if(i == index)
			continue;
		myfprintf(fp, &b[i]);
	}
	fclose(fp);
	return 1;
}

int sortbook(int key)					/* To sort book records according to code, subject, author or shelf number */
{
	book b[MAXSIZE];
	int cnt = 0, i = 0, j = 0, n = 0;
	FILE *fp;
	char s[1028];

	fp = fopen("bookrecord.txt", "r");
	if(!fp)
		return 0;
		
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
	fprintf(fp, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\tShelfNo\tCopies\n");
	for(i = 0; i < n; i++)
		myfprintf(fp, &b[i]);
	fclose(fp);
	return 1;				
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

/* Borrower book issue record managing functions :- */
int addissue(issuerecord *s, short borrow)				/* To add new book issue record from student/faculty */
{
	struct tm *t;
	time_t rawtime;			/* Calender time in seconds */
	FILE *fp, *fpr;
	union int_or_str var;
	int i = 0, index = -1, number = 0;
	char st[1028];
	book b[MAXSIZE];
	issuerecord *p;

	fpr = fopen("bookrecord.txt", "r");
	if(!fpr)
		return 0;

	var.integer = s->mis;
	if(borrow == STUDENT)
	{
		p = search_record(var, MIS, STUDENT, &number);
		if(number >= ST_BOOKS)		/* If borrower already has issued max no of permissible books */
		{
			free(p);			
			return -2;		
		}
	}			
	else if(borrow == FACULTY)
	{
		p = search_record(var, MIS, FACULTY, &number);
		if(number >= FAC_BOOKS)
		{
			free(p);
			return -2;	
		}			
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

	if(index == -1)			/* If book code does not exist */
		return -1;			
	
	strcpy(s->record.status, "issued");

	/* Fetching system date and time to store it as issue date and time */
	time(&rawtime);
	t = localtime(&rawtime);
	s->record.bor_date.date = t->tm_mday;
	s->record.bor_date.month = t->tm_mon + 1;
	s->record.bor_date.year = t->tm_year + 1900;
	s->record.bor_timing.hours = t->tm_hour;
	s->record.bor_timing.mins = t->tm_min;

	if(borrow == STUDENT)
		rawtime += ST_DAYS * 24 * 60 * 60;		/* Day "ST_DAYS" days after today */
	else if(borrow == FACULTY)
		rawtime += FAC_DAYS * 24 * 60 * 60;
	t = localtime(&rawtime);
	s->record.ret_date.date = t->tm_mday;		/* Due date */
	s->record.ret_date.month = t->tm_mon + 1;
	s->record.ret_date.year = t->tm_year + 1900;
	s->record.ret_timing.hours = 0;
	s->record.ret_timing.mins = 0;

	if(borrow == STUDENT)
		fp = fopen("studentrecord.txt", "r");
	else if(borrow == FACULTY)
		fp = fopen("facultyrecord.txt", "r");
	if(!fp)
	{
		if(borrow == STUDENT)
			fp = fopen("studentrecord.txt", "a");
		else if(borrow == FACULTY)
			fp = fopen("facultyrecord.txt", "a");
		fprintf(fp, "MIS\tName\tDept\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
	}
	if(fp)
	{
		fclose(fp);
		if(borrow == STUDENT)
			fp = fopen("studentrecord.txt", "a");
		else if(borrow == FACULTY)
			fp = fopen("facultyrecord.txt", "a");
	}
	myfprintf2(fp, s);
	fclose(fp);
	editcopies(s->bookcode, -1);		/* Decrementing number of available copies of the issued book by 1 */
	return 1;
}

struct fine* returned(int mis, int code, char status, short borrow)	/* To edit status of existing issue record on returning of book */
{
	struct tm *t1, *t2;
	time_t rawtime1, rawtime2;
	char st[1028];
	FILE *fp;
	long diff, ndays;
	union int_or_str var;
	int i = 0, n = 0, index = -1, number;
	struct fine *f;
	issuerecord s[MAXSIZE];
	book *p;
	
	f = (struct fine*) malloc(sizeof(struct fine));
	t1 = (struct tm*) malloc(sizeof(struct tm));
	t2 = (struct tm*) malloc(sizeof(struct tm));

	if(borrow == STUDENT)
		fp = fopen("studentrecord.txt", "r");
	else if(borrow == FACULTY)
		fp = fopen("facultyrecord.txt", "r");
	if(!fp)
		return NULL;
		
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
		return NULL;
	
	t1->tm_mday = s[index].record.ret_date.date;		/* Original due date */
	t1->tm_mon = s[index].record.ret_date.month - 1;
	t1->tm_year = s[index].record.ret_date.year - 1900;
	t1->tm_hour = 0;
	t1->tm_min = 0;
	t1->tm_sec = 0;
	rawtime1 = mktime(t1);

	if(status == 'a')
	{
		strcpy(s[index].record.status, "returned");
		editcopies(code, 1);		/* Incrementing number of available copies of the returned book by 1 */
		f->damage = 0;
	}
	else if(status == 'b')
	{
		strcpy(s[index].record.status, "damaged/lost");
		var.integer = code;
		p = searchbook(CODE, var, &number);
		f->damage = p->price * (1 + PENULTY);	/* Damage fine = Price of book + Penulty(=15% of price) */
	}
	
	/* Fetching system date and time to store it as return date and time */
	time(&rawtime2);
	t2 = localtime(&rawtime2);
	s[index].record.ret_date.date = t2->tm_mday;
	s[index].record.ret_date.month = t2->tm_mon + 1;
	s[index].record.ret_date.year = t2->tm_year + 1900;
	s[index].record.ret_timing.hours = t2->tm_hour;
	s[index].record.ret_timing.mins = t2->tm_min;
	
	if((diff = difftime(rawtime2, rawtime1)) > 0)	/* Diff between due date & return date in seconds */
	{
		ndays = diff / (60 * 60 * 24);		/* Diff between due date & return date in no of days */
		f->late = ndays * 5;
	}
	else
		f->late = 0;
	
	if(borrow == STUDENT)
		fp = fopen("studentrecord.txt", "w");
	else if(borrow == FACULTY)
		fp = fopen("facultyrecord.txt", "w");
	fprintf(fp, "MIS\tName\tDept\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
	for(i = 0; i < n; i++)
		myfprintf2(fp, &s[i]);
	fclose(fp);
	return f;
}

issuerecord* search_record(union int_or_str var, int state, short borrow, int *num)	/* To search issue record according borrower to mis or book code */
{
	issuerecord *s, *b;
	char st[1028];
	FILE *fp;
	
	*num = 0;
	b = (issuerecord *) malloc(64 * sizeof(issuerecord));	
	s = (issuerecord *) malloc(sizeof(issuerecord));

	if(borrow == STUDENT)
		fp = fopen("studentrecord.txt", "r");
	else if(borrow == FACULTY)
		fp = fopen("facultyrecord.txt", "r");
	if(!fp)
		return NULL;
	
	fgets(st, 1028, fp);			/* To read first line of file mentioning column names and discard it */		
	while(fgets(st, 1028, fp) != NULL)	
	{
		mysscanf2(st, s);
		if(state == MIS)
		{
			if(s->mis == var.integer)
				b[(*num)++] = *s;
		}	
		else if(state == BOOKCODE)
		{
			if(s->bookcode == var.integer)
				b[(*num)++] = *s;
		}
		else if(state == BOOKCODE_ISSUED)
		{
			if((s->bookcode == var.integer) && ((strcmp((s->record).status, "issued") == 0)))
				b[(*num)++] = *s;
		}
		else if(state == NAME)
		{
			if(strstr(s->name, var.str))
				b[(*num)++] = *s;
		}
	}
	fclose(fp);
	if(*num == 0)
		return NULL;
	free(s);	
	return b;
}

issuerecord* longtimeissue(int *n, short borrow)       /*To get informationn about issue records exceeding due date by tolerarable no of days*/
{
	issuerecord *b, s;
	FILE *fp;
	struct tm t1;
	int tolerance;
	time_t rawtime1, rawtime2;
	char st[1028];
	long diff;
	
	*n = 0;
	b = (issuerecord *) malloc(64 * sizeof(issuerecord));
	time(&rawtime2);			/* Fetching current system date and time in seconds */

	if(borrow == STUDENT)
	{	fp = fopen("studentrecord.txt", "r");
		tolerance = ST_DAYS + ST_TOLERANCE;
	}
	else if(borrow == FACULTY)
	{	fp = fopen("facultyrecord.txt", "r");
		tolerance = FAC_DAYS + FAC_TOLERANCE;
	}
	if(!fp)
		return NULL;

	fgets(st, 1028, fp);			/* To read first line of file mentioning column names and discard it */		
	while(fgets(st, 1028, fp) != NULL)
	{
		mysscanf2(st, &s);
		if(strcmp(s.record.status, "issued") == 0)
		{
			t1.tm_mday = s.record.bor_date.date;		/* Storing borrow date */
			t1.tm_mon = s.record.bor_date.month - 1;
			t1.tm_year = s.record.bor_date.year - 1900;
			t1.tm_hour = t1.tm_min = t1.tm_sec = 0;
			rawtime1 = mktime(&t1);			/* Converting borrow date into seconds */

			diff = difftime(rawtime2, rawtime1);	/* Difference between today's date and borrow date in seconds */
			if(diff > (tolerance * (60 * 60 * 24)))
				b[((*n)++)] = s;
		}
	}
	fclose(fp);
	return b;
}

int sortrec(int key, short borrow)			/* To sort student records according to student mis, book code or borrow date & time */
{
	issuerecord s[MAXSIZE];
	int cnt = 0, i = 0, j = 0, n = 0;
	FILE *fp;
	char str[1028];
	
	if(borrow == STUDENT)
		fp = fopen("studentrecord.txt", "r");
	else if(borrow == FACULTY)
		fp = fopen("facultyrecord.txt", "r");
	if(!fp)
		return 0;

	fgets(str, 1028, fp);		/* To read first line of file mentioning column names and discard it */		
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

	if(borrow == STUDENT)
		fp = fopen("studentrecord.txt", "w");
	else if(borrow == FACULTY)
		fp = fopen("facultyrecord.txt", "w");
	fprintf(fp, "MIS\tName\tDept\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");
	for(i = 0; i < n; i++)
		myfprintf2(fp, &s[i]);
	fclose(fp);	
	return 1;			
}

int myfprintf2(FILE *fp, issuerecord *s)		/* To write student record in student records' file */
{
	int m;
	m = fprintf(fp, "%d\t%s\t%s\t%d\t%d %d %d\t%d:%d\t%s\t%d %d %d\t%d:%d\n", s->mis, s->name, s->department, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.bor_timing.hours, s->record.bor_timing.mins, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year, s->record.ret_timing.hours, s->record.ret_timing.mins);
	return m;
}

int mysscanf2(char *st, issuerecord *s)		/*To read from char array containing a line red from file into student variable pointed by s*/
{
	int m;
	char *str[15];
	char *strnew = (char *) malloc(128);
	char *strnew2 = (char *) malloc(128);
	for(m = 0; m < 15; m++)
		str[m] = (char *) malloc(128);
	
	m = sscanf(st, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%s%s%s\t%[^\t]\t%[^\t]\t%s%s%s\t%[^\n]\n", str[0], str[1], str[14], str[2], str[3], str[4], str[5], strnew, str[8], str[9], str[10], str[11], strnew2);
	
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
	strcpy(s->department, str[14]);

	free(strnew);
	free(strnew2);
	return m;
}

void swapstud(issuerecord *s, int i, int j)			/* To swap two student records in an array.. Used in sorting */
{
	issuerecord tmp;
	tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}
