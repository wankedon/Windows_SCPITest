#pragma once
#include <boost/asio.hpp>  

namespace SCPI
{
	class TCPSession;
	using SetSessionHandler = std::function<void(std::shared_ptr<TCPSession> session)>;
	using ResetSessionHandler = std::function<void()>;
	using ReceivedDataHandler = std::function<void(const std::vector<char>& data, size_t len)>;

	struct SessionCallBacks {
		SetSessionHandler setSession;
		ResetSessionHandler resetSession;
		ReceivedDataHandler receiveData;
	};

	class TCPSession : public std::enable_shared_from_this<TCPSession>
	{
	public:
		TCPSession(boost::asio::ip::tcp::socket socket, const SessionCallBacks& callbacks);
		~TCPSession();
	public:
		void read();
		void write(const char* data);
	private:
		void do_read();
		void do_write(const char* data, std::size_t len);
	private:
		std::vector<char> cmdBuffer;
		boost::asio::ip::tcp::socket m_socket;
		SessionCallBacks m_callBacks;
		const std::string  m_SUFFIX_RN;
	};
}