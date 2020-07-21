#pragma once
#include "Includes.h"

class Preferences
{
public:
	static char bookDir[2020];
	static char regDir[2020];
	static void CreatePreferences();
	static std::string GetBookDirectory();
	static std::string GetFileName();
	static std::string GetDirectory();
};
inline char Preferences::bookDir[2020];
inline char Preferences::regDir[2020];