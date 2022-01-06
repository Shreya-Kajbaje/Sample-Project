#include<iostream>

using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {

	char* ptr1;
	ptr1 = new char[10];

	char* ptr2;
	ptr2 = new char[10];
	
	
	string abc = "Shreya";
	
	cout << "Hello World!!";

	delete(ptr1);
	//delete(ptr2);

	_CrtDumpMemoryLeaks();

	return 0;
}