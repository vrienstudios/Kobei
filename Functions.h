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

	static mshtml::IHTMLElement^ GetFirstElementByClassName(System::Collections::IEnumerator^ enumerable, System::String^ className, unsigned int length) {
		if (length == NULL) {
			length = 0;
			while (enumerable->MoveNext())
				length++;
			enumerable->Reset();
		}
		for (unsigned int idx = 0; idx < length; idx++) {
			enumerable->MoveNext();
			if (safe_cast<mshtml::IHTMLElement^>(enumerable->Current)->className == className)
				return safe_cast<mshtml::IHTMLElement^>(enumerable->Current);
		}
		return nullptr;
	}

	static VTable^ GetAllElementsByClassName(System::Collections::IEnumerator^ enumerable, System::String^ className, unsigned int length) {
		VTable^ list = gcnew VTable(mshtml::IHTMLElement::typeid);
		if (length == NULL) {
			length = 0;
			while (enumerable->MoveNext())
				length++;
			enumerable->Reset();
		}
		unsigned int i = 0;
		for (unsigned int idx = 0; idx < length; idx++) {
			enumerable->MoveNext();
			System::Console::WriteLine(safe_cast<mshtml::IHTMLElement^>(enumerable->Current)->className);
			if (safe_cast<mshtml::IHTMLElement^>(enumerable->Current)->className == className) {
				list->Add((System::Object^)i, safe_cast<mshtml::IHTMLElement^>(enumerable->Current));
				i++;
			}
		}
		return list;
	}
};