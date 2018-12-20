
#include "stdafx.h"
#include "case_sensitive.h"
#include <ctype.h>

namespace afc{

std::string upper(std::string source)
{
	if (source.size() == 0){
		return "";
	}
	for(int i = 0; i < source.length(); i ++){
			source[i] = toupper(source[i]);
	}
	return source;
}

std::string lower(std::string source)
{
	if (source.size() == 0){
		return "";
	}
	for(int i = 0; i < source.length(); i ++){
		source[i] = tolower(source[i]);
	}
	return source;
}

} //namespace