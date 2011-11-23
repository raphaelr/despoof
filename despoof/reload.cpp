#include "reload.h"
#include <algorithm>

using namespace std;
using namespace boost::asio::ip;
using namespace despoof;

collect_function despoof::collect;

list<adapter_address> despoof::reload()
{
	auto interfaces = collect();
	list<adapter_address> result;

	for(auto ifaceit = interfaces.begin(); ifaceit != interfaces.end(); ++ifaceit) {
		for(auto addrit = (*ifaceit)->addresses().begin(); addrit != (*ifaceit)->addresses().end(); ++addrit) {
			for(auto gwit = (*ifaceit)->gateways().begin(); gwit != (*ifaceit)->gateways().end(); ++gwit) {
				result.push_back(adapter_address(*ifaceit, *addrit, *gwit));
			}
		}
	}

	return result;
}
