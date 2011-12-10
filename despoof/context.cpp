#include "context.h"

using namespace std;
using namespace despoof;

context::context(collect_function collect, log_function log)
	: collect_(collect), log_(logger(log))
{
}

logger& context::log()
{
	return log_;
}

list<adapter_address> context::reload()
{
	auto interfaces = collect_();
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
