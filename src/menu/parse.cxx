//#include <stdio.h>
//#include <iostream>
#include <fstream>

#include "parse.hxx"

const bool menu::parse (const std::string & filename, std::map <std::string, menu::item> & options)
{
	std::map <std::string, menu::item> _options;
	std::ifstream file;
	std::string line = "";
	//std::stringstream sline;
	menu::item item;
	//bool success;
	
	file.open (filename);
	
	if (!file.is_open ())
		return false;
	
	//success = true;
	while (file.good ())
	{
		do
		{
			if (!std::getline (file, line))
			{
				goto ending;
				//success = false;
				//break;
				//file.close ();
				//return false;
			}
		}
		while (line.empty ());
		//if (!success)
		//	break;
		item.value = line;
		
		do
		{
			if (!std::getline (file, line))
			{
				goto ending;
				//success = false;
				//break;
				//file.close ();
				//return false;
			}
		}
		while (line.empty ());
		//if (!success)
		//	break;
		item.selection = line;
		
		do
		{
			if (!std::getline (file, line))
			{
				goto ending;
				//success = false;
				//break;
				//file.close ();
				//return false;
			}
		}
		while (line.empty ());
		//if (!success)
		//	break;
		item.description = line;
		
		_options [item.selection] = item;
		//options.insert (std::pair <std::string, menu::item> (item.selection, item));
	}
	
ending:
	file.close ();
	
	// Guarantee that if an error occurs, the original object is unchanged;
	// that is why it is only set here, at the end:
	options = _options;
	
	return true;
}
