#include <iostream>
#include <vector>
#include <string>
#include <fstream>


#include "common.h"


char logintype = {};
bool login = false;
Customer loginUser;
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
		getline(ss,custmp.email,'|');
		getline(ss,custmp.phone,'|');
		getline(ss,custmp.password,'|');
		getline(ss,tmp,'|');
		custmp.securekey = tmp[0];
		getline(ss,custmp.secureans,'|');
		
		
		customerList.push_back(custmp);

	}
	
	for(const auto& customer : customerList){
		cout << customer.username << "," << customer.email << "," << customer.phone << "," << customer.password
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
		cout << customer.username << "|" << customer.email << "|" << customer.phone << "|" << customer.password
		<< "|" << customer.securekey << "|" << customer.secureans << endl;
		saveFile << customer.username << "|" << customer.email << "|" << customer.phone << "|" << customer.password
		<< "|" << customer.securekey << "|" << customer.secureans << endl;
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







void CustomerManager::CustomerLogin(char& logintype){
	
	bool quit = false;
	while(!quit)
	{
		ShowIndexMenu();
		char key = readMenuSelection(2);
		switch(key)
		{
		case '1':
			logintype = '1';
			cout << "Register..." << endl;
			AccRegister();
			break;
		case '2':
			logintype = '2';
			cout << "Login..." << endl;
			AccLogin();
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
	
	
	cout << registercus1.getusername() << "," << registercus1.getemail() << "," << registercus1.getphone() << "," << registercus1.getpassword()
		<< "," << registercus1.getsecurekey() << "," << registercus1.getsecureans() << endl;
		
	customerList.push_back(registercus1);
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
	cout << "CustomerManager::printCustomerList()" << endl;
	for(const auto& customer : customerList){
	cout << customer.getusername() << "|" << customer.getemail() << "|" << customer.getphone() << "|" << customer.getpassword()
	<< "|" << customer.getsecurekey() << "|" << customer.getsecureans() << endl;
	}
}
