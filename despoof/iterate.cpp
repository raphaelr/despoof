#include <despoof/win32/targetwindows.h>
#include <algorithm>
#include "corelogic.h"

using namespace std;
using namespace despoof;

void despoof::iterate(context &ctx, list<adapter_address> &addresses)
{
	int delay = ctx.config().interval / addresses.size();
	for_each(addresses.begin(), addresses.end(), [&](adapter_address &addr) {
		addr.interface->fix(addr.address, addr.gateway, ctx.log());
		Sleep(delay);
	});
}
