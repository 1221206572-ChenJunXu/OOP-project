#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "common.h"



int main(int argc, char** argv) {
	
	bool quit = false;
	vector<Customer> customerList;
	
	LoadCustomerFile(customerList);
	
	CustomerLogin(customerList, logintype);
	
	
	
	cout << loginUser.getusername() << " is the login user!" << endl;
	
	SaveCustomerFile(customerList);
	
	cout << "bye"<< endl;
	return 0;
}