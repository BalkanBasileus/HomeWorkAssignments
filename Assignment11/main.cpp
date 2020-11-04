/*//////////////////////////////////////////////////////////////////////////////////
Authored by @BalkanBasileus.

Class: CS 302

The following code implements a depth first search across a two dimensional array.
It reads in a file and asks the user for a particular node. It then outputs all 
of the nodes that are connected to that particular node.
//////////////////////////////////////////////////////////////////////////////////*/

#include<iostream>
#include<stdlib.h> //Used for exit function 'exit(0)'.
#include<fstream>  
using namespace std;

//Function Declerations
void dfs(bool **arr,int n,bool booleanGrid[],int start);



//MAIN
//////////////////////////////////////////////////////////////////////////////////

int main()
{
  
  //Open and read file.
  fstream infile("textFile.txt",ios::in);
  int n;
  
  //Read input from the first line
  infile >> n;
  bool booleanGrid[n];
      
  //Create a two dimensional array and store adjacency values
  bool **arr = new bool*[n];
  
  for(int i=0; i<n; ++i)
  {
    booleanGrid[i] = false;
    arr[i] = new bool[n];
  }
  
  //Read all of the input
  for(int i=0; i<n; ++i)
  {
    for(int j=0;j<n;++j)
    {
      infile >> arr[i][j];
    }
  }
  
  //Check the diagonal elements of the matrix
  for(int i=0; i<n; ++i)
  {
    if(arr[i][i]!=0)
    {
      cout << "Diagonal elements are not zero" << endl;
      exit(0);
    }
  }
  
  //Check if the matrix is symmetric
  for(int i=0; i<n; ++i)
  {
    for(int j=i+1; j<n; ++j)
    {
      if(arr[i][j] != arr[j][i])
      {
        cout << "The matrix is not symmetrical" << endl;;
        exit(0);
      }
    }
  }

  //Output.
  cout << "\n////////////////////////////////////////" << endl;
  cout<<"Enter the starting node: ";
  int start;
  cin >> start;

  cout << endl;
  
  booleanGrid[start-1] = true;
  dfs(arr,n,booleanGrid,start-1);
  
  cout<<"The nodes that can be reached from the start node are: ";

  for(int i=0; i<n; ++i){
    if(booleanGrid[i]){
      cout << i+1 << " ";
    }
  }

  cout << "\n////////////////////////////////////////" << endl;
  }


//FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////


  void dfs(bool **arr,int n,bool booleanGrid[],int start)
  {

  /*
  * The array is the adjacency matrix and 'n' is the number of the nodes.
  * booleanGrid has the boolean values for the nodes which come from the source.
  * start is the source node
  */

    //Checks for a link between the node and source, and if it is not 
      //already covered and true we call the dfs() function on that 
      //particular node and include it in the booleanGrid.

    //Traverse through all the nodes
    for(int i=0; i<n; ++i){

      if(arr[start][i] && !booleanGrid[i]){
        booleanGrid[i] = true;

        dfs(arr,n,booleanGrid,i);
      }
    }
  }
