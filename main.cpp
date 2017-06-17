
//22C - Manish Goel
//Extra Credit Lab - recursion based quick sort, merge sort, insertion sort
//Lab Partners: Alexander McNulty, Clifford Smith

/*
this program sorts and array of intergers given by the user of no more than 32 integers in the array
the program will sort the array 3 times using Merge Sort, Insertion Sort, and Quick Sort
during each sorting algorithem the array being sorted will be printed to screen  and a txt document
RECURSIVE FUNCTIONS - all sorting functions for this program can be found above main() in main.cpp
INPUT HANDLING - will be found in Globals.h
*/


#include<iostream>
#include<string>
#include<fstream>
//#include"Globals.h"

using namespace std;
int ARRAY_SIZE;
int getIntegerInput();
int getMenuInput(int);

//declaration of the recursive printing function
void recursiveCP(int *a, int n, ofstream &file, int called = 0);

//declaration for recrusive insertion sort
void insertionSort(int *a, int n, ofstream &file);
void RISA(int *a, int n, ofstream &file, int value, int hole, int i = 0);
int RISB(int *a, int n, ofstream &file, int value, int hole);

//declaration for the recursive quick sort
void QuickSort(int *A, int start, int end, ofstream &file, int size);
int PartitionA(int *A, int start, int end, ofstream &file, int size);
int PartitionB(int *A, int start, int end, ofstream &file, int pivot, int pIndex, int i, int size);


/*
void MergeSort();
//L = the left array which was split from the main array
//R = the right array which was split from the main array
//A = the main array
void Merge(int *L, int *R, int *A);
//SubMerge, does the job of an interative merge, recursively
//those submerge must hold the values for I and J
//this variableswhich hold the index of the next value which must be merged
void SubMerge(int *L, int *R, int *A, int i, int j);
void merge(int *L, int *R, int *A){
int i, j, nL, nR;
nL =
if
}
void MergeSort(){
}
*/


int main()
{
	//acquire the size of the array from the user 
	//then create a dynamically sized array in the heap

	int SORT_MAX_SIZE;
	int tempNumber;
	int *dynamicArray = nullptr;

	// prompt user for the array size
	cout << "enter in the array size, only positive numbers of 32 or less is valid\n";
	cout << "array size: ";
	SORT_MAX_SIZE = getIntegerInput();

	// check the SORT_MAX_SIZE number is a valid choice
	while (SORT_MAX_SIZE > 32 || SORT_MAX_SIZE < 1)
	{
		if (SORT_MAX_SIZE > 32)
		{
			cout << "the array size cannot be greater than 32, try again\n";
			cout << "array size: ";
			SORT_MAX_SIZE = getIntegerInput();
		}
		else
		{
			cout << "the array size cannot be less than 1, try again\n";
			cout << "array size: ";
			SORT_MAX_SIZE = getIntegerInput();
		}
	}

	ARRAY_SIZE = SORT_MAX_SIZE;
	dynamicArray = new int[SORT_MAX_SIZE];

	// prompt user for the values of the array elements
	for (int count = 0; count < SORT_MAX_SIZE; count++)
	{
		cout << "enter in the value for element [" << count << "] of the array: ";
		tempNumber = getIntegerInput();
		dynamicArray[count] = tempNumber;
	}


	// create and open a file
	ofstream myfile;
	myfile.open("EC_Lab.txt");


	// prompt user to select the sort of choice
	int menuChoice;
	cout << endl << endl;
	cout << "Choose one of the three options to sort the array\n";
	cout << "1: Insertion Sort\n";
	cout << "2: Quick Sort\n";
	cout << "3: Merge Sort\n";
	cout << "enter your choice: ";
	menuChoice = getMenuInput(3);
	if (menuChoice == 1)
	{
		cout << "array contents before sorting: ";
		for (int count = 0; count < SORT_MAX_SIZE; count++)
		{
			cout << dynamicArray[count] << " ";
		}
		cout << endl;
		//insertionSort(dynamicArray, 0, (SORT_MAX_SIZE - 1));
		insertionSort(dynamicArray, SORT_MAX_SIZE, myfile);
		cout << "\narray contents after sorting: ";
		for (int count = 0; count < SORT_MAX_SIZE; count++)
		{
			cout << dynamicArray[count] << " ";
		}
		cout << endl;
	}
	else if (menuChoice == 2)
	{
		//quickSort(dynamicArray, 0, (SORT_MAX_SIZE - 1));
		QuickSort(dynamicArray, 0, (SORT_MAX_SIZE - 1), myfile, SORT_MAX_SIZE);
		cout << "\narray contents after sorting: ";
		for (int count = 0; count < SORT_MAX_SIZE; count++)
		{
			cout << dynamicArray[count] << " ";
		}
		cout << endl;
	}
	else
	{
		//mergeSort(dynamicArray, 0, (SORT_MAX_SIZE - 1));
		cout << "\narray contents after sorting: ";
		for (int count = 0; count < SORT_MAX_SIZE; count++)
		{
			cout << dynamicArray[count] << " ";
		}
		cout << endl;
	}

	cout << "press <enter> to exit...";
	cin.get();
	delete[]dynamicArray;
	return 0;



	////CALL QUICK SORT
	//cout << endl << "printing - QUICK SORT" << endl;
	//myfile << endl << "printing - QUICK SORT" << endl;
	//QuickSort(B, 0, size - 1, myfile, size);

	////CALL MERGE SORT
	////cout << endl << "printing - MERGE SORT" << endl;
	////myfile << endl << "printing - MERGE SORT" << endl;
	//cout << endl << "MERGE SORT WAS NOT COMPLETED!! -  CHECK MAIN.CPP TO SEE UNFINISHED WORK" << endl;
	//myfile << endl << "MERGE SORT WAS NOT COMPLETED!! -  CHECK MAIN.CPP TO SEE UNFINISHED WORK" << endl;


	myfile.close();

	cout << "press <enter> to exit...";
	cin.get();
	delete[]dynamicArray;
	return 0;
}















//recursiveCP is short for "recursive cout and print"
//this will be used to print sorting functions at each step to screen and the file
void recursiveCP(int *a, int n, ofstream &file, int called)
{
	cout << a[called] << " ";
	file << a[called] << " ";
	called++;
	//base case for void print function
	if (called == n)
	{
		cout << endl;
		file << endl;
	}
	//if base case not triggered increment called and call recursiveCP again
	else
	{
		recursiveCP(a, n, file, called);
	}
}



//RECURSIVE INSERTION SORT:
//takes an array and the number of element in the array
void QuickSort(int *A, int start, int end, ofstream &file, int size)
{
	int pIndex;
	if (start < end)
	{
		pIndex = PartitionA(A, start, end, file, size);
		QuickSort(A, start, pIndex - 1, file, size);
		QuickSort(A, pIndex + 1, end, file, size);

	}
}
//Partition A will find the pivot point, then swap with pIndex and pivot
//after all lesser values have been placed behind pindex
int PartitionA(int *A, int start, int end, ofstream &file, int size)
{
	int pivot = A[end];
	int pIndex = start;
	int temp;
	int i = start;
	pIndex = PartitionB(A, start, end, file, pivot, pIndex, i, size);
	//cout << "A";
	recursiveCP(A, size, file);
	temp = A[pIndex];
	A[pIndex] = A[end];
	A[end] = temp;
	//cout << "B";
	recursiveCP(A, size, file);

	return pIndex;
}
//Partition B is responsible for interating through the partitioned array
//When B makes a swap it is placing all values that are less than the pivot behind the pIndex
//the pindex and the point will then be swaped in partition A after the base case is called.
int PartitionB(int *A, int start, int end, ofstream &file, int pivot, int pIndex, int i, int size)
{
	if (i < end)
	{
		int temp;
		if (A[i] <= pivot)
		{
			//cout << "C";
			recursiveCP(A, size, file);
			temp = A[i];
			A[i] = A[pIndex];
			A[pIndex] = temp;
			pIndex++;
			//cout << "D";
			recursiveCP(A, size, file);
		}
		i++;
		pIndex = PartitionB(A, start, end, file, pivot, pIndex, i, size);
	}
	return pIndex;
}





//RECURSIVE INSERTION SORT:
//takes an array and the number of element in the array
void insertionSort(int *a, int n, ofstream &file)
{
	int value = 0;
	int hole = 0;
	RISA(a, n, file, value, hole);
	recursiveCP(a, n, file);
}
//RISA - recursive insertion sort part A 
//moves the whole throught the array
void RISA(int *a, int n, ofstream &file, int value, int hole, int i)
{
	value = a[i];
	hole = i;
	recursiveCP(a, n, file);
	hole = RISB(a, n, file, value, hole);
	a[hole] = value;
	i++;
	if (i != n)
	{
		RISA(a, n, file, value, hole, i);
	}
}
//RISB  - recursive insertion sort part B 
//places the correct value into the whole
int RISB(int *a, int n, ofstream &file, int value, int hole)
{
	if (hole > 0 && a[hole - 1] > value)
	{
		a[hole] = a[hole - 1];
		hole = hole - 1;
		recursiveCP(a, n, file);
		hole = RISB(a, n, file, value, hole);
	}
	return hole;
}


//  Filter out any bad <int> input
int getIntegerInput()
{
	int number;
	std::string inputString;
	bool hasAlphaChars = false;
	getline(std::cin, inputString);
	for (unsigned int count = 0; count < (inputString.length()); count++)
		if (isdigit(inputString[count]) == 0)
		{
			hasAlphaChars = true;
		}
	while (hasAlphaChars || inputString == "\0" || inputString[0] == '-')
	{
		hasAlphaChars = false;
		std::cout << "only postive whole numbers are valid, try again: ";
		getline(std::cin, inputString);
		for (unsigned int count = 0; count < (inputString.length()); count++)
		{
			if (isdigit(inputString[count]) == 0)
			{
				hasAlphaChars = true;
			}
		}
	}
	number = stoi(inputString);
	return number;
}

// get the choice for menu input
int getMenuInput(int size)
{
	int userInput = 0;
	std::string tempString;
	getline(std::cin, tempString);
	while ((tempString[0] < 49 || tempString[0] > (48 + size)) || tempString[1] != '\0')
	{
		std::cout << "1 - " << size << " are the only valid choices, try again: ";
		getline(std::cin, tempString);
	}
	userInput = stoi(tempString);
	return userInput;
}