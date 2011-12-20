#include <despoof/argtable.h>

using namespace std;
using namespace despoof;

argtable_error::argtable_error(const char *progname, shared_ptr<argtable> &table, struct arg_end *end)
	: progname(progname), table(table), end(end)
{
}

void argtable_error::print_errors() const
{
	arg_print_errors(stderr, end, progname.c_str());
}

void despoof::print_help(argtable &table, const char *progname)
{
	printf("Usage: %s ", progname);
	arg_print_syntax(stdout, table.data(), "\n\n");
	arg_print_glossary(stdout, table.data(), NULL);
}
