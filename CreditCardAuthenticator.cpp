#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

#include "CreditCardAuthenticator.h"

using namespace std;

const int kMinimumCreditCardSize = 13;
const int kMaximumCreditCardSize = 16;
const int kModCheck = 10;
const int kEndOfNumbers = 0;
const int kEndOfLine = 1024;

namespace creditcardauthenticator
{

	long long GetCreditCardNumber()
	{
		long long creditCardNumber = 0;
		cout << "Enter Credit Card Number : ";
		cin >> creditCardNumber;
		bool isGood = !cin.fail();

		while (!isGood)
		{
			cin.clear();
			cin.ignore(kEndOfLine, '\n');
			cout << endl << "Please Try Again : ";
			cin >> creditCardNumber;
			isGood = !cin.fail();

		}

		return creditCardNumber;
	}

	int GetSize(long long creditCardNumber)
	{
		int creditCardSize = 0;
		while (creditCardNumber != 0)
		{
			creditCardNumber /= 10;
			creditCardSize++;
		}
		return creditCardSize;
	}

	int GetPrefix(long long creditCardNumber, int desiredLength, int creditCardSize)
	{
		int cardNumber = 0;
		int counter = creditCardSize - desiredLength;
		if (desiredLength >= creditCardSize)
		{
			cardNumber = creditCardNumber;
			return cardNumber;
		}
		else
		{
			while (counter != 0)
			{
				creditCardNumber /= 10;
				counter--;
			}
			cardNumber = creditCardNumber;
			return cardNumber;
		}

	}

	string GetCardType(long long creditCardNumber, int creditCardSize)
	{

		int firstNumber = GetPrefix(creditCardNumber, 1, creditCardSize);
		int firstTwoNumbers = GetPrefix(creditCardNumber, 2, creditCardSize);
		if (firstNumber == 4)
		{
			return "Visa";
		}
		else if (firstNumber == 5)
		{
			return "Master Card";
		}
		else if (firstNumber == 6)
		{
			return "Discover Card";
		}
		else if (firstTwoNumbers == 37)
		{
			return "American Express Card";
		}
		else
		{
			return "Invalid";
		}

	}

	int GetDigit(int number)
	{
		if ((number % 10) == 0 && number != 10)
		{
			return number;
		}
		else if ((number % 10) > 0)
		{
			int firstDigit = number / 10;
			int secondDigit = number % 10;
			int sum = firstDigit + secondDigit;
			return sum;

		}
	}

	int SumOfDoubleEvenPlace(long long creditCardNumber, int creditCardSize)
	{
		ofstream fout;
		ifstream fin;
		fout.open("Even Numbers.txt");
		int counter = 0;
		int sumOfDoubleEvenPlace = 0;
		int number = 0;

		while (creditCardNumber != 0)
		{
			++counter;
			bool isEven = counter % 2 == 0;
			int digit = creditCardNumber % 10;
			if (isEven)
			{
				digit = 2 * digit;
				digit = GetDigit(digit);
				fout << digit << endl;
			}
			creditCardNumber /= 10;
		}
		fout << kEndOfNumbers << endl;
		fout.close();

		fin.open("Even Numbers.txt");
		while (!fin.eof())
		{
			fin >> number;
			sumOfDoubleEvenPlace += number;
		}
		fin.close();
		return sumOfDoubleEvenPlace;
	}

	int SumOfOddPlace(long long creditCardNumber, int creditCardSize)
	{
		ofstream fout;
		ifstream fin;
		fout.open("Odd Numbers.txt");
		int counter = 0;
		int sumOfOddPlace = 0;
		int number = 0;

		while (creditCardNumber != 0)
		{
			++counter;
			bool isOdd = counter % 2 != 0;
			int digit = creditCardNumber % 10;
			if (isOdd)
			{
				fout << digit << endl;
			}
			creditCardNumber /= 10;
		}
		fout << kEndOfNumbers << endl;
		fout.close();

		fin.open("Odd Numbers.txt");
		while (!fin.eof())
		{
			fin >> number;
			GetDigit(number);
			sumOfOddPlace += number;
		}
		fin.close();
		return sumOfOddPlace;
	}

	bool IsPrefixMatched(long long creditCardNumber, int creditCardSize, string cardType)
	{
		if (cardType == "Visa")
		{
			bool isMatched = GetPrefix(creditCardNumber, 1, creditCardSize) == 4;
			return isMatched;

		}
		else if (cardType == "Master Card")
		{
			bool isMatched = GetPrefix(creditCardNumber, 1, creditCardSize) == 5;
			return isMatched;
		}
		else if (cardType == "Discover Card")
		{

			bool isMatched = GetPrefix(creditCardNumber, 1, creditCardSize) == 6;
			return isMatched;
		}
		else if (cardType == "American Express")
		{
			bool isMatched = GetPrefix(creditCardNumber, 2, creditCardSize) == 37;
			return isMatched;
		}
	}

	bool IsValid(int creditCardSize, bool isPrefixMatched, int sumOfDoubleEvenPlace, int sumOfOddPlace)
	{
		bool isRightSize = creditCardSize >= kMinimumCreditCardSize && creditCardSize <= kMaximumCreditCardSize;
		bool isMatched = isPrefixMatched;
		bool isDivisible = (sumOfDoubleEvenPlace + sumOfOddPlace) % kModCheck == 0;
		bool isValid = isRightSize && isMatched && isDivisible;
		return isValid;
	}

	void DisplayResults(bool isValid)
	{
		if (isValid)
		{
			cout << "Valid." << endl;
		}
		else if (!isValid)
		{
			cout << "Invalid." << endl;
		}
		return;
	}

	bool IsAgain()
	{
		bool isAgain = 0;
		char answer = 0;
		cout << "Would you like to check another card? Y or N? : ";
		cin >> answer;
		bool isYesOrNo = !cin.fail() && ((answer == 'Y' || answer == 'N') || (answer == 'y' || answer == 'n'));
		if (!isYesOrNo)
		{
			cin.clear();
			cin.ignore(kEndOfLine, '\n');
			cout << "Please try again." << endl << "Check another card? : ";
			cin >> answer;
			isYesOrNo = !cin.fail() && ((answer == 'Y' || answer == 'N') || (answer == 'y' || answer == 'n'));
		}
		if (answer == 'Y' || answer == 'y')
		{
			bool isAgain = 1;
			cout << "yes";
			return isAgain;
		}
		else if (answer == 'N' || answer == 'n')
		{
			bool isAgain = 0;
			cout << "no";
			return isAgain;
		}
		return isAgain;
	}

	void ReRun(bool isAgain)
	{
		if (isAgain)
		{
			long long creditCardNumber = GetCreditCardNumber();
			int creditCardSize = GetSize(creditCardNumber);
			string cardType = GetCardType(creditCardNumber, creditCardSize);
			int sumOfDoubleEvenPlace = SumOfDoubleEvenPlace(creditCardNumber, creditCardSize);
			int sumOfOddPlace = SumOfOddPlace(creditCardNumber, creditCardSize);
			bool isPrefixMatched = IsPrefixMatched(creditCardNumber, creditCardSize, cardType);
			bool isValid = IsValid(creditCardSize, isPrefixMatched, sumOfDoubleEvenPlace, sumOfOddPlace);
			DisplayResults(isValid);
		}
		else
		{
			return;
		}
	}
}