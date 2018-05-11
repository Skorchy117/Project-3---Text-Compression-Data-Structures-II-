#include "Patterns.h"

int Patterns::KMPmatch(const string & text, const string & pattern)
{
	int n = text.size();
	int m = pattern.size();
	std::vector<int> fail = computeFailFunction(pattern);
	int i = 0;					// text index
	int j = 0;					// pattern index
	while (i < n) {
		characterComparison++;
		if (pattern[j] == text[i]) {
			if (j == m - 1)
				return i - m + 1;			// found a match
			i++;  j++;
		}
		else if (j > 0)
		{
			j = fail[j - 1];				// shift 
			stringComparisons++;
		}
		else
		{
			i++;							// shift
			stringComparisons++;
		}
	}
	return -1;					// no match
}

int Patterns::BMmatch(const string & text, const string & pattern)
{
	std::vector<int> last = buildLastFunction(pattern);
	int n = text.size();
	int m = pattern.size();
	int i = m - 1;
	if (i > n - 1)				// pattern longer than text?
		return -1;				// ...then no match
	int j = m - 1;
	do {
		characterComparison++;
		if (pattern[j] == text[i])
			if (j == 0) return i;			// found a match
			else {							// looking-glass heuristic
				i--; j--;					// proceed right-to-left
			}
		else {					// character-jump heuristic
			i = i + m - std::min(j, 1 + last[text[i]]);			
			j = m - 1;
			stringComparisons++;					// shift
		}
	} while (i <= n - 1);
	return -1;					// no match
}

int Patterns::getcharacterComparison()
{
	return characterComparison;
}

double Patterns::getAverageComparison()
{
	if (stringComparisons == 0)
	{
		return 1;
	}
	else return static_cast<double>(characterComparison)/stringComparisons;
}

vector<int> Patterns::buildLastFunction(const string & pattern)
{
	const int N_ASCII = 128;			// number of ASCII characters
	int i;
	std::vector<int> last(N_ASCII);		// assume ASCII character set
	for (i = 0; i < N_ASCII; i++)		// initialize array
		last[i] = -1;
	for (i = 0; i < pattern.size(); i++) {
		last[pattern[i]] = i;			// (implicit cast to ASCII code)
	}
	return last;
}

vector<int> Patterns::computeFailFunction(const string & pattern)
{
	std::vector<int> fail(pattern.size());
	fail[0] = 0;
	int m = pattern.size();
	int j = 0;
	int i = 1;
	while (i < m) {
		if (pattern[j] == pattern[i]) {		// j + 1 characters match
			fail[i] = j + 1;
			i++;  j++;
		}
		else if (j > 0)				// j follows a matching prefix
			j = fail[j - 1];
		else {					// no match
			fail[i] = 0;
			i++;
		}
	}
	return fail;
}