#pragma once

#include <vector>
#include <stdexcept>
#include <memory>
#include <argtable2.h>
#include <despoof/command_line.h>

namespace despoof {
	struct argtable : std::vector<void*> {
		~argtable()
		{
			arg_freetable(data(), size());
		}
	};

	class argtable_error : public command_line_error {
		std::shared_ptr<argtable> table;
		struct arg_end *end;
		std::string progname;
	public:
		argtable_error(const char *progname, std::shared_ptr<argtable> &table, struct arg_end *end);

		virtual void print_errors() const override;
	};

	template<typename Result>
	static Result alloc_check(Result value)
	{
		if(!value) {
			throw bad_alloc();
		}
		return value;
	}

	void print_help(argtable &table, const char *progname);
}
