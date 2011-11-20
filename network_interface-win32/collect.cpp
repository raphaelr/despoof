#include "network_interface_implementation.h"

using namespace std;
using namespace despoof;
using namespace despoof::win32;

namespace {
	class free_me {
		void **ptr;
	public:
		template<typename T>
		free_me(T *&ptr) : ptr((void**) &ptr) { }
		~free_me() { free(ptr); }
	};
}

network_interface::interface_container network_interface::collect()
{
	network_interface::interface_container result;
	IP_ADAPTER_INFO *info = nullptr;
	ULONG length = 0;
	free_me guard(info);

	while(true) {
		switch(GetAdaptersInfo(info, &length)) {
		case ERROR_BUFFER_OVERFLOW:
			info = (IP_ADAPTER_INFO*) realloc(info, length);
			assert(info && "realloc failed");
			break;
		case ERROR_NO_DATA:
			return result;
		case ERROR_SUCCESS:
			goto success;
		default:
			;// Error
		}
	}

success:
	for(auto adapter = info; adapter; adapter = adapter->Next) {
		result.push_back(unique_ptr<network_interface_implementation>(new network_interface_implementation(adapter)));
	}
	return result;
}
