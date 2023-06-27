#include "ThemeManager.h"
#include <iostream>

ThemeManager& ThemeManager::getInstance()
{
	static ThemeManager tm;
	return tm;
}

void ThemeManager::changeTheme(Theme theme)
{
	HANDLE colour = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (theme)
	{
	case Theme::Harmony:
		SetConsoleTextAttribute(colour, 13);
		break;
	case Theme::Colourful:
		SetConsoleTextAttribute(colour, 3);
		break;
	case Theme::Spring:
		SetConsoleTextAttribute(colour, 10);
		break;
	case Theme::FirstPlace:
		SetConsoleTextAttribute(colour, 78);
		break;
	case Theme::SecondPlace:
		SetConsoleTextAttribute(colour, 48);
		break;
	case Theme::ThirdPlace:
		SetConsoleTextAttribute(colour, 90);
		break;
	case Theme::ErrorMessage:
		SetConsoleTextAttribute(colour, 4);
		break;
	default:
		SetConsoleTextAttribute(colour, 7);
		break;
	}
}

void ThemeManager::printThemeName(Theme theme) const
{
	switch (theme)
	{
	case Theme::Default:
		std::cout << "Default";
		break;
	case Theme::Harmony:
		std::cout << "Harmony";
		break;
	case Theme::Colourful:
		std::cout << "Colourful";
		break;
	case Theme::Spring:
		std::cout << "Spring";
		break;
	default:
		std::cout << "Undefined";
		break;
	}
}