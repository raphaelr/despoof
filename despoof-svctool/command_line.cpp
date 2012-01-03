#include <new>
#include <boost/assign/std/vector.hpp>
#include "command_line.h"
#include <despoof/argtable.h>

using namespace std;
using namespace boost::assign;
using namespace despoof;

void despoof::command_line_to_configuration(configuration &config, int argc, char **argv)
{
	auto install = alloc_check(arg_lit0("i", "install", "Installs the despoof service"));
	auto uninstall = alloc_check(arg_lit0("u", "uninstall", "Removes the despoof service"));
	auto start = alloc_check(arg_lit0("s", "start", "Starts the despoof service"));
	auto stop = alloc_check(arg_lit0("t", "stop", "Stops the despoof service"));
	auto spacer = alloc_check(arg_rem("", ""));
	auto install_only = alloc_check(arg_rem("", "--install specific:"));
	auto start_type = alloc_check(arg_str0("y", "start-type", "<auto|manual|disabled>", "Start type of the service; Default: \"auto\""));
	auto args = alloc_check(arg_str0("a", "arguments", "<args>", "Arguments to pass to despoof; see \"despoof --help\""));
	auto debug = alloc_check(arg_str0("d", "debug", "<command>", "Runs the service in a debugger; Default command is \"" DESPOOF_DEFAULT_DEBUGGER "\""));
	auto help = alloc_check(arg_lit0("h", "help", "Displays this help text"));

	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();

	debug->hdr.flag |= ARG_HASOPTVALUE;
	debug->sval[0] = DESPOOF_DEFAULT_DEBUGGER;

	(*table) += install, uninstall, start, stop, spacer, install_only, start_type, args, debug, help, end;

	if(arg_parse(argc, argv, table->data()) > 0) {
		throw argtable_error(argv[0], table, end);
	}

	if(install->count > 0) {
		config.install = true;
	} else if(uninstall->count > 0) {
		config.uninstall = true;
	}

	if(start->count > 0) {
		config.start = true;
	} else if(stop->count > 0) {
		config.stop = true;
	}

	if(args->count > 0) {
		config.args = args->sval[0];
	}

	if(debug->count > 0) {
		config.debugger = debug->sval[0];
	}

	bool invalid_start_type = false;
	if(start_type->count > 0) {
		if(!strcmp(start_type->sval[0], "auto")) {
			config.start_type = configuration::auto_start;
		} else if(!strcmp(start_type->sval[0], "manual")) {
			config.start_type = configuration::demand_start;
		} else if(!strcmp(start_type->sval[0], "disabled")) {
			config.start_type = configuration::disabled;
		} else {
			invalid_start_type = true;
		}
	}

	auto install_count = install->count + uninstall->count;
	auto start_count = start->count + stop->count;
	if(start_count > 1 || install_count > 1 || (install_count + start_count) == 0 ||
			config.start && config.uninstall || config.stop && config.install ||
			help->count > 0 || invalid_start_type) {
		print_help(*table, argv[0]);
		printf("\nAt least one of --install/uninstall/start/stop must be specified. The following combinations are valid:\n");
		printf("  --install\n");
		printf("  --start\n");
		printf("  --install    --start\n");
		printf("  --uninstall\n");
		printf("  --stop\n");
		printf("  --uninstall  --stop\n");
		config._nostart = true;
	}
}
