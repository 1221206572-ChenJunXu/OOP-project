#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

//DEFINE FILE NAME
#define CUSTOMERFILE "./customer.txt"
using namespace std;

class Customer;

extern char logintype;
extern bool login;
extern Customer loginUser;


class FileManager;
//Customer
class Customer{
	
private:
public:
	string username;
	string email;
	string phone;
	string password;
	char securekey;
	string secureans;
	
	
public:
	Customer()
		:securekey(0) 
	{
		cout << "Customer::Customer()" << endl; 
	}
		
	virtual ~Customer()
	{
		cout << "Customer::~Customer()" << endl;
	}
	
	Customer(const Customer& other) 
        : username(other.username),
          email(other.email),
          phone(other.phone),
          password(other.password),
          securekey(other.securekey),
          secureans(other.secureans) {
        cout << "Customer::Customer(const Customer&)" << endl;
    }
	
	friend class FileManager;
//    friend void LoadCustomerFile(vector<Customer>& customerList);
//    friend void SaveCustomerFile(vector<Customer>& customerList);
    
    
    string getusername() const{ return username;	}
    string getemail() const{ return email;}
    string getphone() const{ return phone;}
    string getpassword() const{ return password;}
    char getsecurekey() const{ return securekey;}
    string getsecureans() const{ return secureans;}
    
    void setusername(string username) {this->username = username;}
    void setemail(string email) {this->email = email;}
    void setphone(string phone) {this->phone = phone;}
    void setpassword(string password) {this->password = password;}
    void setsecurekey(char securekey) {this->securekey = securekey;}
    void setsecureans(string secureans) {this->secureans = secureans;}
    
};

class CustomerManager{
private:
	vector<Customer>& customerList;

public:
//	void LoadCustomerFile(vector<Customer>& customerList);
	CustomerManager(vector<Customer>& customers) : customerList(customers) {}
	void CustomerLogin(char& logintype);
	void AccRegister();
	void AccLogin();
	bool checkDuplication(const string& register_attr, const string& check_type);
	void printCustomerList();
};

class FileManager{
public:
	void LoadCustomerFile(vector<Customer>& customerList);
	void SaveCustomerFile(vector<Customer>& customerList);
	
};
//Read from file
//void LoadCustomerFile(vector<Customer>& customerList);

//Index Menu show;
void ShowIndexMenu();


//Read menu selection
char readMenuSelection(int options);
bool checkEmptyInput(const string& check_input);






#endif