#ifndef CDSP_EXCEPTION
#define CDSP_EXCEPTION

#include "define.hpp"

#ifdef CDSP_WIN
#include <assert.h>
#endif
#include <exception>
#include <sstream>
#include <stdexcept>

#include "types.hpp"

namespace cdsp {
	extern void ensure(types::boolean assertion);

	namespace exception {
		class base : public std::runtime_error {
		public:
			base(const std::string& msg) : std::runtime_error(msg) {};
		};

		class runtime : public base {
		public:
			runtime(const std::string& msg) : base(msg) {};
		};

		class template_specialization : public base {
		public:
			template_specialization(const std::string& msg) : base(msg) {};
		};

		class subclass_specialization : public base {
		public:
			subclass_specialization(const std::string& msg) : base(msg) {};
		};
	}
}

#endif