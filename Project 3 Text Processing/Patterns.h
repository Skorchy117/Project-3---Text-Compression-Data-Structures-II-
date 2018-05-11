#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class Patterns {
private:
	int characterComparison = 0;
	int stringComparisons = 0;
	double averageComparison;
public:
	int KMPmatch(const string &text, const string& pattern);
	int BMmatch(const string &text, const string &pattern);
	int getcharacterComparison();
	double getAverageComparison();
protected:
	vector<int> buildLastFunction(const string &pattern);
	vector<int> computeFailFunction(const string &pattern);
};