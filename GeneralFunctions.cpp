#include "GeneralFunctions.h"

int GeneralFunctions::convertStringToNumber(const MyString& string)
{
	int numberResult = 0;
	const short ZERO_ASCII_CODE = '0';
	size_t index = 0;
	bool isNegative = false;
	while (string[index] != '\0')
	{
		if (string[index] == '-')
		{
			if (index != 0)
			{
				throw std::invalid_argument("String was not in the correct format!");
			}
			isNegative = true;
			index++;
		}
		if (!(string[index] >= '0' && string[index] <= '9'))
		{
			return -1;
		}
		numberResult *= 10;
		numberResult += string[index] - ZERO_ASCII_CODE;
		index++;
	}
	return isNegative ? -numberResult : numberResult;
}

double GeneralFunctions::convertStringToDouble(const MyString& string)
{
	//not precise, but for the seek of the application is enough
	const short ZERO_ASCII_CODE = '0';
	size_t index = 0;
	double number = 0;
	bool isAfterPoint = false;
	bool isNegative = false;
	size_t countDigitsAfterPoint = 0;
	while (string[index] != '\0')
	{
		if (string[index] == '-')
		{
			if (index != 0)
			{
				throw std::invalid_argument("String was not in the correct format!");
			}
			isNegative = true;
			index++;
		}
		if (string[index] == '.')
		{
			if (isAfterPoint)
			{
				throw std::invalid_argument("String was not in the correct format!");
			}
			isAfterPoint = true;
			index++;
			continue;
		}
		if (!(string[index] >= '0' && string[index] <= '9'))
		{
			throw std::invalid_argument("String was not in the correct format!");
		}
		number *= 10;
		number += string[index] - ZERO_ASCII_CODE;
		index++;
		isAfterPoint ? countDigitsAfterPoint++ : countDigitsAfterPoint;
	}
	for (size_t i = 0; i < countDigitsAfterPoint; i++)
	{
		number /= 10;
	}
	return isNegative ? -number : number;
}