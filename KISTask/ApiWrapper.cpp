#include "stdafx.h"

ApiWrapper::ApiWrapper(bool result)
{
	if (!result)
	{
		std::string error = GetLastErrorAsString();
		throw std::runtime_error(error);
	}
}

std::string ApiWrapper::GetLastErrorAsString()
{
	DWORD lastError = ::GetLastError();
	if (lastError == 0)
		return std::string();

	LPSTR messageBuffer = nullptr;
	DWORD size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	LocalFree(messageBuffer);

	return message;
}
