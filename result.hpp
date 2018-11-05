#ifndef RESULT_HPP
#define RESULT_HPP

#include <ostream>
#include <functional>

namespace opt
{

	struct error
	{
		int code;
		std::string message;

	public:
		error(int _code, std::string & _msg): 
			code(_code), message(_msg) {}

		error(const std::string & _msg):
			code(-1), message(_msg) {}

		error(const char * _msg):
			code(-1), message(_msg) {}

		error(int _code):
			code(_code), message("") {}
	};

	template <typename ST>
	class result
	{
	private:
		const bool m_defined;

		union {
			ST m_definedValue;
			error m_errorValue;
		};

	public:
		result();

		result(const result & res):
			m_defined(res.m_defined)
		{
			if (res.m_defined) {
				m_definedValue = res.m_definedValue;
			}
			else {
				m_errorValue = res.m_errorValue;
			}
		}

		result(const ST & val):
			m_defined(true), m_definedValue(val) {}

		result(const error & err):
			m_defined(false), m_errorValue(err) {}

		~result() {}
		
		template <typename T>
		static result<ST> of(const T & arg) {
			return result<T>(arg);
		}

		template <typename T>
		static result<ST> empty(const error & err) {
			return result<T>(err);
		}

		bool is_defined() {
			return m_defined;
		}

		bool is_empty() {
			return !m_defined;
		}

		result<ST> & if_defined(std::function<void(const ST &)> func) {
			if (is_defined())
				func(m_definedValue);
			return *this;
		}

		result<ST> & if_empty(std::function<void(const error &)> func) {
			if (is_empty())
				func(m_errorValue);
			return *this;
		}

		template <typename MT>
		result<MT> map(std::function<result<MT>(const ST &)> mapper) {
			if (is_defined())
				return mapper(m_definedValue);
			return m_errorValue;
		}

		template <typename MT>
		result<MT> map(std::function<MT(const ST &)> mapper) {
			if (is_defined())
				return of(mapper(m_definedValue));
			return m_errorValue;
		}
		
		const ST & get_value() {
			return m_definedValue;
		}

		const ST & get_value_or(ST alternative) {
			return is_defined()? get_value() : alternative;
		}

		const error & get_error() {
			return m_errorValue;
		}
	};

	template <typename ST>
	result<ST> of(const ST & arg) 
	{
		return result<ST>(arg);
	}

	inline error empty(const error & err) 
	{
		return err;
	}

}
#endif