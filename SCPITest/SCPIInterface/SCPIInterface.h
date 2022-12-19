#pragma once
#include "asio/NetParser.h"

namespace SCPI
{
	class TCPListner;
	class TCPSession;
	class NetParser;
	class SCPIInterface;
	using CommandHandler = std::function<bool(const SCPIInterface& inter)>;

	class SCPIInterface
	{
	public:
		SCPIInterface(const IDN& idn);
		SCPIInterface();
		~SCPIInterface();
	public:
		void addCommand(const std::string& pattern, const CommandHandler& handler);
		void endAdd();
		void startListen(const unsigned short port);
		void stopListen();
	public:
		template<class T>
		bool getParam(T& param) const { return m_parser->getParam(&param); }
		template<class T>
		bool sendValue(const T& val) const { return m_parser->sendValue(val); }
		template<class T>
		bool sendArray(const std::vector<T>& data) const { return m_parser->sendArray(data); }
	private:
		void loggerConfig();
		void onSetSession(std::shared_ptr<TCPSession> session);
		void onResetSession();
		void onReceivedData(const std::vector<char>& data, size_t len);
	private:
		std::unique_ptr<TCPListner> m_listner;
		std::unique_ptr<NetParser> m_parser;
	};
}