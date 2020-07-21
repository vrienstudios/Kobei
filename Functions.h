#pragma once
struct Functions {
	static constexpr unsigned int SwitchString(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (SwitchString(str, h + 1) * 33) ^ str[h];
	}
};