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

//Customer
class Customer{
	
private:
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
	
    friend void LoadCustomerFile(vector<Customer>& customerList);
    friend void SaveCustomerFile(vector<Customer>& customerList);
    
    
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


//Read from file
void LoadCustomerFile(vector<Customer>& customerList);

//Index Menu show;
void ShowIndexMenu();


//Read menu selection
char readMenuSelection(int options);


void CustomerLogin(vector<Customer>& customerList, char& logintype);

void AccRegister(vector<Customer>& customerList);
bool checkDuplication(const vector<Customer>& customerList, const string& register_attr, const string& check_type);
bool checkEmptyInput(const string& register_attr);


void AccLogin(vector<Customer>& customerList);



#endif