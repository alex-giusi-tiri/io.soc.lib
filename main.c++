/*
	Based on
	https://github.com/numato/samplecode/tree/master/RelayAndGPIOModules/USBRelayAndGPIOModules/c/VCExpress2010/usbgpio8/USBGpio8Demo
*/

// A quick implmenetation.


#include <string>
#include <iostream>
#include <map>
//#include <boost/algorithm/string.hpp>

#include "menu/item"
#include "menu/parse"
#include "gpio"
#include "supporters"

// The number of GPIO pins which the module features:
//#define DIGITS 8

//int main (int argc, char * argv [])
signed int main (const unsigned long long int argc, const char * argv [])
{
/*
	for (unsigned int i = 0; i < argc; ++ i)
		std::cout << argv [i] << ' ';
	std::cout << std::endl;
	std::cout << "Argument count: " << argc << std::endl;
*/
	if (argc < 3)
	{
		//display_error_insufficient_arguments ();
		std::cout << "Usage: '" << argv [0] << "' '<port>' '<mapped values file>'" << std::endl;
		std::cout << "\tExample: '" << argv [0] << "' /dev/ttyACM0 outputs.txt" << std::endl;
		std::cout << "\tExample: '" << argv [0] << "' COM3 outputs.txt" << std::endl;
		
		return 1;
	}
	
	//std::cout << pad (b2h ("10110010"), 5, '0') << std::endl;
	//std::cout << h2b ("b2") << std::endl;
	
	//return EXIT_SUCCESS;
	
	gpio port;
	std::string option/* = ""*/;	// current option
	//std::string current;	// current hexadecimal value
	std::map <std::string, menu::item> options;
	//std::map <std::string, std::string> values;	// Maps binary values to selectable options.
	std::map <std::string, menu::item>::iterator researcher;
	
	
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
	
	// The port should now be properly open.
	if (!port.execute ("gpio iodir 00"))
			std::cout << "Error: Could not set GPIO direction to output" << std::endl;
	
	// Read the current value only at the beginning,
	// as I did not have enough time to debug the reading errors at run-time.
	// This should be enough though, normally.
	if (!port.execute ("gpio readall", option))
		std::cout << "Error: Could not read current value" << std::endl;
	else
		for (auto & opt : options)
		{
		//	values [opt.second.value] = opt.second.selection;
			if (opt.second.value == h2b (option))
			{
				option = opt.second.selection;
				
				break;
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
		
		
		researcher = options.find (option);
		
		if (researcher == options.end ())
		{
			std::cout << '\'' << option << "': unavailable option; please reselect: ";
			
			goto search;
		}
		else
		{
			if (!port.execute ("gpio writeall " + pad (b2h (researcher -> second.value), 2, '0')))
				std::cout << "\tFailed to interact with the GPIO module" << std::endl;
		}
	}
}

