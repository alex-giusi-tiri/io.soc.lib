/*
	Based on
	https://github.com/numato/samplecode/tree/master/RelayAndGPIOModules/USBRelayAndGPIOModules/c/VCExpress2010/usbgpio8/USBGpio8Demo
*/

// A quick implmenetation.


#include <string>
#include <iostream>
#include <map>
#include <math.h>
//#include <boost/algorithm/string.hpp>

#include "menu/item"
#include "menu/parse"
#include "gpio"
#include "support"

// The number of GPIO pins which the module features:
//#define DIGITS 8

//int main (int argc, char * argv [])
//signed int main (const unsigned long long int argc, const char * argv [])
signed int main (const unsigned int argc, const char * argv [])
{
/*
	for (unsigned int i = 0; i < argc; ++ i)
		std::cout << argv [i] << ' ';
	std::cout << std::endl;
	std::cout << "Argument count: " << argc << std::endl;
*/
	
	gpio port;
	std::string option/* = ""*/;	// current option
	//std::string current;	// current hexadecimal value
	std::map <std::string, menu::item> options;
	//std::map <std::string, std::string> values;	// Maps binary values to selectable options.
	std::map <std::string, menu::item>::iterator searcher;
	unsigned long int digits_binary;	// Number of pins (number of binary digits).
	unsigned int digits_hexadecimal;
	
	
	if (argc < 3)
	{
		//display_usage ();
		std::cout << "Usage: '" << argv [0] << "' <port> <mapped values file>" << std::endl;
		std::cout << "\tExample: '" << argv [0] << "' /dev/ttyACM0 outputs.txt" << std::endl;
		std::cout << "\tExample: '" << argv [0] << "' COM3 outputs.txt" << std::endl;
		
		return 1;
	}
	
	//std::cout << pad (b2h ("10110010"), 5, '0') << std::endl;
	//std::cout << h2b ("b2") << std::endl;
	
	//return EXIT_SUCCESS;
	/*
	if (!is_numeric (argv [2]))
	{
		std::cout << argv [0] << ": " << argv [2] << " must be a positive integer in radix 10" << std::endl;
		
		return 1;
	}
	
	try
	{
		digits_binary = std::stoul (argv [2]);
	}
	catch (...)
	{
		std::cout << argv [0] << ": " << argv [2] << " must be a positive integer in radix 10" << std::endl;
		
		return 1;
	}
	
	if (digits_binary < 1)
	{
		std::cout << argv [0] << ": " << argv [2] << " must >= 1" << std::endl;
		
		return 1;
	}
	*/
	
	//digits_hexadecimal = digits_binary / 4;
	
	//if (digits_hexadecimal < 1)
	//	digits_hexadecimal = 1;
	
	//std::cout << " 2 :: " << digits_binary << std::endl;
	//std::cout << "16 :: " << digits_hexadecimal << std::endl;
	
	// Try parsing the mapped binary values:
	if (!menu::parse (argv [2], options))
	{
		std::cout << argv [0] << ": Error: Unable to parse the specified file (" << argv [2] << ')' << std::endl;
		
		return 2;
	}
	
	// Try opening the port:
	if (!port.connect (argv [1]))
	{
		std::cout << argv [0] << ": Error: Unable to open the specified port (" << argv [1] << ')' << std::endl;
		
		return 3;
	}
	
	// Find the pin count
	// by reading all the pins at once
	// as a string and then equally using its length.
	if (!port.execute ("gpio readall", option))
	{
		std::cout << '\'' << argv [0] << "': '" << argv [1] << "': Error: Could not detect the number of pins" << std::endl;
		
		return 3;
	}
	else
	{
		//std::cout << "       option :: [" << option << ']' << std::endl;
		//std::cout << "option_binary :: [" << option_binary << ']' << std::endl;
		
		digits_binary = h2b (option).length ();
		
		// The provided values should not exceed the number of pins.
		for (auto & opt : options)
		{
			//std::cout << "      selection :: " << opt.second.selection << std::endl;
			//std::cout << "    description :: " << opt.second.description << std::endl;
			//std::cout << "          value :: " << opt.second.value << std::endl;
			//
			//std::cout << "value.length () :: " << opt.second.value.length () << std::endl;
			
			if (opt.second.value.length () > digits_binary)
			{
				std::cout << argv [0] << ": Error: '" << argv [2] << "': At least one binary value exceeds the found number of pins" << std::endl;
				
				return 2;
			}
		}
	}
	
	digits_hexadecimal = ceil (digits_binary / float (4));
	
	// The port would be used only as output.
	if (!port.execute ("gpio iodir " + pad ("0", digits_hexadecimal, '0')))
			std::cout << "Error: Could not set GPIO direction to output" << std::endl;
	
	// Read the current value only at the beginning,
	// as I did not have enough time to debug the encountered errors when reading during the run-time.
	// This should normally be enough.
	if (!port.execute ("gpio readall", option))
		std::cout << "Error: Could not read current value" << std::endl;
	else
	{
		const std::string option_binary = h2b (option);
		
		//std::cout << "       option :: [" << option << ']' << std::endl;
		//std::cout << "option_binary :: [" << option_binary << ']' << std::endl;
		
		for (auto & opt : options)
		{
			//std::cout << "        opt :: [" << opt.second.value << ']' << std::endl;
			
		//	values [opt.second.value] = opt.second.selection;
			if (pad (opt.second.value, digits_binary, '0') == option_binary)	// It is expected that the same number of pins is outputted for either direction (gpio iodir).
			//if (pad (opt.second.value, option_binary.length (), '0') == option_binary)	// 'Correct' way/Alternative.
			{
				option = opt.second.selection;
				
				break;
			}
		}
	}
	
	
	while (true)
	{
		//current = "";
		//if (!port.execute ("gpio readall", current))
		//	std::cout << "Error: Could not read current value" << std::endl;
		
		std::cout << std::endl;
		//std::cout << "Current: [" << option << ']' << std::endl;
		std::cout << "Menu: " << std::endl;
		//std::cout << std::endl;
		//std::cout << "values [h2b (current)]: [" << values [h2b (current)] << ']' << std::endl;
		//display_main_menu (options, "\t", values [h2b (current)]);
		display_main_menu (options, "\t", option);
		//std::cout << std::endl;
		std::cout << "\t" << "E/e. Exit" << std::endl;
		std::cout << std::endl;
		std::cout << "Legend: [Current Selection]" << std::endl;
		std::cout << std::endl;
		std::cout << "Please select an option: ";
		
	search:
		std::getline (std::cin, option);
		//boost::algorithm::trim (option);
		
		if (option == "E" || option == "e")
		{
			// Reset all pins to logical off:
			//port.execute ("gpio writeall 00");
			break;
		}
		/*
		switch (true)
		{
			// Exit:
			case option == "E":
			case option == "e":
				break;
		}
		*/
		
		
		searcher = options.find (option);
		
		if (searcher == options.end ())
		{
			std::cout << '\'' << option << "': unavailable option; please reselect: ";
			
			goto search;
		}
		else
		{
			if (!port.execute ("gpio writeall " + pad (b2h (searcher -> second.value), digits_hexadecimal, '0')))
				std::cout << "\tFailed to interact with the device" << std::endl;
		}
	}
}
