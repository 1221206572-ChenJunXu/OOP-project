#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

//DEFINE FILE NAME
#define CUSTOMERFILE "./customer.txt"
#define STAFFFILE "./staff.txt"
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
	
	friend struct FileManager;
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
	void printCustomerList();
	void addCustomer();
	void delCustomer(const int& key);
	void updateCustomer(const int& key);
	void viewCustomer();
};


class Staff : public User{

public:
	Staff():User(){};
	virtual ~Staff(){};
	Staff(const Staff& other):User(other)
	{ cout << "Staff(const Staff& other)" << endl; }
	string getusername() const{ return username;}
    string getpassword() const{ return password;}
	
	friend struct FileManager;

};

class StaffManager{
public:
	vector<Staff>& staffList;
	StaffManager(vector<Staff>& staff) : staffList(staff) {}
};

struct FileManager{
	void LoadCustomerFile(vector<Customer>& customerList);
	void SaveCustomerFile(vector<Customer>& customerList);
	void LoadStaffFile(vector<Staff>& staffList);
	void SaveStaffFile(vector<Staff>& staffList);
	
};
//Read from file
//void LoadCustomerFile(vector<Customer>& customerList);

//Index Menu show;
void ShowIndexMenu();


//Read menu selection
char readMenuSelection(int options);
bool checkEmptyInput(const string& check_input);




extern bool isCustomer;
extern bool login;
extern User loginUser;


#endif