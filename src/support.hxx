#pragma once

//// Effectively, he number of GPIO pins which the module features:
//#if !defined (DIGITS)
//	// A default value.
//	#define DIGITS 8
//#endif

#include <map>
//#include <iostream>
//#include <sstream>
#include <string>

#include "menu/item"

//void display_error_insufficient_arguments (void);
void display_main_menu (const std::map <std::string, menu::item> &, const std::string & = "", const std::string & = "");

const bool is_numeric	(const std::string &);

const std::string pad (std::string, const unsigned short int & /*minimum length*/, const char & /*filler*/ = ' ', const bool & /*append*/ = false, const bool & /*force minimum length*/ = false);

// Convert a binary number to a hexadecimal number:
// http://www.cplusplus.com/forum/windows/35848/
//const std::string b2h (const std::string & number, const unsigned short int &);
const std::string b2h (const std::string &);
// Convert a hexadecimal number to a binary number:
// http://stackoverflow.com/questions/18310952/convert-strings-between-hex-format-and-binary-format
const std::string h2b (const std::string &/*, const unsigned short int & = 8*/);
const std::string h2b (const char &);

const unsigned short int s2usint (const std::string & number);
