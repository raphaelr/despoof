#include <despoof/config.h>
#include "configuration.h"

using namespace despoof;

configuration::configuration()
	: interval(5000),
	  log_module(DESPOOF_DEFAULT_LOG_MODULE),
	  nw_module(DESPOOF_DEFAULT_NET_MODULE),
	  _nostart(false)
{
}
