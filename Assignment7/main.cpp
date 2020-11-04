	/*/////////////////////////////////////////////////////////////////////
	Authored by @BalkanBasileus.										
																		
	CS202	 
														 
																		 
	The following C++ code utilizes pointers.							 
	The following C++ code reads in a file containing 5 matrixes. The 	 
	code will read in the size of each matrix and populates it with		 
	true/false values. Afterwards it checks for symmetry on both the x 	 
	and y axis. If both are symmetries exits, it will output "YES", 	 
	otherwise "NO". Finally it deallocates each matrix.					 
																		 
	Files: 1)main 														 
		     2)A07.txt													 
																		 
	/////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <fstream>
using namespace std;

//FUNCTIONS
void processMatrix(bool **m, int size, ifstream& in);
bool testSymmetry(bool **m, int size);
void deleteMatrix(bool **m, int size);

//MAIN
int main(int argc, char const *argv[])
{

	//File input
	ifstream inFile;
	ofstream outFile;
	string fileName;

	//Input File variables.	
	int t;
	bool **m;
	int size;
	
	//Read file.
	//Read in a char from input.

	do{//open file
    cout << "Enter the input file: "; 
    cin >> fileName;
    inFile.open(fileName.c_str());
  } while(!inFile.is_open());
  
  	inFile >> t; 

  	//Test

  	//For loop to read M

  	for(int i = 0;i<t;i++)
  	{
  		//read in size next matrix from file 
  		
  		inFile >> size;
  		m = new bool*[size];

  		//process matrix
  		processMatrix(m,size,inFile);
  		
  		//test symmetry
  		if(testSymmetry(m,size)==true)
  		{
  			cout << "Test case " << i << ": YES" << endl;
  		}
  		else
  		{
  			cout << "Test case " << i << ": No" << endl;
  		}

  		//delete matrix
  		deleteMatrix(m,size);
  	}
	inFile.close(); //Close file.


	return 0;
}

void processMatrix(bool **m, int size, ifstream& in)
{
	char c;

	for(int i = 0;i<size;i++)
	{
		m[i] = new bool[size];
	
		for(int j = 0;j<size;j++)
		{
			in >> c;
			if(c == '1')
			{
				m[i][j] = true;
			}
			else if(c == '0')
			{
				m[i][j] = false;
			}
		}
	}
}

bool testSymmetry(bool **m, int size)
{	
	//x-plane
	int i = 0;
	int j = size-1;
	//y-plane
	int p = 0;
	int q = size-1;

	//Nested for loop
	//[itr][p]!=[itr][q] not symmetric

	//every time leave outer loop, reset q.
	while(i<=j)
	{
		p = 0;
		q = size-1;

		while(p<=q)
		{		//upper quadrants		lower quadrants			upper left and lower left quad
			if(m[i][q]!=m[i][p] || m[j][q]!=m[j][p] || m[i][p]!=m[j][p])
			{
				return false;
			}
			p++;
			q--;
		}
		i++;
		j--;
	}
	return true;
}

//Deallocate matrix.
void deleteMatrix(bool **m, int size)
{	
	for(int i = 0;i<size;i++)
	{
		delete [] m[i];
	}
	delete [] m;
}
