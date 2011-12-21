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
	auto help = alloc_check(arg_lit0("h", "help", "Displays this help text"));

	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();

	(*table) += install, uninstall, start, stop, help, end;

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

	auto install_count = install->count + uninstall->count;
	auto start_count = start->count + stop->count;
	if(start_count > 1 || install_count > 1 || (install_count + start_count) == 0 || config.start && config.uninstall || config.stop && config.install || help->count > 0) {
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
