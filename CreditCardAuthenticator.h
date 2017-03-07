#ifndef CREDITCARDAUTHENTICATOR_H
#define CREDITCARDAUTHENTICATOR_H

#include <string>

using namespace std;

namespace creditcardauthenticator
{
	long long GetCreditCardNumber();
	int GetSize(long long);
	int GetPrefix(long long, int, int);
	string GetCardType(long long, int);
	int GetDigit(int);
	int SumOfDoubleEvenPlace(long long, int);
	int SumOfOddPlace(long long, int);
	bool IsPrefixMatched(long long, int, string);
	bool IsValid(int, bool, int, int);
	void DisplayResults(bool);
	bool IsAgain();
	void ReRun(bool);
}
#endif

