#pragma once
#include"pch.h"

class Error
{
public:
	static void error(const std::string& err)
	{
#if defined(NDEBUG)
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring werr = converter.from_bytes(err);

		int msgboxID = MessageBoxW(
			NULL,
			(LPCWSTR)(werr.c_str()),
			(LPCWSTR)L"Error",
			MB_ICONERROR | MB_OK
		);
#else
		std::cerr << "Error: " << err << std::endl;
#endif
	}
};

