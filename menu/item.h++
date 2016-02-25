#pragma once

#include <string>

namespace menu
{
	class item
	{
		public:
			item (void);
			//~item (void) = default;
		//protected:
			std::string selection;	// index selection
			std::string description;
			std::string value;
	};
}

