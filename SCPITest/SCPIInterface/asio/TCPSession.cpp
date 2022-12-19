#include "TCPSession.h"
#include "Tools.h"
#include "../logger/Logger.h"

namespace SCPI
{
	TCPSession::TCPSession(boost::asio::ip::tcp::socket socket, const SessionCallBacks& callbacks)
		:cmdBuffer(1024),
		m_socket(std::move(socket)),
		m_callBacks(callbacks),
		m_SUFFIX_RN("\r\n")
	{

	}

	TCPSession::~TCPSession()
	{
	}

	void TCPSession::read()
	{
		LOG("Client {} Enter", remoteEndpoint(m_socket));
		do_read();
	}

	void TCPSession::write(const char* data)
	{
		do_write(data, std::string(data, 1024).find_first_of('\0'));
	}

	void TCPSession::do_write(const char* data, std::size_t len)
	{
		auto handler = [](const boost::system::error_code& erro, std::size_t len)
		{
			if (erro)
			{
				LOG("Write Erro: {}", erro.message());
			}
		};
		boost::asio::async_write(m_socket, boost::asio::buffer(data, len), handler);
	}

	void TCPSession::do_read()
	{
		auto self(shared_from_this());
		auto handler = [self](boost::system::error_code erro, std::size_t len)
		{
			if (!erro)
			{
				std::size_t length = len;
#ifdef NET_ASSIS
				memcpy(self->cmdBuffer.data() + len, self->m_SUFFIX_RN.c_str(), self->m_SUFFIX_RN.length());
				length = len + self->m_SUFFIX_RN.length();
#endif
				if (self->m_callBacks.receiveData)
				{
					self->m_callBacks.receiveData(self->cmdBuffer, length);
				}
				self->do_read();
			}
			else
			{
				if (self->m_callBacks.resetSession)
				{
					self->m_callBacks.resetSession();
				}
				LOG("Client {} Exit", remoteEndpoint(self->m_socket));
			}
		};
		m_socket.async_read_some(boost::asio::buffer(cmdBuffer), handler);
	}
}