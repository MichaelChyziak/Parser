#include "parserClasses.h"
#include <iostream>

void append(const char &str); //example comment

void foo() {
	int i = 1;
	int j = 2;
	i &= i;
	int x = -3;
}

void test() {
	Token b;
	b.getStringRep();
	cout << b.getStringRep();
}
