#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"
#include "AVL.h"

using namespace std;

int main(){

	string filename;
	cout << "Please enter the contact file name: \n";
	cin >> filename;

	ifstream file(filename);
	string line;
    
	if (!file.is_open()) {

    cout << "Error opening file.\n";

    }

	else{

		cout << "Loading the phonebook into a BST. \n";

		while (getline(file, line)) { 
		//cout << line << '\n';    
		//while reading every line, load them in the BST according to their first names
			int pos1 = line.find(",");
			int pos2 = line.find(",", pos1+1);
			string FullName = line.substr(0, pos1);
			string phoneNumber = line.substr(pos1+1, pos2-pos1-1);
			string city = line.substr(pos2+1);
			BinaryTreeNode contact = {FullName,phoneNumber,city};
			AddContactToBST(root, FullName, phoneNumber, city);

		}
		
}