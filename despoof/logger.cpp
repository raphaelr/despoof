#include "logger.h"
#include <despoof/loglevels.h>

using namespace boost;
using namespace despoof;

logger::logger(log_function log)
	: log(log)
{
}

void logger::info(const format &format)
{
	log(log_info, format.str());
}
