/* ----HEADER FILES---- */
#include<fstream>
#include<ctype.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include<iostream>
using namespace std;
using std::endl;

/* ----CLASSES---- */
class account
{
 int acno;
 char name[50];
 int dep;
 char type;
public:
 void create_acc();        //To create an account
 void show_acc();          //To show account info
 void modify_acc();        //To perform modifications in account
 void deposit(int);        //To add balance amount
 void withdraw(int);       //To subract from balance amount
 void report();            //To show data in form of a table
 int retacno();            //To return account number
 int retdeposit();         //To return balance amount
 char type_acc();          //To return type of account
};

void account::create_acc()
{ system("cls");
  cout<<"\n\t CREATING A NEW ACCOUNT";
  cout<<"\n\t~~~~~~~~~~~~~~~~~~~~~~~~"<<"\n";
  cout<<"\n\tEnter the Account Number : ";
  cin>>acno;
  cout<<"\n\tEnter the Name of Account Holder : ";
  gets(name);
  cout<<"\n\tEnter the type of Account (C:for current; S:for savings) : ";
  cin>>type;
  cout<<"\n\tEnter Initial Amount (>=1000 for savings; >=1500 for current : ";
  cin>>dep;
}

void account::show_acc()
{ system("cls");
  cout<<"\n\n\t ACCOUNT DETAILS ";
  cout<<"\n\t~~~~~~~~~~~~~~~~~~~~~";
  cout<<"\n\t Account Number      : "<<acno;
  cout<<"\n\t Account Holder Name : ";
  puts(name);
  cout<<"\n\t Account Type        : "<<type;
  cout<<"\n\t Balance Amount      : "<<dep;
}

void account::modify_acc()
{system("cls");
 cout<<"\n Account Number : "<<acno;
 cout<<"\n\t Enter the Name of the Account Holder : ";
 gets(name);
 cout<<"\n\t Enter the Account Type (C:for current ;S:for savings) : ";
 cin>>type;
 cout<<"\n\t Enter the Amount : ";
 cin>>dep;
}

void account::deposit(int x)
{ system("cls");
  dep=dep+x; }

void account::withdraw(int x)
{ system("cls");
  dep=dep-x; }

void account::report()
{system("cls");
 cout<<"\t   "<<acno<<"\t   "<<name<<"\t    "<<type<<"\t  "<<dep<<"\n";
}

int account::retacno()
{ system("cls");
  return acno;  }

int account::retdeposit()
{ system("cls");
  return dep;   }

char account::type_acc()
{ system("cls");
  return type;  }

/* ----DECLARING FUNCTIONS----*/
 void write_acc();           //To write records in binary file
 void display_ac(int);       //To display account details
 void modify_acc(int);       //To modify record
 void delete_acc(int);       //To delete record
 void display_all();         //To display all account details
 void dep_withdraw(int,int); //To deposit or withdraw
 void intro();               //Introduction screen
/* ----MAIN FUNCTION---- */
int main()
{ char a;
  int num,ch;
  system("cls");
  intro();
do
{ system("cls");
 cout<<"\n\n\t MENU ";
 cout<<"\n\t~~~~~~~~~~\n";
 cout<<"\n\n\t1) CREATE NEW ACCOUNT";
 cout<<"\n\t2) DEPOSIT AMOUNT";
 cout<<"\n\t3) WITHDRAW AMOUNT";
 cout<<"\n\t4) BALANCE ENQUIRY";
 cout<<"\n\t5) ACCOUNT HOLDER'S LIST";
 cout<<"\n\t6) MODIFY AN ACCOUNT";
 cout<<"\n\t7) CLOSE AN ACCOUNT";
 cout<<"\n\t8) EXIT";

 cout<<"\n\n\n\t Select Your Option- ";
 cin>>ch;
 cout<<"\n\n(Note:The field mentioned below is for users with existing account,those who want to create a new account should enter 0)";
 cout<<"\n\n\tEnter the Account Number  : ";
 cin>>num;
 switch(ch)
{
 case 1:
    write_acc();
    break;
 case 2:
    dep_withdraw(num,1);
    break;
 case 3:
    dep_withdraw(num,2);
    break;
 case 4:
    display_ac(num);
    break;
 case 5:
    display_all();
    break;
 case 6:
    modify_acc(num);
    break;
 case 7:
    delete_acc(num);
 case 8:
    break;
 default:
    cout<<"\n\t\t INPUT INVALID ";
}
system("cls");
  cout<<"\n\n\t\t################################################## ";
    cout<<"\n\n\t\t## THANKS FOR USING MY BANK MANAGMENT SOFTWARE ## ";
    cout<<"\n\n\t\t################################################## ";

cout<<"\n\n\n\n\n\t     TO CONTINUE  ==> PRESS'Y'";
cout<<"\n\n\t     TO EXIT      ==> PRESS ANY KEY"<<endl;
 cin>>a;
}while(a=='Y'||a=='y');

return 0;
}

/* ----FUNCTIONS---- */
void write_acc()      //Function to write in file
{
 account ac;
 ofstream filout;
 filout.open("account.dat",ios::binary|ios::app);
 ac.create_acc();
 cout<<"\n\n\t ACCOUNT CREATED SUCCESSFULLY";

 cout<<"\n\t Press Any Key ";
 getch();
 filout.write((char*)&ac,sizeof(ac));
 filout.close();
}

void display_ac(int n)
{
 account ac;
 int flag=0;
 ifstream filin;
 filin.open("account.dat",ios::binary);
 if(!filin)
  {
   cout<<"\n\n\t FILE COULD NOT BE OPENED";
   getch();
   return;
  }
 while(filin.read((char*)&ac,sizeof(account)))
  { if(ac.retacno()==n)
    ac.show_acc();
    cout<<"\n\n\t Press Any Key";
    getch();
    flag=1;
  }

filin.close();
if(flag==0)
{ cout<<"\n\n\t ACCOUNT DOES NOT EXIST";
  cout<<"\n\t Press Any Key";
  getch();
}

}



void modify_acc(int n)  //Function to modify record in  file
{
 account ac;
 int found=0;
 fstream fil;
 fil.open("account.dat",ios::binary|ios::in|ios::out);
 if(!fil)
 {
    cout<<"\n\n\t FILE CANNOT BE OPENED ";
    getch();
    return;
 }
 while(fil.read((char*)&ac,sizeof(account))&& found==0);
 {
    if(ac.retacno()==n)
   { ac.show_acc();
     cout<<"\n\n\t MODIFIYONG ACCOUNT...";
     cout<<"\n\t Enter The New Details: ";
     ac.modify_acc();
     cout<<"\n\n\t ACCOUNT UPDATED !";
     cout<<"\n\t Press Any Key ";
     getch();
     int pos=(-1)*sizeof(account);
     fil.seekp(pos,ios::cur);
     fil.write((char*)&ac,sizeof(account));
     found=1;
   }
 }
 fil.close();
 if(found==0)
 {
  cout<<"\n\n\t ACCOUNT DOES NOT EXIST ";
  cout<<"\n\t Press Any Key ";
  getch();
 }
}

void delete_acc(int n)    //Function to delete record from file
{
 account ac;
 ifstream filin;
 ofstream filout;
 filin.open("account.dat",ios::binary);
 if(!filin)
  {
   cout<<"\n\n\t FILE COULD NOT BE FOUND";
   getch();
   return;
  }
 filout.open("temp.dat",ios::binary);
 filin.seekg(0,ios::beg);
 while(filin.read((char*)&ac,sizeof(account)))
 {
  if(ac.retacno()!=0)
  { filout.write((char*)&ac,sizeof(account)); }
 }
 filin.close();
 filout.close();
 cout<<"\n\n\t Enter your 7 digit pin..";
 for(int i=0;i<5;i++)
 {
  getch();
  cout<<" * ";
 }
 remove("account.dat");
 rename("temp.dat","account.dat");
 cout<<"\n\n\t YOUR ACCOUNT HAS BEEN CLOSED";
 cout<<"\n\n Press Any Key  ";
 getch();
}

void display_all()   //Function to display all the records from file
{
 account ac;
 ifstream filin;
 filin.open("account.dat",ios::binary);
 if(!filin)
 {
   cout<<"File could not be opened !!";
   cout<<"\n Press Any Key ";
   getch();
   return;
 }
else
{
 cout<<"\n\n\t\t ACCOUNT HOLDER LIST ";
 cout<<"\n\t\t~~~~~~~~~~~~~~~~~~~~~~\n\n\n";
 cout<<"\t__________________________________________\n";
 cout<<"\tA/C No.\t  NAME\t  ACCOUNT TYPE\t  BALANCE\n";
 cout<<"\t__________________________________________\n";
 while(filin.read((char*)&ac,sizeof(account)));
 { ac.report(); }
 filin.close();
 getch();
 }
}
void dep_withdraw(int n,int option)   //Function to deposit and withdraw from account
{ int amt,found=0;
  account ac;
  fstream fil;
  fil.open("account.dat",ios::binary|ios::in|ios::out);
  if(!fil)
  {
   cout<<"\n\n\t FILE COULD NOT BE OPENED ";
   getch();
   return;
  }
 while(fil.read((char*)&ac,sizeof(account)) && found==0)
 {
  if(ac.retacno()==n)
  {
    found=1;
    ac.show_acc();
    if(option==1)
    {
      cout<<"\n\n\t DEPOSIT AMOUNT";
	cout<<"\n\t ______________";
      cout<<"\n\n\t Enter the Amount to be Deposited";
      cin>>amt;
      ac.deposit(amt);
      cout<<"\n\n\t AMOUNT DEPOSITED!";
      cout<<"\n\t Press Any Key";
      getch();
    }
    if(option==2)
     {
      cout<<"\n\n\t WITHDRAW AMOUNT";
	cout<<"\n\t_________________";
      cout<<"\n\n\t Enter the Amount to be Withdrawn";
      cin>>amt;
      int  bal=ac.retdeposit()-amt;
      if((bal<1000 && ac.type_acc()=='S' || bal<1500 && ac.type_acc()=='C'))
	{
	cout<<"\n\n\t INSUFFICIENT BALANCE !";
	cout<<"\n\t Press Any Key ";
	getch();
	}
      else
	{
	ac.withdraw(amt);
	cout<<"\n\n\t AMOUNT WITHDRAWN";
	cout<<"\n\t Press Any Key ";
	getch();
	}
      }
  int pos=(-1)* sizeof(ac);
  fil.seekp(pos,ios::cur);
  fil.write((char*)&ac,sizeof(account));
  found=1;
    }
   }
  fil.close();
  if(found==0)
  {
   cout<<"\n\n\t ACCOUNT DOES NOT EXIST ";
   cout<<"\n\t Press Any Key: ";
   getch();
   }
}

void intro()     //Function for introductory page
{
 cout<<"\n      __________________________________________________________________";


   cout<<"\n\n\t\t\t  =====================  ";
     cout<<"\n\t\t\t# INVESTIGATORY PROJECT #";
   cout<<"\n\n\t\t\t  =====================  ";

  
   cout<<"\n\n\t Press Any Key to Start";
   getch();
   system("cls");

 cout<<"\n ----------------------------------------------------------------------";
 cout<<"\n ----------------------------------------------------------------------";
 cout<<"\n\n\n*********************************************************************";
 cout<<"\n\n\t\t\t|        BANK             |";
 cout<<"\n\n\t\t\t|      MANAGEMENT         |";
 cout<<"\n\n\t\t\t|       SOFTWARE          |";
 cout<<"\n\n********************************************************************";
 cout<<"\n\n\n ----------------------------------------------------------------------";
 cout<<"\n ----------------------------------------------------------------------";
 cout<<"\n\n Press Any Key:   ";
 getch();
}
