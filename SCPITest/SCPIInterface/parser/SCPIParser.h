#pragma once
#include "SCPIDef.h"
#include <memory>

namespace SCPI
{
	struct IDN
	{
		std::string idn1;
		std::string idn2;
		std::string idn3;
		std::string idn4;
	};
	
	class Parser
	{
	public:
		Parser();
		~Parser();
	public:
		void addCommandEntry(const std::string& pattern, scpi_command_callback_t handler);
		void setInterface(scpi_interface_t itfc);
		bool start(const IDN& idn);
		bool input(const char* data, int len);	
		scpi_t* context();
	private:
		class Impl;
		std::unique_ptr<Impl> impl;
	};

	template<class T>
	bool resultArray(scpi_t* context, const std::vector<T>& array, scpi_array_format_t format);
	template<class T>
	bool resultValue(scpi_t* context, const T& val);
	template<class T>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, T* value);
	template<class T>
	bool paramArray(scpi_t* context, std::vector<T>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory);
	template<class T>
	bool paramValue(scpi_t* context, T* value, scpi_bool_t mandatory);
}