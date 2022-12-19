#include"NetParser.h"
#include "TCPSession.h"
#include "../logger/Logger.h"

namespace SCPI
{
	NetParser::NetParser(const IDN& idn)
		:ParserBase(idn)
	{
	}

	NetParser::~NetParser()
	{
	}

	bool NetParser::setSession(std::shared_ptr<TCPSession> session)
	{
		if (m_session != nullptr || m_canAddCmd)
			return false;
		m_session = session;
		return true;
	}

	void NetParser::resetSession()
	{
		if (m_canAddCmd)
			return;
		m_session = nullptr;
	}

	void NetParser::write(const char* data, std::size_t len)
	{
		if (m_session)
		{
			m_session->write(data);
		}
		else
		{
			FLOG("Parser Default IO: ", std::string(data, len));
		}
	}
}