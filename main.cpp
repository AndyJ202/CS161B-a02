/******************************************************************************
# Author:           Andy Joy
# Assignment:       Assignment 2
# Date:             10/07/2026
# Description:      This program takes the user's name, if the work would be
#                   turned in late, student ID, file name, and date. It then
#                   uses char arrays to encode the information into a file name.
# Input:            option (char), lName  (char array), fName (char array), 
#                   userChoice (char), stdID (char array), fileName (char array)
#                   ,hours (int), minutes (int).
# Output:           encodeFileName (char array).
# Sources:          zyBooks 10.5.1.
#******************************************************************************/
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

//Constants
const int MAX_CHAR = 101;
const int STD_ID_LEN = 12;
const int PARSED_ID_LEN = 5;
const int CHAR_TIME = 6;

//Function prototypes
void welcome();
void displayMenu();
void readOption(char &option);
void encode(char encodeFileName[]);
void readInput(char fName[], char lName[], bool &lateFlag);
void readInput(char parsedID[], char fileName[]);
void readTime(char strTime[]);
void cstringToLower(char cstring[]);

//Main function
int main (){
	char userOption = 'a';
	char encodeFileName[MAX_CHAR];

	welcome();
	readOption(userOption);

	while(userOption != 'q'){
		cout << "\nThis program will ask you a few questions and generate an encoded fileName based on your answers." << endl;
		encode(encodeFileName);
		cout << "\nYour encoded file name is: " << encodeFileName << endl;
		readOption(userOption);	
	}

	cout << "\nThank you for using my fileName generator!" << endl;

	return 0;
}

//Welcome function
void welcome(){
        cout << "Welcome to my fileName encoding program!!" << endl;
}

//Menu display function for encode or quit
void displayMenu(){
        cout << "\nPlease pick an option below:" << endl;
        cout << "(e)Encode a file name" << endl;
        cout << "(q)quit" << endl;
}

//Read option function for encode or quit, validates for e/q
void readOption(char &option){
        displayMenu();
        cin >> option;
        option = tolower(option);

        while (option != 'e' && option != 'q'){
                cout << "\nInvalid option! Please try again!!" << endl;
                cin.clear();
                cin.ignore(100, '\n');
                displayMenu();
                cin >> option;
                option = tolower(option);
        }
}

//Encode function, combines all char arrauys for the final encoded file name
void encode(char encodeFileName[]){
        char fName[MAX_CHAR];
        char lName[MAX_CHAR];
	char parsedID[MAX_CHAR];
	char fileName[MAX_CHAR];
	char strTime[CHAR_TIME] {};
        bool isLate = false;

        readInput(fName, lName, isLate);
	readInput(parsedID, fileName);
	readTime(strTime);

	strncpy(encodeFileName, lName, MAX_CHAR);
	strcat(encodeFileName, "_");
	strcat(encodeFileName, fName);
	strcat(encodeFileName, "_");

	if (isLate == true){
                strcat(encodeFileName, "LATE");
		strcat(encodeFileName, "_");
        }
	strcat(encodeFileName, parsedID);
	strcat(encodeFileName, "_");
	strcat(encodeFileName, strTime);
	strcat(encodeFileName, "_");
	strcat(encodeFileName, fileName);
}

//Read Input function for first name, last name, and late status. Also validates yes/no choice for late status.
void readInput(char fName[], char lName[], bool &lateFlag){
        char userChoice;

        cout << "\nEnter your last name: ";
        cin >> lName;
        cstringToLower(lName);

        cout << "Enter your first name: ";
        cin >> fName;
        cstringToLower(fName);

        cout << "\nWas your assignment Late (y/n)? ";
        cin >> userChoice;
        userChoice = tolower(userChoice);

        while(userChoice != 'y' && userChoice != 'n'){
                cout << "\nInvalid option! Please try again!!" << endl;
                cin.clear();
                cin.ignore(100, '\n');
                cout << "\nWas your assignment Late (y/n)? ";
                cin >> userChoice;
                userChoice = tolower(userChoice);
        }
        if (userChoice == 'y'){
                lateFlag = true;
        }
        else {
                lateFlag = false;
        }
}

//Read Input function for student ID and file name. Also shortens the student ID to four digits.
void readInput(char parsedID[], char fileName[]){
	char stdID[STD_ID_LEN];
	
	cout << "\nEnter your Student-ID (format: 222-22-2222): ";
	cin >> stdID;
	strncpy(parsedID, stdID + 7, 4);
	parsedID[4] = '\0';
	
	cout << "\nEnter the file name: ";
	cin >> fileName;
}

//Read time function. Reads time in military, validates values, and validates formate. Also converts input from int to char array.
void readTime(char strTime[]){
	int hour = 0;
	int min = 0;
	char discard = ':';

	cout << "\nEnter the time submitted (military time - ex: 18:24 for 6:24pm): ";
	cin >> hour >> discard >> min;

	while (hour < 0 || hour > 24){
		cout << "\nInvalid input! Hours must be between 0-24!!" << endl;
		cin.clear();
                cin.ignore(100,'\n');
		cout << "\nEnter the time submitted (military time - ex: 18:24 for 6:24pm): ";
	        cin >> hour >> discard >> min;
	}	

	while (min < 0 || min >= 60){
        	cout << "\nInvalid input! Minutes must be between 0-60!!" << endl;
		cin.clear();
                cin.ignore(100,'\n');
                cout << "\nEnter the time submitted (military time - ex: 18:24 for 6:24pm): ";
                cin >> hour >> discard >> min;
        }

	if (hour < 10) {
     		strTime[0] = '0';
   	}
   	strncat(strTime, to_string(hour).c_str(),10);

   	if (min < 10) {
      		strcat(strTime, "0");
   	}
   	strcat(strTime, to_string(min).c_str());
}	

//Convert to lower case function
void cstringToLower(char cstring[]){
        for (int i = 0; cstring[i] != '\0'; i++){
                cstring[i] = tolower(cstring[i]);
        }
}