#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "common.h"



int main(int argc, char** argv) {
	
	bool quit = false;
	vector<Customer> customerList;
	
	FileManager fileManager;
	fileManager.LoadCustomerFile(customerList);
	
	CustomerManager customerManager(customerList);
//	customerManager.LoadCustomerFile(customerList);
	customerManager.CustomerLogin(logintype);
	
	
	
	cout << loginUser.getusername() << " is the login user!" << endl;
	
//	if (customerList.empty()) {
//        cout << "Main Error: Customer list is empty. Nothing to save!" << endl;
//    }
	fileManager.SaveCustomerFile(customerList);
//	customerManager.printCustomerList();
	
	cout << "bye"<< endl;
	return 0;
}