#include "configuration.h"

using namespace std;
using namespace despoof;

configuration::configuration()
	: start_type(auto_start),
	  install(false), uninstall(false), start(false), stop(false), _nostart(false)
{
}
