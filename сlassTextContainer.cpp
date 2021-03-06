
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

//добавить функцию очищающую строку от лишних пробелов 
//или переработать split on token
class textContainer {
	char str[80];
public:
	textContainer(const char *inistring = "") {
		strcopy(inistring, str);
	}

	void strcopy(const char *copyit, char * destination);
	friend void strcopy(char *copyit, char * destination);
	textContainer operator= (textContainer obj);
	void showString() { cout << str; }
	friend istream &operator>> (istream &stream, textContainer &obj);
	void setStr(char *pstring);
	void stringCat(char * str, char * destination, char * endArray);
	void stringCat(const char * string);
	textContainer operator+(textContainer obj);
	textContainer operator-(textContainer obj);
	void splitOnToken(char * p, int numRowLimit, int numColLimit, char * initialString);
	friend bool stringComparisson(char * pstr, char * pstr2);
};

void textContainer::strcopy(const char *copyit, char * destination) {

	while (*copyit) {
		*destination = *copyit;
		destination++;
		copyit++;
		if (*copyit == '\0') {
			*destination = '\0';
		}
	}
}

void strcopy(char *copyit, char * destination) {

	while (*copyit != '\0') {
		*destination = *copyit;
		destination++;
		copyit++;
		if (*copyit == '\0') {
			*destination = '\0';
		}
	}
}

textContainer textContainer::operator= (textContainer obj) {
	strcopy(obj.str, str);
	return *this;
}

istream &operator>>(istream &stream, textContainer &obj) {
	stream >> obj.str;
	return stream;
}

void textContainer::setStr(char *pstring) {
	strcopy(pstring, str);
	return;
}

void textContainer::stringCat(const char * string) {
	char * pstr;
	pstr = str;
	while (*pstr != '\0') pstr++;
	try {
		while (*string != '\0') {
			if ((pstr - str) == (sizeof(str) / sizeof(char) - 1)) {
				*pstr = '\0';
				throw 1;
			}
			*pstr = *string;
			pstr++; string++;
			if (*string == '\0') {
				*pstr = '\0';
				break;
			}
		}
	}
	catch (int i) {
		cout << "Only a part of string has been concatenated" << endl;
	}
}

void textContainer::stringCat(char * str, char * destination, char * endArray) {



	while (*str != '\0') {
		if (destination == endArray) {
			*destination = '\0';
			break;
		}
		*destination = *str;
		destination++; str++;
		if (*str == '\0') {
			*destination = '\0';
			break;
		}
	}
}

textContainer textContainer::operator+(textContainer obj) {
	textContainer buffer;

	char * pstr = buffer.str;
	strcopy(this->str, pstr);
	buffer.stringCat(obj.str);

	return buffer;
}

bool stringComparisson(char * pstr, char * pstr2) {
	while (*pstr != '\0' || *pstr2 == '\0') {
		if (*pstr == *pstr2) {
			pstr++; pstr2++;
			if (*pstr == '\0' && *pstr2 == '\0') return true;
		}
		else
			return false;
	}
}

void textContainer::splitOnToken(char * p, int numRowLimit, int numColLimit, char * initialString) {
	int numRowCount = 0, numColCount = 0;
	char * pstr = initialString;
	while (*pstr != ' ' || *pstr != '\0') {
		*p = *pstr;
		if (numColCount < numColLimit) numColCount++;
		else {
			numColCount = 0;
			if (numRowCount < numRowLimit) numRowCount++;
			else {
				cout << "Token array is full";
				break;
			}
		}
		pstr++;
		p++;

		if (*pstr == ' ') {
			*p = '\0';
			while (numColCount < numColLimit) {
				p++;
				numColCount++;
			}
			numColCount = 0;
			numRowCount++;
			pstr++;
		}

		if (*pstr == '\0') {
			*p = '\0';
			break;
		}
	}
}

textContainer textContainer::operator-(textContainer obj) {

	char * pFirstObString = this->str;
	char * pSecondObString = obj.str;

	textContainer result;
	const int numArrCols = 80;
	const int numArrRows = 80;
	char firstOperandTokens[numArrRows][numArrCols];
	char secondOperandTokens[numArrRows][numArrCols];
	char * par1, *par2;
	par1 = &firstOperandTokens[0][0];
	par2 = &secondOperandTokens[0][0];

	this->splitOnToken(par1, numArrRows, numArrCols, pFirstObString);
	obj.splitOnToken(par2, numArrRows, numArrCols, pSecondObString);
	
	char * presult = &(result.str[0]);
	char * last = &(result.str[79]);
	while (presult <= last) {
		*presult = '\0';
		presult++;
	}

	presult = &(result.str[0]);

	int row = 0; //номер строки для обхода массива токенов1
	int row2 = 0;//номер строки для обхода массива токенов2

	while (par1 < (&firstOperandTokens[0][0] + numArrRows * numArrCols - 1)) {
		par1 = &firstOperandTokens[0][0];
		par1 = par1 + row * numArrCols;
		if (static_cast <int> (*par1) == -52) break;
		else static_cast <char> (*par1);
		while (par2 < (&secondOperandTokens[0][0] + numArrRows * numArrCols - 1)) {
			par2 = &secondOperandTokens[0][0];
			par2 = par2 + row2 * numArrCols;
			if (!stringComparisson(par1, par2)) {
				if (row2 == numArrRows) {
					while (*presult != '\0') presult++;
					if (presult != &(result.str[0])) {
						*presult = ' ';//добавляет пробел после скопированого слова, если оно в резалте будет не одно
						presult++;
					}
					stringCat(par1, presult, last);
					row++;
					row2 = 0;
					break;
				}
				row2++;
			}
			else {
				row++;
				row2++;
				break;
			}
		}
	}
	return result;
}

int main() {

	textContainer firstTestObj("This is what sun"),
		secondTestObj("this is thing. Test has been passed successfuly");
	textContainer thirdTestObj("This is what used to be");

	textContainer fourth;

	fourth = firstTestObj - thirdTestObj;
	firstTestObj.showString();
	cout << endl;
	thirdTestObj.showString();
	cout << endl;
	fourth.showString();

	/*
	textContainer resulting;
	resulting = firstTestObj + thirdTestObj;

	resulting.showString();
	*/
	/*
	cout << "Please enter the string: " << endl;

	textContainer INI;

	char ch[49];
	char * p = 0;
	p = ch;
	cin.get(p, 49);

	INI.setStr(p);
	INI.showString();
	cout << endl;
	INI.stringCat(" I locked the target. Destroy it.");
	cout << endl;

	INI.showString();
	cout << endl;
	INI.showString();
	*/

	system("pause");
	return 0;
}