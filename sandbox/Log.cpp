#include "Log.h"

using namespace Log;

#include <iostream>
#include <ostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <Windows.h>

using namespace std;

bool Log::StopOnErrors = true;;



Handler Log::Error(std::cerr, "ERROR");
Handler Log::Warning(std::cerr, "WARNING");
Handler Log::Info(std::cout, "INFO");
Handler Log::Debug(std::cerr, "DEBUG");


/*
Prints an [hh:mm:ss.ms] time stamp. Surely there is an easier way to do this. :(
*/
string Log::GetTimeStamp()
{
	const float totalSeconds = 0;// Game::Instance().Time.TotalSeconds();

	int ms = (int)truncf(totalSeconds * 1000.f) % 1000;

	int ss = (int)floor(totalSeconds);

	int sec = ss % 60;
	int hours = ss / 3600;
	int minutes = (ss % 3600) / 60;

	stringstream str;

	str << "[" << hours << ":";

	str.width(2);
	str.fill('0');

	str << minutes << ":";

	str.width(2);
	str << sec << ".";

	str.width(3);

	str << ms << "] ";

	return str.str();

}

// Create a string with last error message
const std::string Log::LastWinError()
{
	DWORD error = GetLastError();
	if (error)
	{
		LPVOID lpMsgBuf;

		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			std::string result(lpMsgStr, lpMsgStr + bufLen);

			LocalFree(lpMsgBuf);

			return result;
		}
	}
	return std::string();
}