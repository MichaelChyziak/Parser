//Use only the following libraries:
#include "parserClasses.h"
#include <string>

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
		Token * new_tail;
		new_tail = token;
		tail->next = new_tail;
		new_tail->prev = tail;
		new_tail->next = NULL;
		tail = new_tail;
	}
	else {
		//token is NULL, do nothing
	}
}

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token) { 
	if (token) {
		Token *temp, *after, *before;
		temp = token;
		if (head == token && tail == token) {
			delete temp;
			head = NULL;
			tail = NULL;
		}
		else if (token->getPrev() == NULL) {
			head = head->getNext();
			head->setPrev(nullptr);
			delete temp;
		}
		else if (token->getNext() == NULL) {
			tail = token->getPrev();
			tail->setNext(nullptr);\
			delete temp;
		}
		else {
			after = token->getNext();
			before = token->getPrev();
			before->setNext(after);
			after->setPrev(before);
			delete temp;
		}
	
	}
	else {
		//token is null, do nothing
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
	}
	if (!complete) {
		bool found = false;
		int i = offset;
		if (inlineFlag) {
			tokenLength = str->length() - offset;
		}
		else if(blockFlag) {
			if (str->find("*/", i) == -1) {
				tokenLength = str->length() - offset;
			}
			else {
				i = str->find("*/") - offset;
				tokenLength = i;
			}
		}
		else {
			while (!found && i < str->length()) {
				switch (str->at(i)) {
				case ' ':
				case '\t':
					tokenLength = i - offset;
					found = true;
					if (tokenLength == 0) {
						if (i == str->length()){
							complete = true;
							found = true;
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
					if ((i < str->length() - 1) && (str->at(i + 1) == '=')) {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '&') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find { &, &= , &&}
				case '*':
					tokenLength = i - offset;
					if ((i < str->length() - 1) && (str->at(i + 1) == '/') && tokenLength == 0) {
						tokenLength = 2;
					}
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
					}
					found = true;
					break;
					//includes cases where I find { *= , */}
				case '!':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					break;
					//includes cases where I find { !, != }
				case '"':
					while (i < str->length()-1 && str->at(i+1) != '"') {
						i++;
					}
					tokenLength = i + 2 - offset;
					found = true;
					break;
					//includes the case where anything between "..." is 1 token (including the quotation marks)
				case '+':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '+') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '>') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 2) && (str->at(i + 1) == '>') & (str->at(i + 2) == '*')){
						tokenLength = 3;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '-') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == ':') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '/') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '*') {
						tokenLength = 2;
						found = true;
					}
					//includes cases where I find {/,/=,//,/* }
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
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == '|') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {|,||,|=}
				case '.':
					tokenLength = i - offset;
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '*') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == ':') {
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
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
						found = true;
					}
					if ((i < str->length() - 2) && (str->at(i + 1) == '>') && (str->at(i + 2) == '=')){
						tokenLength = 3;
						found = true;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '>') {
						tokenLength = 2;
						found = true;
					}
					found = true;
					break;
					//includes cases where I find {>, >= , >> , >>=}
				case '<':
					tokenLength = i - offset;
					if (includeFlag) {
						while ((i < str->length() - 1) && (str->at(i + 1) != '>')) {
							i++;
						}
						tokenLength = i + 2 - offset;
					}
					if (tokenLength == 0) {
						tokenLength = 1;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '=') {
						tokenLength = 2;
					}
					if ((i < str->length() - 2) && (str->at(i + 1) == '<') && (str->at(i + 2) == '=')){
						tokenLength = 3;
					}
					if ((i < str->length() - 1) && str->at(i + 1) == '<') {
						tokenLength = 2;
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
				default:
					i++;
					//by defult if non of these cases apply, increment by one till you either reach the end of the string or you find a specified character
				}
			}
		}
		if (i == str->length()) {
			tokenLength = str->length() - offset;
		}
	}
}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str) {
	if (str->length() == 0) {
		includeFlag = false;
		complete = true;
	}
	else {
		includeFlag = false;
		complete = false;
		offset = 0;
		tokenLength = 0;
		this->str = str;
		prepareNextToken();
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
	if (inlineFlag) {
		inlineFlag = false;
	}
	if (temp == "//")
	{
		inlineFlag = true;
		//if their is a comment on a line every character after is a comment
		//inline case
	}
	if (blockFlag && offset < str->length()) {
		blockFlag = false;
	}
	if (temp == "/*")
	{
		blockFlag = true;
		//if a block comment gets started activate the processing block comment flag
		//block line case
	}
	if (hashFlag) {
		hashFlag = false;
		if (temp == "include") {
			includeFlag = true;
		}
	}
	if (temp == "#") {
		hashFlag = true;
	}
	prepareNextToken();
	//get next token length for next call to get next token

	return temp;
}
