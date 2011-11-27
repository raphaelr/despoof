#include "log.h"
#include <despoof/loglevels.h>

using namespace boost;
using namespace despoof;
using namespace despoof::log;

log_function despoof::log::logger;

void despoof::log::info(const format &format)
{
	logger(log_info, format.str());
}
