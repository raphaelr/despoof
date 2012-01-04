#include <despoof/config.h>
#include "configuration.h"

using namespace despoof;

configuration::configuration()
	: interval(DESPOOF_DEFAULT_INTERVAL),
	  log_module(DESPOOF_DEFAULT_LOG_MODULE),
	  nw_module(DESPOOF_DEFAULT_NET_MODULE),
	  _nostart(false)
{
}
