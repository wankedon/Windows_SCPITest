#include "TCPListner.h"
#include <memory>
#include <thread>
#include "../logger/Logger.h"
using boost::asio::ip::tcp;

namespace SCPI
{
	TCPListner::TCPListner(const unsigned short port, const SessionCallBacks& callbacks)
		:m_callbacks(callbacks),
		m_acceptor(m_ioservice, tcp::endpoint(tcp::v4(), port))
	{
		do_accept();
		LOG("SCPI Server Start Port:{}", port);
		m_thread = std::thread([this](){
				boost::system::error_code err;
				m_ioservice.run(err);
				if (err)
				{
					LOG("ioservice run error");
				}
			});
	}

	TCPListner::~TCPListner()
	{
		m_ioservice.stop();
		m_thread.join();
	}

	void TCPListner::do_accept()
	{
		auto handler = [this](boost::system::error_code erro, tcp::socket socket)
		{
			auto session = std::make_shared<TCPSession>(std::move(socket), m_callbacks);
			m_callbacks.setSession(session);
			do_accept();
		};
		m_acceptor.async_accept(handler);
	}
}