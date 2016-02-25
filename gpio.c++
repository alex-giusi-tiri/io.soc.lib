//#include <iostream>
//#include <vector>
//#include <boost/algorithm/string.hpp>

#include "gpio.h++"

gpio::gpio (void)
{
	endport = new boost::asio::serial_port (io);
	endportname = "";
}

gpio::~gpio (void)
{
	disconnect ();
	
	delete endport;
	//endport = nullptr;
}

const bool gpio::connect (const std::string & portname)
{
	if (connected ())
		if (endportname == portname)
			return true;
		else
			if (!disconnect ())
				return false;
	
	try
	{
		endport -> open (portname);
	}
	catch (...)
	{
		return false;
	}
	
	if (endport -> is_open ())
	{
		endportname = portname;
		
		return true;
	}
	else
	{
		return false;
	}
}

const bool gpio::disconnect (void)
{
	if (connected ())
	{
		endport -> close ();
		endportname = "";
	}
	
	return true;
}

const bool gpio::connected (void) const
{
	return endport -> is_open ();
}

const std::string & gpio::name (void) const
{
	return endportname;
}

const bool gpio::execute (const std::string & cmd)
{
	std::string output;
	return execute (cmd, output);
	/*
	if (!connected ())
		return false;
	
	// Prepend 0x0D (\r?) (Enter) (twice) to clear any remaining data from any previous state or command:
	// Append 0x0D (\r?) to emulate the [Enter] key to execute the command:
	//cmd = 0x0D + cmd + 0x0D;
	cmd = "\r" + cmd + "\r";
	
	// Write the command to the serial port:
	return endport -> write_some (boost::asio::buffer (cmd)) == cmd.length ();
	*/
}

const bool gpio::execute (std::string cmd, std::string & output)
{
	if (!connected ())
		return false;
	
	// Prepend 0x0D (\r?) (Enter) (twice) to clear any remaining data from any previous state or command:
	// Append 0x0D (\r?) to emulate the [Enter] key to execute the command:
	//cmd = 0x0D + cmd + 0x0D;
	cmd = "\r" + cmd + "\r";
	//cmd = "\r\n" + cmd + "\r\n";
	
	//DWORD bytes_written_count;
	
	// Write the command to the serial port:
	auto written = endport -> write_some (boost::asio::buffer (cmd));
	
	char op [32];	// output
	//std::vector <char> op (64);
	auto read = endport -> read_some (boost::asio::buffer (op, 32));
	
	output = op;
	//std::string out (op.begin (), op.end ());
	//std::cout << "Directly Read Output: [" << output << ']' << std::endl;
	//output = output.substr (3 + cmd.length () + 2);
	//std::cout << "cmd.length (): [" << cmd.length () << ']' << std::endl;
	//std::cout << "out.length ()  (pre): [" << out.length () << ']' << std::endl;
	output.erase (0, cmd.length () + 3);
	//output.erase (0, cmd.length () + 1);
	//out = out.substr (cmd.length () + 3);
	//output.erase (0, cmd.length () + 7);
	//std::cout << "out.length () (post): [" << out.length () << ']' << std::endl;
	//std::cout << "out.size () (post): [" << out.size () << ']' << std::endl;
	//if (out.length () >= 3)
	//	out.erase (out.end () - 3, out.end ());
		output.erase (output.end () - 3, output.end ());
		//output.erase (output.end () - 1, output.end ());
	//	out.erase (out.length () - 3);
	//out = out.substr (0, out.length () - 3);
	
	//output.erase (output.begin (), output.begin () + 2);
	//output.erase (0, 2);
	//boost::algorithm::trim (output);
	//output.erase (output.end () - 6, output.end ());
	//output = out;
	//std::cout << "out.length () (post): [" << out.length () << ']' << std::endl;
	//std::cout << "output.length () (post): [" << output.length () << ']' << std::endl;
	return written == cmd.length ();
	
	//return true;
	//return output.length () == length;
}

