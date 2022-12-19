#include "SCPIInterface.h"
#include "asio/TCPListner.h"
#include "logger/StringConv.h"
#include "logger/Logger.h"

namespace SCPI
{
	SCPIInterface::SCPIInterface(const IDN& idn)
		:m_parser(std::make_unique<NetParser>(idn))
	{
		loggerConfig();
	}

	SCPIInterface::SCPIInterface()
		: m_parser(std::make_unique<NetParser>(IDN{ "CETC41","DGL","VER","1.0.1" }))
	{
		loggerConfig();
	}

	SCPIInterface::~SCPIInterface()
	{
		stopListen();
		m_parser.reset();
	}

	//添加指令及其响应函数
	void SCPIInterface::addCommand(const std::string& pattern, const CommandHandler& handler)
	{
		auto cmdHandler = [this, handler](scpi_t* context)->scpi_result_t
		{
			return handler(*this) ? SCPI_RES_OK : SCPI_RES_ERR;
		};
		m_parser->addCommand(pattern, cmdHandler);
	}

	//结束添加指令
	void SCPIInterface::endAdd()
	{
		m_parser->start();
	}

	//开始监听
	void SCPIInterface::startListen(const unsigned short port)
	{
		SessionCallBacks cbs{
		std::bind(&SCPIInterface::onSetSession, this, std::placeholders::_1),
		std::bind(&SCPIInterface::onResetSession, this),
		std::bind(&SCPIInterface::onReceivedData, this, std::placeholders::_1, std::placeholders::_2)
		};
		m_listner = make_unique<TCPListner>(port, cbs);
	}

	//结束监听
	void SCPIInterface::stopListen()
	{
		onResetSession();
		m_listner.reset();
	}

	void SCPIInterface::onSetSession(shared_ptr<TCPSession> session)
	{
		if (m_parser->setSession(session))
		{
			session->read();
		}
	}

	void SCPIInterface::onResetSession()
	{
		m_parser->resetSession();
	}

	void SCPIInterface::onReceivedData(const std::vector<char>& data, size_t len)
	{
		m_parser->inputCmd(data, len);
	}

	static std::wstring locateModulePath()
	{
		TCHAR szbufPath[MAX_PATH] = TEXT("");
		TCHAR szLongPath[MAX_PATH] = TEXT("");
		::GetModuleFileName(NULL, szbufPath, MAX_PATH);
		::GetLongPathName(szbufPath, szLongPath, MAX_PATH);
		std::wstring fileName(szLongPath);
		std::wstring::size_type pos = fileName.find_last_of(L"\\");
		return fileName.substr(0, pos);
	}

	void SCPIInterface::loggerConfig()
	{
		std::wstring path = locateModulePath();
		auto u8String = StrConvert::wstringToUTF8(path);
		auto gbkString = StrConvert::UTF8ToGbk(u8String);
		time_t ttnow = time(NULL);
		tm tmnow;
		localtime_s(&tmnow, &ttnow);
		Logger::PATH = fmt::format("{}\\scpilog\\scpilog_{:04}-{:02}-{:02}.log", gbkString, tmnow.tm_year + 1900, tmnow.tm_mon + 1, tmnow.tm_mday);
	}
}