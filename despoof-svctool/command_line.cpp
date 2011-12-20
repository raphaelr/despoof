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
	auto help = alloc_check(arg_lit0("h", "help", "Displays this help text"));

	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();

	(*table) += install, uninstall, help, end;

	if(arg_parse(argc, argv, table->data()) > 0) {
		throw argtable_error(argv[0], table, end);
	}

	if((install->count + uninstall->count) != 1 || help->count > 0) {
		print_help(*table, argv[0]);
		printf("You must specify exactly one of -i and -u.\n");
		config._nostart = true;
	}

	if(install->count > 0) {
		config.install = true;
	} else if(uninstall->count > 0) {
		config.uninstall = true;
	}
}
