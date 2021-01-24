/*This is a menu driven program that accesses/manipulates books
  Created by:  Devon Wilson
  October-18-2017*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_ARRAY = 200;
const int MAX_STR = 200;

struct Book
{
	int ISBN;
	char title[MAX_STR];
	char author[MAX_STR];
	char publisher[MAX_STR];
	double price;
	int total;
};

void search(Book books[], int count);
void findIsbn(Book books[], int count);
void addBook(Book books[], int& count);
void readIn(Book books[], int count, int newIsbn, int newTotal, char newTitle[], char newAuthor[], char newPublisher[], double newPrice);

int readIn(Book books[], int count) //Read the provided txt file into the array of Book
{	
	ifstream infile;
	infile.open("inventory.txt");
	if(!infile)
	{
		do
		{
			cout << "Failed to open file " << endl;
		}while(!infile);
	}
	char c = infile.peek();
	while(!infile.eof() && count <= MAX_STR && c != '\n')
	{
		infile >> books[count].ISBN;
		infile.ignore(MAX_STR, '\n');
		infile.getline(books[count].title, MAX_STR);
		infile.getline(books[count].author, MAX_STR);
		infile.getline(books[count].publisher, MAX_STR);
		infile >> books[count].price;
		infile.ignore(MAX_STR, '\n');
		infile >> books[count].total;
		infile.ignore(MAX_STR, '\n');
		c = infile.peek();
		count++;	
	}
	infile.close();
	return count;
}

void print(Book books[], int count) // print all books to screen
{	
	cout << " " << endl;
	cout << " " << endl;
	cout << "%%%%%%%%%% Book Inventory %%%%%%%%%% " << endl;
	cout << " " << endl;
	cout << " " << endl;
	for(int i = 0; i < count-1; i++)
	{
		cout << "------- ISBN: ";
		cout << setw(3) << setfill('0'); // leading zeros to hundreds
		cout << books[i].ISBN;
		cout << "------------ " << endl;
		cout << "Title: " << books[i].title << endl;
		cout << "Author: " << books[i].author << endl;
		cout << "Publisher: " << books[i].publisher << endl;
		cout << fixed << setprecision(2);
		cout << "Price: " << books[i].price << endl;
		cout << "In Stock Total: " << books[i].total << endl;	
		cout << "--------------------------------" << endl;
	}
}

void printMenu()
{
		cout << " " << endl;
                cout << " " << endl;
                cout << "********MAIN MENU******** " << endl;
                cout << "1 - Print Inventory " << endl;
                cout << "2 - Search by Publisher " << endl;
                cout << "3 - Find book by ISBN Number " << endl;
                cout << "4 - Add Book " << endl;
                cout << "5 - quit " << endl;
                cout << "Enter choice: " << endl;
}


void menu(Book books[], int& count)
{	
	char choice;	
	bool gameOn = true; //breaks the repeating menu when false
	while(gameOn != false)
	{
		printMenu();
		cin >> choice;
		switch(choice)
		{
			case '1':
				print(books, count);
				break;
			case '2':
				search(books, count);
				break;
			case '3':
				findIsbn(books, count);
				break;
			case '4':
				addBook(books, count);
				break;
			case '5': // quits menu
				cout << "*** END OF PROGRAM **" << endl;
				gameOn = false;	 
				break;
			default:	
				break;
		}
	}
}

void search(Book books[], int count) // searches by publisher
{
	int counter = 0;
	char choice[MAX_ARRAY];
	cout << "Publisher? " << endl;
	cin.ignore();
	cin.getline(choice, 256);
	for(int i = 0; i < 9; i++)
	{
		if(strcmp(books[i].publisher, choice) == 0)
		{
			cout << "------- ISBN: ";
                	cout << setw(3) << setfill('0'); // leading zeros to hundreds
                	cout << books[i].ISBN;
                	cout << "------------ " << endl;
			cout << books[i].ISBN << endl;
			cout << books[i].title << endl;
			cout << books[i].author << endl;
			cout << books[i].publisher << endl;
			cout << books[i].price << endl;
			cout << books[i].total << endl;
			cout << "--------------------------------" << endl;
			counter++;
		}
	}
	if(counter == 0)
	{
		cout << "No books in the inventory from that publisher " << endl;	
	}
}

void findIsbn(Book books[], int count) // searches by ISBN
{
	int counter = 0;
	int isbn;
	cout << "Enter isbn of book: " << endl;
	cin >> isbn;
	for(int j = 0; j < count; j++)
	{
		if(books[j].ISBN == isbn)
		{
			cout << "------- ISBN: ";
                        cout << setw(3) << setfill('0'); // leading zeros to hundreds
                        cout << books[j].ISBN;
                        cout << "------------ " << endl;
                        cout << books[j].ISBN << endl;
                        cout << books[j].title << endl;
                        cout << books[j].author << endl;
                        cout << books[j].publisher << endl;
                        cout << books[j].price << endl;
                        cout << books[j].total << endl;
                        cout << "--------------------------------" << endl;
			counter++;
		}
	}	
	if(counter == 0)
	{
		cout << "The book does not exist. " << endl;
	}
}

int checkIsbn(Book books[], int count, int newIsbn) // check to make sure ISBN is unique
{
	int h;
	if(newIsbn == 10)
	{
		return newIsbn;
	}
	do
	{
        	for(h = 0; h < count-1; h++)
                {
                	if(books[h].ISBN == newIsbn)
                        {
                        	cout << "That ISBN is already in the inventory. ";
                                cout << "Please re-enter." << endl;
                                cin >> newIsbn;
				cin.ignore();
				if(newIsbn == 10)
				{
					return newIsbn;
				}
				
                        }
        	}
	}while(books[h].ISBN == newIsbn);
	return newIsbn;
}

int checkTotal(int count, int newTotal) // check to make sure total is positive
{
	while(newTotal < 0)
	{
		cout << "Negative price.  Please re-enter" << endl;
		cin >> newTotal;
		cin.ignore();
	}
	return newTotal;
}

int checkPrice(int count, double newPrice) // check to make sure price is positive
{
	while(newPrice < 0)
	{
		cout << "Negative price.  Please re-enter" << endl;
		cin >> newPrice;
		cin.ignore();
	}
	return newPrice;
}

void readIn(Book books[], int count, int newIsbn, int newTotal, char newTitle[], char newAuthor[], char newPublisher[], double newPrice)
{
        books[count-1].ISBN = newIsbn;
        strcpy(books[count-1].title, newTitle);
        strcpy(books[count-1].author, newAuthor);
        strcpy(books[count-1].publisher, newPublisher);
	books[count-1].price = newPrice;
        books[count-1].total = newTotal;
}

void addBook(Book books[], int& count) // adds books to inventory
{
        int newIsbn;
	int  newTotal;
        char newTitle[MAX_ARRAY];
        char newAuthor[MAX_ARRAY];
        char newPublisher[MAX_ARRAY];
        double newPrice;
        cout << "Book's ISBN? (must be unique) " << endl;
        cin >> newIsbn; 
	cin.ignore();
        newIsbn = checkIsbn(books, count, newIsbn);	
        cout << "Title:" << endl;
        cin.getline(newTitle, MAX_ARRAY);
        cout << "Author? " << endl;
        cin.getline(newAuthor, MAX_ARRAY);
        cout << "Publisher? " << endl;
        cin.getline(newPublisher, MAX_ARRAY);
        cout << "Price?" << endl;
        cin >> newPrice;
        newPrice = checkPrice(count, newPrice);
        cout << "In Stock Total?( < 0) " << endl;
        cin >> newTotal;
        newTotal = checkTotal(count, newTotal);
	readIn(books, count, newIsbn, newTotal, newTitle, newAuthor, newPublisher, newPrice);
        count++;
}

int writeOut(Book books[], int count) //Read the provided txt file into the array of Book
{
        ofstream outfile;
        outfile.open("inventory.txt");
        if(!infile)
        {
                do
                {
                        cout << "Failed to open file " << endl;
                }while(!infile);
        }
        char c = infile.peek();
        for(int i = 0; i < count; i++)
        {
                outfile >> books[count].ISBN;
                outfile.ignore(MAX_STR, '\n');
                outfile.getline(books[count].title, MAX_STR);
                outfile.getline(books[count].author, MAX_STR);
                outfile.getline(books[count].publisher, MAX_STR);
                outfile >> books[count].price;
                outfile.ignore(MAX_STR, '\n');
                outfile >> books[count].total;
                outfile.ignore(MAX_STR, '\n');
                c = infile.peek();
                count++;
        }
        outfile.close();
        return count;
}


int main()
{
        int count = 0 ;
        cout << " " << endl;
        cout << " " << endl;
        cout << "******* Overstock Books Wholesaler's ******* " << endl;
	cout << " " << endl;
	cout << " " << endl;
        Book books[MAX_ARRAY];
        count = readIn(books, count);
        menu(books, count);
	writeOut(books, count);
        return 0;
}

