#include <iostream>
#include <sstream>
//#include <bitset>
//#include <string>
//#include <boost/algorithm/string.hpp>
//#include <math.h>
#include <cmath>
#include <iomanip>

#include <boost/dynamic_bitset.hpp>

#include "supporters.h++"


//void display_error_insufficient_arguments (void)
//{
//}

void display_main_menu (const std::map <std::string, menu::item> & options, const std::string & indentation, const std::string & current)
{
	for (auto & option: options)
	{
		//std::cout << option.first << ": " << option.second << std::endl;
		std::cout << indentation;
		if (option.first == current)
			std::cout << '[' << option.second.selection << ". " << option.second.description << ']' << std::endl;
		else
			std::cout << ' ' << option.second.selection << ". " << option.second.description << ' ' << std::endl;
	}
}

const std::string pad (std::string source, const unsigned short int & indentation, const char & indenter, const bool & postfix)
{
	//std::stringstream ss;
	if (postfix)
		while (source.length () < indentation)
			source = source + indenter;
	else
		while (source.length () < indentation)
			source = indenter + source;
	//ss << std::setw (indenation) << source;
	//return ss.str();
	return source;
}

// Convert a binary number to a hexadecimal number:
//const std::string b2h (const std::string & number, const unsigned short int & digits)
const std::string b2h (const std::string & number)
{
	/*
	std::bitset <digits> bs (number);
	unsigned long long int n = bs.to_ullong ();
	stringstream ss;
	ss << hex << n;
	return "0x" + ss.str ();
	*/
	
	//if (number.empty ())
	//	return "";
	
	unsigned long long int n = 0;
	unsigned long long int length = number.length ();
	std::stringstream ss;
	
	for(unsigned long long int i = 0; i < length; ++ i)
	{
		n += (number [length-i-1] - 48) * std::pow (2, i);
	}
	
	ss << std::setbase (16);
	ss << n;
	
	return ss.str ();
}

const std::string h2b (const char & c)
{
	// TODO handle default / error
	switch (std::toupper (c))
	{
		case '0': return "0000";
		case '1': return "0001";
		case '2': return "0010";
		case '3': return "0011";
		case '4': return "0100";
		case '5': return "0101";
		case '6': return "0110";
		case '7': return "0111";
		case '8': return "1000";
		case '9': return "1001";
		case 'A': return "1010";
		case 'B': return "1011";
		case 'C': return "1100";
		case 'D': return "1101";
		case 'E': return "1110";
		case 'F': return "1111";
		default: return "";
	}
}

// Convert a hexadecimal number to a binary number:
const std::string h2b (const std::string & number/*, const unsigned short int & digits*/)
{
	/*
	std::stringstream ss;
	ss << std::hex << number;
	unsigned long long int n;
	ss >> n;
	//std::bitset <digits> bs (n);
	//std::bitset <DIGITS> bs (n);
	boost::dynamic_bitset <> bs (digits, n);
	
	return bs.to_string ();
	//ss.clear ();
	//ss << bs;
	//ss.str ();
	*/
	
	unsigned long long int length = number.length ();
	std::string result = "";
	
	for(unsigned long long int i = 0; i < length; ++ i)
	{
		result = h2b (number [length-i-1]) + result;
	}
	
	return result;
}

const unsigned short int s2usint (const std::string & number)
{
	std::stringstream ss;
	unsigned short int n;
	
	ss << number;
	ss >> n;
	
	return n;
}
