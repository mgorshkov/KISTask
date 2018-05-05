#pragma once

#include <string>

class ApiWrapper
{
public:
	explicit ApiWrapper(bool result);

private:
	static std::string GetLastErrorAsString();
};
