#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include "context.h"

using namespace std;
using namespace despoof;

void context::iterate(list<adapter_address> &addresses)
{
	int delay = config().interval / addresses.size();
	for_each(addresses.begin(), addresses.end(), [&](adapter_address &addr) {
		if(api_->invalid()) {
			addresses = reload();
			return;
		}

		addr.interface->fix(addr.address, addr.gateway, log_);
		Sleep(delay);
	});
}
