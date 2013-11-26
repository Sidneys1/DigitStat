/***          DigitStat.cpp v1.0          ***/
/***       (C) 2013 DigitStat Corp.       ***/
/*** The Leading Name in Digit Statistics ***/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "DigitStat.h"
#include <list>
#include <locale>
#define ERROR_INVALID_ARGS	1
#define ERROR_INVALID_FILE	2
#define ERROR_BAD_FORMAT	3

using namespace std;

int main(int argc, char* argv[]) {
	// Variables...
	ofstream outFile;
	ifstream inFile;
	LinkedNode *head = nullptr;
	int integers = 0, fractions = 0;
	int firstDigCount[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	if (argc != 3) { // Check argument count...
		cout << "Format: " << argv[0] << " infile outfile" << endl;
		return ERROR_INVALID_ARGS;
	}
	else { // Check for good files...
		inFile.open(argv[1]);
		outFile.open(argv[2], ofstream::trunc);
		
		if (!inFile.good() || !outFile.good()) {
			cout << "Invalid file(s)! (In: " << argv[1] << ", out: " << argv[2] << ")" << endl;
			return ERROR_INVALID_FILE;
		}
	}

	// So now our input and output files are initialized, we need to read the numbers in one by one and insert them into a doubly linked list.
	for (string line; getline(inFile, line); ) {
		// Convert the string into a stringstream
 	 	istringstream ss(line);
		// And read it into a double. Exit with a bad format if we can't read a double.
		
		double val;
		if (!(ss >> val))
			return ERROR_BAD_FORMAT;

		// Now we create a new LinkedNode to store our value...
		LinkedNode *temp = new LinkedNode;
		temp->value = line;
		temp->actualValue = val;
		temp->prev = nullptr;
		temp->next = nullptr;

		//Counting first digit occurrences.
		firstDigCount[((int)line[0] - 48)]++;

		//Checking whether or not the value is a fraction or an integer
		if(val == (long long)val)
			integers++;
		else 
			fractions++;

		// And we set up the DigitCounts struct.
		// Note: b + 30 is converting byte b into a char with a value of '0', '1', etc
		// "count" is from the algorithms import, and operates on templated collections.
		// Since string is a templated collection of chars, this works.
		for (unsigned char b = 0; b < 10; b++) { // Iterate 0-9
			temp->digitCounts[b] = count(line.begin(), line.end(), (char)(b + 48));
     		}

		// Now we need to insert this in the current array. In a sorted fashion, mind you.
		if (head == nullptr) // CASE: list is empty.
			head = temp;
		else { // CASE: List is not empty.

			// Determine the node we need to insert before.
			LinkedNode *before = head;
			while (before->actualValue < val && before->next != nullptr)
				before = before->next;

			if (before->actualValue < val && before->next == nullptr) { // CASE: insert on tail
				before->next = temp;
				temp->prev = before;
			}
			else { // CASE: insert in the middle or at the head.
				temp->next = before;
				temp->prev = before->prev;

				if (before == head)
					head = temp;

				if (before->prev != nullptr)
					before->prev->next = temp;
				before->prev = temp;
			}
		}
	}

	/* Start of file output */
	
	//Printing ordered list to the outfile.
	LinkedNode* holder = head;
	while(holder != nullptr) {
		
		outFile << holder->value << "\n";

		//Need to specify C++11 for compiling
		outFile << "[0-9]: ";
		for(int k = 0; k < 9; k++)
			outFile << holder->digitCounts[k] << ", ";
		outFile << holder->digitCounts[9] << "\n";

		holder = holder->next;
	}

	//Printing integer value occurrence
	outFile << "There were " << integers << " integer values in the data set.\n";

	//Printing fraction occurrence
	outFile << "There were " << fractions << " fractional values in the data set.\n";

	//Printing first digit occurrence distrivbution.
	outFile << "Distribution of first digit [0-9]: \n";
	for(int j = 0; j < 9; j++)
		outFile << firstDigCount[j] << ", ";
	outFile << firstDigCount[9] << "\n";
  
	outFile.close();
	/*End of file output*/

	//Calling the menu function
	menu(head);

	//Cleanup
	LinkedNode* node = head;
	while(node != nullptr) {
		if(node->next == nullptr) {
			delete node;
			node = nullptr;
		} else {
			node = node->next;
			delete node->prev;
		}
	}
}

void menu(LinkedNode* head) {
	cout << "Entering menu, type 'q' to quit.\n" << endl;
	string input;

	do {
		cout << "Input a set of digits: " << endl;
		cin >> input;

		//Checking for quit.
		if(input.compare("q") == 0 || input.compare("Q") == 0) {
			break;
		}

		//Then here we can call your function or algorithm. 
		//I don't know if we need to check the input, we probably should.
      int total=0;
      LinkedNode* holder=head;
  		std::vector<int> mylist;
    //  int t;
    //  istringstream three(input);
  //		int fiVal;
      
	//	if (!(three >> fiVal))
		//	return ERROR_BAD_FORMAT;
    int t=0;
    //  while(input[t]){
    //  if (isdigit(input[t])){
    /*			for(int j=0; j<input.length(); j++){
      				mylist.push_back(stoi(input[t]));
              cout<<stoi(input[t]);
           }
  		}
  		else{
    		cout<<"not a number";
  		}*/
      mylist.reserve(input.size());
      std::transform(std::begin(input), std::end(input), 
std::back_inserter(mylist), [](char c){
          return c-'0';
        });
  //  t++;
  // }
    
  		LinkedNode* holder2=head;
  //		int nuTotal=0;
  		while(holder2!=nullptr){
    		  int nuTotal=0;
          for(unsigned int u=0; u<mylist.size(); u++){
     			  //int nuTotal=0;
            for(int z=0; z<10; z++){
        			//holder2->digitCounts[z];
              //int nuTotal=0;
               if(mylist[u]==z){
                     //nuTotal+=holder2->digitCounts[z];  
        	        nuTotal+=holder2->digitCounts[z];
                  
              cout<<"number of instances of "<< mylist[u]<<" for actual value "<< holder2->actualValue<<" is "<< holder2->digitCounts[z]<<endl;
            cout<<"nuTotal is "<<nuTotal<<endl;
            }
          
       
    if(nuTotal>total){
      total=nuTotal;
      cout<<"total for"<< holder2->actualValue<<" is "<<total<<endl;
      }}}
    holder2=holder2->next;
  }
  std::list<string> digiStatNum;
  //I can completely see how inefficient this is
  LinkedNode* holder3=head;
  
  while(holder3 != nullptr){
      int nunuTotal=0;
      for(int u=0; u<mylist.size(); u++){
        for(int z=0; z<10; z++){
         if(mylist[u]==z){
            nunuTotal+=holder3->digitCounts[z];
          }
        }
      }
      if(nunuTotal==total){
       
        digiStatNum.push_back(holder3->value);
      }
    holder3=holder3->next;
  }
  digiStatNum.sort();
  for(std::list<string>::iterator z=digiStatNum.begin(); z!=digiStatNum.end(); z++){
      cout<<' '<<*z<<endl;
  } 

	} while(true);
}

