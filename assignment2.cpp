//Use only the following three libraries:
#include "parserClasses.h"
#include <iostream>
#include <fstream>
using namespace std;
//Removes all inline comments from the tokenList including the // marker
//Returns the number of comments removed
int removeInlineComments(TokenList &tokenList) {
		int completeflag;
	int removecount;
	// a variable to use as a flag in the while loop determining whether the data is processed
	// a variable to determine the number of comments removed
    removecount = 0;
	//initialy you have no comments removed 
	Token* endflag;
	Token* beginingflag;
	Token* temp;
	// a flag to search through the link list and anouther to use in the removal process 

	completeflag = 0;
	//initiating the while loop 

	beginingflag = tokenList.getFirst();
	// getting the node address of the first node in the tokenlist


	while (!completeflag)
	{
      if( "//" == beginingflag->getStringRep())
	  {
	    endflag = beginingflag;
		endflag = endflag -> getNext();
		endflag = endflag -> getNext();
		//move a pointer two ahead in the list since a inline comment always has 3 tokens
		// 1 for the //, anouther for the comment itself , and the last comment for the \n
	   
	   while ( beginingflag != endflag )
		{ temp = beginingflag ;
		 beginingflag =  beginingflag ->getNext();
	      tokenList.deleteToken(temp);
	    }
	
	   ++removecount;
	   //3 tokens removed means one inline comment removed and is thus incremented 
	  }

	   beginingflag =  beginingflag->getNext();
	   //move through the list

	  if ( tokenList.getLast() == beginingflag )
	  {
		  //if you get to the last token then their is no way you have a inline comment as it needs 3 tokens 
		  completeflag = 1;
	  }

	}
	 
	return removecount;
}
//Remove all block comments from the tokenList including /* and */ markers
//Returns the number of block comments removed (where each pair of /* and */ count as one comment)
int removeBlockComments(TokenList &tokenList) {
	//TO DO
	return 0;
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





//////////////  note this line causes an error when the line read in has no length
		//while the current line ends with a line-continuation \ append the next line to the current line
//		while (lineA[lineA.length() - 1] == '\\') {
//			lineA.erase(lineA.length() - 1, 1);
//			getline(sourceFile, lineB);
//			lineA += lineB;
	//	}
		///////////////////////////





		tokenizer.setString(&lineA);
		while (!tokenizer.isComplete()) {
			tokens.append(tokenizer.getNextToken());
		}
		//Re-insert newline that was removed by the getline function
		tokens.append("\n");
	}
    removeInlineComments(tokens);
	removeBlockComments(tokens);
	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
	Token *t = tokens.getFirst();
	// while (t) {
	// cout << t->getStringRep() << endl;
	// t = t->getNext();
	// }
	for (int i = 0; t; i++) {
		cout << "token" << i << ": " << t->getStringRep() << endl;
		t = t->getNext();
	}
	return 0;
	cin.get();
}


