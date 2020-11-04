 /***************************************************************************
 *Authored by @BalkanBasileus												
 *																			
 *The following  C++ program is a bank account manager. It is composed of 	
 *an array of structs, each containing a person profile with a balance. The 
 *bank accounts are read from a file. The program calls 4 functions to 		
 *store the information, sort it numerically by account numbers, search it 
 *with a binary search, and output the information formatted with <iomanip>.
 *User will withdrawal or deposit amount.									
 *																			
 *Program error checks, asking the user if they wish to continue. If so, the
 *program breaks out of error check loop and returns to top of do-while loop
 *that wraps around most of program in main().								
 *																			
 *If account balance is negative or becomes negative, program will not allow
 *withdrawal. No alphabetical nor negative(-) number input is allowed with  
 *deposit and withdrawal. 													
 ****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

//Struct.
struct bankAcct
{
	string first, last; //Name of person
	double amount;		//Account balance
	long acctNo;		//Account num.
	short pin;			//Account pin
};

//Functions
int storeInfo(bankAcct bankAccount[], ifstream& inFile);
void sort(bankAcct[], int);
int search(bankAcct[], int, long);
void outputAndHandleRequest(bankAcct&);

//Constant. Sets size of array of structs.
const int BANKINFO = 20;
							
							
//MAIN()
int main(int argc, char const *argv[])
{
  bankAcct bankAccount[BANKINFO]; //Calls array of structs.

  ifstream inFile;
  ofstream outFile;
  string fileName;

  //Input Variables
  int accountNumberInput;
  int accountPinInput = -1;
  char menuChoice, pinErrorCheckChoice, endOfProgramChoice; //Menu driven input varialbes

  do{//open file
    cout << "Enter the input file: "; 
    cin >> fileName;
    inFile.open(fileName.c_str());
  } while(!inFile.is_open());

  //Call store,sort,search functions.
  //Set results to 'numAc'.
  int numAc = storeInfo(bankAccount, inFile);
  sort(bankAccount, numAc);
  
  search(bankAccount,numAc,accountNumberInput);
  int accountIndex= -1;

//do{
  //Prompt Account Number:
	do{//Menu Driven do-while.
		accountIndex = -1;
		pinErrorCheckChoice = 0; 
			
			/*
			 Error check, Reprompt. 
			 While 'accountIndex == -1, loop. Otherwise
			 continue through do-while.
			*/

			while(cin.fail() || accountIndex == -1)
			{
				cin.clear();
				cin.ignore(100,'\n');

				cout << "Enter account number: " << endl;
				cin >> accountNumberInput;

	  			accountIndex= search(bankAccount,numAc,accountNumberInput); //Set new value, otherwise -1.

	  			if(accountIndex == -1)
	  			{
					cout << "Account not found! :( " << endl;
					cout << "Do you wish to continue? [Y/N]" << endl;
					cin >> menuChoice;

					menuChoice = toupper(menuChoice);

					if(menuChoice == 'N')	//If 'No', exit program.
					{
						return 0;
					}
				}
			}



				cin.clear();
				cin.ignore(100,'\n');

				cout << "Enter PIN: " << endl;
				cin >> accountPinInput;

				/*
				 Error check. If pin incorrect and they wish to continue,
				 program continues by redoing do-while loop since while
				 parameter is not met. Ends up reprompting for account
				 number. Otherwise if 'No', exits program.
				*/

				if(accountPinInput != bankAccount[accountIndex].pin)
				{
				
					accountPinInput = -1;

					cout << "Incorrect PIN, Exiting out of account. " << endl;
					cout << "Do you wish to continue? [Y/N] " << endl;
					cin >> pinErrorCheckChoice;

					pinErrorCheckChoice = toupper(pinErrorCheckChoice);

						//Error check. Excludes all input other than [Y,y,N,n].
						while(pinErrorCheckChoice != 'Y' && pinErrorCheckChoice != 'N')
						{
							cout << "Incorrect PIN, Exiting out of account. " << endl;
							cout << "Do you wish to continue? [Y/N] " << endl;
							cin >> pinErrorCheckChoice;

							pinErrorCheckChoice = toupper(pinErrorCheckChoice);
						}
					if(pinErrorCheckChoice == 'N')
					{
						return 0;
					}
					else if(pinErrorCheckChoice == 'Y')
					{
						continue;
					}
				}
				else	//If account number and pin correct, calls final output function.
				{
					outputAndHandleRequest(bankAccount[accountIndex]);
				}
		/*
		Final prompt. If they wish to continue it keeps value of 'pinErrorCheckChoice' as 'Y'
		meaning the do-while in main() continues to loop (allowing access to more accounts).
		If no, then do-while terminates thus program terminates.
		*/

		cout << "Do you wish to continue: [Y/N]" << endl;
		cin >> endOfProgramChoice;
		endOfProgramChoice = toupper(endOfProgramChoice);

			//Error check. Excludes all input other than [Y,y,N,n].
			while(endOfProgramChoice != 'Y' && endOfProgramChoice != 'N')
			{
				cout << "Do you wish to continue: [Y/N]" << endl;
				cin >> endOfProgramChoice;
				endOfProgramChoice = toupper(endOfProgramChoice);
			}
		if(endOfProgramChoice == 'Y')
		{
			pinErrorCheckChoice = 'Y'; //Re-loops do-while loop. Program begins again.
		}
		else if(endOfProgramChoice == 'N')//Terminates program.
		{
			cout << "Have a nice Day!" << endl;
			return 0;
		}


	}while(toupper(pinErrorCheckChoice)=='Y');


	return 0;
}


//Functions
int storeInfo(bankAcct bankAccount[], ifstream& inFile)
{	/*
	Reads file line by line, incrementing 'numOfAccounts'. Returns 'numOfAccounts',
	which is set to int varialbe 'numAc' in main(). Located on line 66.
	*/
	int numOfAccounts=0;
	int i = 0;
	
		while(inFile >> bankAccount[i].first >> bankAccount[i].last >> bankAccount[i].acctNo
				>> bankAccount[i].pin >> bankAccount[i].amount) {

				
		i++;
		numOfAccounts += 1;
		}
	inFile.close(); //Close file.
	return numOfAccounts;
}


void sort(bankAcct bankAccount[], int numOfAccounts)
{	/*
	Sorts bank accounts from least to greatest number using selection sort from
	textbook.
	*/
	int index;
	int smallestIndex;
	int location;
	bankAcct temp;

	//Selection sort
	for(index = 0; index < numOfAccounts; index++)
	{	
		smallestIndex = index;

		for(location=index+1; location < numOfAccounts; location++)
		{
			if(bankAccount[location].acctNo < bankAccount[smallestIndex].acctNo)
				smallestIndex = location;

		temp = bankAccount[smallestIndex];
		bankAccount[smallestIndex] = bankAccount[index];
		bankAccount[index] = temp;

		}
	}
}


int search(bankAcct bankAccount[], int numOfAccounts, long desiredAccount)
{	
	//Binary search. Example taken from book.
	int first = 0;
	int last = numOfAccounts - 1;
	int mid;

	bool found = false;

	while(first <= last && !found)
	{
		mid = (first + last) / 2;

		if(bankAccount[mid].acctNo == desiredAccount)
			found = true;
		else if (bankAccount[mid].acctNo > desiredAccount)
			last = mid - 1;
		else first = mid + 1;
	}
	if(found)
		return mid;
	else
		return -1;

}


void outputAndHandleRequest(bankAcct& bankAccountStruct)
{
	/*Outputs bank account profile using <iomanip>. Sets precision to 2 decimal places
	 *and aligns everything to the right. First sentence is concatenated so that 
	 *regardless of how long the name is, it will be aligned correctly. Error
	 *checks input and sets new balance whether it is withdrawl or deposit. Cannot
	 *withdrawl if balance is, or becomes, negative.
	 */
	char balanceChoice;
	double withdrawalOrDepositAmount;

	cout << fixed << showpoint << setprecision(2) << endl;
	cout << right << endl;

	cout <<  "Name:  " << setw(20) << bankAccountStruct.last + ", " //Concatenated so as to stay 'right' aligned
		 + bankAccountStruct.first << endl;
	cout << "AcctNo:" << setw(20) << bankAccountStruct.acctNo << endl;
	cout << "Balance" << setw(20) << setfill('.') << bankAccountStruct.amount << endl;

	cout << "Would you like to make a withdrawl or deposit: [W/D]" << endl;
	cin >> balanceChoice;

	balanceChoice = toupper(balanceChoice);
		//Error check. Excludes all input other than [Y,y,N,n].
		while(balanceChoice != 'W' && balanceChoice != 'D')
		{
			cout << "Would you like to make a withdrawl or deposit: [W/D]" << endl;
			cin >> balanceChoice;

			balanceChoice = toupper(balanceChoice);
		}

	if(balanceChoice == 'W')
	{	
		cout << "Enter amount you would like to withdrawl: " << endl;
		cin >> withdrawalOrDepositAmount;

		while(withdrawalOrDepositAmount < 0 || cin.fail())
		{
			cin.clear();
			cin.ignore(100,'\n');

			cout << "Invalid amount entered >:( " << endl;
			cout << "Enter amount you would like to withdrawl: " << endl;
			cin >> withdrawalOrDepositAmount;
		}
		//If account balance < 0, cannot withdrawl.
		if(bankAccountStruct.amount < 0)
		{
			cout << "Cannot process transaction...  O.o " << endl;
		}
		else
		{
			bankAccountStruct.amount -= withdrawalOrDepositAmount;
		}
	}
	else if(balanceChoice == 'D')
	{
		cout << "Enter amount you would like to deposit: " << endl;
		cin >> withdrawalOrDepositAmount;

		while(withdrawalOrDepositAmount < 0 || cin.fail())
		{
			cin.clear();
			cin.ignore(100,'\n');

			cout << "Invalid amount entered >:( " << endl;
			cout << "Enter amount you would like to deposit: " << endl;
			cin >> withdrawalOrDepositAmount;
		}

		bankAccountStruct.amount += withdrawalOrDepositAmount;

	}
}


//Sample Result
/*
Enter the input file: hello
Enter the input file: 33
Enter the input file: BankData.txt
Enter account number: 
3
Account not found! :( 
Do you wish to continue? [Y/N]
y
Enter account number: 
2100655
Enter PIN: 
4444
Incorrect PIN, Exiting out of account. 
Do you wish to continue? [Y/N] 
y
Enter account number: 
2100655
Enter PIN: 
8973


Name:         Buzza, Lawton
AcctNo:             2100655
Balance..............111.78
Would you like to make a withdrawl or deposit: [W/D]
k
Would you like to make a withdrawl or deposit: [W/D]
d
Enter amount you would like to deposit: 
100
Do you wish to continue: [Y/N]
y
Enter account number: 
210065
Account not found! :( 
Do you wish to continue? [Y/N]
y
Enter account number: 
2100655
Enter PIN: 
8973


Name:  .......Buzza, Lawton
AcctNo:.............2100655
Balance..............211.78
Would you like to make a withdrawl or deposit: [W/D]
w
Enter amount you would like to withdrawl: 
1000
Do you wish to continue: [Y/N]
y
Enter account number: 
2100655
Enter PIN: 
8973


Name:  .......Buzza, Lawton
AcctNo:.............2100655
Balance.............-788.22
Would you like to make a withdrawl or deposit: [W/D]
w
Enter amount you would like to withdrawl: 
1
Cannot process transaction...  O.o 
Do you wish to continue: [Y/N]
n
Have a nice Day!
*/
