#include <despoof/win32/targetwindows.h>
#include <boost/format.hpp>
#include "context.h"

using namespace std;
using boost::format;
using namespace despoof;

context::context(configuration &config,unique_ptr<network_api> &&api, log_function log)
	: config_(config), api_(move(api)), log_(logger(log))
{
}

configuration& context::config()
{
	return config_;
}

logger& context::log()
{
	return log_;
}

list<adapter_address> context::reload()
{
	auto interfaces = api_->collect_interfaces();
	list<adapter_address> result;

	for(auto ifaceit = interfaces.begin(); ifaceit != interfaces.end(); ++ifaceit) {
		for(auto addrit = (*ifaceit)->addresses().begin(); addrit != (*ifaceit)->addresses().end(); ++addrit) {
			for(auto gwit = (*ifaceit)->gateways().begin(); gwit != (*ifaceit)->gateways().end(); ++gwit) {
				log().info(format("%1%: %2% -> %3%") % (*ifaceit)->name() % addrit->to_string() % gwit->to_string());
				result.push_back(adapter_address(*ifaceit, *addrit, *gwit));
			}
		}
	}

	if(result.empty()) {
		log().warn(format("No interfaces or address-gateway pairs found"));
	}
	return result;
}
