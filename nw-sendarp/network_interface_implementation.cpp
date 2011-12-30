#include "network_interface_implementation.h"
#include <WinSock2.h>
#include <despoof/win32/error.h>

using boost::format;
using namespace boost::asio::ip;
using namespace despoof;
using namespace despoof::win32;

network_interface_implementation::network_interface_implementation(const IP_ADAPTER_INFO *info, logger&)
	: common_network_interface(info)
{
}

void network_interface_implementation::fix(const address_v4 &me, const address_v4 &him, const logger &log)
{
	ULONG mac[2];
	ULONG size = sizeof(mac);

	auto result = SendARP(ntohl(him.to_ulong()), ntohl(me.to_ulong()), mac, &size);
	switch(result) {
	case ERROR_SUCCESS:
		// Everything OK
		break;
	case ERROR_GEN_FAILURE:
	case ERROR_BAD_NET_NAME:
		log.warn(format("%1%: Host %2% not found - host down?") % name() % him.to_string());
		break;
	case ERROR_NOT_FOUND:
		// Source IP (me) does not exist
		break;
	default:
		throw_windows_error2("network_interface_implementation::fix [nw-sendarp.dll]", result);
	}
}
