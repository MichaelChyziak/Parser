#include "parserClasses.h"

void append(const char &str); //example comment
void foo() {
	int i = 1;
	int j = 2;
	i &= i;
}

void test() {
	TokenList a;
	a = new TokenList;
	Token b = a.getFirst();
}
