#pragma once

#include <string>
//#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

class gpio
{
	public:
		gpio (void);
		~gpio (void);
		
		const bool connect (const std::string &/*port*/);
		const bool disconnect (void);
		
		const bool connected (void) const;
		
		const bool execute (const std::string &);
		const bool execute (std::string, std::string &);
		
		// The name of the port which we are connected to.
		const std::string & name (void) const;	// connected_to
	protected:
		boost::asio::io_service io;
		boost::asio::serial_port * endport;
		std::string endportname;
};
