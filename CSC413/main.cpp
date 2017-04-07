/****************************************************************************************
*	Title:			CSC413 - Sorting Algorithms											*
*																						*
*	Description:	Demonstrates Insertion Sort, Selection Sort, Merge Sort             *
*					Heapsort, and Quicksort and displays their runtimes					*
*                                                                                       *
*	Author:			Jessica Talbot														*
*                                                                                       *
*	Date:			3/15/17																*
*                                                                                       *
****************************************************************************************/

#include <iostream>			// Provides cin and cout
#include <fstream>			// Provides file access and modification
#include <ctime>			// Provides rand()
#include <cstdlib>			// Provides namespace std
#include <string>			// Provides usage of string variable
#include <algorithm>		// Provides swap function

const int ERROR = 1;
using namespace std;

void step1();
int validInput();
void generateData(int arraySize);
void createFile(string fileName, int *arr, float t);
void displayFile(string fileName);
int createArray(string fileName, int *arr);
void step2();
void step3(string fileName);
void step4(string fileName);
void step5(string fileName);
void insertionSort(int *arr);
void selectionSort(int *arr);
void mergeSort(int *arr, int p, int r);
void merge(int *arr, int p, int q, int r);
void buildHeap(int *arr);
void heapsort(int *arr, int n);
void heapify(int *arr,int n, int i);
void quicksort(int *arr, int p, int r);
void sortAll();
int partition(int *arr, int p, int r);
float processTime(clock_t t);

int num = 0;
int optNum = 0;
int *randArray;

int main()
{
	cout << "Sorting Algorithms!!!\n";
	cout << "---------------------\n\n";
	step1();

	system("Pause");
	return 0;
}

void step1()
{
	cout << "\nEnter a number of integers to generate: ";	// Prompts user to enter a number
	num = validInput();										// Store valid input into num

	generateData(num);										// Generate num random numbers
	cout << "\n\n";
	step2();												// Proceed to next step
}

// Checks for valid user input. If valid, return input.
// If invalid, display error message and reprompt for valid input
int validInput()
{
	int x;
	cin >> x;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cout << "ERROR: Please enter a valid number.\n";
		cout << "Enter a number of integers to generate: ";
		cin >> x;
	}
	return x;
}

// Generate a random number between 0 and 9999 for each element of array
void generateData(int arraySize)
{
	srand(time(NULL));							// Seed rand()
	randArray = new int[arraySize];

	for (int i = 0; i < arraySize; i++)
		randArray[i] = rand() % 9999;
}

// Creates a file for specified sort
void createFile(string fileName, int *arr, float t)
{
	ofstream OutFile;

	OutFile.open(fileName);
	
	if (OutFile.is_open())						// If specified filename is open
	{
		if(fileName == "Data.txt")				// For Data.txt, add the user-specified number as 1st entry
			OutFile << num << "\n";
		for (int i = 0; i < num; i++)			// Add each number of array to a new line
			OutFile << arr[i] << "\n";
		
		OutFile << "\n\n" << t;
		
		OutFile.close();						// Close file
	}
	else
		cout << "\nUnable to open \"" << fileName << "\".\n";
	
}

// Displays specified file contents
void displayFile(string fileName)
{
	string line;
	ifstream InFile;

	InFile.open(fileName);						// Open file

	if (InFile.is_open())
	{
		cout << "\nFile \"" << fileName << "\" contains the following: \n\n";
		while (getline(InFile, line))			// Print each line of the file
			cout << "\t" << line << "\n";
		cout << "\n";

		InFile.close();							// Close file
	}
	else
		cout << "\nUnable to open \"" << fileName << "\".\n";
}

// Create array from file contents
int createArray(string fileName, int *arr)
{
	ifstream inFile;
	int *buff = new int[num];
	int i = 0;
	int x = 0;
	int arrSize;

	inFile.open(fileName);
	if (inFile.is_open())
	{
		while (inFile >> x)
		{
			buff[i] = x;
			i++;
		}
		arrSize = buff[0];

		for (i = 0; i < arrSize; i++)
			arr[i] = buff[i + 1];

		cout << "Successfully created array of " << arrSize << " elements from \"" << fileName << "\".\n\n";

	}
	else
		cout << "Error in creating array.\n\n";

	return arrSize;
}

void step2()
{
	char opt;;

	cout << "You've entered: " << num << ".\n\n";			// Display user input
	cout << "\nSelect from the following options: \n";
	cout << "\t1: Write data file\n";
	cout << "\t2: Enter a different number.\n\n";

	while (1)
	{
		cout << "Enter your selection (1 or 2): ";	
		cin >> opt;											// Store user input into opt

		if (opt == '1')										// If user enters 1
		{
			createFile("Data.txt", randArray, 0);				// Create Data.txt
			step3("Data.txt");								// Continue to step3
		}
		else if (opt == '2')								// If user enters 2
			step1();										// Go back to step1
		else
			cout << "Invalid input.\n\n";					// Display error message for invalid input 
	}
}

void step3(string fileName)
{
	char opt;
	cout << "\n\n" << fileName << " successfully created with " << num << " random integers.\n\n";
	cout << "Select from the following options: \n";
	cout << "\t1: Display Data\n";
	cout << "\t2: Sort Data\n\n";

	while (1)
	{
		cout << "Enter your selection (1 or 2): ";
		cin >> opt;

		if (opt == '1')										// If user enters 1
			displayFile(fileName);							// Display file contents
		else if (opt == '2')								// If user enters 2
			step4(fileName);								// Proceed to step4
		else
			cout << "Invalid input.\n\n";					// Display error message for invalid input
	}
}

void step4(string fileName)
{
	char opt = 0;
	int *sortArr = new int[num];							// Create new array of num integers
	clock_t t;
	float ptime;

	cout << "\n\nSelect from the following options: \n";
	cout << "\t1: Insertion Sort\n";
	cout << "\t2: Selection Sort\n";
	cout << "\t3: Merge Sort\n";
	cout << "\t4: Heapsort\n";
	cout << "\t5: Quicksort\n";
	cout << "\t6: Sort All\n";
	cout << "\t0: Start Over\n\n";

	while (opt != 1 || opt != 2 || opt != 3 || opt != 4 || opt !=5 || opt !=6 || opt !=0)
	{
		cout << "Enter your selection (0-5): ";
		cin >> opt;
		int arrSize = createArray(fileName, sortArr);

		if (opt == '1')									// Proceed to Insertion Sort
		{
			cout << "Begin insertion sort...\n\n";
			t = clock();								// Read clock
			insertionSort(sortArr);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("InsertionSort.txt", sortArr, ptime);
			step5("InsertionSort.txt");
		}
		else if (opt == '2')							// Proceed to Selection Sort
		{
			cout << "Begin selection sort...\n\n";
			t = clock();								// Read clock
			selectionSort(sortArr);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("SelectionSort.txt", sortArr, ptime);
			step5("SelectionSort.txt");
		}
		else if (opt == '3')							// Proceed to Merge Sort
		{
			cout << "Begin merge sort...\n\n";
			t = clock();								// Read clock
			mergeSort(sortArr, 0, num-1);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("MergeSort.txt", sortArr, ptime);
			step5("MergeSort.txt");
		}
		else if (opt == '4')							// Proceed to Heapsort
		{
			cout << "Begin heap sort...\n\n";
			t = clock();								// Read clock
			heapsort(sortArr, num);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("HeapSort.txt", sortArr, ptime);
			step5("HeapSort.txt");
		}
		else if (opt == '5')							// Proceed to Quicksort
		{
			cout << "Begin quicksort...\n\n";
			t = clock();								// Read clock
			quicksort(sortArr, 0, num - 1);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("Quicksort.txt", sortArr, ptime);
			step5("Quicksort.txt");
		}

		else if (opt == '6')
		{
			cout << "Sorting all...\n\n";
			t = clock();								// Read clock
			insertionSort(sortArr);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("InsertionSort.txt", sortArr, ptime);

			t = clock();								// Read clock
			selectionSort(sortArr);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("SelectionSort.txt", sortArr, ptime);

			t = clock();								// Read clock
			mergeSort(sortArr, 0, num - 1);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("MergeSort.txt", sortArr, ptime);

			t = clock();								// Read clock
			heapsort(sortArr, num);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("HeapSort.txt", sortArr, ptime);

			t = clock();								// Read clock
			quicksort(sortArr, 0, num - 1);
			t = clock() - t;							// Measure time elapsed
			ptime = processTime(t);								// Display seconds to complete algorithm
			createFile("Quicksort.txt", sortArr, ptime);
			cout << "All sorts complete\n\n";
			step1();
		}
		else if (opt == '0')
			step1();

		else
			cout << "Invalid input.\n\n";
	}
}

void step5(string fileName)
{
	char opt;

	cout << "Select from the following options:\n\n";
	cout << "\t1: View sorted data\n";
	cout << "\t2: Select a different sorting algorithm\n";
	cout << "\t0: Start over\n\n";

	while (1)
	{
		cout << "Enter your selection (0-2): ";
		cin >> opt;

		if (opt == '1')									// If user enters 1
			displayFile(fileName);						// Display file contents
		else if (opt == '2')							// If user enters 2
			step4("Data.txt");							// Select a different sorting alorithm
		else if (opt == '0')							// If user enters 0
			step1();									// Go back to step 1
		else
			cout << "Invalid input.\n\n";				// Display error message for invalid input
	}
}

/****************************************************************************************/
/*	Algorithm:		Insertion Sort														*/
/*                                                                                      */
/*	Precondition:	arr is a pointer to an unsorted array								*/
/*                                                                                      */
/*	Postcondition:	The elements of arr have been rearranged so that 					*/
/*                  arr[0] <= arr[1] <=...<= arr[num-1]									*/
/*                                                                                      */
/*	Runtime:		Best-case	 - n													*/
/*					Average-case - n^2													*/
/*					Worst-case   - n^2													*/
/*                                                                                      */
/****************************************************************************************/
void insertionSort(int *arr)
{
	for (int j = 1; j < num; j++)
	{
		int key = arr[j];
		int i = j;
		while (i > 0 )
		{ 
			if (arr[i - 1] > key)
			{
				arr[i] = arr[i - 1];
				i--;
			}
			else
				break;
		}
		arr[i] = key;
	}
}
/****************************************************************************************/
/*	Algorithm:		Selection Sort														*/
/*                                                                                      */
/*	Precondition:	arr is a pointer to an unsorted array								*/
/*                                                                                      */
/*	Postcondition:	The elements of arr have been rearranged so that 					*/
/*                  arr[0] <= arr[1] <=...<= arr[num-1]									*/
/*                                                                                      */
/*	Runtime:		Best-case	 - n^2													*/
/*					Average-case - n^2													*/
/*					Worst-case   - n^2													*/
/*                                                                                      */
/****************************************************************************************/

void selectionSort(int *arr)
{
	for (int i = 0; i < num - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < num; j++)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		if (min != i)
			swap(arr[i], arr[min]);
	}
}

/****************************************************************************************/
/*	Algorithm:		Merge Sort															*/
/*                                                                                      */
/*	Precondition:	arr is a pointer to an unsorted array (or subarray)					*/
/*					with at least n1 + n2 elements. The first n1 elements				*/
/*					(from arr[0] to arr[n1-1]) are sorted from smallest to largest,		*/
/*					and the last n2 (from arr[n1] to arr[n1 + n2 - 1]) are also			*/
/*					sorted from smallest to largest.									*/
/*                                                                                      */
/*	Postcondition:	The elements of arr have been rearranged so that 					*/
/*                  arr[0] <= arr[1] <=...<= arr[num-1]									*/
/*                                                                                      */
/*	Runtime:		Best-case	 - n log n												*/
/*					Average-case - n log n												*/
/*					Worst-case   - n log n												*/
/*                                                                                      */
/****************************************************************************************/
// p = left index and r = right index of subarray of arr to be sorted
void mergeSort(int *arr, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;	

		// Sort first and second halves
		mergeSort(arr, p, q);
		mergeSort(arr, q + 1, r);

		merge(arr, p, q, r);
	}
}


// Merges two subarrays of arr[]
// Left subarray is from arr[p..q]
// Right subarray is arr[q+1..r]
void merge(int *arr, int p, int q, int r)
{
	int i, j, k;
	int n1 = q - p + 1;
	int n2 = r - q;

	int *left = new int[n1];
	int *right = new int[n2];

	for (i = 0; i < n1; i++)
		left[i] = arr[p + i];
	for (j = 0; j < n2; j++)
		right[j] = arr[q + 1 + j];

	// Merge left and right arrays back into arr[l..r]

	i = 0; // Initial index of left subarray
	j = 0; // Initial index of right subarray
	k = p; // Initial index of merged subarray

	while (i < n1 && j < n2)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}

	// Copy any remaining elements of left subarray
	while (i < n1)
	{
		arr[k] = left[i];
		i++;
		k++;
	}

	// Copy any remaining elements of right subarray
	while (j < n2)
	{
		arr[k] = right[j];
		j++;
		k++;
	}
	
	// Release allocated memory
	delete[] left;
	delete[] right;
}

/****************************************************************************************/
/*	Algorithm:		Heapsort															*/
/*                                                                                      */
/*	Precondition:	arr is a pointer to an unsorted array								*/
/*                                                                                      */
/*	Postcondition:	The elements of arr have been rearranged so that 					*/
/*                  arr[0] <= arr[1] <=...<= arr[num-1]									*/
/*                                                                                      */
/*	Runtime:		Best-case	 - 	log n												*/
/*					Average-case - 	n log n												*/
/*					Worst-case   - 	n log n												*/
/*                                                                                      */
/****************************************************************************************/

void buildHeap(int *arr)
{
	for (int i = ((num / 2) - 1); i >= 0; i--)
		heapify(arr, num, i);
}

int parent(int i)
{
	return i / 2;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return (2 * i) + 2;
}
void heapify(int *arr, int n, int i)
{
	int largest;

	int l = left(i);
	int r = right(i);
	if (l < n && arr[l] > arr[i])
		largest = l;
	else
		largest = i;

	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}


void heapsort(int *arr, int n)
{
	buildHeap(arr);

	for (int i = n - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

/****************************************************************************************/
/*	Algorithm:		Quicksort															*/
/*                                                                                      */
/*	Precondition:	arr is a pointer to an unsorted array								*/
/*                                                                                      */
/*	Postcondition:	The elements of arr have been rearranged so that 					*/
/*                  arr[0] <= arr[1] <=...<= arr[num-1]									*/
/*                                                                                      */
/*	Runtime:		Best-case	 - n log n (even splits)								*/
/*					Average-case - n log n (balanced splits)							*/
/*					Worst-case   - n^2	   (sorted data)								*/
/*                                                                                      */
/****************************************************************************************/
void quicksort(int *arr, int p, int r)
{
	if (p < r)							// If there is more than 1 element
	{	
		int q = partition(arr, p, r);	// Call partition; assign return value to q
		quicksort(arr, p, q - 1);		// Pass left partition to quicksort
		quicksort(arr, q + 1, r);		// Pass right partition to quicksort
	}
}

void sortAll()
{

}

int partition(int *arr, int p, int r)
{
	int pivot = arr[r];				// Set last value in array to pivot
	int i = p - 1;					// Set partition to be before first value

	for (int j = p; j < r; j++)		// Loop from first index up to pivot (not inclusive)
	{
		if (arr[j] <= pivot)		// If value in arr[j] < pivot
		{
			i++;					// Move partition wall
			swap(arr[i], arr[j]);	// Swap values in arr[i] and arr[j]
		}
	}
	swap(arr[i + 1], arr[r]);		// Swap pivot value with first number past the partition

	return i + 1;					// Return index location of where pivot ended up
}

float processTime(clock_t tm)
{
	float ft = static_cast <float>(tm) / CLOCKS_PER_SEC;		// Convert to float
	cout << "\nTime: " << ft << " seconds\n";
}
