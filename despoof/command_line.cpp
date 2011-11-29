#include <memory>
#include <vector>
#include <new>
#include <boost/assign/std/vector.hpp>
#include "command_line.h"
#include "argtable2.h"

using namespace std;
using namespace boost::assign;
using namespace despoof;

namespace {
	class argtable : public vector<void*> {
	public:
		~argtable() { arg_freetable(data(), size()); }
	};

	class argtable_error : public command_line_error {
		shared_ptr<argtable> table;
		struct arg_end *end;
		std::string progname;
	public:
		argtable_error(const char *progname, shared_ptr<argtable> &table, struct arg_end *end);

		virtual void print_errors() const override;
	};
}

template<typename Result>
static Result alloc_check(Result value)
{
	if(!value) {
		throw bad_alloc();
	}
	return value;
}

void despoof::command_line_to_configuration(configuration &config, int argc, char **argv)
{
	auto interval = alloc_check(arg_int0("i", "interval", "<n>", "Time of one despoof iteration in milliseconds"));
	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();
	(*table) += interval, end;

	if(arg_parse(argc, argv, table->data()) > 0) {
		throw argtable_error(argv[0], table, end);
	}

	if(interval->count > 0) {
		config.interval = interval->ival[0];
	}
}

command_line_error::command_line_error()
	: runtime_error("Cannot parse command line")
{
}

argtable_error::argtable_error(const char *progname, shared_ptr<argtable> &table, struct arg_end *end)
	: progname(progname), table(table), end(end)
{
}

void argtable_error::print_errors() const
{
	arg_print_errors(stderr, end, progname.c_str());
}
