/*////////////////////////////////////////////////////////////////
/Authored by @BalkanBasileus
/
/CS302 
/
/
/The following C++ code evaluates a post fix expression. Reads in 
/numbers with '\$' termination character. Converts nums to char 
/and pushes onto stack. When arithmetic symbol is reached, performs 
/arithmetic with previous two nums on stack. New num is pushed.
/
////////////////////////////////////////////////////////////////*/
#include <iostream>
#include <stack>
using namespace std;

int CharToInt(const char c);

//MAIN
//////////////////////////////////////////////////
int main(int argc, char const *argv[])
{

	//Input Variables
	char c; 
	stack<int> stack; //Our char stack
	
	//DISPLAY INSTRUCTION
	cout << "******Enter Expression $ ******" << endl;
	

	//Input
	while(cin && ((cin.peek()) != '\$')){
		cin >> c;
		

		if(c != '+' && c != '-' && c != '*' && c != '/'){ //push only nums onto stack
		stack.push(CharToInt(c));			
		}


		//ADDITION
		if(c == '+'){

			//Check if Valid Expression
			if(stack.empty()){
				cout << "This is not a valid postfix expression, termination. " << endl;
				return 0;
			}
			
				//Compute
				int firstNum = stack.top();//establish first num
				stack.pop();	//remove it
				int secondNum = stack.top();//establish scnd num
				stack.pop(); //remove it

				int result = (secondNum + firstNum); //arithmetic
				stack.push(result); //push onto stack.
			}

			//SUBTRACTION
			if(c == '-'){

			//Check if Valid Expression
			if(stack.empty()){
				cout << "This is not a valid postfix expression, termination. " << endl;
				return 0;
			}
			
				//Compute
				int firstNum = stack.top();//establish first num
				stack.pop(); //remove it
				int secondNum = stack.top();//establish scnd num
				stack.pop(); //remove it

				int result = (secondNum - firstNum); //arithmetic
				stack.push(result); //push onto stack
			}

			//MULTIPLICATION
			if(c == '*'){

			//Check if Valid Expression
			if(stack.empty()){
				cout << "This is not a valid postfix expression, termination. " << endl;
				return 0;
			}
			
				//Compute
				int firstNum = stack.top();//establish first num
				stack.pop(); //remove it
				int secondNum = stack.top();//establish scnd num
				stack.pop(); //remove it

				int result = (secondNum * firstNum); //arithmetic
				stack.push(result); //push onto stack
			}

			//DIVISION
			if(c == '/'){

			//Check if Valid Expression
			if(stack.empty()){
				cout << "This is not a valid postfix expression, termination. " << endl;
				return 0;
			}
			
				//Compute
				int firstNum = stack.top();//establish first num
				stack.pop(); //remove it
				int secondNum = stack.top();//establish first num
				stack.pop(); //remove it

				int result = (secondNum / firstNum); //arithmetic
				stack.push(result); //push onto stack
			}
	
		//DEBUG TEST
		//cout << stack.top() << endl;

		//DEBUG TEST
		//cout << c << endl;
	}

	// DEBUG TEST
	//stack.pop();
	//stack.pop();
	//cout << stack.top() << endl;


	//DISPLAY STACK
	cout << "***Stack Contents in Reverse***" << endl;
	while(!stack.empty()){
				cout << stack.top() << " ";
				stack.pop();
			}
	cout << endl;
	cout << "*******************************" << endl;
   

	return 0;
}

//FUNCTIONS
//////////////////////////////////////////////////
int CharToInt(const char c)
{
switch (c)
{
case '0': return 0;
case '1': return 1;
case '2': return 2;
case '3': return 3;
case '4': return 4;
case '5': return 5;
case '6': return 6;
case '7': return 7;
case '8': return 8;
case '9': return 9;
default: return 0; }
}

