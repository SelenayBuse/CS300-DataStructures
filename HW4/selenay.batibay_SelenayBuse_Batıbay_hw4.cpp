#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include "BST.h"
#include "quadraticHASH.h"
using namespace std;

// IMPORTANT NOTE: most of the command lines which begins with "cout" used for debugging the code



void to_upper(string& str) { // it is taken from "https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case?page=1&tab=scoredesc#tab-top" to make strings upper case.
	string::iterator it;
	int i;
	for (i = 0; i < str.size(); ++i) {
		((char*)(void*)str.data())[i] = toupper(((char*)str.data())[i]);
	}
}

bool readingFile(string fileName, BinarySearchTree<PhoneInfo>& BSTtree, HashTable<PhoneInfo>& HT) // // it is built to read the file and push the elements into the BST and Hashtable
{
	int count = 0;
	PhoneInfo tempPI;
	ifstream in;
	in.open(fileName.c_str());
	string line, word;
	if (in.fail())
	{
		cout << "Error: The file cannot be opened!" << endl;
		return false;
	}
	else
	{

		while (getline(in, line))
		{
			//cout << line << endl;
			istringstream iLine(line);
			while (iLine >> word)
			{
				if (count == 0)
				{
					//to_upper(word);
					tempPI.name = word;
				}
				else if (count == 1)
				{
					//to_upper(word);
					tempPI.surname = word;
				}
				else if (count == 2)
				{
					tempPI.phoneNum = word;
				}
				else if (count == 3)
				{
					tempPI.city = word;
				}
				count++;
			}
			count = 0;
			//cout << tempPI << endl;
			BSTtree.insert(tempPI);
			HT.insert(tempPI);
			//cout<< "inserted: " << tempPI << endl;
			
		}

		return true;
	}
}




int main()

{
	PhoneInfo First("", "", "", "");  // it is simply "notfound" element
	BinarySearchTree<PhoneInfo> MainTree(First);
	HashTable<PhoneInfo> mainHT(First);
	string fileName, personName, names, fname = "", sname = "";
	cout << "Enter the filename: ";
	cin >> fileName;

	if(readingFile(fileName, MainTree, mainHT) == true){

		//MainTree.printTree();
		mainHT.printLoadFt();

		int answer;
		answer = 0;

		while (answer != 4) {

			cout << "\nChoose which action to perform from 1 to 6:\n";
			cout << "1 - Search a phonebook contact\n";
			cout << "2 - Adding a phonebook contact\n";
			cout << "3 - Deleting a phonebook contact\n";
			cout << "4 - Press 4 to exit\n";
			cin >> answer;

			if (answer == 1) {

				cout << "Enter name to search for: ";
				cin.ignore();
				getline(cin, personName);

				istringstream ss(personName);
				int count = 0;
				while (ss >> names)
				{
					//cout << "names: " << names << endl;
					count++;
					if (count == 1)
					{
						fname = names;
					}
					else if (count == 2)
					{
						sname = names;
					}

				}
				//mainHT.writeStu();
				//cout << fname << "    " << sname << endl;
				PhoneInfo wantedOne(fname, sname, "", "");
				cout << endl << "Searching for an item in the phonebook (BST)..." << endl;
				cout << "Phonebook: Searching for: (" << fname << sname << ")" << endl;
				cout << "====================================" << endl;
				PhoneInfo* outBST = MainTree.findElement(wantedOne);
				cout << outBST->name << " " << outBST->surname << " "
					<< outBST->city << " " << outBST->phoneNum << endl << endl;

				cout << "Searching for an item in the phonebook (HashTable)..." << endl;
				cout << "Phonebook: Searching for: (" << fname << sname << ")" << endl;
				cout << "====================================" << endl;
				PhoneInfo* outHT = mainHT.find(wantedOne);



				cout << outHT->name << " " << outHT->surname << " "
					<< outHT->city << " " << outHT->phoneNum << endl;


				int k = 500;
				auto start = chrono::high_resolution_clock::now();
				for (int i = 0; i < k; i++) {
					// FindContact(withBST);
					MainTree.find(wantedOne);
				}

				auto BSTTime = chrono::duration_cast<std::chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);
				cout << "\nBSTSearchTime: " << BSTTime.count() / k << "\n";

				start = chrono::high_resolution_clock::now();
				for (int i = 0; i < k; i++) {
					// FindContact(withhashtable);
					mainHT.find(wantedOne);
				}

				auto hashtableTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);
				cout << "HashTableSearchTime: " << hashtableTime.count() / k << "\n";
				cout << "Speed Up: " << double(BSTTime.count()) / hashtableTime.count() << endl;




			} // ifin parantezi


			if (answer == 2) { //adding contact

				typedef chrono::high_resolution_clock Clock;

				cout << "Enter the information of the contact to be added: \n";
				string phonenumber; string city;

				cout << "Name: "; cin >> fname >> sname;
				cout << "Tel: "; cin >> phonenumber;
				cout << "City: ";  cin >> city;

				cout << "Adding an item to the phonebook BST . . .\n";

				//adding item to BST

				auto startTime = Clock::now();

				PhoneInfo toBeAddedOne(fname, sname, phonenumber, city);
				MainTree.insert(toBeAddedOne);

				auto endTime = Clock::now();
				chrono::nanoseconds bstDuration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);

				cout << "====================================\n";
				cout << "Contact has been added successfully to the BST Tree\n";


				/// ///////////////////////////////////////////////////////////////////////////////////////////////////////

				//adding item to Hashtable

				cout << "Adding an item to the phonebook (Hashtable) . . .\n";
				cout << "====================================\n";

				startTime = Clock::now();
				PhoneInfo toBeAdded(fname, sname, phonenumber, city);
				mainHT.insert(toBeAdded);
				endTime = Clock::now();

				chrono::nanoseconds htDuration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime);
				cout << "Contact has been added successfully to the Hashtable\n";

				cout << "Adding a contact to the Binary Tree took " << bstDuration.count() << " nanoseconds\n";
				cout << "Adding a contact to the Hashtable took " << htDuration.count() << " nanoseconds\n";

			}

			if (answer == 3) { // deleting

				typedef chrono::high_resolution_clock Clock;
				cout << "\nDeleting an item from the phonebook . . .\n";
				cout << "Enter the full name of the contact to be deleted: ";

				cin >> fname >> sname;
				PhoneInfo deletedOne(fname, sname, "", "");
				//cout << deletedOne;

				auto startTimeBST = Clock::now();
				MainTree.remove(deletedOne);
				auto endTimeBST = Clock::now();

				auto startTimeHT = Clock::now();
				mainHT.remove(deletedOne);
				auto endTimeHT = Clock::now();

				chrono::nanoseconds bstDuration = chrono::duration_cast<chrono::nanoseconds>(endTimeBST - startTimeBST);
				chrono::nanoseconds htDuration = chrono::duration_cast<chrono::nanoseconds>(endTimeHT - startTimeHT);

				cout << "Deleted succcessfully. . .\n" << endl;
				cout << "Deletion from the Binary Tree took " << bstDuration.count() << " nanoseconds. . .\n";
				cout << "Deletion from the Hashtable took " << htDuration.count() << " nanoseconds. . .\n";

			} // if = 3 parantezi


		}


	} // dýs while'in parantezi


} // int mainin parantezi