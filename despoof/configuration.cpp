#include "configuration.h"

using namespace despoof;

configuration::configuration()
	: interval(5000),
	  log_module("console"),
	  nw_module("sendarp"),
	  _nostart(false)
{
}
