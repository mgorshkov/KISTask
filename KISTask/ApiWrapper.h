#pragma once

#include <Windows.h>
#include <string>

class ApiWrapper
{
public:
	ApiWrapper(bool result);

private:
	static std::string GetLastErrorAsString();
};
