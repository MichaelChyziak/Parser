+//Use only the following libraries:
+#include "parserClasses.h"
+#include <string>
+
+#include <iostream>
+
+//Complete the implementation of the following member functions:
+
+//****TokenList class function definitions******
+
+//Creates a new token for the string input, str
+//Appends this new token to the TokenList
+//On return from the function, it will be the last token in the list
+void TokenList::append(const string &str) {
+ if (str.empty()) {
+ //do nothing if the given string is empty. Ignore it basically
+ }
+ else {
+ Token *temp;
+ temp = new Token(str);
+ if (tail) {
+ tail->next = temp;
+ temp->prev = tail;
+ tail = temp;
+ }
+ else {
+ tail = temp;
+ head = temp;
+ }
+ }
+}
+
+//Appends the token to the TokenList if not null
+//On return from the function, it will be the last token in the list
+void TokenList::append(Token *token) {
+ if (token) {
+ tail->next = token;
+ token->prev = tail;
+ tail = token;
+ }
+ else {
+ //token is NULL
+ exit(1);
+ }
+}
+
+//Removes the token from the linked list if it is not null
+//Deletes the token
+//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
+void TokenList::deleteToken(Token *token) {
+ if (token) {
+ if (head && tail) {
+ bool deleted = false;
+ Token *temp;
+ temp = head;
+ while (!deleted) {
+ if (temp == token) {
+ Token *destroy;
+ Token *previous;
+ destroy = temp;
+ previous = temp->getPrev();
+ temp = temp->getNext();
+ previous->setNext(temp);
+ temp->setPrev(previous);
+ delete destroy;
+ }
+ else {
+ temp = temp->getNext();
+ }
+ }
+ }
+ else {
+ //Failed to delete token. List is empty or missing either head or tail
+ exit(1);
+ }
+ }
+ else {
+ //token is NULL
+ exit(1);
+ }
+}
+
+
+//****Tokenizer class function definitions******
+
+//Computes a new tokenLength for the next token
+//Modifies: size_t tokenLength, and bool complete
+//(Optionally): may modify offset
+//Does NOT modify any other member variable of Tokenizer
+void Tokenizer::prepareNextToken(){
+ if (offset == str->length()) {
+ complete = true;
+ }
+ if (!complete) {
+ bool found = false;
+ int i = offset;
+ while (!found && i < str->length()) {
+ switch (str->at(i)) {
+ case ' ':
+ case '\t':
+ tokenLength = i - offset;
+ found = true;
+ if (tokenLength == 0) {
+ if (i == str->length()){
+ complete = true;
+ found = true;
+ }
+ else {
+ offset++;
+ i++;
+ found = false;
+ }
+ }
+ break;
+ case '(':
+ case ')':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '&':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ if (str->at(i + 1) == '=') {
+ tokenLength = 2;
+ found = true;
+ }
+ found = true;
+ break;
+ case '*':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '+':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '-':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '^':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '!':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '=':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case ';':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case ':':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '/':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '#':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '[':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case ']':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '%':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '|':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '.':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '?':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case ',':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '>':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '<':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '~':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '{':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ case '}':
+ tokenLength = i - offset;
+ if (tokenLength == 0) {
+ tokenLength = 1;
+ }
+ found = true;
+ break;
+ default:
+ i++;
+ }
+ }
+ if (i == str->length()) {
+ tokenLength = str->length() - offset;
+ int a = 1;
+ int b = 2;
+ }
+ }
+}
+
+//Sets the current string to be tokenized
+//Resets all Tokenizer state variables
+//Calls Tokenizer::prepareNextToken() as the last statement before returning.
+void Tokenizer::setString(string *str) {
+ if (str->length() == 0) {
+ complete = true;
+ }
+ else {
+ complete = false;
+ offset = 0;
+ tokenLength = 0;
+ this->str = str;
+ prepareNextToken();
+ }
+}
+
+//Returns the next token. Hint: consider the substr function
+//Updates the tokenizer state
+//Updates offset, resets tokenLength, updates processingABC member variables
+//Calls Tokenizer::prepareNextToken() as the last statement before returning.
+string Tokenizer::getNextToken() {
+ if (offset == str->length()) {
+ complete = true;
+ return "";
+ }
+ string temp = str->substr(offset, tokenLength);
+ offset = offset + tokenLength;
+ tokenLength = 0;
+ prepareNextToken();
+ return temp;
+
+}
