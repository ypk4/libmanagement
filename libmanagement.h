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

#include<ncurses.h>

#define TITLE 1
#define AUTHOR 2
#define SUBJECT 3
#define CODE 4
#define SHELF_NO 5

#define MAXSIZE 1028		/* Maximum no of records */ 
#define MIS 0
#define BOOKCODE 1
#define BORROW 2
#define NAME 3
#define BOOKCODE_ISSUED 4
#define MIS_ISSUED 5

#define STUDENT 1
#define FACULTY 2

#define ST_DAYS 10		/* No of days allowed to keep issued book by student */
#define FAC_DAYS 100		/* No of days allowed to keep issued book by faculty */

#define ST_BOOKS 3		/* No of books that can be kept at a time by student */
#define FAC_BOOKS 8		/* No of books that can be kept at a time by faculty */

#define PENULTY 0.05		/* Percentage of additional fine on damaging/losing book */

#define ST_TOLERANCE 7		/* No of days after due date for which keeping book by student is tolerable (Subject to fine on returning) */
#define FAC_TOLERANCE 20	/* No of days after due date for which keeping book by faculty is tolerable (Subject to fine on returning) */

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

typedef struct issuerecord			/* New book issue record by student or faculty */
{
	struct bor_record
	{
		date bor_date;
		timing bor_timing;
		char status[16];		/* Whether issued or returned or damaged */
		date ret_date;
		timing ret_timing;
	}record;
	char name[32];
	char department[16];
	int mis;
	int bookcode;
}issuerecord;

union int_or_str
{
	int integer;
	char str[64];
};

struct fine
{
	int late;
	int damage;
};

/* Book record managing functions */
int addbook(book *p);						/* To add a new book record */
book* searchbook(short key, union int_or_str var, int *num);	/* To search book according to title, author, subject or code */
int editcopies(int code, int number);				/* To edit number of copies of an existing book */
int deletebook(int code);				/* To delete a book record from library (Because of damage of all copies or because of 							     wrong entry of book record or due to circumstances like ban on the book by government)*/
int sortbook(int key);						/* To sort book records according to code, subject, author or shelf number */
void display(book *p, WINDOW *vin);				/* To display a book record on screen */

/* Book record utility functions */
int myfprintf(FILE *fp, book *p);			/* To write a book record into book records' file */
int mysscanf(char *s, book *p);			/* To read from char array containing a line red from file into book variable pointed by p */
void swapbook(book *b, int i, int j);			/* To swap two books in array.. used in sorting */

/* Borrower book issue record managing functions */
int addissue(issuerecord *s, short borrow);			/* To add new book issue record from student/faculty */
issuerecord* search_record(union int_or_str var, int state, short borrow, int *num);
								/* To search issue record according to student/faculty mis or book code */
struct fine* returned(int mis, int code, char status, short borrow);	/* To edit status of existing issue record on returning of book */
issuerecord* longtimeissue(int *n, short borrow);	/* To get information about issue records exceeding due date by specified days */
int sortrec(int key, short borrow);			/* To sort student/faculty records according to mis, book code or borrow date & time */
void displayrec(issuerecord *s, WINDOW *vin);		/* To display a student/faculty record on screen */

/* Borrower record utility functions */
int myfprintf2(FILE *fp, issuerecord *s);		/* To write student/faculty record in respective records' file */
int mysscanf2(char *st, issuerecord *s);		/*To read from char array containing a line red from file into borrower variable pointed by s*/
void swapstud(issuerecord *s, int i, int j);		/* To swap two student records in an array.. Used in sorting */

