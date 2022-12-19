#pragma once
#include "../parser/SCPIParser.h"
#include <type_traits>

namespace SCPI
{
	class Parser;
	class ParserBase
	{
	public:
		ParserBase(const IDN& idn);
		virtual ~ParserBase();
	public:
		void addCommand(const std::string& pattern, scpi_command_callback_t handler);
		void start();
		void inputCmd(const std::vector<char>& data, int len);
	public:
		template<class T>
		bool getParam(T* param) const
		{
			return SCPI::paramValue(m_parser->context(), param, FALSE);
		}

		template<class T>
		bool sendArray(const std::vector<T>& data) const
		{
			return SCPI::resultArray(m_parser->context(), data, SCPI_FORMAT_ASCII);
		}
		template<class T>
		bool sendValue(const T& val) const
		{
			return SCPI::resultValue(m_parser->context(), val);
		}
	protected:
		virtual void write(const char* data, std::size_t len = 0) = 0;
	private:
		size_t onSCPIWrite(scpi_t* context, const char* data, size_t len);
		scpi_result_t onSCPIFlush(scpi_t* context);
		int onSCPIError(scpi_t* context, int_fast16_t err);
		scpi_result_t onSCPIControl(scpi_t* context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
		scpi_result_t onSCPIReset(scpi_t* context);
	protected:
		bool m_canAddCmd;
	private:
		IDN m_idn;
		std::unique_ptr<Parser> m_parser;
	};
}