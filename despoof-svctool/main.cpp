#include <despoof/win32/targetwindows.h>
#include "command_line.h"
#include "operations.h"

using namespace std;
using namespace despoof;

int realmain(int argc, char **argv)
{
	configuration cfg;
	try {
		command_line_to_configuration(cfg, argc, argv);
	} catch(command_line_error &e) {
		e.print_errors();
		return 1;
	}
	if(cfg._nostart) { return 0; }

	if(cfg.install) {
		install(cfg);
	} else if(cfg.uninstall) {
		uninstall(cfg);
	}

	return 0;
}

int main(int argc, char **argv)
{
	try {
		return realmain(argc, argv);
	} catch(exception &e) {
		fprintf(stderr, "%s\n", e.what());
		return 1;
	}
}
