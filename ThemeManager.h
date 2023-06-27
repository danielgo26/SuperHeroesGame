#pragma once
#include <windows.h>
#include "Enums.h"

class ThemeManager
{
	ThemeManager() = default;
	ThemeManager(const ThemeManager& other) = delete;
	ThemeManager& operator=(const ThemeManager& other) = delete;
public:
	static ThemeManager& getInstance();
	void changeTheme(Theme theme);
	void printThemeName(Theme theme) const;
};