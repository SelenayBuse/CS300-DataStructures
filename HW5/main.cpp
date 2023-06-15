#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "PhoneInfo.h"


using namespace std;

bool readingFile(string fileName, BinarySearchTree<PhoneInfo>& BSTtree) { // // it is built to read the file and push the elements into the BST
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
			//cout<< "inserted: " << tempPI << endl;

		}

		return true;
	}
}


vector<PhoneInfo> readingFileintoArray(string filename) {

	vector<PhoneInfo> phoneInfoList = {};
	ifstream file(filename);

	if (file.is_open()) {

		string line;
		while (getline(file, line)) {

			stringstream ss(line);
			string name, surname, phoneNum, city;
			ss >> name >> surname >> phoneNum >> city;

			PhoneInfo newPhoneInfo(name, surname, phoneNum, city);
			phoneInfoList.push_back(newPhoneInfo);

		}

		file.close();
	}

	return phoneInfoList;

}


// HELPER FUNCTIONS


int findingTheMedian(vector<PhoneInfo>& PhoneInfoList, int low, int high) {

	int mid = low + (high - low) / 2;

	if (PhoneInfoList[low].name > PhoneInfoList[mid].name) {
		swap(PhoneInfoList[low], PhoneInfoList[mid]);
	}

	if (PhoneInfoList[mid].name > PhoneInfoList[high].name) {
		swap(PhoneInfoList[mid], PhoneInfoList[high]);
	}

	if (PhoneInfoList[low].name > PhoneInfoList[mid].name) {
		swap(PhoneInfoList[low], PhoneInfoList[mid]);
	}

	return mid;

}


vector<string> substringFinder(const string& inputString, char endWRT) {
	vector<string> substrings;
	string substring;
	stringstream ss(inputString);

	while (getline(ss, substring, endWRT)) {
		substrings.push_back(substring);
	}

	return substrings;
}


int partition(vector<PhoneInfo>& PhoneInfoList, int low, int high) {

	PhoneInfo pivot = PhoneInfoList[low];
	int i = low + 1;
	int j = high;

	while (true) {
		while (i <= j && PhoneInfoList[i].name <= pivot.name) {
			i++;
		}
		while (j >= i && PhoneInfoList[j].name > pivot.name) {
			j--;
		}
		if (i > j) {
			break;
		}
		swap(PhoneInfoList[i], PhoneInfoList[j]);
	}

	swap(PhoneInfoList[low], PhoneInfoList[j]);

	return j;
}


void merge(vector<PhoneInfo>& PhoneInfoList, int lowerBound, int middle, int upperBound) {
	if (PhoneInfoList[middle].name <= PhoneInfoList[middle + 1].name) { // if already sorted

		return;
	}

	int leftSt = lowerBound; int leftEnd = middle; int rightSt = middle + 1; int rightEnd = upperBound;

	while (leftSt <= leftEnd && rightSt <= rightEnd) {

		if (PhoneInfoList[leftSt].name <= PhoneInfoList[rightSt].name) {
			leftSt++;
		}

		else {
			PhoneInfo temp = PhoneInfoList[rightSt];

			for (int i = rightSt; i > leftSt; i--) {
				PhoneInfoList[i] = PhoneInfoList[i - 1];
			}

			PhoneInfoList[leftSt] = temp;

			leftSt++;
			leftEnd++;
			rightSt++;
		}
	}


}


void heapify(vector<PhoneInfo>& PhoneInfoList, int j, int i) {

	int upper = i; int leftElem = 2 * i + 1; int rightElem = 2 * i + 2;

	if (leftElem < j && PhoneInfoList[leftElem].name > PhoneInfoList[upper].name) {
		upper = leftElem;
	}

	if (rightElem < j && PhoneInfoList[rightElem].name > PhoneInfoList[upper].name) {
		upper = rightElem;
	}

	if (upper != i) {
		swap(PhoneInfoList[i], PhoneInfoList[upper]);
		heapify(PhoneInfoList, j, upper);
	}

}





				// SORTING ALGOS


void insertionSort(vector<PhoneInfo>& PhoneInfoList) {
	int PhoneInfoNum = PhoneInfoList.size();
	for (int i = 1; i < PhoneInfoNum; i++) {
		PhoneInfo key = PhoneInfoList[i];
		int j = i - 1;

		while (j >= 0 && PhoneInfoList[j].name > key.name) {
			PhoneInfoList[j + 1] = PhoneInfoList[j];
			j--;
		}

		PhoneInfoList[j + 1] = key;
	}

	//cout << "insertion sort calisiyor\n";
}


void quickSort(vector<PhoneInfo>& PhoneInfoList, int low, int high) { // burda sýkýntý var

	if (low < high) {
		if (high - low + 1 < 10) {
			insertionSort(PhoneInfoList);
			return;
		}

	int pivotIndex = partition(PhoneInfoList, low, high);
	quickSort(PhoneInfoList, low, pivotIndex - 1);
	quickSort(PhoneInfoList, pivotIndex + 1, high);

	}

	//cout << "quick sort calisiyor\n";
}


void mergeSort(vector<PhoneInfo>& PhoneInfoList, int low, int high) {
	if (low < high) {
		if (high - low + 1 < 10) {
			insertionSort(PhoneInfoList);
			return;
		}

		int mid = low + (high - low) / 2;
		mergeSort(PhoneInfoList, low, mid);
		mergeSort(PhoneInfoList, mid + 1, high);
		merge(PhoneInfoList, low, mid, high);
	}

	//cout << "Merge sort calisiyor\n";
}


void heapSort(vector<PhoneInfo>& PhoneInfoList) {
	int listSize = PhoneInfoList.size();

	for (int i = listSize / 2 - 1; i >= 0; i--) {
		heapify(PhoneInfoList, listSize, i);
	}

	for (int i = listSize - 1; i > 0; i--) {
		swap(PhoneInfoList[0], PhoneInfoList[i]);
		heapify(PhoneInfoList, i, 0);
	}

	//cout << "heap sort calisiyor\n";
}


					//  SEARCH ALGOS

double seqSearch(const vector<PhoneInfo>& PhoneInfoList, const string& ToBeSearched) { // calculation included

	bool isFound = false;
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < PhoneInfoList.size(); i++) {
		if ((PhoneInfoList[i].name.find(ToBeSearched) != string::npos) || (PhoneInfoList[i].surname.find(ToBeSearched) != string::npos) || (PhoneInfoList[i].city.find(ToBeSearched) != string::npos) || (PhoneInfoList[i].phoneNum.find(ToBeSearched) != string::npos)) {
			cout << PhoneInfoList[i].name <<" " << PhoneInfoList[i].surname << " " << PhoneInfoList[i].city << " " << PhoneInfoList[i].phoneNum << endl;
			isFound = true;
		}

	}

	if (isFound == false) {
		cout << ToBeSearched << " does NOT exist in the dataset\n";
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

	cout << "\nSequential Search Time: " << duration.count() << " Nanoseconds\n";

	return static_cast<double>(duration.count());

}

double binarySearch(const vector<PhoneInfo>& PhoneInfoList, const string& ToBeSearched) {
	int left = 0;
	int right = PhoneInfoList.size() - 1;
	bool isfound = false;

	auto start = chrono::high_resolution_clock::now();
	while (left <= right) {
		int middle = left + (right - left) / 2;

		if (PhoneInfoList[middle].name.find(ToBeSearched) != string::npos ||
			PhoneInfoList[middle].surname.find(ToBeSearched) != string::npos ||
			PhoneInfoList[middle].city.find(ToBeSearched) != string::npos ||
			PhoneInfoList[middle].phoneNum.find(ToBeSearched) != string::npos) {
			cout << PhoneInfoList[middle].name << " " << PhoneInfoList[middle].surname << " "
				<< PhoneInfoList[middle].city << " " << PhoneInfoList[middle].phoneNum << endl;
			isfound = true;
		}

		if (PhoneInfoList[middle].name == ToBeSearched) {
			cout << PhoneInfoList[middle].name << " " << PhoneInfoList[middle].surname << " "
				<< PhoneInfoList[middle].city << " " << PhoneInfoList[middle].phoneNum << endl;
			isfound = true;
		}
		else if (PhoneInfoList[middle].name < ToBeSearched) {
			left = middle + 1;
			isfound = true;

		}
		else {
			right = middle - 1;
			isfound = true;
		}
	}


	if (isfound == false) {
		cout << ToBeSearched << " does NOT exist in the dataset\n";
	}

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

	cout << "\nBinary Search Time: " << duration.count() << " Nanoseconds\n";

	return static_cast<double>(duration.count());

}


				
					// MAIN FUNC


int main() {

	PhoneInfo First("", "", "", "");  // it is simply "notfound" element
	BinarySearchTree<PhoneInfo> MainTree(First);
	string fileName, personName, names, fname = "", sname = "";

	cout << "Please enter the contact file name: ";
	cin >> fileName;

	if (readingFile(fileName, MainTree)) {
		
		vector<PhoneInfo> phoneInfoList = readingFileintoArray(fileName); // creating the main PhoneInfo array

		//  different copies for each sorting algos
		vector<PhoneInfo> quickSortPhoneList = phoneInfoList;
		vector<PhoneInfo> insertionSortPhoneList = phoneInfoList;
		vector<PhoneInfo> mergeSortPhoneList = phoneInfoList;
		vector<PhoneInfo> heapSortPhoneList = phoneInfoList;

		string word;
		cout << "Please enter the word to be queried : ";
		cin >> word;

		cout << "\nSorting the vector copies\n";
		cout << "======================================\n";



		// Measure execution time for Quick Sort
		auto start = chrono::high_resolution_clock::now();
		quickSort(quickSortPhoneList, 0, quickSortPhoneList.size() - 1);
		auto stop = chrono::high_resolution_clock::now();
		auto QuickSortduration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
		cout << "Quick Sort Time: " << QuickSortduration.count() << " Nanoseconds" << endl;



		// Measure execution time for Insertion Sort
		start = chrono::high_resolution_clock::now();
		insertionSort(insertionSortPhoneList);
		stop = chrono::high_resolution_clock::now();
		auto InsertionSortduration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
		cout << "Insertion Sort Time: " << InsertionSortduration.count() << " Nanoseconds" << endl;



		// Measure execution time for Merge Sort
		start = chrono::high_resolution_clock::now();
		mergeSort(mergeSortPhoneList, 0, mergeSortPhoneList.size() - 1);
		stop = chrono::high_resolution_clock::now();
		auto MergeSortduration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
		cout << "Merge Sort Time: " << MergeSortduration.count() << " Nanoseconds" << endl;



		// Measure execution time for Heap Sort
		start = chrono::high_resolution_clock::now();
		heapSort(heapSortPhoneList);
		stop = chrono::high_resolution_clock::now();
		auto HeapSortduration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
		cout << "Heap Sort Time: " << HeapSortduration.count() << " Nanoseconds" << endl<<endl;


		cout << "Searching for " << word << "\n";
		cout << "======================================\n";

		binarySearch(phoneInfoList, word); cout << endl;

		cout << "Search results for Sequential Search:\n";
		seqSearch(phoneInfoList, word); cout << endl;
		

		double IQ = static_cast<double>(InsertionSortduration.count()) / QuickSortduration.count();
		double MQ = static_cast<double>(MergeSortduration.count()) / QuickSortduration.count();
		double HQ = static_cast<double>(HeapSortduration.count()) / QuickSortduration.count();
		double SeqBin = seqSearch(phoneInfoList, word) / binarySearch(phoneInfoList, word);

		cout << "\nSpeedUp between Search Algorithms" << endl;
		cout << "======================================" << endl;
		cout << "(Sequential Search/ Binary Search) SpeedUp = " << SeqBin << endl ;

		cout << "\nSpeedUp between Sort Algorithms" << endl;
		cout << "======================================" << endl;
		cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << IQ << endl;
		cout << "(Merge Sort / Quick Sort) SpeedUp = " << MQ << endl;
		cout << "(Heap Sort / Quick Sort) SpeedUp = " << HQ << endl;



	}

	return 0;
}