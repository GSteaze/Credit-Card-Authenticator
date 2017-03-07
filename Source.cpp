#include <iostream>
#include <string>
#include <fstream>

#include "CreditCardAuthenticator.h"

using namespace std;

using namespace creditcardauthenticator;

int main()
{
	bool isAgain = 0;
	do
	{
		long long creditCardNumber = GetCreditCardNumber();
		int creditCardSize = GetSize(creditCardNumber);
		string cardType = GetCardType(creditCardNumber, creditCardSize);
		int sumOfDoubleEvenPlace = SumOfDoubleEvenPlace(creditCardNumber, creditCardSize);
		int sumOfOddPlace = SumOfOddPlace(creditCardNumber, creditCardSize);
		bool isPrefixMatched = IsPrefixMatched(creditCardNumber, creditCardSize, cardType);
		bool isValid = IsValid(creditCardSize, isPrefixMatched, sumOfDoubleEvenPlace, sumOfOddPlace);
		DisplayResults(isValid);
		bool isAgain = IsAgain();

	} while (isAgain);

	return 0;
}
