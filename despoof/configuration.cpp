#include <memory>
#include <vector>
#include <new>
#include <boost/assign/std/vector.hpp>
#include "configuration.h"
#include "argtable2.h"

using namespace std;
using namespace boost::assign;
using namespace despoof;

static configuration default_config();

namespace {
	class argtable : public vector<void*> {
	public:
		~argtable() { arg_freetable(data(), size()); }
	};

	class argtable_error : public configuration_error {
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

configuration configuration::load(int argc, char **argv)
{
	auto interval = alloc_check(arg_int0("i", "interval", "<n>", "Time of one despoof iteration in milliseconds"));
	auto end = alloc_check(arg_end(20));
	auto table = make_shared<argtable>();
	(*table) += interval, end;

	if(arg_parse(argc, argv, table->data()) > 0) {
		throw argtable_error(argv[0], table, end);
	}

	configuration config = default_config();
	if(interval->count > 0) {
		config.interval = interval->ival[0];
	}
	return config;
}

configuration default_config()
{
	configuration config;
	config.interval = 5000;

	return config;
}

configuration_error::configuration_error()
	: runtime_error("Cannot parse command line parameters")
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
