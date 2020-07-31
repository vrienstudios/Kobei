#pragma once
#include <ctype.h>
#include <cctype>
struct Functions {
	static constexpr unsigned int SwitchString(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (SwitchString(str, h + 1) * 33) ^ str[h];
	}

	static constexpr unsigned int LeadingIntegralCount(const char* str, int h = 0) {
		return (unsigned char(str[h]) >= '0' && (unsigned char)str[h] <= '9') ? LeadingIntegralCount(str, h + 1) : h;
	}

	static unsigned int CountFollowingWhiteSpace(std::string str, int h, int i = 0) {
		return (h > 0) ? (std::isspace(str[h])) ? CountFollowingWhiteSpace(str, h - 1, i + 1) : i : CountFollowingWhiteSpace(str, str.length() - 1);
	}
};