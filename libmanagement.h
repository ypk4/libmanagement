/* Library management */
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

