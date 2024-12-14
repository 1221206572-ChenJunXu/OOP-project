#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

//DEFINE FILE NAME
#define CUSTOMERFILE "./customer.txt"
#define STAFFFILE "./staff.txt"
#define BOOKFILE "./book.txt"
using namespace std;


class User;
//class Customer : public User;



class FileManager;

class User{

protected:
	string username;
	string password;

public:
    User() : username(""), password("") {}
    virtual ~User() {}
    virtual  string getusername() const{ return username;}
    User(const User& other)
    : username(other.username),
      password(other.password) {}
};

//Customer
class Customer : public User{
	
private:
	string email;
	string phone;
	char securekey;
	string secureans;
	
	
public:
	Customer()
		:User(),securekey('\0') 
	{
		cout << "Customer::Customer()" << endl; 
	}
		
	virtual ~Customer()
	{
		cout << "Customer::~Customer()" << endl;
	}
	
	Customer(const Customer& other) 
        :
//		 username(other.username),
//          password(other.password),
		  User(other),
          email(other.email),
          phone(other.phone),
          securekey(other.securekey),
          secureans(other.secureans) {
        cout << "Customer::Customer(const Customer&)" << endl;
    }
	
	friend class FileManager;
//    friend void LoadCustomerFile(vector<Customer>& customerList);
//    friend void SaveCustomerFile(vector<Customer>& customerList);


    string getusername() const{ return username;}
    string getpassword() const{ return password;}
    string getemail() const{ return email;}
    string getphone() const{ return phone;}
    char getsecurekey() const{ return securekey;}
    string getsecureans() const{ return secureans;}

    void setusername(string username) {this->username = username;}
    void setpassword(string password) {this->password = password;}
    void setemail(string email) {this->email = email;}
    void setphone(string phone) {this->phone = phone;}
    void setsecurekey(char securekey) {this->securekey = securekey;}
    void setsecureans(string secureans) {this->secureans = secureans;}

};

class CustomerManager{
private:
	vector<Customer>& customerList;

public:
//	void LoadCustomerFile(vector<Customer>& customerList);
	CustomerManager(vector<Customer>& customers) : customerList(customers) {}
	void CustomerLogin();
	void AccRegister();
	void AccLogin();
	bool checkDuplication(const string& register_attr, const string& check_type);
	void viewCustomer(const int& key);
	void addCustomer();
	void updateCustomer(const int& key);

	//admin platform function:
	void printCustomerList();
	void delCustomer(const int& key);
};


class Staff : public User{

public:
	Staff():User(){};
	virtual ~Staff(){};
	Staff(const Staff& other):User(other)
	{ cout << "Staff(const Staff& other)" << endl; }
	string getusername() const{ return username;}
    string getpassword() const{ return password;}
	
	friend class FileManager;

};

class StaffManager{
public:
	vector<Staff>& staffList;
	StaffManager(vector<Staff>& staff) : staffList(staff) {}
};


class Book{
private:
	string ISBN;
	char type;
	string name;
	string author;
	string publisher;
	string publishdate;
	string description;
	float rentalprice;
	int quantity;
	char status;
	int maxduration;
public:
//	virtual void conditionDisplay();
	Book()
	:rentalprice(0.0), type('\0'), quantity(0), status('\0'), maxduration(0)
	{
		cout << "Book::Book()" << endl;
	}

	Book(const string& isbn, char t, const string& n, const string& a, const string& p, const string& date, const string& desc,
     float price, int qty, char s, int maxDur)
     : ISBN(isbn), type(t), name(n), author(a), publisher(p), publishdate(date), description(desc),
       rentalprice(price), quantity(qty), status(s), maxduration(maxDur) {}

	virtual ~Book();
	Book(const Book& other) :
		ISBN(other.ISBN), type(other.type), name(other.name), author(other.author), publisher(other.publisher),
		publishdate(other.publishdate),description(other.description),rentalprice(other.rentalprice),quantity(other.quantity),
		status(other.status),maxduration(other.maxduration)
	{
		cout << "Book::Book(const Book&)" << endl;
	}

	virtual void display() const {
        cout << "ISBN: " << ISBN << " "
             << "Type: " << type << " "
             << "Name: " << name << " "
             << "Author: " << author << " "
             << "Publisher: " << publisher << " "
             << "Publish Date: " << publishdate << " "
             << "Description: " << description << " "
             << "Rental Price: " << rentalprice << " "
             << "Quantity: " << quantity << " "
             << "Status: " << status << " "
             << "Max Duration: " << maxduration << " days" << endl;


    }

	friend class FileManager;

};

class NewBook : public Book{
public:
	NewBook(const string& isbn, char t, const string& n, const string& a, const string& p, const string& date, const string& desc,
            float price, int qty, char s, int maxDur)
        : Book(isbn, t, n, a, p, date, desc, price, qty, s, maxDur) {}
    ~NewBook() override {}

    void display() const override {
        cout << "=== New Book ===" << endl;
        Book::display();
    }
};

class SlightlyUsedBook : public Book{
public:
	SlightlyUsedBook(const string& isbn, char t, const string& n, const string& a, const string& p, const string& date, const string& desc,
            float price, int qty, char s, int maxDur)
        : Book(isbn, t, n, a, p, date, desc, price, qty, s, maxDur) {}
    ~SlightlyUsedBook() override {}

    void display() const override {
        cout << "=== Slightly Used Book ===" << endl;
        Book::display();
    }
};

class HeavilyUsedBook : public Book{
public:
	HeavilyUsedBook(const string& isbn, char t, const string& n, const string& a, const string& p, const string& date, const string& desc,
            float price, int qty, char s, int maxDur)
        : Book(isbn, t, n, a, p, date, desc, price, qty, s, maxDur) {}
    ~HeavilyUsedBook() override {}

    void display() const override {
        cout << "=== Heavily Used Book ===" << endl;
        Book::display();
    }
};

class BookManager{
private:
	vector<shared_ptr<Book>> books;
public:
	BookManager(const vector<shared_ptr<Book>>& b): books(b) {}
	void displayAllBooks() const {
        cout << "Displaying all books:" << endl;
        for (const auto& book : books) {
            book->display();
            cout << "------------------------" << endl;
        }
    }
};

class FileManager{
public:
	void LoadCustomerFile(vector<Customer>& customerList);
	void SaveCustomerFile(vector<Customer>& customerList);
	void LoadStaffFile(vector<Staff>& staffList);
	void SaveStaffFile(vector<Staff>& staffList);
	void LoadBookFile(vector<shared_ptr<Book>>& bookList);
//	void SaveBookFile(vector<Staff>& staffList);

};
//Read from file
//void LoadCustomerFile(vector<Customer>& customerList);

//Index Menu show;
void ShowIndexMenu();
void ShowMainMenu();

//Read menu selection
char readMenuSelection(int options);
bool checkEmptyInput(const string& check_input);




extern bool isCustomer;
extern bool login;
extern User loginUser;


#endif