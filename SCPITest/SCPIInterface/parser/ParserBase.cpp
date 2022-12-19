#include "ParserBase.h"
#include <fmt_/format.h>
#include "../scpi/scpi-def.h"
#include "../logger/Logger.h"

namespace SCPI
{
	ParserBase::ParserBase(const IDN& idn)
		:m_canAddCmd(true),
		m_idn(idn),
		m_parser(make_unique<Parser>())
	{
		int i = 0;
		do
		{
			m_parser->addCommandEntry(scpi_commands[i].pattern, scpi_commands[i].callback);
			i++;
		} while (scpi_commands[i].pattern != nullptr);
	}

	ParserBase::~ParserBase()
	{

	}

	void ParserBase::addCommand(const std::string& pattern, scpi_command_callback_t handler)
	{
		if (m_canAddCmd)
			m_parser->addCommandEntry(pattern, handler);
	}

	void ParserBase::start()
	{
		scpi_interface_t scpiItfc{
		std::bind(&ParserBase::onSCPIError, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&ParserBase::onSCPIWrite, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
		std::bind(&ParserBase::onSCPIControl, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
		std::bind(&ParserBase::onSCPIFlush, this, std::placeholders::_1),
		std::bind(&ParserBase::onSCPIReset, this, std::placeholders::_1)
		};
		m_parser->setInterface(scpiItfc);
		m_parser->start(m_idn);
		m_canAddCmd = false;
	}

	void ParserBase::inputCmd(const std::vector<char>& data, int len)
	{
		if (m_canAddCmd)
			return;
		auto res = m_parser->input(data.data(), len);
		std::string prefix = (res == true) ? "Receive" : "--Invalid";
		auto length = (data[(size_t)len - 1] == '\n') ? len - 1 : len;
		LOG("{} {}", prefix, std::string(data.data(), length));
	}

	size_t ParserBase::onSCPIWrite(scpi_t* context, const char* data, size_t len)
	{
		write(data, len);
		return len;
	}

	scpi_result_t ParserBase::onSCPIFlush(scpi_t* context)
	{
		return SCPI_RES_OK;
	}

	int ParserBase::onSCPIError(scpi_t* context, int_fast16_t err)
	{
		FLOG("{}", fmt::format("**ERROR: {}, {}", (int16_t)err, SCPI_ErrorTranslate(err)));
		return 0;
	}

	scpi_result_t ParserBase::onSCPIControl(scpi_t* context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val)
	{
		if (SCPI_CTRL_SRQ == ctrl)
		{
			FLOG("{}", fmt::format("**SRQ: 0x{:X} ({})", val, val));
		}
		else
		{
			FLOG("{}", fmt::format("**CTRL {:02x}: 0x{:X} ({})", ctrl, val, val));
		}
		return SCPI_RES_OK;
	}

	scpi_result_t ParserBase::onSCPIReset(scpi_t* context)
	{
		FLOG("**Reset");
		return SCPI_RES_OK;
	}
}