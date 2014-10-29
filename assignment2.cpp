//Use only the following three libraries:
#include "parserClasses.h"
#include <iostream>
#include <fstream>

using namespace std;

//Removes all inline comments from the tokenList including the // marker
//Returns the number of comments removed
//tokenList must be existing object
int removeInlineComments(TokenList &tokenList) {
	int count = 0; //counts the amount of inline comments removed
	Token* temp;
	temp = tokenList.getFirst();
	while (temp) {
		if (temp->getStringRep() == "//") {
			count++;
			Token* destroy1;
			destroy1 = temp;
			if (temp->getNext() != NULL) {
				Token* destroy2;
				destroy2 = temp->getNext();
				temp = destroy2->getNext();
				tokenList.deleteToken(destroy1);
				tokenList.deleteToken(destroy2);
			}
			else {
				delete temp;
			}
		}
		else {
			temp = temp->getNext();

		}
	}
	return count;
}

//Remove all block comments from the tokenList including /* and */ markers
//Returns the number of block comments removed (where each pair of /* and */ count as one comment)
int removeBlockComments(TokenList &tokenList) {
	int count = 0;
	bool deleted = false;
	Token* temp, *destroy;
	temp = tokenList.getFirst();
	while (temp) {
		if (temp->getStringRep() == "/*") {
			count++;
			while (!deleted) {
				destroy = temp;
				temp = temp->getNext();
				tokenList.deleteToken(destroy);
				if (temp->getStringRep() == "*/") {
					destroy = temp;
					temp = temp->getNext();
					deleted = true;
					tokenList.deleteToken(destroy);
				}
			}
		}
		else {
			int k = 1;
			temp = temp->getNext();
		}
	}
	return count;
}

//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int main() {
	ifstream sourceFile;
	TokenList tokens;
	Tokenizer tokenizer;

	//Read in a file line-by-line and tokenize each line
	sourceFile.open("test.cpp");
	if (!sourceFile.is_open()) {
		cout << "Failed to open file" << endl;
		return 1;
	}

	while (!sourceFile.eof()) {
		string lineA, lineB;

		getline(sourceFile, lineA);
		//while the current line ends with a line-continuation \ append the next line to the current line
		while (lineA.length() > 0 && lineA[lineA.length() - 1] == '\\') {
			lineA.erase(lineA.length() - 1, 1);
			getline(sourceFile, lineB);
			lineA += lineB;
		}
		tokenizer.setString(&lineA);
		while (!tokenizer.isComplete()) {
			tokens.append(tokenizer.getNextToken());
		}
		//Re-insert newline that was removed by the getline function
		tokens.append("\n");
	}

	cout << "Inline comments removed: " << removeInlineComments(tokens) << endl;
	cout << "Block comments removed: " << removeBlockComments(tokens) << endl;

	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
	Token *t = tokens.getFirst();
	//	while (t) {
	//		cout << t->getStringRep() << endl;
	//		t = t->getNext();
	//	}

	for (int i = 0; t; i++) {
		cout << t->getStringRep() << " ";
		t = t->getNext();
	}
	return 0;

}
