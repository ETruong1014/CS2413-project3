/*
 * project3.cpp
 *
 *  Created on: Mar 16, 2021
 *      Author: erictruong1014
 */

#include<iostream>

using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++) {
			A[i] = '\0'; //changes each char to \0
	}
}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) { //copies each char from A to B
			B[i] = A[i];
	}
}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') size++;
	return size; //size is the last index position
}

class myString;

class myString {
	friend ostream& operator << (ostream& s, myString& A);
protected:
	char* strArray;
	int size;
	void strCpy (char* A, char* B, int n);
public:
	myString ();
	myString(char* inpStr);
	myString (myString& B);
	int Size();
	char* getWord();
    bool operator == (myString& B);
    bool operator > (myString& B);
    bool operator < (myString& B);
    myString& operator = (myString& B);
    myString& operator = (char* B);
};

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}

// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}

// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0') //counts number of letters in parameter word
		i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1); //empties the string array
	for (int j=0; j < size; j++) //copies letters to the string array
		strArray[j] = inpStr[j];
}

// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray; //deletes current string array
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1); //empties the string array
	stringCopy (B.strArray, size, strArray); //copies the string from myString B
}

char* myString::getWord()
{
	return strArray;
}

// getter for size of myString
int myString::Size () {
	return size;
}

// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
	//almost identical code to the non-default constructor using a char array parameter
	if (B == NULL) { //default constructor if B is NULL
		size = 0;
		strArray = new char[1];
		strArray[0] = '\0';
		return *this;
	}
	else {
		int i = 0;
		while (B[i] != '\0') { //counts number of letters in parameter word
			i++;
		}
		size = i;
		strArray = new char[size];
		emptyString (strArray, size+1); //empties the string array
		for (int j = 0; j < size; j++) { //copies letters to the string array
			strArray[j] = B[j];
		}

		return *this;
	}

}

// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
	//almost identical code to the non-default constructor using a myString paramenter

	delete [] strArray; //deletes current string array
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1); //empties the string array
	stringCopy (B.strArray, size, strArray); //copies the string from myString B

	return *this;
}

// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {

	bool same = true; //value to determine if strings are the same
	int i = 0; //index of comparison

	if (size != B.size) { //if myStrings are different sizes, they cannot be the same
		same = false;
	}
	else {
		while (i < size) { //iterates through every character in the myStrings until the end or a difference is found
			if (strArray[i] != B.strArray[i]) { //if a character doesn't match, the myStrings are different
				same = false;
				break;
			}
			i++;
		}
	}
	return same;
}

// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {

	bool less = true; //value to determine if this myString is less than B
	bool sameStart = true; //if a word starts with the same letters as the other
	int i = 0; //index of comparison

	while (i < size && i < B.size) { //iterates through letters of this and B until the end of one of the myStrings
			if (strArray[i] != B.strArray[i]) { //if there is a letter difference, one must be less than the other
				sameStart = false;
				if (strArray[i] > B.strArray[i]) { //if the letter in this myString is greater than the letter in B, it is greater than B
					less = false;
					break;
				}
				else { //if the letter in this myString is less than the letter in B, it is less than B
					less = true;
					break;
				}
			}
			i++;
		}
	if (sameStart == true) { //check if a word that starts with the same letters as the other word is longer or shorter
		if (size > B.size) { //if this myString is longer than B, it is greater than B
			less = false;
		}
	}
	return less;
}

// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {

	bool greater = true; //value to determine if this myString is greater than B
	bool sameStart = true; //if a word starts with the same letters as the other
	int i = 0; //index of comparison

	while (i < size && i < B.size) { //iterates through letters of this and B until the end of one of the myStrings
		if (strArray[i] != B.strArray[i]) { //if there is a letter difference, one must be greater than the other
			sameStart = false;
			if (strArray[i] < B.strArray[i]) { //if the letter in this myString is less than the letter in B, it is less than B
				greater = false;
				break;
			}
			else { //if the letter in this myString is greater than the letter in B, it is greater than B
				greater = true;
				break;
			}
		}
		i++;
	}
	if (sameStart == true) { //check if a word that starts with the same letters as the other word is longer or shorter
		if (size < B.size) { //if this myString is shorter than B, it is less than B
			greater = false;
		}
	}
	return greater;
}

// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);

	char c;
	int i = 0;
	while (!cin.eof()) { //iterates until the end of the input
		cin.get(c); //gets the current char
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) { //if the current char is a letter, a period, or a hyphen, add to str and increment index
				if ( ((c >= 'a') && (c <= 'z')) ||
					 ((c >= 'A') && (c <= 'Z')) ||
					 ((c >= '0') && (c <= '9')) ||
					 (c == '.') || (c == '-')) {
					str[i++] = c;
				}
			}
			else if ((c == '\n') && (i > 0)) //if the character is the end of the line
				return str;
			else if ((c == ' ') && (i > 0)) //if the character is a white space
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}

class webLinks {

	friend ostream& operator << (ostream& s, webLinks& A);
	protected:
		myString URL; //URL of the site
		int numLinks; //number of hyper links this site links to
		webLinks** hyperLinks; //array of pointers to other sites
		int nextIdx = 0; //next available index in hyperLinks
	public:
		webLinks ();
		webLinks (myString& x, int n);
		~webLinks ();
		int getNumLinks();
		webLinks* getHyperLink(int i);
		myString& getURL();
        void addSite(myString& t);
		void addNeighbor(webLinks& link);
        void setNeighbors(int nei);
};

//prints the site name and its neighbors
ostream& operator << (ostream& s, webLinks& A)
{
	cout << A.URL << ":" << endl; //prints URL
	for (int i = 0; i < A.numLinks; i++) { //prints out each related link
		cout << "** ";
		cout << (*(A.hyperLinks[i])).URL; //prints the URL of the related link
		cout << endl;
	}
	cout << endl;
	return s;
}

//default constructor
webLinks::webLinks()
{
	numLinks = 0;
	hyperLinks = new webLinks*[0];
}

//non-default constructor
webLinks::webLinks(myString& x, int n)
{
	URL = x;
	numLinks = n;
	hyperLinks = new webLinks*[numLinks];
}

//returns URL
myString& webLinks::getURL()
{
	return URL;
}

//returns number of neighbor links
int webLinks::getNumLinks()
{
	return numLinks;
}

//returns pointer to the hyper link at i
webLinks* webLinks::getHyperLink(int i)
{
	return hyperLinks[i];
}

//destructor
webLinks::~webLinks()
{
	numLinks = 0;
	if (hyperLinks != NULL) delete [] hyperLinks; //deletes the array of hyperLinks pointers
}

//adds name of URL
void webLinks::addSite(myString& t)
{
	URL = t;
}

//sets number of neighbors
void webLinks::setNeighbors(int nei)
{
	numLinks = nei;
	delete [] hyperLinks; //deletes current array of hyperLinks
	hyperLinks = new webLinks*[numLinks]; //sets new size for hyperLinks
}

//adds neighbor link to hyperLinks
void webLinks::addNeighbor(webLinks& link)
{
	hyperLinks[nextIdx] = &link; //adds link to hyperLinks
	nextIdx++; //increment nextIdx
}

int main () {

	int numSites; //total number of sites
	int siteNo; //number of a site in the array
	int numNeighbors; //number of neighbors for a site
	int neighbor; //index number in main array for a neighbor

    char* token;
	myString* tokenString;

	cin >> numSites;
    cout << "Number of websites: " << numSites << endl;

	webLinks* myWeb = new webLinks [numSites];
	for (int i=0; i < numSites; i++) // read all URL and store them in the myWeb array of webLink objects
	{
		token = getNextToken(); //get URL name
		tokenString = new myString(token); //create a myString object with the token
		myWeb[i].addSite(*tokenString); //add the site to myWeb
	}
    // store the neighbours/hyperlinks
	for (int i = 0; i < numSites; i++)
	{
		cin >> siteNo >> numNeighbors; //retrieve site number and its number of neighbors
		myWeb[siteNo].setNeighbors(numNeighbors); //sets number of neighbors for given site
		for (int j=0; j < numNeighbors; j++) //iterates through every neighbor number for a given site
		{
			cin >> neighbor; //retrieves neighbor number
			myWeb[siteNo].addNeighbor((myWeb[neighbor])); //adds neighbor to given site
		}
	}

    // display all webLink objects using the overloaded << operator
	cout << "~~~~~WebLinks:" << endl;
	for (int i = 0; i < numSites; i++) {
		cout << myWeb[i];
	}

	cout << "~~~~~Webpages contained as hyperLinks:" << endl;
    // display all the incoming nodes here
	myString* incomingNodes; //array of myString objects to store incoming links
	for (int i = 0; i < numSites; i++) {
		cout << endl;
		incomingNodes = new myString[numSites - 1]; //initialize for maximum possible values, excludes current link itself
		int count = 0; //number of incoming links

		for (int j = 0; j < numSites; j++) { //checks every site for a link to the current site
			for (int k = 0; k < myWeb[j].getNumLinks(); k++) { //iterates through the hyperLinks array of the site at index j
				if (myWeb[i].getURL() == (*myWeb[j].getHyperLink(k)).getURL()) { //if the current site is contained in the hyperLinks array
					incomingNodes[count] = myWeb[j].getURL();
					count++;
					break;
				}
			}
		}
		cout << myWeb[i].getURL() << ": " << count << endl;
		for (int j = 0; j < count; j++) { //prints out every site that links to the current site
			cout << "** " << incomingNodes[j] << endl;
		}
		delete [] incomingNodes; //deletes current array of incoming nodes
	}

	delete [] myWeb;

	return 0;
}


