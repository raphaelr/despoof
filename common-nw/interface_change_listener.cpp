#include <despoof/common-nw/interface_change_listener.h>
#include "notify_addr_change_listener.h"

using namespace std;
using namespace despoof;
using namespace despoof::win32;

unique_ptr<interface_change_listener> interface_change_listener::create()
{
	return unique_ptr<interface_change_listener>(new notify_addr_change_listener());
}
