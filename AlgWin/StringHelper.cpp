#include "stdafx.h"
#include "StringHelper.h"

template<typename Out>
StringHelper<Out>::StringHelper()
{
}

template<typename Out>
StringHelper<Out>::~StringHelper()
{
}

template<typename Out>
void StringHelper<Out>::split(const std::string & s, char delim, Out result)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

template<typename Out>
std::vector<std::string> StringHelper<Out>::split(const std::string & s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
