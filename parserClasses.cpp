//Use only the following libraries:
#include "parserClasses.h"
#include <string>
#include <iostream>
//Complete the implementation of the following member functions:
//****TokenList class function definitions******
//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str) {
	if (str.empty()) {
		//do nothing if the given string is empty. Ignore it basically
	}
	else {
		Token *temp;
		temp = new Token(str);
		if (tail) {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
		else {
			tail = temp;
			head = temp;
		}
	}
}
//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token) {
	if (token) {
		tail->next = token;
		token->prev = tail;
		tail = token;
	}
	else {
		//token is NULL
		exit(1);
	}
}
//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token) { //this will fail, it has no exit condition----------------------------------------
	if (token) {
		if (head && tail) {
			bool deleted = false;
			Token *temp;
			temp = head;
			while (!deleted) {
				if (temp == token) {
					Token *destroy;
					Token *previous;
					destroy = temp;
					previous = temp->getPrev();
					temp = temp->getNext();
					previous->setNext(temp);
					temp->setPrev(previous);
					delete destroy;
				}
				else {
					temp = temp->getNext();
				}
			}
		}
		else {
			//Failed to delete token. List is empty or missing either head or tail
			exit(1);
		}
	}
	else {
		//token is NULL
		exit(1);
	}
}
//****Tokenizer class function definitions******
//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken(){
	if (offset == str->length()) {
		complete = true;
		//if you are already at the end of the list return nothing
	}

	if(processingBlockComment == false)
	{
		if (!complete) {
			//while loop is not complete keep searching till you hit a character and you determine lengh from offset
			bool found = false;
			
			int i = offset;
			// set incrementing index equal to the offset position in string
			while (!found && i < str->length())
			{ // while you have not found a specified character or your string index has not gone out of the string size keep searching
				switch (str->at(i)) {
				case '/n':
				case ' ':
				case '\t':
					//the white space character has been reached and there for the characters before it should be a token
					tokenLength = i - offset;
					found = true;
					if (tokenLength == 0) {
						if (i == str->length())
						{
							complete = true;
							found = true;
							// if this condition holds you have reached the end of string
						}
						else {
							offset++;
							i++;
							found = false;
						}
					}
					break;
				case '(':
				case ')':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
				case '&':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '&') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find { &, &= , &&}
				case '*':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '/') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find { *= , */}
				case '!':
					tokenLength = i - offset;
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					break;
					//includes cases where I find { !, != }
				case '+':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '+') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find { +, +=, ++ }
				case '-':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '>') {
						tokenLength = 2;
						found = true;
					}
					if ( (str->at(i + 1) == '>') & (str->at(i + 2) == '*')){
						tokenLength = 3;
						found = true;
					}
					if (str->at(i + 1) == '-') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find { -, -=, ->, ->*, -- }
				case '^':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {^=, ^ }
				case '=':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {==, = }
				case ';':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find {; }
				case ':':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == ':') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {:,:: }
				case '/':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '/') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '*') {
						tokenLength = 2;
						found = true;
					}
				    //includes cases where I find {/,/=,//,'/* }
					found = true;
					break;
				case '#':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find {#}
				case '[':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find {[ }
				case ']':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find { ] }
				case '%':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {% , %= }
				case '|':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '|') {
						tokenLength = 2;
						found = true;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {|,||,|=}
				case '.':     //// what about filename.name
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '*') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {.,.*}
				case '?':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == ':') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {?,?:}
				case ',':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find {,}
				case '>':
					tokenLength = i - offset;

					if (tokenLength == 0) {
						tokenLength = 1;
					}
						if ( i+2 <= str ->length()) 
						{// making sure I will not read outside of the string 
							if (str->at(i + 1) == '=') {
								tokenLength = 2;
								found = true;
							}
							
							if ( (str->at(i + 1) == '>') & (str->at(i + 2) == '=')){
								tokenLength = 3;
								found = true;
							}
							

							if (str->at(i + 1) == '>') {
								tokenLength = 2;
								found = true;
							}
						}
					found = true;
					break;
					//includes cases where I find {>, >= , >> , >>=}
				case '<':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if (str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if ( (str->at(i + 1) == '<') & (str->at(i + 2) == '=')){
						tokenLength = 3;
						found = true;
					}
					if (str->at(i + 1) == '<') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {<,<= , <<= , <<}
				case '~':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find {~}
				case '{':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
						//includes cases where I find { { }
				case '}':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					found = true;
					break;
					//includes cases where I find { } }
				case '"':
				tokenLength = i - offset;
				    i++;
				if (tokenLength == 0 ) {

					while( str->at(i) != '"')
					{
						i++;
					}
					i++;
					tokenLength = i - offset;
				}
				found = true;
				break;
				//includes cases where I find { "" }
				default:
					i++;
					//by defult if non of these cases apply, increment by one till you either reach the end of the string or you find a specified character
				}
			}
			if (i == str->length()) {
				tokenLength = str->length() - offset;
			}
		}
	}

		if( processingBlockComment == true) /////////////////////////////////////////////////////////////// need to cover case were you have a 1 line block comment
	{
		// this statement gets executed upon hitting a block comment entry term
		// this will run in every call to get parser till you find a block exit
		// it will keep all comments together BY LINE. 

		bool found = false;
		int i = offset;
		int endblock = 0;
		// This is to detect that 
		while (!found && i+2 < str->length())
		{ // this ends the loop if you are one index locations before the end because it is not possible to have a end block term with less then 2 spaces
			if ( str-> at(i+1) == '*')
			{
				if( str-> at(i+2) == '/')
				{
					tokenLength = i - offset;
					found = true;
					processingBlockComment = false;
					endblock = 1;
					//this ends the loop and resets the flag, aswell as setting a flag that you hit a end block 
				}
			}
			i++;
		}

		if( i+2 >= str->length() && endblock == 0)
		{
	    // this statement gets executed if your block comment goes over one line
		tokenLength = str->length() - offset;
		}
	}////////////////////////////////////////////////////////////////////////////////////////////////////




}
//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str) {
	if (str->length() == 0) {
		complete = true;
		//if string is made of nothing make no string and return nothing
	}
	else { //average case : their are terms to tokenize in a string
		complete = false;
		offset = 0;
		tokenLength = 0;
		this->str = str;
		prepareNextToken();
		//prepare next token lengh for call to get next token
	}
}
//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken() {
	if (offset == str->length()) {
		complete = true;
		return "";
		//if at end of list return complete
	}
	string temp = str->substr(offset, tokenLength);
	//substr takes a string and outputs a string of a specified length starting at a point
	offset = offset + tokenLength;
	//move to the new position to seek forward
	tokenLength = 0;
	//reset token length
	if (temp == "//")
	{
		tokenLength = (str -> length()) - offset;
		return temp;
		//if their is a comment on a line every character after is a comment
		//inline case
	}
	if (temp == "/*")
	{
		processingBlockComment = true;
		return temp;
		//if a block comment gets started activate the processing block comment flag
		//block line case
	}
	prepareNextToken();
	//get next token length for next call to get next token
	return temp;
	//
}