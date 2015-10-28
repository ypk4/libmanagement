/* Library management */
#include<stdio.h>
#include<stdlib.h>
#include"libmanagement.h"

int main()
{
	book *p;
	char ch, ch2; //str[64];
	union int_or_str var;
	int choice, code, number, mis, key, i;
	borrower *s;
	struct fine* f;
	
	printf("Welcome to library management\n");
	while(1)
	{
		Label_1:
		printf("Enter the record which is to be managed\n");
		printf("1. Book record\t2. Student record\t3. Faculty record\t4. End the session\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				while(1)
				{
					Label_2:
					printf("x. Add new book record\ty. Search book\tz. Edit number of copies of existing book\t");
					printf("u. Sort book records\n\tv. Go to library management stage\tw.End session\tt. Delete a book\n");
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
								number = addbook(p);
								if(number == -1)
									printf("Book code already exists.\tPlease use unique code.\n");
								free(p);
								break;
				
						case 'y' :	printf("Search according to:\n");
								printf("a. Title\tb. Author\tc. Subject Category\td. Code\t");
								printf("e. Go to book record managing\tf. Go to library management\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a' :	printf("Enter title\n");
											scanf(" %[^\n]s", var.str);
											p = searchbook(TITLE, var, &number);
											if(!p)
											{	printf("No records found\n");
												break;
											}
											printf("Code\tTitle\tAuthor\tSubject\tPrice\t");
											printf("ShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i]);
											free(p);
											break;

									case 'b' :	printf("Enter author\n");
											scanf(" %[^\n]s", var.str);
											p = searchbook(AUTHOR, var, &number);
											if(!p)
											{	printf("No records found\n");
												break;
											}
											printf("Code\tTitle\tAuthor\tSubject\tPrice\t");
											printf("ShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i]);
											free(p);

											break;

									case 'c' :	printf("Enter Subject category\n");
											scanf(" %[^\n]s", var.str);
											p = searchbook(SUBJECT, var, &number);
											if(!p)
											{	printf("No records found\n");
												break;
											}											
											printf("Code\tTitle\tAuthor\tSubject\tPrice\t");
											printf("ShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i]);
											free(p);
											break;

									case 'd' :	printf("Enter book code\n");
											scanf("%d", &(var.code));
											p = searchbook(CODE, var, &number);
											if(!p)
											{	printf("No records found\n");
												break;
											}
											printf("Code\tTitle\tAuthor\tSubject\tPrice\t");
											printf("ShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i]);
											free(p);
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
								i = editcopies(code, number);
								if(i == 0)
									printf("No book of matching code found\n");
								break;

						case 'u' : 	printf("Sort according to:\n");
								printf("a. Book code\tb. Subject\tc. Author\td. Shelf number\n");
								scanf(" %c", &ch2);	
								switch(ch2)
								{
									case 'a':	i = sortbook(CODE);
											if(i == 0)
												printf("No book records exist\n");
											break;
									case 'b':	i = sortbook(SUBJECT);
											if(i == 0)
												printf("No book records exist\n");
											break;
									case 'c':	i = sortbook(AUTHOR);
											if(i == 0)
												printf("No book records exist\n");
											break;
									case 'd':	i = sortbook(SHELF_NO);
											if(i == 0)
												printf("No book records exist\n");
											break;
									default :	break;
								}
								break;

						case 't' :	printf("Enter book code\n");
								scanf("%d", &code);
								number = deletebook(code);
								if(number == 0)
									printf("Book code does not exist\n");
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
			case 3:
				while(1)
				{
					printf("x. Add new issue record\ty. Search an issue record\t");
					printf("z. Edit issued book record on returning\tu. Sort issue records\n");
					printf("\tv. Go to library managing\tw. End session\n");
					scanf(" %c", &ch);
					switch(ch)
					{
						case 'x':	s = (borrower *) malloc(sizeof(borrower));
								printf("Enter first name of student/faculty\n");
								scanf("%s", s->name);
								printf("Enter department abbreviation of student/faculty\n");
								scanf("%s", s->department);
								printf("Enter student/faculty mis\n");
								scanf("%d", &(s->mis));
								printf("Enter book code\n");
								scanf("%d", &(s->bookcode));
								if(choice == 2)
									number = addissue(s, STUDENT);
								else if(choice == 3)
									number = addissue(s, FACULTY);
								free(s);
								if(number == -2)
								{	printf("Cannot issue the book.\t");
									printf("Borrower already has maximum permissible no of books.\n");
								}
								if(number == 0)
									printf("No book records exist");
								if(number == -1)
									printf("Book code does not exist\n");
								break;

						case 'y':	printf("Search according to: a. book code\tb. student/faculty mis\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a':	printf("Enter book code\n");
											scanf("%d", &key);
											if(choice == 2)
											    s = search_record(key, BOOKCODE, STUDENT, &number);
											else if(choice == 3)
											    s = search_record(key, BOOKCODE, FACULTY, &number);
											if(!s)
											{
												printf("No matching issue record found\n");
												break;
											}
											printf("MIS\tName\tDept\tBookcode\tBorrow Date\t");
											printf("Time\tStatus\tDue/Return Date\tTime\n");
											for(i = 0; i < number; i++)
												displayrec(&s[i]);
											free(s);
											break;

									case 'b':	printf("Enter student/faculty mis\n");
											scanf("%d", &key);
											if(choice == 2)
												s = search_record(key, MIS, STUDENT, &number);
											else if(choice == 3)
												s = search_record(key, MIS, FACULTY, &number);
											if(!s)
											{
												printf("No matching issue record found\n");
												break;
											}
											printf("MIS\tName\tDept\tBookcode\tBorrow Date\t");
											printf("Time\tStatus\tDue/Return Date\tTime\n");
											for(i = 0; i < number; i++)
												displayrec(&s[i]);
											free(s);
											break;

									default :	break;
								}
								break;

						case 'z':	printf("Enter student/faculty mis\n");
								scanf("%d", &mis);
								printf("Enter book code\n"); 
								scanf("%d", &code);
								printf("a. Returned in good condition\tb. Damaged/Lost\n");
								scanf(" %c", &ch2);
								if(choice == 2)
									f = returned(mis, code, ch2, STUDENT);
								else if(choice == 3)
									f = returned(mis, code, ch2, FACULTY);
								if(!f)
									printf("No matching issue record found\n");
								else
								{
									printf("Late by %d days\tLate fine = %d\n", f->late / 5, f->late);
									printf("Damage/lost fine = %d\n", f->damage);
									printf("Total fine = %d\n", f->late + f->damage);
									free(f);
								}
								break; 

						case 'u' :	printf("Sort according to:\n");
								printf("a. Student/faculty MIS\tb. Book code\tc. Borrow date-time\n");
								scanf(" %c", &ch2);
								switch(ch2)
								{
									case 'a' :	if(choice == 2)
												number = sortrec(MIS, STUDENT);
											else if(choice == 3)
												number = sortrec(MIS, FACULTY);
											if(number == 0)
												printf("No issue records exist\n");
											break;

									case 'b' :	if(choice == 2)
												number = sortrec(BOOKCODE, STUDENT);
											else if(choice == 3)
												number = sortrec(BOOKCODE, FACULTY);
											if(number == 0)
												printf("No issue records exist\n");
											break;

									case 'c' :	if(choice == 2)
												number = sortrec(BORROW, STUDENT);
											else if(choice == 3)
												number = sortrec(BORROW, FACULTY);
											if(number == 0)
												printf("No issue records exist\n");
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

			case 4:	return 0;

			default: break;
		}
	}
	return 0;
}
