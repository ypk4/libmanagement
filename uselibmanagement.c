/* Library management */
#include<stdio.h>
#include<stdlib.h>
#include"libmanagement.h"

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
		printf("Enter the record which is to be managed\n");
		printf("1. Book record\t2. Student record\t3. End the session\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				while(1)
				{
					Label_2:
					printf("x. Add new book record\ty. Search book\tz. Edit number of copies of existing book\t");
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

									default :	break;
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
									default :	break;
								}
								break;

						case 'v' :	/* goto library managing */
								goto Label_1;
								break;

						case 'w':	return 0;
								break;

						default :	break;
					
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

									default :	break;
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
									default :	break;
								}
								break;
		
						case 'v' :	goto Label_1;
								break;

						case 'w':	return 0;
								break;

						default :	break;
					}
				}
				break;

			case 3:	return 0;

			default: break;
		}
	}
	return 0;
}
