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
#include<stdlib.h>
#include<string.h>
#include"libmanagement.h"

char lpw[32] = "Lib_User";		/* Librarian password */
char spw[32] = "Stud_User";		/* Student password */
char fpw[32] = "Fac_User";		/* Faculty password */

int main()
{
	book *p;
	char ch, ch2, pw[64], pword[32];
	union int_or_str var;
	int choice, choice2, code, number, mis, i, number2;
	issuerecord *s;
	struct fine* f;
	WINDOW *vin;
	
	Label_n:
	initscr();
	clear();
	scrollok(stdscr, TRUE);				/* To auto scroll down ncurses window */
	idlok(stdscr, TRUE);
	printw("Welcome to library management\n");
	refresh();
				
	Label:
	touchwin(stdscr);
	printw("------------------------------------------------------------------------------------------------------------------\n");
	refresh();
	printw("Login as:\n1. Librarian\t2. Student\t3. Faculty\t4. Quit application\n");
	refresh();
	scanw("%d", &choice2);
	
	switch(choice2)
	{
		case 1:
			printw("Enter password\n");
			noecho();
			scanw("%s", pw);
			echo();
			if(strcmp(pw, lpw) == 0)
			{
				vin = newwin(0, 0, 0, 0);
				scrollok(vin,TRUE);					/* To auto scroll down ncurses window */
				idlok(vin, TRUE);
				wprintw(vin, "Hello librarian !\n");
				while(1)
				{
					Label_1:
					wprintw(vin, "\n---------------------------------------------------------------------------------------------------------------------\n");
					wprintw(vin, "Enter the record which is to be managed\n");
					wprintw(vin, "1. Book record  \t2. Student record\t3. Faculty record\t4. Log out session\n");
					wscanw(vin, "%d", &choice);
					switch(choice)
					{
						case 1:
							wprintw(vin, "\n------------------------------------------------------------------------------------------------------------------\nWelcome to book managing...");
							while(1)
							{
								Label_2:
								wprintw(vin, "\n------------------------------------------------------------------------------------------------------------------\n");
								wprintw(vin, "x. Add new book record \ty. Search book \tz. Edit number of copies of existing book\t");	
								wprintw(vin, "u. Sort book records\n\tt. Delete a book\tv. Go to library management stage\tw.Log out session\n");			
								wscanw(vin, " %c", &ch);
								switch(ch)
								{	
									case 'x' :	p = (book *) malloc(sizeof(book));
											wprintw(vin, "Enter title\n");
											wscanw(vin, " %[^\n]s", p->title);
											wprintw(vin, "Enter author name\n");
											wscanw(vin, " %[^\n]s", p->author);
											wprintw(vin, "Enter subject category\n");
											wscanw(vin, " %[^\n]s", p->subject);
											wprintw(vin, "Enter book code\n");
											wscanw(vin, "%d", &(p->code));
											wprintw(vin, "Enter price\n");
											wscanw(vin, "%d", &(p->price));
											wprintw(vin, "Enter shelf number\n");
											wscanw(vin, "%d", &(p->shelf_num));
											wprintw(vin, "Enter available copies\n");
											wscanw(vin, "%d", &(p->avail_copies));	
											number = addbook(p);
											if(number == -1)
												wprintw(vin, "Book code already exists.\tPlease use unique code.\n");			
											free(p);
											break;
							
									case 'y' :	wprintw(vin, "Search according to:\n");
											wprintw(vin, "a. Title\tb. Author\tc. Subject Category\td. Code\t  e. Go to book record managing\t f. Go to library management\n");			
											wscanw(vin, " %c", &ch2);
											switch(ch2)
											{
												case 'a' :	wprintw(vin, "Enter title\n");
														wscanw(vin, " %[^\n]s", var.str);	
														p = searchbook(TITLE, var, &number);	
														if(!p)
														{	wprintw(vin, "No records found\n");	
															break;
														}
														wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\t");	
														wprintw(vin, "ShelfNo\tCopies\n");	
														for(i = 0; i < number; i++)
															display(&p[i], vin);
														free(p);
														break;
			
												case 'b' :	wprintw(vin, "Enter author\n");
														wscanw(vin, " %[^\n]s", var.str);	
														p = searchbook(AUTHOR, var, &number);	
														if(!p)
														{	wprintw(vin, "No records found\n");			
															break;
														}
														wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\t");			
														wprintw(vin, "ShelfNo\tCopies\n");	
														for(i = 0; i < number; i++)
															display(&p[i], vin);
														free(p);
			
														break;
			
												case 'c' :	wprintw(vin, "Enter Subject category\n");			
														wscanw(vin, " %[^\n]s", var.str);	
														p = searchbook(SUBJECT, var, &number);	
														if(!p)
														{	wprintw(vin, "No records found\n");			
															break;
														}											
														wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\t");			
														wprintw(vin, "ShelfNo\tCopies\n");	
														for(i = 0; i < number; i++)
															display(&p[i], vin);
														free(p);
														break;
			
												case 'd' :	wprintw(vin, "Enter book code\n");	
														wscanw(vin, "%d", &(var.integer));
														p = searchbook(CODE, var, &number);	
														if(!p)
														{	wprintw(vin, "No records found\n");			
															break;
														}
														wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\tPrice\t");	
														wprintw(vin, "ShelfNo\tCopies\n");	
														for(i = 0; i < number; i++)
															display(&p[i], vin);
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
							
									case 'z' :	wprintw(vin, "Enter book code\n");
											wscanw(vin, "%d", &code);
											wprintw(vin, "Enter number of new copies of this book purchased\n");	
											wscanw(vin, "%d", &number);
											i = editcopies(code, number);
											if(i == 0)
												wprintw(vin, "No book of matching code found\n");	
											break;
		
									case 'u' : 	wprintw(vin, "Sort according to:\n");
											wprintw(vin, "a. Book code\tb. Subject\tc. Author\td. Shelf number\n");	
											wscanw(vin, " %c", &ch2);	
											switch(ch2)
											{
												case 'a':	i = sortbook(CODE);
														if(i == 0)
															wprintw(vin, "No book records exist\n");	
														break;
												case 'b':	i = sortbook(SUBJECT);
														if(i == 0)
															wprintw(vin, "No book records exist\n");	
														break;
												case 'c':	i = sortbook(AUTHOR);
														if(i == 0)
															wprintw(vin, "No book records exist\n");	
														break;
												case 'd':	i = sortbook(SHELF_NO);
														if(i == 0)
															wprintw(vin, "No book records exist\n");	
														break;
												default :	break;
											}
											break;
	
									case 't' :	wprintw(vin, "Enter book code\n");
											wscanw(vin, "%d", &code);
											number = deletebook(code);
											if(number == 0)
												wprintw(vin, "Book code does not exist\n");
											break;
		
									case 'v' :	/* goto library managing */
											goto Label_1;
											break;
		
									case 'w':	wrefresh(vin);
											delwin(vin);
											goto Label_n;
											break;
	
									default :	break;
						
								}
							}
							break;
		
						case 2:	
						case 3:	if(choice == 2)
								wprintw(vin, "\n----------------------------------------------------------------------------------------------------------------------\nWelcome to student record managing...");					
							if(choice == 3)
								wprintw(vin, "\n----------------------------------------------------------------------------------------------------------------------\nWelcome to faculty record managing...");					
							while(1)
							{
								wprintw(vin, "\n----------------------------------------------------------------------------------------------------------------------\n");
								wprintw(vin, "x. Add new issue record\t  y. Search an issue record\t ");
								wprintw(vin, "z. Edit issued book record on returning\t u. Sort issue records\n\tt. Display long-time issue records\tv. Go to library managing\tw. Log out session\n");
								wscanw(vin, " %c", &ch);
								switch(ch)
								{
									case 'x':	s = (issuerecord *) malloc(sizeof(issuerecord));
											wprintw(vin, "Enter name of student/faculty\n");
											wscanw(vin, "%[^\n]s", s->name);
											wprintw(vin, "Enter department abbreviation of student/faculty\n");	
											wscanw(vin, "%s", s->department);
											wprintw(vin, "Enter student/faculty mis\n");
											wscanw(vin, "%d", &(s->mis));		
											wprintw(vin, "Enter book code\n");
											wscanw(vin, "%d", &(s->bookcode));
											if(choice == 2)
												number = addissue(s, STUDENT);
											else if(choice == 3)
												number = addissue(s, FACULTY);
											free(s);
											if(number == -2)
											{	wprintw(vin, "Cannot issue the book.\t");
												wprintw(vin, "Borrower already has maximum permissible no of books.\n");			
											}
											if(number == 0)
												wprintw(vin, "No book records exist");
											if(number == -1)
												wprintw(vin, "Book code does not exist\n");
											break;
			
									case 'y':	wprintw(vin, "Search according to:\na. Student  mis\t b. Book code\tc. Book code with status \"issued\"\td. Student/faculty name\t e. Student mis and status \"issued\"\n");
											wscanw(vin, " %c", &ch2);
											switch(ch2)
											{
												case 'a':	wprintw(vin, "Enter student/faculty mis\n");
														wscanw(vin, "%d", &(var.integer));
														s = search_record(var, MIS, STUDENT, &number);												
														if(!s)
														{
															wprintw(vin, "No matching issue record found\n");			
															break;
														}
														wprintw(vin, "MIS\t\tName\tDept\tBookcode\tBorrow Date\t");	
														wprintw(vin, "Time\tStatus\tDue/Return Date\tTime\n");		
														for(i = 0; i < number; i++)
															displayrec(&s[i], vin);
														free(s);
														break;

												case 'b':	wprintw(vin, "Enter book code\n");	
														wscanw(vin, "%d", &(var.integer));
														if(choice == 2)
														    s = search_record(var, BOOKCODE, STUDENT, &number);	
														else if(choice == 3)
														    s = search_record(var, BOOKCODE, FACULTY, &number);			
														if(!s)
														{
															wprintw(vin, "No matching issue record found\n");			
															break;
														}
														wprintw(vin, "MIS\t\tName\tDept\tBookcode\tBorrow Date\t");	
														wprintw(vin, "Time\tStatus\tDue/Return Date\tTime\n");			
														for(i = 0; i < number; i++)
															displayrec(&s[i], vin);
														free(s);
														break;

												case 'c':	wprintw(vin, "Enter book code\n");	
														wscanw(vin, "%d", &(var.integer));
														if(choice == 2)
														    s = search_record(var, BOOKCODE_ISSUED, STUDENT, &number);	
														else if(choice == 3)
														    s = search_record(var, BOOKCODE_ISSUED, FACULTY, &number);			
														if(!s)
														{
															wprintw(vin, "No matching issue record found\n");			
															break;
														}
														wprintw(vin, "\tMIS\t\ttName\tDept\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");			
														for(i = 0; i < number; i++)
															displayrec(&s[i], vin);
														free(s);
														break;

												case 'd':	if(choice == 2)
															wprintw(vin, "Enter student name\n");
														else
															wprintw(vin, "Enter faculty name\n");	
														wscanw(vin, "%s", var.str);
														if(choice == 2)
														    s = search_record(var, NAME, STUDENT, &number);	
														else if(choice == 3)
														    s = search_record(var, NAME, FACULTY, &number);			
														if(!s)
														{
															wprintw(vin, "No matching issue record found\n");			
															break;
														}
														wprintw(vin, "MIS\t\tName\tDept\tBookcode\tBorrow Date\t");	
														wprintw(vin, "Time\tStatus\tDue/Return Date\tTime\n");			
														for(i = 0; i < number; i++)
															displayrec(&s[i], vin);
														free(s);
														break;

												case 'e':	wprintw(vin, "Enter student/faculty mis\n");
														wscanw(vin, "%d", &(var.integer));
														s = search_record(var, MIS_ISSUED, STUDENT, &number);												
														if(!s)
														{
															wprintw(vin, "No matching issue record found\n");			
															break;
														}
														wprintw(vin, "MIS\t\tName\tDept\tBookcode\tBorrow Date\t");	
														wprintw(vin, "Time\tStatus\tDue/Return Date\tTime\n");		
														for(i = 0; i < number; i++)
															displayrec(&s[i], vin);
														free(s);
														break;

												default :	break;
											}
											break;
	
									case 'z':	if(choice == 2)
												wprintw(vin, "Enter student/faculty mis\n");
											wscanw(vin, "%d", &mis);
											wprintw(vin, "Enter book code\n"); 
											wscanw(vin, "%d", &code);
											wprintw(vin, "a. Returned in good condition\tb. Damaged/Lost\n");			
											wscanw(vin, " %c", &ch2);
											if(choice == 2)
												f = returned(mis, code, ch2, STUDENT);
											else if(choice == 3)
												f = returned(mis, code, ch2, FACULTY);
											if(!f)
												wprintw(vin, "No matching issue record found\n");	
											else
											{
												wprintw(vin, "Late by %d days\tLate fine = %d\n", f->late / 5, f->late);			
												wprintw(vin, "Damage/lost fine = %d\n", f->damage);	
												wprintw(vin, "Total fine = %d\n", f->late + f->damage);	
												free(f);
											}
											break;

									case 't' :	if(choice == 2)
												s = longtimeissue(&number, STUDENT);
											else if(choice == 3)
												s = longtimeissue(&number, FACULTY);
											if(number == 0)
												wprintw(vin, "No long time borrowers :)\n");
											else
												wprintw(vin, "Long time borrowers :\nMIS\t\tName\tDept\tBookcode\tBorrow Date\tTime\tStatus\tDue/Return Date\tTime\n");			
											for(i = 0; i < number; i++)
												displayrec(&s[i], vin);
											free(s);
											break;
	
									case 'u' :	wprintw(vin, "Sort according to:\n");
											wprintw(vin, "a. Student/faculty MIS\tb. Book code\tc. Borrow date-time\n");	
											wscanw(vin, " %c", &ch2);
											switch(ch2)
											{
												case 'a' :	if(choice == 2)
															number = sortrec(MIS, STUDENT);	
														else if(choice == 3)
															number = sortrec(MIS, FACULTY);	
														if(number == 0)
															wprintw(vin, "No issue records exist\n");	
														break;
	
												case 'b' :	if(choice == 2)
															number = sortrec(BOOKCODE, STUDENT);			
														else if(choice == 3)
															number = sortrec(BOOKCODE, FACULTY);			
														if(number == 0)
															wprintw(vin, "No issue records exist\n");			
														break;
	
												case 'c' :	if(choice == 2)
															number = sortrec(BORROW, STUDENT);	
														else if(choice == 3)
															number = sortrec(BORROW, FACULTY);		
														if(number == 0)
															wprintw(vin, "No issue records exist\n");	
														break;
	
												default :	break;
											}
											break;
				
									case 'v' :	goto Label_1;
											break;
			
									case 'w':	wrefresh(vin);
											delwin(vin);
											goto Label_n;
											break;
	
									default :	break;
								}
							}
							break;
	
						case 4:		wrefresh(vin);
								delwin(vin);
								goto Label_n;
								break;
	
						default: break;
					}
				}
			}
			else
			{
				printw("Wrong password\n");
				refresh();
				goto Label;
			}	
			break;	
	
		case 2:
		case 3:
			printw("Enter password\n");
			noecho();
			scanw("%s", pw);
			echo();
			if(choice2 == 2)
				strcpy(pword, spw);
			else if(choice2 == 3)
				strcpy(pword, fpw);
			if(strcmp(pw, pword) == 0)
			{
				vin = newwin(0, 0, 0, 0);
				scrollok(vin,TRUE);
				idlok(vin, TRUE);
				if(choice2 == 2)
					wprintw(vin, "Hello Dear Student !\n");
				else
					wprintw(vin, "Hello Sir/Madam !\n");
				while(1)
				{
					Label_3:
					wprintw(vin, "\n----------------------------------------------------------------------------------------------------------------------------\n");
					wprintw(vin, "x. Search book\ty. Sort book records\tz. Search issue records\n\tu. Sort issue records\t v.Log out session\n");			
					wscanw(vin, " %c", &ch);
					switch(ch)
					{
						case 'x':	wprintw(vin, "Search book according to:\n");
								wprintw(vin, "a. Title\tb. Author\tc. Subject Category\td. Code\t e. Go to previous stage\n");			
								wscanw(vin, " %c", &ch2);
								switch(ch2)
								{
									case 'a' :	wprintw(vin, "Enter title\n");
											wscanw(vin, " %[^\n]s", var.str);	
											p = searchbook(TITLE, var, &number);	
											if(!p)
											{	wprintw(vin, "No records found\n");
												break;
											}
											wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\t");
											wprintw(vin, "Price\tShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i], vin);
											free(p);
											break;
				
									case 'b' :	wprintw(vin, "Enter author\n");
											wscanw(vin, " %[^\n]s", var.str);	
											p = searchbook(AUTHOR, var, &number);	
											if(!p)
											{	wprintw(vin, "No records found\n");
												break;
											}
											wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\t");
											wprintw(vin, "Price\tShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i], vin);
											free(p);
											break;
				
									case 'c' :	wprintw(vin, "Enter Subject category\n");
											wscanw(vin, " %[^\n]s", var.str);	
											p = searchbook(SUBJECT, var, &number);	
											if(!p)
											{	wprintw(vin, "No records found\n");
												break;
											}											
											wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\t");
											wprintw(vin, "Price\tShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i], vin);
											free(p);
											break;
				
									case 'd' :	wprintw(vin, "Enter book code\n");	
											wscanw(vin, "%d", &(var.integer));
											p = searchbook(CODE, var, &number);	
											if(!p)
											{	wprintw(vin, "No records found\n");
													break;
											}

											wprintw(vin, "Code\t\t\t\tTitle\t\t\t\tAuthor\tSubject\t");
											wprintw(vin, "Price\tShelfNo\tCopies\n");
											for(i = 0; i < number; i++)
												display(&p[i], vin);
											free(p);
											break;
		
									case 'e' :	goto Label_3;
											break;
		
									default :	break;
								}
								break;

						case 'y':	wprintw(vin, "Sort books according to:\n");
								wprintw(vin, "a. Book code\tb. Subject\tc. Author\td. Shelf number\n");	
								wscanw(vin, " %c", &ch2);	
								switch(ch2)
								{
									case 'a':	i = sortbook(CODE);
											if(i == 0)
												wprintw(vin, "No book records exist\n");
											break;
									case 'b':	i = sortbook(SUBJECT);
											if(i == 0)
												wprintw(vin, "No book records exist\n");
											break;
									case 'c':	i = sortbook(AUTHOR);
											if(i == 0)
												wprintw(vin, "No book records exist\n");
												break;
									case 'd':	i = sortbook(SHELF_NO);
											if(i == 0)
												wprintw(vin, "No book records exist\n");
												break;
									default :	break;
								}
								break;

						case 'z':	wprintw(vin, "Search issue record according to Book code with status \"issued\"\n\t");
								wprintw(vin, "Enter book code\n");	
								wscanw(vin, "%d", &(var.integer));
								if(choice2 == 2)
									s = search_record(var, BOOKCODE_ISSUED, STUDENT, &number);	
								else if(choice2 == 3)
									s = search_record(var, BOOKCODE_ISSUED, FACULTY, &number);
								if(!s)
								{
									wprintw(vin, "No issue record. \n");
									break;
								}
								wprintw(vin, "\tMIS\tName\tDept\tBookcode\tBorrow Date\t");	
								wprintw(vin, "Time\tStatus\tDue/Return Date\tTime\n");			
								for(i = 0; i < number; i++)
									displayrec(&s[i], vin);
								free(s);
								break;

						case 'u':	wprintw(vin, "Sort issue records according to:\n");
								wprintw(vin, "a. Student/faculty MIS\tb. Book code\tc. Borrow date-time\n");
								wscanw(vin, " %c", &ch2);
								switch(ch2)
								{
									case 'a' :	if(choice2 == 2)
												number = sortrec(MIS, STUDENT);	
											else if(choice2 == 3)
												number = sortrec(MIS, FACULTY);	
											if(number == 0)
												wprintw(vin, "No issue records exist\n");
											break;

									case 'b' :	if(choice2 == 2)
												number = sortrec(BOOKCODE, STUDENT);
											else if(choice2 == 3)
												number = sortrec(BOOKCODE, FACULTY);
											if(number == 0)
												wprintw(vin, "No issue records exist\n");
											break;
	
									case 'c' :	if(choice2 == 2)
											number = sortrec(BORROW, STUDENT);	
											else if(choice2 == 3)
												number = sortrec(BORROW, FACULTY);	
											if(number == 0)
												wprintw(vin, "No issue records exist\n");
											break;

									default :	break;
								}
								break;

						case 'v':	wrefresh(vin);
								delwin(vin);
								goto Label_n;
								break;
					}			
				}
			}
			else
			{
				printw("Wrong password\n");
				refresh();
				goto Label;
			}		
			break;
	
		case 4:
			refresh();
			endwin();
			return 0;
			break;
		
		default:
			goto Label;
	}
	return 0;
}

void display(book *p, WINDOW *vin)					/* To display a book record on screen */
{
	wprintw(vin, "%d\t%s\t%s\t%s\t%d\t%d\t%d\n", p->code, p->title, p->author, p->subject, p->price, p->shelf_num, p->avail_copies);	
}

void displayrec(issuerecord *s, WINDOW *vin)				/* To display a student record on screen */
{
	wprintw(vin, "%d\t%s\t%s\t%d\t%d %d %d\t%d:%d\t%s\t%d %d %d\t%d:%d\n", s->mis, s->name, s->department, s->bookcode, s->record.bor_date.date, s->record.bor_date.month, s->record.bor_date.year, s->record.bor_timing.hours, s->record.bor_timing.mins, s->record.status, s->record.ret_date.date, s->record.ret_date.month, s->record.ret_date.year, s->record.ret_timing.hours, s->record.ret_timing.mins);
	return;
}
