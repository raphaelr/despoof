#include "configuration.h"

using namespace despoof;

#ifdef BUILD_SERVICE
# define DEFAULT_LOG_MODULE "file"
#else
# define DEFAULT_LOG_MODULE "console"
#endif

configuration::configuration()
	: interval(5000),
	  log_module(DEFAULT_LOG_MODULE),
	  nw_module("sendarp"),
	  _nostart(false)
{
}
