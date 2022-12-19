#include "SCPIParser.h"
#include <assert.h>
#include "../scpi/scpi-def.h"

namespace SCPI
{
	char m_buffer[100];
	template<>
	bool resultValue(scpi_t* context, const int32_t& val)
	{
		return SCPI_ResultInt32(context, val);
	}

	template<>
	bool resultValue(scpi_t* context, const int64_t& val)
	{
		return SCPI_ResultInt64(context, val);
	}

	template<>
	bool resultValue(scpi_t* context, const float& val)
	{
		return SCPI_ResultFloat(context, val);
	}

	template<>
	bool resultValue(scpi_t* context, const double& val)
	{
		return SCPI_ResultDouble(context, val);
	}
	
	template<>
	bool resultArray(scpi_t* context, const std::vector<int8_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayInt8(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<uint8_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayUInt8(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<int16_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayInt16(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<uint16_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayUInt16(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<int32_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayInt32(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<uint32_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayUInt32(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<int64_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayInt64(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<uint64_t>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayUInt64(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<float>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayFloat(context, array.data(), array.size(), format);
	}

	template<>
	bool resultArray(scpi_t* context, const std::vector<double>& array, scpi_array_format_t format)
	{
		return SCPI_ResultArrayDouble(context, array.data(), array.size(), format);
	}

	template<>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, int32_t* value)
	{
		return SCPI_ParamToInt32(context, parameter, value);
	}

	template<>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, uint32_t* value)
	{
		return SCPI_ParamToUInt32(context, parameter, value);
	}

	template<>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, int64_t* value)
	{
		return SCPI_ParamToInt64(context, parameter, value);
	}

	template<>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, uint64_t* value)
	{
		return SCPI_ParamToUInt64(context, parameter, value);
	}

	template<>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, float* value)
	{
		return SCPI_ParamToFloat(context, parameter, value);
	}

	template<>
	bool paramToValue(scpi_t* context, scpi_parameter_t* parameter, double* value)
	{
		return SCPI_ParamToDouble(context, parameter, value);
	}

	template<>
	bool paramValue(scpi_t* context, scpi_number_t* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamNumber(context, scpi_special_numbers_def, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, int32_t* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamInt32(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, uint32_t* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamUInt32(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, int64_t* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamInt64(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, uint64_t* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamUInt64(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, float* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamFloat(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, double* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamDouble(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, scpi_bool_t* value, scpi_bool_t mandatory)
	{
		return SCPI_ParamBool(context, value, mandatory);
	}

	template<>
	bool paramValue(scpi_t* context, std::string* value, scpi_bool_t mandatory)
	{
		size_t copy_len;
		auto erro = SCPI_ParamCopyText(context, m_buffer, sizeof(m_buffer), &copy_len, mandatory);
		*value = m_buffer;
		return erro;
	}

	template<>
	bool paramArray(scpi_t* context, std::vector<int32_t>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory)
	{
		return SCPI_ParamArrayInt32(context, data.data(), i_count, o_count, format, mandatory);
	}

	template<>
	bool paramArray(scpi_t* context, std::vector<uint32_t>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory)
	{
		return SCPI_ParamArrayUInt32(context, data.data(), i_count, o_count, format, mandatory);
	}

	template<>
	bool paramArray(scpi_t* context, std::vector<int64_t>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory)
	{
		return SCPI_ParamArrayInt64(context, data.data(), i_count, o_count, format, mandatory);
	}

	template<>
	bool paramArray(scpi_t* context, std::vector<uint64_t>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory)
	{
		return SCPI_ParamArrayUInt64(context, data.data(), i_count, o_count, format, mandatory);
	}

	template<>
	bool paramArray(scpi_t* context, std::vector<float>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory)
	{
		return SCPI_ParamArrayFloat(context, data.data(), i_count, o_count, format, mandatory);
	}

	template<>
	bool paramArray(scpi_t* context, std::vector<double>& data, size_t i_count, size_t* o_count, scpi_array_format_t format, scpi_bool_t mandatory)
	{
		return SCPI_ParamArrayDouble(context, data.data(), i_count, o_count, format, mandatory);
	}

	struct CommandEntry
	{
		CommandEntry(const std::string& pt, scpi_command_callback_t hd)
			:pattern(pt),
			handler(hd)
		{

		}
		std::string pattern;
		scpi_command_callback_t handler;
	};

	class Parser::Impl
	{
	public: 
		Impl()
			:heapCmdArray(nullptr)
		{
		}

		~Impl()
		{
			if (heapCmdArray != nullptr)
			{
				delete[] heapCmdArray;
				heapCmdArray = nullptr;
			}
		}
	public:
		void addCommandEntry(const std::string& pattern, scpi_command_callback_t handler)
		{
			commandEntry.emplace_back(pattern, handler);
		}

		void setInterface(scpi_interface_t write)
		{
			itfc.write = write.write;
			itfc.control = write.control;
			itfc.error = write.error;
			itfc.flush = write.flush;
			itfc.reset = write.reset;
		}

		bool start(const IDN& idn)
		{
			if (commandEntry.empty())
				return false;
			if (itfc.write == nullptr)
				return false;
			if (heapCmdArray != nullptr)
				return false;
			heapCmdArray = new scpi_command_t[commandEntry.size() + 1];
			int i = 0;
			for (i = 0; i < commandEntry.size(); i++)
			{
				heapCmdArray[i].pattern = commandEntry[i].pattern.c_str();
				heapCmdArray[i].callback = commandEntry[i].handler;
				heapCmdArray[i].tag = 0;
			}
			heapCmdArray[i].pattern = nullptr;
			heapCmdArray[i].callback = nullptr;
			heapCmdArray[i].tag = 0;
			
			SCPI_Init(&scpi_context,
				heapCmdArray,
				&itfc,
				scpi_units_def,
				//SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
				idn.idn1.c_str(), idn.idn2.c_str(), idn.idn3.c_str(), idn.idn4.c_str(),
				scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
				scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);
			return true;
		}

		bool input(const char* data, int len)
		{
			return SCPI_Input(&scpi_context, data, len);
		}

		scpi_t* context()
		{
			return &scpi_context;
		}

	private:
		scpi_interface_t itfc;
		std::vector<CommandEntry> commandEntry;
		scpi_command_t* heapCmdArray;
		scpi_t scpi_context;
	};

	Parser::Parser()
		:impl(std::make_unique<Parser::Impl>())
	{

	}
	Parser::~Parser() = default;

	void Parser::addCommandEntry(const std::string& pattern, scpi_command_callback_t handler)
	{
		impl->addCommandEntry(pattern, handler);
	}

	void Parser::setInterface(scpi_interface_t itfc)
	{
		impl->setInterface(itfc);
	}

	bool Parser::start(const IDN& idn)
	{
		return impl->start(idn);
	}

	bool Parser::input(const char* data, int len)
	{
		return impl->input(data, len);
	}

	scpi_t* Parser::context()
	{
		return impl->context();
	}
}
