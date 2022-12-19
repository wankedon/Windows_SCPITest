#pragma once
#include "../parser/ParserBase.h"

namespace SCPI
{
	class TCPSession;
	class NetParser : public ParserBase
	{
	public:
		NetParser(const IDN& idn);
		~NetParser();
	public:
		bool setSession(std::shared_ptr<TCPSession> session);
		void resetSession();
	protected:
		void write(const char* data, std::size_t len = 0) override;
	private:
		std::shared_ptr<TCPSession> m_session;
	};
}