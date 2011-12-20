#include <new>
#include <boost/assign/std/vector.hpp>
#include "command_line.h"
#include <despoof/argtable.h>

using namespace std;
using namespace boost::assign;
using namespace despoof;

void despoof::command_line_to_configuration(configuration &config, int argc, char **argv)
{
	auto interval = alloc_check(arg_int0("i", "interval", "<n>", "Time of one despoof iteration in milliseconds"));
	auto log_module = alloc_check(arg_str0("o", "log", "<mod>", "Name of the log module, without the \"log\" prefix"));
	auto nw_module = alloc_check(arg_str0("n", "network", "<mod>", "Name of the network module, without the \"nw\" prefix"));
	auto help = alloc_check(arg_lit0("h", "help", "Displays this help text"));

	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();

#ifndef BUILD_SERVICE
	(*table) += help;
#endif
	(*table) += interval, log_module, nw_module, end;

	if(arg_parse(argc, argv, table->data()) > 0) {
		throw argtable_error(argv[0], table, end);
	}

	if(interval->count > 0) {
		config.interval = interval->ival[0];
	}
	if(log_module->count > 0) {
		config.log_module = log_module->sval[0];
	}
	if(nw_module->count > 0) {
		config.nw_module = nw_module->sval[0];
	}
	if(help->count > 0) {
		print_help(*table, argv[0]);
		config._nostart = true;
	}
}
