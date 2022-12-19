#pragma once
#include "TCPSession.h"

namespace SCPI
{
	class TCPListner
	{
	public:
		TCPListner(const unsigned short port, const SessionCallBacks& callbacks);
		~TCPListner();
	private:
		void do_accept();
	private:
		SessionCallBacks m_callbacks;
		boost::asio::io_service m_ioservice;
		boost::asio::ip::tcp::acceptor m_acceptor;
		std::thread m_thread;
	};
}