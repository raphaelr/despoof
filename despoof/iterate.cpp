#include <despoof/win32/targetwindows.h>
#include <despoof/win32/error.h>
#include <algorithm>
#include "context.h"

using namespace std;
using namespace despoof;

void context::iterate(list<adapter_address> &addresses)
{
	if(addresses.empty()) {
		api_->wait_until_invalid(*this);
		if(!aborting()) { addresses = reload(); }
		return;
	}
	int delay = config().interval / addresses.size();

	for(auto it = addresses.begin(); it != addresses.end(); ++it) {
		if(api_->invalid()) {
			addresses = reload();
			return;
		}

		it->interface->fix(it->address, it->gateway, log_);

		switch(WaitForSingleObject(wait_event(), delay)) {
		case WAIT_OBJECT_0:
		case WAIT_TIMEOUT:
			break;
		case WAIT_FAILED:
			throw_windows_error("WaitForSingleObject");
		default:
			assert(!"WaitForSingleObject didn't return WAIT_OBJECT_0, WAIT_TIMEOUT or WAIT_FAILED");
		}
	}
}
