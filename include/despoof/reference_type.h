#pragma once

namespace despoof {
	class reference_type {
	protected:
		reference_type() { }
		virtual ~reference_type() { }
	private:
		reference_type(const reference_type &) { }
		const reference_type& operator =(const reference_type &) { }
	};
}
