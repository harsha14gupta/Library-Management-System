#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
///////////////FUNCTIONS///////////////

/**********MAIN LIBRARY FUNCTIONS**********/
void main_library();
void issue_book();
void return_book();
void book_menu();
void student_menu();

/**********BOOK FUNCTIONS**********/
void create_book();
void display_book();
void modify_book();
void delete_book();
void append_book();
void count_book();
void search_book();
void searchbno_book();
void searchbname_book();
int searchbno_book(int);
/**********STUDENT FUNCTIONS**********/
void create_student();
void display_student();
void modify_student();
void delete_student();
void append_student();
void count_student();
void search_student();
void searchadminno_student();
void searchstudname_student();
int searchadminno_student(int);
///////////////CLASSES///////////////

/*********STUDENT CLASS**********/
class student
{
     int rollno;
     int admin_no;
     char studname[30];
     int issued_bno;
     char issued_bname[30];
     char issue_date[20];
     char return_date[20];
     public:
	student()
	{
		issued_bno=-1;
		strcpy(issued_bname,"");
		strcpy(issue_date,"");
		strcpy(return_date,"");
		rollno = -1;
	}
	void insert();
	void display();
	void modify();
	int getadminno();
	int getrollno();
	char* getstudentname();
	int getbookno();
	void setbno(int);
	void setbname(char*);
	void setissue_date(char*);
	void setreturn_date(char*);
};
/***********BOOK CLASS**********/
class book
{
    int bno;
    char bname[30];
    char bauthor[30];
    char btype[30];
    public:
	book()
	{
		strcpy(bname, "");
	}
	void insert();
	void display();
	void modify();
	int getbno();
	char* getbname();
};
void book::insert()
{
	cout<<endl<<"ENTER BOOK NUMBER: ";
	cin>>bno;
	int x =searchbno_book(bno);
	if(x == -1)
	{
	cout<<endl<<"ENTER BOOK NAME: ";
	gets(bname);
	cout<<endl<<"ENTER BOOK AUTHOR: ";
	gets(bauthor);
	cout<<endl<<"ENTER BOOK TYPE: ";
	gets(btype);

	}
	else
	{
		cout<<"\n\t** BOOK ALREADY EXIST **";
	}
}
void book::display()
{
	cout<<endl<<"BOOK NUMBER: "<<bno;
	cout<<endl<<"BOOK NAME: "<<bname;
	cout<<endl<<"BOOK AUTHOR: "<<bauthor;
	cout<<endl<<"BOOK TYPE: "<<btype;
}
void book::modify()
{       cout<<"\n\t** ENTER MODIFIED DETAILS **";
	cout<<endl<<"ENTER BOOK NAME: ";
	gets(bname);
	cout<<endl<<"ENTER BOOK AUTHOR: ";
	gets(bauthor);
	cout<<endl<<"ENTER BOOK TYPE: ";
	gets(btype);
}
int book::getbno()
{
	return bno;
}
char* book::getbname()
{
	return bname;
}
void create_book()
{
	clrscr();
	book b;
	ofstream fout;
	fout.open("book.dat",ios::app|ios::binary);
	if(!fout)
	{}
	else
	{
			b.insert();
			if(strcmp(b.getbname(),"")!=0)
			{
			fout.write((char*)&b,sizeof(b));
			cout<<"\n\n\t\t** BOOK INSERTED SUCCESSFULLY **";
			}
	}
	fout.close();
	getch();
}
void display_book()
{
	clrscr();
	book b1;
	int flag = 0;
	ifstream fin;
	fin.open("book.dat",ios::in|ios::binary);
	if(!fin)
	{}
	else
	{       cout<<endl<<"\n\n\t\t----------- BOOK DETAILS ---------- ";
		while(fin.read((char*)&b1,sizeof(b1)))
		{       flag = 1;
			b1.display();
			cout<<endl;
		}
	}

		if(flag == 0)
		{
			cout<<"\n\n*NO BOOK EXIST*";
		}

	fin.close();
	getch();
}
void modify_book()
{
	clrscr();
	int flag = 0;
	int bookno;
	fstream fs;
	book b;
	fs.open("book.dat",ios::in|ios::out|ios::binary);
	cout<<"\n\n\t\t---------- MODIFY BOOK ----------";
	cout<<endl<<endl<<"ENETR BOOK NUMBER TO BE MODIFIED: " ;
	cin>>bookno;
	if(!fs)
	{}
	else
	{
		while(fs.read((char*)&b,sizeof(b)))
		{
			if(b.getbno()==bookno)
			{       flag = 1;
				b.modify();
				int pos= -1 * sizeof(b);
				fs.seekg(pos,ios::cur);
				fs.write((char*)&b,sizeof(b));
			}
		}
	}
	fs.close();
	if(flag == 1)
	{
	   cout<<"\n\n\t*****BOOK DETAILS MODIFIED SUCCESSFULLY*****";
	}
	else
	{
	  cout<<"\n\n\t*** BOOK DOESN'T EXIST ***";
	}
	getch();
}
void delete_book()
{
    clrscr();
    book b2;
    int bookno;
    int flag = 0;
    ifstream fi;
    fi.open("book.dat",ios::in|ios::binary);
    if(!fi)
    {}
    else
    {
	  ofstream fo;
    fo.open("temp_del1.dat",ios::out|ios::binary);
    cout<<"\t\t\n\n---------- DELETE BOOK ----------";
    cout<<endl<<"ENTER BOOK NUMBER TO BE DELETED: " ;
    cin>>bookno;

	while(fi.read((char*)&b2,sizeof(b2)))
	{
		if(b2.getbno()!=bookno)
		{
			fo.write((char*)&b2,sizeof(b2));
		}
		else
		{
			flag = 1;
			      cout<<"\n\n\t\t***BOOK DELETED IS ***";
			      b2.display  ();

		}
	}
	 remove("book.dat");
	 rename("temp_del1.dat","book.dat");
	 fo.close();
    }
    if(flag== 0)
    {
	cout<<"\n\n\t\t** BOOK DOESN't EXIST **";
    }
    else
    {
	cout<<"\n\n\t** BOOK DELETED SUCCESSFULLY **";
    }
    fi.close();
    getch();
}
void search_book()
{
	clrscr();
	int choice;
		cout<<endl<<"\t\t**********SEARCH BOOK MENU**********" ;
		cout<<endl<<"\t\t1* SEARCH BOOK NUMBER" ;
		cout<<endl<<"\t\t2* SEARCH BOOK NAME" ;
		cout<<endl<<"\t\t3* BACK TO BOOK MENU" ;
		cout<<endl<<endl<<"\t\tENTER YOUR CHOICE: " ;
		cin>>choice;
		switch(choice)
		{
			case 1: searchbno_book();
				search_book();
				break;

			case 2: searchbname_book();
				search_book();
				break;

			case 3: book_menu();
				break;

			default: cout<<endl<<"INVALID CHOICE! ";
		}
}
int searchbno_book(int bookno)
{
     book b;
     ifstream fin;
     fin.open("book.dat",ios::in|ios::binary);
     if(!fin)
     {}
     else
     {
	while(fin.read((char*)&b,sizeof(b)))
	{
	  if(b.getbno()==bookno)
	  {
		return -2;
	  }
	}
     }
     fin.close();
     return -1;
}
void searchbno_book()
{    clrscr();
     book b;
     int bookno;
     int flag = 0;
     ifstream fin;
     fin.open("book.dat",ios::in|ios::binary);
      cout<<"\n\n\t\t---------- SEARCH BOOK NUMBER ----------";
	cout<<endl<<"ENTER BOOK NUMBER TO BE SEARCHED:" ;
	cin>>bookno;
     if(!fin)
     {}
     else
     {
	while(fin.read((char*)&b,sizeof(b)))
	{
	  if(b.getbno()==bookno)
	  {     flag = 1;
		b.display();
		break;
	  }
	}
     }
     fin.close();
     if(flag == 0)
     {
	cout<<"\n\t***BOOK DOESN'T EXIST***";
     }
     else
     {
	cout<<"\n\t**BOOK SEARCHED SUCCESSFULLY**";
     }
     getch();
}
void searchbname_book()
{  clrscr();
   book b;
   int flag = 0;
   char bookname[30];
   ifstream fin;
   fin.open("book.dat",ios::in|ios::binary);
	cout<<"\n\n\t\t---------- SEARCH BOOK NAME----------";
	cout<<endl<<"ENTER BOOK NAME TO BE SEARCHED:" ;
	gets(bookname);
   if(!fin)
   {}
   else
   {
	  while(fin.read((char*)&b,sizeof(b)))
	  {
		if(strcmp(b.getbname(),bookname)==0)
		{      flag = 1;
			b.display();
			break;
		}
	  }
   }
    if(flag == 0)
     {
	cout<<"\n\t***BOOK DOESN'T EXIST***";
     }
     else
     {
	cout<<"\n\t**BOOK SEARCHED SUCCESSFULLY**";
     }
     getch();
}
void count_book()
{       clrscr();
	book b;
	int count=0;
	ifstream fin;
	fin.open("book.dat",ios::in|ios::binary);
	if(!fin)
	{}
	else
	{       cout<<"\n\n\t\t---------- COUNT BOOKS ----------";
		while(fin.read((char*)&b,sizeof(b)))
		{
			count++;
		}

	}
	cout<<endl<<"\t\nTOTAL NUMBER OF BOOKS ARE:"<<count;
	fin.close();
	getch();
}
void student::insert()
{
	cout<<"\n\n\t\t----------ENTER STUDENT DETAILS----------";
	cout<<endl<<"ENTER ADMISSION NUMBER: " ;
	cin>>admin_no;
	int x = searchadminno_student(admin_no);
	if(x == -1 || x >0)
	{
		cout<<"\n\t***STUDENT ALREADY EXIST ***";
	}
	else
	{
	cout<<endl<<"ENTER ROLL NUMBER: " ;
	cin>>rollno;
	cout<<endl<<"ENTER FULL NAME: ";
	gets(studname);
	}
}
void student::display()
{
	cout<<endl<<"ROLL NUMBER: "<<rollno;
	cout<<endl<<"ADMISSION NUMBER: "<<admin_no;
	cout<<endl<<"FULL NAME: "<<studname;
	if(issued_bno==-1)
	{
		cout<<endl<<"*NO BOOK IS ISSUED TO STUDENT*" ;
	}
	else
	{
		cout<<endl<<"BOOK NUMBER: "<<issued_bno;
		cout<<endl<<"BOOK NAME: " <<issued_bname;
		cout<<endl<<"ISSUE DATE: " <<issue_date;
		cout<<endl<<"RETURN DATE: " <<return_date;
	}
}
void student::modify()
{
	cout<<endl<<"\t\t*ENTER MODIFIED DETAILS*";
	cout<<endl<<"ENTER ROLL NUMBER: ";
	cin>>rollno;
	cout<<endl<<"ENTER FULL NAME: ";
	gets(studname);
}
int student::getadminno()
{
	return admin_no;
}
int student::getrollno()
{
	return rollno;
}
char*student::getstudentname()
{
	return studname;
}
int student::getbookno()
{
	return issued_bno;
}
void student::setbno(int bookno)
{
	issued_bno=bookno;
}
void student::setbname(char* bookname)
{
	strcpy(issued_bname,bookname);
}
void student::setissue_date(char* is_date)
{
	strcpy(issue_date,is_date);
}
void student::setreturn_date(char* ret_date)
{
	strcpy(return_date,ret_date);
}
void create_student()
{
	clrscr();
	student s;
	ofstream fout;
	char ch1;
	fout.open("student.dat",ios::app|ios::binary);
	if(!fout)
		cout<<endl<<"*FILE DOESN'T EXIST*" ;
	else
	{
			s.insert();
			if(s.getrollno() != -1)
			{ fout.write((char*)&s,sizeof(s));
			  cout<<"\n\n\t\t*DETAILS INSERTED SUCCESSFULLY*";
			}
	}
	fout.close();
	getch();
}
void display_student()
{
	clrscr();
	student s1;
	int flag = 0;
	ifstream fin;
	fin.open("student.dat",ios::in|ios::binary);
	if(!fin)
		cout<<endl<<"*FILE DOESN'T EXIST*" ;
	else
	{       cout<<endl<<"\t\t---------- STUDENT DETAILS ----------";
		while(fin.read((char*)&s1,sizeof(s1)))
		{
			flag = 1;
			s1.display();
			cout<<endl;
		}
		if(flag == 0)
		{
			cout<<"\n\n*NO STUDENT EXIST*";
		}

	}
	getch();
	fin.close();
}
void modify_student()
{
	clrscr();
	int adminno;
	fstream fs;
	student s;
	int flag = 0;
	fs.open("student.dat",ios::in|ios::out|ios::binary);
	cout<<endl<<endl<<"\t\t---------- MODIFY STUDENT ----------";
	cout<<endl<<endl<<"ENTER STUDENT ADMISION NUMBER TO BE MODIFIED: " ;
	cin>>adminno;
	if(!fs)
	{}
	else
	{
		while(fs.read((char*)&s,sizeof(s)))
		{
			if(s.getadminno()==adminno)
			{       flag = 1;
				s.modify();
				int pos= -1 * sizeof(s);
				fs.seekg(pos,ios::cur);
				fs.write((char*)&s,sizeof(s));
			}
		}

	}
	fs.close();
		if(flag == 1)
		{
			cout<<endl<<"\t\t**STUDENT MODIFIED SUCCESSFULLY**";
		}
		else
		{
			cout<<endl<<"\t\t*STUDENT DOESN'T EXIST*";
		}
	getch();
}
void delete_student()
{   clrscr();
    student s2;
    int adminno;
    int flag = 0;
    ifstream fi;
    fi.open("student.dat",ios::in|ios::binary);
    if(!fi)
	cout<<endl<<"*FILE DOESN'T EXIST*" ;
    else
    {
	ofstream fo;
	fo.open("temp_del2.dat",ios::out|ios::binary);
	cout<<endl<<endl<<"\t\t\t----------DELETE STUDENT ----------" ;
	cout<<endl<<endl<<"\t\tENTER STUDENT ADMISSION NUMBER TO BE DELETED: ";
	cin>>adminno;
	while(fi.read((char*)&s2,sizeof(s2)))
	{
		if(s2.getadminno()!=adminno)
		{
			fo.write((char*)&s2,sizeof(s2));
		}
		else
		{
			flag = 1;
			cout<<"\n\n\t\t***STUDENT DELETED IS ***";
			s2.display();
		}
	}
	if(flag == 0)
	{
		cout<<"\n\n\t\t*STUDENT DOESN'T EXIST*";
	}
	fo.close();
	 remove("student.dat");
	 rename("temp_del2.dat","student.dat");
	 getch();
    }
    fi.close();
}
void search_student()
{       clrscr();
	int choice;
		cout<<endl<<"\t\t\n---------- SEARCH STUDENT MENU -----------" ;
		cout<<endl<<"\t1* SEARCH ADMISSION NUMBER" ;
		cout<<endl<<"\t2* SEARCH STUDENT NAME" ;
		cout<<endl<<"\t3* BACK TO STUDENT MENU" ;
		cout<<endl<<endl<<"\tENTER YOUR CHOICE: " ;
		cin>>choice;
		switch(choice)
		{
			case 1: searchadminno_student();
				search_student();
				break;

			case 2: searchstudname_student();
				search_student();
				break;

			case 3: student_menu();
				break;

			default: cout<<endl<<"invalid choice";
		}
}
int searchadminno_student(int adminno)
{
     student s;
     ifstream fin;
     int flag = 0;
     fin.open("student.dat",ios::in|ios::binary);
     if(!fin)
     {}
     else
     {
	while(fin.read((char*)&s,sizeof(s)))
	{
	  if(s.getadminno()==adminno)
	  {
		flag = 1;
		break;
	  }
	}
     }
     fin.close();
     if(flag == 1 && s.getbookno() == -1)
     {
	return -1;
     }
     else if(flag == 1)
     {
       return s.getbookno();
     }
     flag = 0;
     return -99;

}
void searchadminno_student()
{
     clrscr();
     student s;
     int adminno;
     int flag = 0;
     ifstream fin;
     fin.open("student.dat",ios::in|ios::binary);
     if(!fin)
	cout<<endl<<"*FILE DOESN'T EXIST*" ;
     else
     {  cout<<endl<<endl<<"\t\t\n\n----------SEARCH STUDENT ADMISSION NUMBER----------";
	cout<<endl<<"\n\t\tENTER ADMISSION NUMBER: " ;
	cin>>adminno;
	while(fin.read((char*)&s,sizeof(s)))
	{
	  if(s.getadminno()==adminno)
	  {
		cout<<endl<<"\t\t**STUDENT DETAILS ARE**";
		flag = 1;
		s.display();
		break;
	  }
	}
	if(flag == 0)
	{
		cout<<"\n\t\t**STUDENT DOESN'T EXIST**";
	}
     }
     getch();
     fin.close();
}
void searchstudname_student()
{
   clrscr();
   student s;
   int flag =0;
   char studname[30];
   ifstream fin;
   fin.open("student.dat",ios::in|ios::binary);
   if(!fin)
		cout<<endl<<"*FILE DOESN'T EXIST*" ;
   else
   {      cout<<"\n\n\t\t----------- SEARCH STUDENT NAME ----------";
	  cout<<endl<<"ENTER STUDENT NAME: " ;
	  gets(studname);
	  while(fin.read((char*)&s,sizeof(s)))
	  {
		if(strcmp(s.getstudentname(),studname)==0)
		{       flag = 1;
			cout<<endl<<"\t**STUDENT DETAILS ARE**";
			s.display();
			break;
		}
	  }
	  if(flag == 0)
	  {
		cout<<"\n\n\t**STUDENT DOESN'T EXIST**";
	  }
   }
   getch();
   fin.close();
}
void count_student()
{
	clrscr();
	student s;
	int count1=0;
	ifstream fin;
	fin.open("student.dat",ios::in|ios::binary);
	if(!fin)
		cout<<endl<<"*FILE DOESN'T EXIST*" ;
	else
	{       cout<<"\n\n\t\t---------- COUNT STUDENTS ---------- ";
		while(fin.read((char*)&s,sizeof(s)))
		{
			count1++;
		}

	}
	cout<<endl<<"\n\n\t\t***TOTAL STUDENTS ARE ****:\t"<<count1;
	fin.close();
	getch();
}
void main_library()
{
	clrscr();
	int choice;
		cout<<endl<<"\t\t********** MAIN MENU **********" ;
		cout<<endl<<"\t\t1* ISSUE BOOK(ONLY 1 BOOK CAN BE ISSUED)" ;
		cout<<endl<<"\t\t2* RETURN BOOK" ;
		cout<<endl<<"\t\t3* BOOK MENU" ;
		cout<<endl<<"\t\t4* STUDENT MENU" ;
		cout<<endl<<"\t\t5* EXIT" ;
		cout<<endl<<endl<<"\t\tENTER YOUR CHOICE=  " ;
		cin>>choice;
		switch(choice)
		{
			case 1: issue_book();
				main_library();
				break;

			case 2: return_book();
				main_library();
				break;

			case 3: book_menu();
				break;

			case 4: student_menu();
				break;

			case 5: exit(1);
				break;

			default: cout<<endl<<"WRONG CHOICE ENTERED! " ;
		}
}
void issue_book()
{
	clrscr();
	int admin_no;
	char issue_date[20];
	char return_date[20];
	int bno;
	char bname[30];
	student s;
	fstream fin;
	cout<<"\n\n\t\t------------ ISSUE BOOK ----------";
	cout<<endl<<"\nENTER ADMISSION NUMBER: " ;
	cin>>admin_no;
	int x = searchadminno_student(admin_no);
	if(x == -99)
	{
		cout<<endl<<endl<<"\t\t*** STUDENT DOESN'T EXIST ***";
		getch();

	}
	else if(x > 0)
	{
		cout<<"\n\n*** BOOK IS ALREADY ISSUED TO A STUDENT ***";
		getch();
	}
	else
	{

		cout<<endl<<"ENTER BOOK NUMBER: " ;
		cin>>bno;
		int y = searchbno_book(bno);
		if(y == -1)
		{
		 cout<<"\n\n\tTHE BOOK DOESN'T EXIST";
		 getch();
		}
		else
		{
		cout<<endl<<"ENTER BOOK NAME: " ;
		gets(bname);
		cout<<endl<<"ENTER ISSUE DATE: " ;
		gets(issue_date);
		cout<<endl<<"ENTER RETURN DATE: " ;
		gets(return_date);
		fin.open("student.dat",ios::in|ios::out|ios::binary);
		if(!fin)
		{}
		else
		{
			while(fin.read((char*)&s,sizeof(s)))
			{
			  if(s.getadminno()==admin_no)
			  {
				s.setbno(bno);
				s.setbname(bname);
				s.setissue_date(issue_date);
				s.setreturn_date(return_date);
				int pos=-1*sizeof(s);
				fin.seekg(pos,ios::cur);
				fin.write((char*)&s,sizeof(s));
				break;
			  }
			}
		}
		fin.close();
		}
	}
	getch();
}
void return_book()
{
	int flag =0;
	clrscr();
	student s;
	fstream fin;
	int admin_no;
	fin.open("student.dat",ios::in|ios::out|ios::binary);
	cout<<"\n\n\t-------------- RETURN BOOK -------------";
	cout<<endl<<"\n\tENTER THE ADMISSION NUMBER: " ;
	cin>>admin_no;
     if(!fin)
     {}
     else
     {
	while(fin.read((char*)&s,sizeof(s)))
	{
	  if(s.getadminno()==admin_no)
	  {     flag = 1;
		if(s.getbookno() == -1)
		{
		 cout<<"\n\n\t*** BOOK IS NOT ISSUED TO A STUDENT ***";
		}
		else
		{
		cout<<"\n**THE DETAILS ARE**";
		s.display();
		s.setbno(-1);
		s.setbname("");
		s.setissue_date("");
		s.setreturn_date("");
		int pos=-1*sizeof(s);
		fin.seekg(pos,ios::cur);
		fin.write((char*)&s,sizeof(s));
		cout<<"\n\n\t\t****** BOKK RETURNED SUCCESSFULLY ******";
		break;
		}
	  }
	}
     }
     if(flag == 0)
     {
	cout<<endl<<endl<<"\t\t**STUDENT DOESN'T EXIST**";
     }
     fin.close();
     getch();
}
 void book_menu()
{
	clrscr();
	int choice;
		cout<<endl<<"\t\t********** BOOK MENU **********";
		cout<<endl<<"\t\t1* ADD BOOK";
		cout<<endl<<"\t\t2* DISPLAY BOOK";
		cout<<endl<<"\t\t3* MODIFY BOOK";
		cout<<endl<<"\t\t4* DELETE BOOK";
		cout<<endl<<"\t\t5* SEARCH BOOK";
		cout<<endl<<"\t\t6* COUNT BOOKS";
		cout<<endl<<"\t\t7* BACK TO MAIN LIBRARY";
		cout<<endl<<endl<<"\t\tENTER YOUR CHOICE: ";
		cin>>choice;
		switch(choice)
		{
			case 1: create_book();
				book_menu();
				break;

			case 2: display_book();
				book_menu();
				break;

			case 3: modify_book();
				book_menu();
				break;

			case 4: delete_book();
				book_menu();
				break;

			case 5: search_book();
				book_menu();
				break;

			case 6: count_book();
				book_menu();
				break;

			case 7: main_library();
				break;

			default: cout<<endl<<"INVALID CHOICE! ";
		}
}
void student_menu()
{
	clrscr();
	int choice;
		cout<<endl<<"\t\t********** STUDENT MENU **********";
		cout<<endl<<"\t\t1* ADD STUDENT";
		cout<<endl<<"\t\t2* DISPLAY STUDENT";
		cout<<endl<<"\t\t3* MODIFY STUDENT";
		cout<<endl<<"\t\t4* DELETE STUDENT";
		cout<<endl<<"\t\t5* SEARCH STUDENT";
		cout<<endl<<"\t\t6* COUNT STUDENTS";
		cout<<endl<<"\t\t7* BACK TO MAIN LIBRARY";
		cout<<endl<<endl<<"\t\tENTER YOUR CHOICE=  " ;
		cin>>choice;
		switch(choice)
		{
			case 1: create_student();
				student_menu();
				break;

			case 2: display_student();
				student_menu();
				break;

			case 3: modify_student();
				student_menu();
				break;

			case 4: delete_student();
				student_menu();
				break;

			case 5: search_student();
				student_menu();
				break;

			case 6: count_student();
				student_menu();
				break;

			case 7: main_library();
				break;

			default: cout<<endl<<"INVALID CHOICE! ";
		}
}
void main()
{
   clrscr();
   main_library();
   getch();
}

