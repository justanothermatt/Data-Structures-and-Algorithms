// Assignment 3 DSA.cpp : Defines the entry point for the console application.
// This code will take in a text file and ensue the brackets are lined up properly
// It will then output to a text file with the answers either labeled "Correct" or "Incorrect"
// Author: Matt Walker Date: 10/7/2018
//

#include "stdafx.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

//Queue class will be used for testing the brackets in the input file
//Below is the basic class for a queue using enqueue, dequeue, isEmpty, and isFull

const int SIZE = 20; //Maximum size of the queue

class Queue {
private:
	int front;
	int rear;
	int arr[SIZE];
public:
	Queue();				// constructor to initialize the queue
	void enqueue(int x);	// insert an integer at the rear of the queue
	char dequeue();			// remove an integer from the front of the queue
	bool isEmpty();			// check if the queue is empty
	bool isFull();			// check if the queue is full
};

//Basic Constructor setting front and rear pointers
Queue::Queue() {
	front = 0;
	rear = 0;
}

//Enqueue: Takes the paramter integer and adds it to the queue
//Parameter: x, the value the user wishes to enqueue
void Queue::enqueue(int x) {
	if (isFull()) { cout << "Queue is full" << endl; }
	else{
		arr[rear] = x;
		rear = (rear + 1) % SIZE;
	}
}

//Dequeue: Returns the value of the first value (or char in this case) entered into the queue
char Queue::dequeue(){
	if (isEmpty()) { return NULL; }
	else {
		char value = arr[front];
		front = front = (front + 1) % SIZE;
		return value;
	}
}

//Tests for if the queue is at capacity
bool Queue::isFull() {
	if (front == (rear + 1) % SIZE) {return true;}
	else {return false;}
}

//Tests to make sure there are values in the queue
bool Queue::isEmpty() {
	if (front == rear) {return true;}
	else { return false; }
}


int main()
{
	Queue myQueue;	//Creating a new Queue object for use later on
	char inChar;	//This is the input character

	ifstream infile;																									//Creating a new ifstream object so we can use input or output
	infile.open("C:\\Users\\ID139\\Downloads\\Things I want on my desktop but not actually ON it\\testme.txt");			//Defines the path for the input file

	const char *path = "C:\\Users\\ID139\\Downloads\\Things I want on my desktop but not actually ON it\\results.txt";	//Defines the path for the output file
	ofstream cout(path);																								//redirecting all "cout" statements to the output path


	//All of these integers are used to count the number of types of brackets. Their chacter will be commented in-line.
	//This will be used for testing for correctness. If all bracket types are equal, then the line is correct. Else it's wrong.
	int leftSquig	 = 0;	// {
	int rightSquig	 = 0;	// }
	int leftPara	 = 0;	// (
	int rightPara	 = 0;	// )
	int leftBracket	 = 0;	// [
	int rightBracket = 0;	// ]
	int leftAngle	 = 0;	// <
	int rightAngle	 = 0;	// >
	int bracketSum	 = 0;	//Sum of all bracket counts, will be canged later in code
	char out;				//Output during a dequeue

	//Testing to make sure the input text file could be opened
	if (!infile) {
		cout << "Unable to open text file" << endl;
		exit(1);
	}

	else {		
		do {
			infile.get(inChar);	//getting the character

			while (inChar != '\n') {	//As long as the character isn't a new line, this will enqueue it
				myQueue.enqueue(inChar);
				break;
			}

			if (inChar == '\n' || infile.eof()) {	//If the character is a new line, or the end of the file

				if ((leftSquig == rightSquig) && (leftPara == rightPara) &&
					(leftBracket == rightBracket) && (leftAngle == rightAngle)) { //This is the test for equal brackets. If they're equal, it must be correct

					for (int i = 0; i < bracketSum; i++) { //Dequeuing loop
						out = myQueue.dequeue();

						cout << out;
					}

					//This if accounts for the number at the number at the begining of the data
					if (out != '{' && out != '}' && out != '(' && out != ')' && out != '[' && out != ']' && out != '<' && out != '>') { cout << endl; }

					else { cout << "  --- Solution is correct" << endl; }
				}

				else {
					for (int i = 0; i < bracketSum; i++) {
						char out = myQueue.dequeue();
						cout << out;
					}
					cout << "  --- Solution is incorrect" << endl;
				}

				//This is setting all bracket variables back to 0 for the next line of testing
				leftSquig = 0;
				rightSquig = 0;
				leftPara = 0;
				rightPara = 0;
				leftBracket = 0;
				rightBracket = 0;
				leftAngle = 0;
				rightAngle = 0;
			}
			else {

				char temp = inChar;	//temp value for bracket addition

				//This if updates bracketSum win the case of a non-bracket (number at begining)
				if (temp != '{' && temp != '}' && temp != '(' && temp != ')' && temp != '[' && temp != ']' && temp != '<' && temp != '>') { bracketSum++; }

				//Adding to local bracket variables for testing
				else {
					if (temp == '{') { leftSquig++; }
					if (temp == '}') { rightSquig++; }
					if (temp == '(') { leftPara++; }
					if (temp == ')') { rightPara++; }
					if (temp == '[') { leftBracket++; }
					if (temp == ']') { rightBracket++; }
					if (temp == '<') { leftAngle++; }
					if (temp == '>') { rightAngle++; }
					bracketSum = (leftSquig + rightSquig + leftPara + rightPara + leftBracket + rightBracket + leftAngle + rightAngle);
				}
			}
		} while (!infile.eof());
		infile.close();
	}
    return 0;
}