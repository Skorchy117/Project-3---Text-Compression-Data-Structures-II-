#include <iostream>
#include <fstream>
#include <cctype>
#include <chrono>
#include "Patterns.h"
#include <fstream>

using namespace std;


struct information {
	double averageComparisons;
	int totalComparisons, found;
	chrono::milliseconds runtime;
};

string createText(string);
information processPattern(int, string, string);

int main()
{
	string textUS, textDNA, P;
	information value;
	ofstream outFile;
	int select, selectTwo;
	int cases = 1;
	textUS = createText("usdeclarPC.txt");
	textDNA = createText("humanDNA.txt");
	cout << "Please select which text you would like to work with: \n";
	cout << "1) humanDNA.txt\n2) usdeclarPC.txt\n";
	cout << "Option: ";
	cin >> select;
	cout << endl;
	outFile.open("resultsPM.txt");
	while (select != -1)
	{
		while (select > 2 || select < 1)
		{
			cout << "Please select one of the options above: ";
			cin >> select;
		}
		cout << "Please input a pattern you are looking for: ";
		cin.ignore();
		getline(cin, P);
		cout << endl;
		for (int i = 0; i < P.size(); i++)
		{
			P[i] = tolower(P[i]);
		}
		cout << "Please select a pattern searching method: \n";
		cout << "1) BM pattern matching\n2) KMP pattern matching\n";
		cout << "Option: ";
		cin >> selectTwo;
		cout << endl;
		while (selectTwo > 2 || selectTwo < 1)
		{
			cout << "Please select one of the options above: ";
			cin >> selectTwo;
		}
		outFile << "Case: " << cases << endl;
		outFile << "Text File: ";
		if (select == 1)
		{
			value = processPattern(selectTwo, textDNA, P);
			outFile << "humanDNA.txt" << endl;
		}
		else
		{
			value = processPattern(selectTwo, textUS, P);
			outFile << "usdeclarPC.txt" << endl;
		}
		outFile << "Pattern Matching Method: ";
		if (selectTwo == 1)
		{
			outFile << "Boyer-More\n";
		}
		else outFile << "Knuth-Morris-Pratt\n";
		outFile << "Pattern: " << P << endl;
		if (value.found != -1)
		{
			outFile << "Pattern was found.\n";
		}
		else outFile << "Pattern was not found\n";
		
		outFile << "Average Comparisons: " << value.averageComparisons << " || Characters Compared: " << value.totalComparisons << endl;
		outFile << "Runtime: " << value.runtime.count() << " ms" << endl << endl;
		cout << "1) humanDNA.txt\n2) usdeclarPC.txt\n";
		cout << "Please select which text file to work with (or input -1 to exit): ";
		cin >> select;
		cout << endl;
		cases++;
	}
	outFile.close();
	return 0;
}

string createText(string fileName)
{
	ifstream inFile;
	string buffer;
	string text = "";
	inFile.open(fileName);
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> buffer;
			for (int i = 0; i < buffer.size(); i++)
			{
				if (isalpha(buffer[i]))
				{
					buffer[i] = tolower(buffer[i]);
				}
			}
			text = text + buffer + " ";
		}
	}
	inFile.close();
	return text;
}

information processPattern(int matchingType, string text, string pattern)
{
	Patterns a;
	information info;
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elaspedTime;
	if (matchingType == 1)
	{
		start = chrono::system_clock::now();
		info.found = a.BMmatch(text, pattern);
		end = chrono::system_clock::now();
	}
	else
	{
		start = chrono::system_clock::now();
		info.found = a.KMPmatch(text, pattern);
		end = chrono::system_clock::now();
	}

	elaspedTime = end - start;
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds>(elaspedTime);

	info.runtime = ms;
	info.totalComparisons = a.getcharacterComparison();
	info.averageComparisons = a.getAverageComparison();
	return info;
}
