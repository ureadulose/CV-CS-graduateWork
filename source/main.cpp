// standart hpps
#include <iostream>

// my hpps
#include "general/TrackerBody.h"

void main()
{
	std::string filename = "../resources/1.mp4";
	std::string window_name = "my Window";
	TrackerBody TB(filename, window_name);
	TB.Run();
}