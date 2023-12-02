#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;


// structure
/*structure needed for list
contains double linked list*/
struct Node {
	int Value;
	struct Node* next;
	struct Node* previous;
};

// stucture stack
struct data {
	int Code;
	int Index;
	int Val;
	struct data* link;
};

//structure end..


// initialization
/*These are all the variables and pointers
that were initialized for the code*/
struct Node* start = NULL;
struct Node* End = NULL;
struct Node* cursor = NULL;
struct data* top = NULL;
int counter = 0;
int cursorcount = 0;
int check = 0;
// intialization end...

//-------------------------------------------stack------------------------------------------------

// function pushes value in stack
void PUSH(int code, int index, int val) {
	struct data* temp = (struct data*)malloc(sizeof(struct data));
	temp->Code = code;
	temp->Index = index;
	temp->Val = val;

	temp->link = NULL;

	if (top == NULL) {
		top = temp;
		top->link = NULL;
	}
	else {
		temp->link = top;
		top = temp;
	}
}

void printStack() {
	struct data* current = top;
	if (current == NULL) {
		cout << "Linked List is empty";
	}
	else {
		while (current != NULL) {
			cout << "Code : " << current->Code<< endl;
			cout << "Index : " << current->Index << endl;
			cout << "Value : " << current->Val << endl;
			current = current->link;
		}
		cout << "top of stack is : " << top->Val << endl;
	}
}

// function pops value from stack
void POP() {
	struct data* current = top;
	top = top->link;
	free(current);
	cout << "Stack popped" << endl;
}
//----------------------------------------stack end------------------------------------------------


//------------------------------------------sub functions------------------------------------------
/*These are all the sub functions*/

// this function adds node at the start
void ADDstart(Node* temp) {
	Node* current = start;
	temp->next = current;
	current->previous = temp;
	start = temp;
}

// this function adds node in the middle
void ADDmiddle(Node* prev, Node* temp) {
	prev->next->previous = temp;
	temp->previous = prev;
	temp->next = prev->next;
	prev->next = temp;
}

// this function adds node at the end
void ADDend(Node* temp) {
	struct Node* current = start;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = temp;
	temp->previous = current;
	End = temp;
}

//this function deletes node at the start
void DeleteStart() {
	Node* current = start;
	start = start->next;
	if (start != NULL)
		start->previous = NULL;
	free(current);
}

// this function deletes node in the middle
void DeleteMid(Node* current) {
	current->previous->next = current->next;
	current->next->previous = current->previous;
	free(current);
}

// this function deletes node at the end
void DeleteEnd() {
	Node* current = End;
	End = End->previous;
	End->next = NULL;
	free(current);
}
//----------------------------------------sub function end-----------------------------------------


//----------------------------------------main functions-------------------------------------------
//-------------------------------------------------------------------------------------------------
/*These are the main functions of the program*/

//-----------------------------------insertion functions-------------------------------------------
// this function inserts node in a sequence
void ADD(int v) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->Value = v;
	temp->next = NULL;
	temp->previous = NULL;
	counter += 1;
	if (start == NULL) {
		start = temp;
		End = start;
		start->previous = NULL;
		cursor = start;
	}
	else {
		ADDend(temp);
	}
	if (check == 0)
	{
		PUSH(1, counter - 1, temp->Value);
	}
}

// this function inserts at a given value						
void Add_Index_Num(int index, int id) {
	struct Node* temp = (Node*)malloc(sizeof(struct Node));
	temp->Value = id;
	temp->next = NULL;
	temp->previous = NULL;
	//checks if given index is within range(number of nodes)
	if (index > counter || index < 0) {
		cout << "Error, wrong index" << endl;
		return;
	}
	counter += 1;
	//checks if insertion is in the start
	if (index == 0) {
		ADDstart(temp);
	}
	else {
		struct Node* prev = start;
		//going to (index - 1) position.
		for (int i = 0; i < index - 1; i++) {
			prev = prev->next;
		}
		//if insertion at end
		if (prev->next == NULL) {
			ADDend(temp);
		}
		//if insertion in middle
		else {
			ADDmiddle(prev, temp);
		}
	}
	if (index <= cursorcount)
	{
		cursor = cursor->previous;
	}
	if (check == 0) {
		PUSH(2, index, temp->Value);
	}
}
// -------------------------------------insertion function end------------------------------------

// ---------------------------------------delete functions-----------------------------------------
// this function deletes the end of the list
void Delete() {
	if (start == NULL)
	{
		return;
	}
	counter -= 1;
	if (cursorcount > counter)
	{
		cursor = cursor->previous;
		cursorcount -= cursorcount;
	}
	if (check == 0) {
		PUSH(3, counter - 1, End->Value);
	}
	if (End == start)
	{
		Node* current = start;
		start = NULL;
		End = NULL;
		free(current);
	}
	else
	{
		DeleteEnd();
		cout << "Tail of the list deleted" << endl;
	}


}

// this function deletes at given index
void DeleteIndex(int Index) {
	int hold;
	if (start == NULL) {
		cout << "list is empty" << endl;
		return;
	}
	if (Index >= counter || Index < 0) {
		cout << "Error, wrong index" << endl;
		return;
	}

	// checking conditions for cursor 
	if (Index <= cursorcount && cursor->next != NULL)
	{
		cursor = cursor->next;
	}
	else if (Index <= cursorcount && cursor->next == NULL)
	{
		cursor = cursor->previous;
		cursorcount -= 1;
	}

	counter -= 1;
	if (Index == 0) {
		hold = start->Value;
		DeleteStart();
		cout << "Deleted start....";
	}
	else {
		Node* current = start;
		for (int i = 0; i < Index; i++) {
			current = current->next;
		}
		hold = current->Value;
		if (current == End) {
			DeleteEnd();
		}
		else {
			DeleteMid(current);
		}
	}
	if (start == NULL) {
		End = NULL;
	}
	if (check == 0) {
		PUSH(4, Index, hold);
	}
}
//------------------------------------delete functions end-----------------------------------------

// this function update value at the given index
void UpdateIndex(int index, int v) {
	if (index < 0 || index >= counter) {
		cout << "Error, index out of bound" << endl;
		return;
	}
	Node* current = start;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	if (check == 0) {
		PUSH(5, index, current->Value);
	}
	current->Value = v;
}

//-------------------------------------cursor functions--------------------------------------------
// this function moves cursor forward by given steps 
void MoveForward(int steps) {
	cursorcount += steps;
	// checking if steps are within range (number of nodes)
	if (cursorcount + 1 > counter)
	{
		cursorcount = counter - 1;
		cursor = End;
		cout << "Cursor updated." << endl;
		if (check == 0) {
			PUSH(6, cursorcount, counter - steps);
		}
		return;
	}
	for (int i = 0; i < steps; i++)
	{
		cursor = cursor->next;
	}
	if (check == 0) {
		PUSH(6, cursorcount,steps);
	}
}

// this function moves cursor backwards by givem steps
void MoveBackward(int steps) {
	int hold = cursorcount;
	cursorcount -= steps;
	// checking if steps are within range (number of nodes)
	if (cursorcount < 0)
	{
		if (check == 0){ 
			PUSH(7, cursorcount, hold);
		}
		cursorcount = 0;
		cursor = start;
		cout << "Cursor updated." << endl;
		return;
	}
	for (int i = 0; i < steps; i++)
	{
		cursor = cursor->previous;
	}
	if (check == 0) {
		PUSH(7, cursorcount, steps);
	}
}

// this function adds number just after cursor position
void ADDImmediate(int value){
	int index = cursorcount + 1;
	check = 1;
	Add_Index_Num(index, value);
	check = 0;
	if (check == 0) {
		PUSH(8, index, value);
	}
}

// this function updates data at which the cursor is pointing
void UpdateImmediate(int newval) {
	if (check == 0) {
		PUSH(9, cursorcount, cursor->Value);
	}
	cursor->Value = newval;
	cout << "Value is updated.." << endl;
}

// this function deletes the index where the cursor is present
void DeleteImmediate() {
	if (check == 0) {
		PUSH(10, cursorcount, cursor->Value);
	}
	check = 1;
	DeleteIndex(cursorcount);
	check = 0;
	cout << "Index succesfully deleted! " << endl;
}

// this function shifts the current data with data of the index specified
void Shift(int index) {
	if (index >= counter) {
		cout << "Error, index out of bound" << endl;
		return;
	}
	Node* current = start;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	if (check == 0) {
		PUSH(11, index, 0);
	}
	swap(cursor->Value, current->Value);
	cout << "Swapped!!" << endl;
}
//-----------------------------------cursor functions end-----------------------------------------

//--------------------------------------print function--------------------------------------------
void printNode() {
	struct Node* current = start;
	if (current == NULL) {
		cout << "Linked List is empty";
	}
	else {
		cout << "list: ";
		while (current != NULL) {
			cout  << current->Value << ", ";
			current = current->next;
		}
		cout << "tail: " << End->Value << endl;
	}
}


void printCursor() {
	cout << "cursor data: " << cursor->Value << endl;
}
//---------------------------------------print function end----------------------------------------

//---------------------------------------------undo-----------------------------------------------
/*
codes:
ADD = 1
Add_Index_Num = 2
Delete = 3
DeleteIndex = 4
UpdateIndex = 5
MoveForward = 6
MoveBackward = 7
ADDImemediate = 8
UpdateImmediate = 9
DeleteImmediate = 10
shift = 11
*/

void UNDO() {
	check = 1;
	if (top == NULL) {
		cout << "NO Operations performed...";
		check = 0;
		return;
	}
	if (top->Code == 1)
	{
		Delete();
		POP();
		cout << "1 is running" << endl;
	}
	else if (top->Code == 2)
	{
		DeleteIndex(top->Index);
		POP();
		cout << "2 is running" << endl;
	}
	else if (top->Code == 3)
	{
		ADD(top->Val);
		POP();
		cout << "3 is running" << endl;
	}
	else if (top->Code == 4)
	{
		Add_Index_Num(top->Index, top->Val);
		POP();
		cout << " 4 is running" << endl;
	}
	else if (top->Code == 5) {
		UpdateIndex(top->Index, top->Val);
		POP();
		cout << "5 is running" << endl;
	}
	else if (top->Code == 6) {
		MoveBackward(top->Val);
		POP();
		cout << "6 is running" << endl;
	}
	else if (top->Code == 7) {
		MoveForward(top->Val);
		POP();
		cout << "7 runned" << endl;
	}
	else if (top->Code == 8) {
		DeleteIndex(top->Index);
		POP();
		cout << "8 runned" << endl;
	}
	else if (top->Code == 9) {
		UpdateImmediate(top->Val);
		POP();
		cout << "9 runned" << endl;
	}
	else if (top->Code == 10) {
		Add_Index_Num(top->Index, top->Val);
		POP();
		cout << "10 runned" << endl;
	}
	else if (top->Code == 11) {
		Shift(top->Index);
		POP();
		cout << "11 runned" << endl;
	}
	check = 0;
}

//---------------------------------------------undo end-------------------------------------------

//-----------------------------------------main function end---------------------------------------
//-------------------------------------------------------------------------------------------------

int main() {
	int number;
	string operation;
	int stopcheck = 0;
	int index;
	ifstream File_Input("E:/chrome downloads/assignment 2/TestCases/04/Test02.txt");

	while (stopcheck != -1) {
		File_Input >> operation;

		if (operation == "Add") {
			File_Input.get();
			File_Input >> index;
			stopcheck = File_Input.get();
			if (stopcheck == 10 || stopcheck == -1) {
				ADD(index);
				cout << "List is: ";
				printNode();
				continue;
			}
			else {
				File_Input >> number;
				Add_Index_Num(index, number);
			}
		}
		else if (operation == "Delete") {
			stopcheck = File_Input.get();
			if (stopcheck == 10 || stopcheck == -1) {
				Delete();
				cout << "List is sub : ";
				printNode();
				continue;
			}
			else {
				File_Input >> index;
				DeleteIndex(index);
			}
		}
		else if (operation == "Print") {
			printCursor();
		}
		else if (operation == "MoveForward") {
			File_Input.get();
			File_Input >> number;
			MoveForward(number);
		}
		else if (operation == "MoveBackward") {
			File_Input.get();
			File_Input >> number;
			MoveBackward(number);
		}
		else if (operation == "AddImmediate") {
			File_Input.get();
			File_Input >> number;
			ADDImmediate(number);
		}
		else if (operation == "DeleteImmediate") {
			DeleteImmediate();
		}
		else if (operation == "Update") {
			File_Input.get();
			File_Input >> index;
			File_Input.get();
			File_Input >> number;
			UpdateIndex(index, number);
		}
		else if (operation == "UpdateImmediate") {
			File_Input.get();
			File_Input >> number;
			UpdateImmediate(number);
		}
		else if (operation == "Shift") {
			File_Input.get();
			File_Input >> index;
			Shift(index);
		}
		else if (operation == "Undo") {
			UNDO();
		}
		stopcheck = File_Input.get();
		cout << "List is: ";
		printNode();
	}
	File_Input.close();
}
