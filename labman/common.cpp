#include <iostream>
#include <vector>
#include <string>
#include <fstream>


#include "common.h"


bool isCustomer = true;
bool login = false;
User loginUser;
//Read from file

void FileManager::LoadCustomerFile(vector<Customer>& customerList){
	ifstream checkFile(CUSTOMERFILE);
	cout << "Loading File..." << endl;
	if (!checkFile.is_open()) {
        cout << "Error: Could not open customer file!" << endl;
        return;
    }
	
	string tmp;
	Customer custmp;
	string line;
	while(getline(checkFile,line)){
		stringstream ss(line);
		getline(ss,custmp.username,'|');
		getline(ss,custmp.password,'|');
		getline(ss,custmp.email,'|');
		getline(ss,custmp.phone,'|');
		getline(ss,tmp,'|');
		custmp.securekey = tmp[0];
		getline(ss,custmp.secureans,'|');
		
		
		customerList.push_back(custmp);

	}
	
	for(const auto& customer : customerList){
		cout << customer.username << "," << customer.password << "," << customer.email << "," << customer.phone
		<< "," << customer.securekey << "," << customer.secureans << endl;
	}
	
	checkFile.close();
}

//void CustomerManager::LoadCustomerFile(vector<Customer>& ccustomerList){
//	customerList = move(ccustomerList);
//}

void FileManager::SaveCustomerFile(vector<Customer>& customerList){
	ofstream saveFile(CUSTOMERFILE);
	cout << "Saving File..." << endl;
	if (!saveFile.is_open()) {
        cout << "Error: Could not open customer file!" << endl;
        return;
    }
    if (customerList.empty()) {
        cout << "Error: Customer list is empty. Nothing to save!" << endl;
        return;
    }
	for(const auto& customer : customerList){
		cout << customer.username << "|" << customer.password << "|" << customer.email << "|" << customer.phone
		<< "|" << customer.securekey << "|" << customer.secureans << endl;
		saveFile << customer.username << "|" << customer.password << "|" << customer.email << "|" << customer.phone
		<< "|" << customer.securekey << "|" << customer.secureans << endl;
	}
	cout << "All data Saved..." << endl;
	saveFile.close();
}




//staff file
void FileManager::LoadStaffFile(vector<Staff>& staffList){
	ifstream checkFile(STAFFFILE);
	cout << "Loading File..." << endl;
	if (!checkFile.is_open()) {
        cout << "Error: Could not open staff file!" << endl;
        return;
    }
	
	string tmp;
	Staff stafftmp;
	string line;
	while(getline(checkFile,line)){
		stringstream ss(line);
		getline(ss,stafftmp.username,'|');
		getline(ss,stafftmp.password,'|');
		
		
		staffList.push_back(stafftmp);

	}
	
	for(const auto& staff : staffList){
		cout << staff.username << "," << staff.password << endl;
	}
	
	checkFile.close();
}

//void CustomerManager::LoadCustomerFile(vector<Customer>& ccustomerList){
//	customerList = move(ccustomerList);
//}

void FileManager::SaveStaffFile(vector<Staff>& staffList){
	ofstream saveFile(STAFFFILE);
	cout << "Saving File..." << endl;
	if (!saveFile.is_open()) {
        cout << "Error: Could not open staff file!" << endl;
        return;
    }
    if (staffList.empty()) {
        cout << "Error: Customer list is empty. Nothing to save!" << endl;
        return;
    }
	for(const auto& staff : staffList){
		cout << staff.username << "|" << staff.password << endl;
	}
	cout << "All data Saved..." << endl;
	saveFile.close();
}


//Index Menu Show
void ShowIndexMenu(){
	cout << "Welcome" << endl;
	cout << "----------" << endl;
	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "0. Exit" << endl;
}


//Read menu selection
char readMenuSelection(int options){
	string str;
	cout << "readMenuSelection()" << endl;
	
	while(true)
	{
		getline(cin, str);
		
		//validation
		if(str.size() != 1 || str[0] - '0' < 0 || str[0] - '0' > options)
			cout << "Wrong input, please try again : ";
		else
			break;
	}	
	
	return toupper(str[0]);
}



bool checkEmptyInput(const string& check_input){
	cout << "checkEmptyInput()" << endl;
	return check_input.empty();
}







void CustomerManager::CustomerLogin(){
	
	bool quit = false;
	while(!quit)
	{
		ShowIndexMenu();
		char key = readMenuSelection(2);
		switch(key)
		{
		case '1':
			cout << "Register..." << endl;
			AccRegister();
			break;
		case '2':
			cout << "Login..." << endl;
			AccLogin();
			printCustomerList();
			cout << "Book Content Blabla";
			break;
			quit = true;
		default:
			quit = true;
		}
	}
	
}

void CustomerManager::AccLogin(){
	
	Customer logincus1;
	Staff loginstaff1;
	
	vector<Staff> staffList;
	FileManager fileManager;
	fileManager.LoadStaffFile(staffList);
	StaffManager staffManager(staffList);
	
	
	string login_attr, login_attr2;
	int wrong_count = 0;
	bool found_acc = false;
	bool quit = false;
	while(!quit)
	{
			
		cout << "Please Enter your Username : ";
		
		while(true && wrong_count<3)
		{	
			getline(cin, login_attr);
			if(checkEmptyInput(login_attr))
			{
				cout << "Please enter a proper Username : ";
				continue;
			}
			else
			{
				for(const auto& customer : customerList)
				{
					if(login_attr == customer.getusername()){
						found_acc = true;
						logincus1 = customer;
						break;
					}
				}
				for(const auto& staff : staffList)
				{
					if(login_attr == staff.getusername()){
						found_acc = true;
						loginstaff1 = staff;
						break;
					}
				}
				if(!found_acc){
					cout << "Could not match any username. Please try again" << endl;
					wrong_count++;
				}
				if(found_acc || wrong_count >= 3)break;
			}
			
		}
		if(found_acc) wrong_count = 0;
		while(found_acc && wrong_count < 3)
		{
			while(true)
			{	
				cout << "Please enter your Password : ";
				getline(cin, login_attr2);
				if(checkEmptyInput(login_attr2))
				{
					cout << "Please enter a proper password : ";
				}
				else
				{
					if(logincus1.getpassword() == login_attr2){
						cout << "Welcome back" << logincus1.getusername() << " !" << endl;
						loginUser = logincus1;
						quit = true;
//						login = true;
						isCustomer = true;
						break;
					}
					if(loginstaff1.getpassword() == login_attr2){
						cout << "Welcome back" << loginstaff1.getusername() << " !" << endl;
						loginUser = loginstaff1;
						quit = true;
						isCustomer = false;
//						login = true;
						break;
					}
					
					else{
						cout << "Wrong Password. Please try again !!" << endl;
						wrong_count++;
						if(wrong_count >= 3) break;
						continue;
					}
				}
			}
			
			break;
			
		}
		
		int last_chance = 0;
		bool securetest = false;
		while(true && wrong_count >= 3)
		{
			last_chance = 0;
			
			cout << "Try another login method?" << endl;
			cout << "1. Using Email login" << endl;
			cout << "2. Using Phone Number login" << endl;
			cout << "0. Back" << endl;
			cout << endl << "Your Answer : ";
			
			char key = readMenuSelection(2);
			switch(key)
			{
				
			case '1':
				cout << "Please enter your email : ";
				while(true && last_chance<3)
				{	
					getline(cin, login_attr);
					if(checkEmptyInput(login_attr))
					{
						cout << "Please enter a proper Email : ";
						continue;
					}
					else
					{
						for(const auto& customer : customerList)
						{
							if(login_attr == customer.getemail()){
								found_acc = true;
								logincus1 = customer;
								break;
							}
						}
						if(!found_acc){
							cout << "Could not match any email. Please try again" << endl;
							last_chance++;
						}
						if(found_acc) securetest = true;
						if(found_acc || last_chance >= 3)break;
					}       
					
				}
				break;
			case '2':
				cout << "Please enter your phone number : ";
				while(true && last_chance<3)
				{	
					getline(cin, login_attr);
					if(checkEmptyInput(login_attr))
					{
						cout << "Please enter a proper Phone Number : ";
						continue;
					}
					else
					{
						for(const auto& customer : customerList)
						{
							if(login_attr == customer.getphone()){
								found_acc = true;
								logincus1 = customer;
								break;
							}
						}
						if(!found_acc){
							cout << "Could not match any Phone Number. Please try again" << endl;
							last_chance++;
						}
						if(found_acc) securetest = true;
						if(found_acc || last_chance >= 3)break;
					}
					
				}
				break;
			default:
				quit = true;
				break;
			}
			if(quit) break;
			if(securetest) break;
		}
		
		
		while(securetest){
			cout << endl;
			cout << logincus1.getsecurekey() << endl;
			switch(logincus1.getsecurekey()){
				case '1':
					cout << "Where do you live" << endl;
					break;
				case '2':
					cout << "How old is your father" << endl;
					break;
				case '3':
					cout << "What is your primary school name" << endl;
					break;
				default:
					cout << "Something error!" << endl;
			}
			
			while(true)
			{	
				cout << "Please enter your Answer : ";
				getline(cin, login_attr2);
				if(checkEmptyInput(login_attr2))
				{
					cout << "Please enter a proper Answer : ";
				}
				else
				{
					if(logincus1.getsecureans() == login_attr2){
						cout << "Correct! your password is : " << logincus1.getpassword()<< endl;
						cout << "Welcome Back " << logincus1.getusername() << " ! " << endl;
						loginUser = logincus1;
						//login = true;
						break;
					}
					else{
						cout << "Wrong Answer. Please try again !!" << endl;
						last_chance++;
						if(last_chance >= 3){
							quit = true;
							break;	
						}
						continue;
					}
				}
			}
			if(logincus1.getsecureans() == login_attr2 || quit) break;
		}
		if(logincus1.getsecureans() == login_attr2 || quit) break;
	}
	
}

void CustomerManager::AccRegister(){
	addCustomer();
}

bool CustomerManager::checkDuplication(const string& register_attr, const string& check_type){
	cout << "checkDuplication():" << endl;
	cout << register_attr << endl;
	
	if(check_type == "check_name")
	{
			
		
	    for (const auto& customer : customerList)
		{
	        if (customer.getusername() == register_attr)
			{
				cout<< "walao" << endl;
	            return true;
	        }
	    }
	    
	}
	else if(check_type == "check_email")
	{
		
	    for (const auto& customer : customerList)
		{
	        if (customer.getemail() == register_attr)
			{
				cout<< "walao" << endl;
	            return true;
	        }
	    }
	 
	}
	else if(check_type == "check_phone")
	{
		
	    for (const auto& customer : customerList)
		{
	        if (customer.getphone() == register_attr)
			{
				cout<< "walao" << endl;
	            return true;
	        }
	    }
	 
	}
    
    cout << "good good" << endl;
    return false;
}

void CustomerManager::printCustomerList(){
	while(true)
	{
		
		cout << "CustomerManager::printCustomerList()" << endl;
		for(const auto& customer : customerList){
		cout << customer.getusername() << "|" << customer.getpassword() << "|" << customer.getemail() << "|" << customer.getphone()
		<< "|" << customer.getsecurekey() << "|" << customer.getsecureans() << endl;
		}
		cout << "1. view customer (delete, update)" << endl;
		cout << "2. add new customer" << endl;
		cout << "3. previous page" << endl;
		cout << "4. next page" << endl;
		cout << "0. back" << endl;
		char key = readMenuSelection(4);
			switch(key){
				case '1':
					viewCustomer();
					break;
				case '2':
					addCustomer();
				case '3':
				case '4':
				case '0':
					break;
				default:
					cout << "Default" << endl;
			}
		if(key == '0') break;
	}
	
	
}


//void printCustomerList();
//	void delCustomer();
//	void updateCustomer();
//	void viewCustomer();
	
void CustomerManager::addCustomer(){
Customer registercus1;
	string register_attr,register_attr2;
	
	
	
	cout << "Please Enter your Username : ";
	while(true)
	{	
		getline(cin, register_attr);
		if(checkDuplication(register_attr,"check_name")){
			cout << "already exist... Please change another username : ";
		}
		else{
			if(checkEmptyInput(register_attr))
			{
				cout << "Please enter a proper name : ";
			}
			else
			{
				registercus1.setusername(register_attr);
				break;
			}
		}
		
	}
	
	
	
	cout << "Please Enter your Email : ";
	
	while(true)
	{	
		getline(cin, register_attr);
		if(checkDuplication(register_attr,"check_email")){
			cout << "already exist... Please change another Email : " << endl;
		}
		else{
			if(checkEmptyInput(register_attr))
			{
				cout << "Please enter a proper name : ";
			}
			else
			{
				registercus1.setemail(register_attr);
				break;
			}
		}
	}
	
	
	cout << "Please enter your Phone Number : ";
	
	
	while(true)
	{	
		getline(cin, register_attr);
		if(checkDuplication(register_attr,"check_phone")){
			cout << "already exist... Please change another phone : " << endl;
		}
		else{
			if(checkEmptyInput(register_attr))
			{
				cout << "Please enter a proper name : ";
			}
			else
			{
				registercus1.setphone(register_attr);
				break;
			}
		}
	}
	
	
	cout << "Please enter your Password : ";
	
	
	while(true)
	{	
		getline(cin, register_attr);
		if(checkEmptyInput(register_attr))
		{
			cout << "Please enter a proper password : ";
		}
		else
		{
			break;
		}
	}
	
	cout << "Please reenter your Password : ";
	
	
	while(true)
	{	
		getline(cin, register_attr2);
		if(checkEmptyInput(register_attr2))
		{
			cout << "Please enter a proper password : ";
		}
		else
		{
			if(register_attr != register_attr2)
			{
				cout << "Doesn't Match with the previous password. Please try again : ";
			}
			else
			{
				registercus1.setpassword(register_attr);
				break;
			}
		}
	}
	
	
	cout << "Please Select your Secure Key : ";
	cout << "1. Where do you live" << endl;
	cout << "2. How old is your father" << endl;
	cout << "3. What is your primary school name" << endl;
	
	char key = readMenuSelection(3);
	switch(key)
	{
	case '1':
	case '2':
	case '3':
		cout << "Please enter your answer : ";
		
		while(true)
		{	
			getline(cin, register_attr);
			if(checkEmptyInput(register_attr))
			{
				cout << "Please enter a proper answer : ";
			}
			else
			{
				registercus1.setsecureans(register_attr);
				break;
			}
		}
		registercus1.setsecurekey(key);
		break;
	}
	
	
	cout << registercus1.getusername() << "," << registercus1.getpassword() << "," << registercus1.getemail() << "," << registercus1.getphone()
		<< "," << registercus1.getsecurekey() << "," << registercus1.getsecureans() << endl;
		
	customerList.push_back(registercus1);
}



void CustomerManager::viewCustomer(){
	while(true)
	{
		cout << endl;
		cout << "Please Enter No. to view : ";
		int key = readMenuSelection(9) - '0';;
		cout << key << endl;
		key--;
		cout << key << endl;
		cout << setw(17) << left << "Username" << ":" << customerList[key].getusername() << endl;
		cout << setw(17) << left << "Password" << ":" << customerList[key].getpassword() << endl;
		cout << setw(17) << left << "Email" << ":" << customerList[key].getemail() << endl;
		cout << setw(17) << left << "Phone" << ":" << customerList[key].getphone() << endl;
		cout << setw(17) << left << "Securekey" << ":" << customerList[key].getsecurekey() << endl;
		cout << setw(17) << left << "Securekey answer" << ":" << customerList[key].getsecureans() << endl;
		cout << endl << endl;
		cout << "1. Update customer details" << endl;
		cout << "2. View customer rental status" << endl;
		cout << "3. View customer rental history" << endl;
		cout << "4. Delete customer" << endl;
		cout << "0. Back" << endl;
		char key2 = readMenuSelection(4);
		switch(key2){
			case '1':
				updateCustomer(key);
				break;
			case '2':
			case '3':
				break;
			case '4':
				delCustomer(key);
				break;
			case '0':
				break;
			default:
				cout << "Default" << endl;
		}
		break;
	}
}


void CustomerManager::updateCustomer(const int& key){
	string yorn;
	while(true)
	{
		cout << "Are you sure to update? [Y/N] : ";
		getline(cin,yorn);
		if(yorn == "Y" || yorn == "y")
		{
			cout << "Which attribute would you like to Edit ?" << endl;
			cout << "Enter the number: ";
			char key2 = readMenuSelection(6);
			while(true)
			{
				string change_attribute;
				cout << "Change to : ";
				fflush(stdin);
				getline(cin, change_attribute);
			//empty check
				if(checkEmptyInput(change_attribute))
				{
					cout << "Please Enter properly !" << endl;
					continue;
				}
			//duplication check
				if(key2 == '1')
				{
					if(checkDuplication(change_attribute,"check_name")){
						cout << "already exist... Please change another Name : " << endl; continue;
					}
				}
				else if(key2 == '3')
				{
					if(checkDuplication(change_attribute,"check_email")){
						cout << "already exist... Please change another Email : " << endl; continue;
					}
				}
				else if(key2 == '4')
				{
					if(checkDuplication(change_attribute,"check_phone")){
						cout << "already exist... Please change another Phone : " << endl; continue;
					}
				}
				
			//Update attribute
				switch(key2)
				{
					case '1': customerList[key].setusername(change_attribute); break;
					case '2': customerList[key].setpassword(change_attribute); break;
					case '3': customerList[key].setemail(change_attribute); break;
					case '4': customerList[key].setphone(change_attribute); break;
					case '5': customerList[key].setsecurekey(change_attribute[0]); break;
					case '6': customerList[key].setsecureans(change_attribute); break;
				}
				
				cout << "Done Changed Attribute!" << endl;
				break;
			}
			break;
		}
		else if(yorn == "N" || yorn == "n")	break;
		else cout << "Wrong Input. Please try again!" << endl;
	}
}
void CustomerManager::delCustomer(const int& key){
	while(true)
	{
		string yorn;
		cout << "Are you really sure to delete the user ? [Y/N]";
			getline(cin,yorn);
		if(yorn == "Y" || yorn == "y")
		{
			customerList.erase(customerList.begin()+key);
			cout << "The user have been deleted..." << endl;
			break;
		}
		else if(yorn == "N" || yorn == "n")	break;
		else cout << "Wrong Input. Please try again!" << endl;
	}
}