#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

// gloabal variable
const int Length = 26;    // count english letter : constant 
char initialLetter = 65;  // initial character value 'A' = 65 --> ASKII code
char Possibil1[26];       // array to store anther possibil 1 to replac letter 
char Possibil2[26];       // array to store anther possibil 2 to replac letter   
string plaintext;

// plaintext structer
struct PlaintextEntry {
	char letter;
	int countLetter;
	float freqLetter;
};

PlaintextEntry PlaintextTable[Length];

PlaintextEntry EnglishFreq[Length] = { { 'E', 0, 12.02}, { 'T', 0, 9.10 }, { 'A', 0, 8.12 }, { 'O', 0, 7.68 }, { 'I', 0, 7.31 }, 
								   { 'N', 0, 6.95 }, { 'S', 0, 6.28 }, { 'R', 0, 6.02 }, { 'H', 0, 5.92 }, { 'D', 0, 4.32 }, 
								   { 'L', 0, 3.98 }, { 'U', 0, 2.88 }, { 'C', 0, 2.71 }, { 'M', 0, 2.61 }, { 'F', 0, 2.30 }, 
								   { 'Y', 0, 2.11 }, { 'W', 0, 2.09 }, { 'G', 0, 2.03 }, { 'P', 0, 1.82 }, { 'B', 0, 1.49 }, 
								   { 'V', 0, 1.11 }, { 'K', 0, 0.69 }, { 'X', 0, 0.17 }, { 'Q', 0, 0.11 }, { 'J', 0, 0.10 }, 
								   { 'Z', 0, 0.07 } };

// insert sentences "Plaintext" 
void Entries() {

LP:
	cout << "  Enter plaintext : ";
	cin >> plaintext;

	for (int i = 0; i < plaintext.length(); i++) {
		if (plaintext[i] < 65 || plaintext[i] > 90) {
			cout << "  Your plaintext invalid please enter anter plaintext just contain Capital Letter" << endl;
			goto LP;
		}
	}
}

// Initializtion Array 
void InitialTable() {

	for (int i = 0; i < Length; i++) {
		PlaintextTable[i].letter = initialLetter;
		PlaintextTable[i].countLetter = 0;
		PlaintextTable[i].freqLetter = 0;

		initialLetter++;
	}
	initialLetter = 65;
}

// Counter repetition letter
void Counter() {

	for (int i = 0; i < plaintext.length() ; i++) {
		for (int j = 0; j < Length ; j++) {

			if (plaintext[i] == PlaintextTable[j].letter) {
				PlaintextTable[j].countLetter++;
			}
		}
	}
}

// Descending refill according to the value of repetition
void Order() {

	PlaintextEntry temp;
	
	for (int i = 0; i < Length; i++) {
		for (int j = 0; j < Length; j++) {
			if (PlaintextTable[i].countLetter > PlaintextTable[j].countLetter) {
				temp = PlaintextTable[i];
				PlaintextTable[i] = PlaintextTable[j];
				PlaintextTable[j] = temp;
			}
		}
	}
}

// Other possibilities to replacing the letter with another suitable one
void Possibil() {

	float someSmallNumber = 0.1;
	char temp;

	for (int i = 0; i < Length; i++) {
		Possibil1[i] = Possibil2[i] = EnglishFreq[i].letter;
	}

	for (int i = 0; i < Length; i++) {

		if ((EnglishFreq[i].freqLetter - EnglishFreq[i + 2].freqLetter) < someSmallNumber 
			&& EnglishFreq[i + 2].freqLetter != '\0') {

			temp = Possibil1[i];
			Possibil1[i] = Possibil1[i + 2];
			Possibil1[i + 2] = temp;
		}

		if ((EnglishFreq[i].freqLetter - EnglishFreq[i + 1].freqLetter) < someSmallNumber
			&& EnglishFreq[i + 1].freqLetter != '\0') {

			temp = Possibil2[i];
			Possibil2[i] = Possibil2[i + 1];
			Possibil2[i + 1] = temp;
		}
	}
}

// Replacing the letter with another suitable one
void Ciphertext() {

	Entries();
	InitialTable();
	Counter();
	Order();
	Possibil();

	string ciphertext1, ciphertext2, ciphertext3;
	ciphertext1 = ciphertext2 = ciphertext3 = plaintext;

	for (int i = 0; i < plaintext.length(); i++) {
		for (int j = 0; j < Length; j++) {

			if (plaintext[i] == PlaintextTable[j].letter) {

				ciphertext1[i] = EnglishFreq[j].letter;
				ciphertext2[i] = Possibil1[j];
				ciphertext3[i] = Possibil2[j];
			}
		}
	}
	cout << endl;
	cout << "  ciphertext result 1 : " << ciphertext1 << endl;
	cout << endl;
	cout << "  ciphertext result 2 : " << ciphertext2 << endl;
	cout << endl;
	cout << "  ciphertext result 3 : " << ciphertext3 << endl;

	cout << endl;
	cout << "  The difference between the letters in the texts above is shown here" << endl;
	cout << "  English freq. letter : ";
	for (int j = 0; j < Length; j++) {

		cout << EnglishFreq[j].letter;
	}          
	cout << endl;
	cout << "  Possibil 1 letter :    " << Possibil1 << endl;
	cout << "  Possibil 2 letter :    " << Possibil2 << endl;
}

// Calculate the frequency
void Frequency() {

	float len = plaintext.length();

	for (int i = 0; i < Length; i++) {
		PlaintextTable[i].freqLetter = (PlaintextTable[i].countLetter / len) * 100;
	}
}

// Extra service for duplicate letter printing
void PrintTable() {

	Entries();
	InitialTable();
	Counter();
	Frequency();
	Order();

	cout << "  Table count letters :" << endl;

	for (int i = 0; i < Length; i++) {
		cout << "  " << PlaintextTable[i].letter << " | " << PlaintextTable[i].countLetter << " | " << PlaintextTable[i].freqLetter << endl;
	}
}

int main()
{
	char choice;
	bool next = true;
	
	cout << " " << endl;
	cout << "  You are welcome in Least-Simple Substitution" << endl;

	do
	{
		plaintext = "";
		
		cout << "  -------------------  " << endl;
		cout << "  Choose from menu " << endl;
		cout << "  1. Print chipertext result " << endl;
		cout << "  2. Print table result " << endl;
		cout << "  3. End " << endl;
		cout << "  -------------------  " << endl;
		cout << "  Your choice : ";
		cin >> choice;

		switch (choice) {
			case '1': Ciphertext(); break;
			case '2': PrintTable(); break;
			case '3': next = false; break;
		default: cout << "  Your choice is not valid" << endl; break;
		}

	} while (next);

	system("PAUSE");
    return 0;
}
