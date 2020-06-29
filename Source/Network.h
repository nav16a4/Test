#ifndef NETWORK_H
#define NETWORK_H

namespace My
{
	class MainChat;
}

namespace My
{
	class Network
	{
	protected:
		std::string GetIP();
		int			GetPort();

	public:
		virtual void Setup();
		int GetErrorNum();
		std::string GetErrorMsg(int _error);
		std::function<void(std::string)> Print;
		std::function<void(std::string)> Log;

		
		void SetFunc();
		void	Startup(int,int);
		void	Socket(const int _type,const int _protocol);
		void	Bind();
		void	Listen();
		virtual void	Accept();
		virtual void	Connect();

	protected:
		My::MainChat* m_Chat;
		
		WSADATA	m_WsaData;
		SOCKET m_Sock;
		sockaddr_in m_SockAddr;

		
	};
	class ServerNet : public Network
	{
		//virtual void Setup();

	};
	class TCPserverNet final : public ServerNet
	{
		virtual void Setup();
		virtual void Accept();
	private:
		std::vector<std::thread> m_RecvThread;
		std::vector<std::thread> m_SendThread;
	};


	class ClientNet : public Network
	{
		virtual void Setup();

		virtual void Connect();
	};
}
#endif
