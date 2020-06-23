#ifndef NETWORK_H
#define NETWORK_H
namespace My
{
	class Network
	{
		std::string GetIP();
		int			GetPort();

	public:
		virtual void Setup();
		int GetErrorNum();
		std::string GetErrorMsg(int _error);


		void	Startup(int,int);
		void	Socket();
		void	Bind();
		void	Listen();
		void	Accept();
		void	Connect();

	private:
		WSADATA	m_WsaData;
	};
	class ServerNet : public Network
	{
		//virtual void Setup();

	};
	class TCPserverNet final : public ServerNet
	{
		virtual void Setup();
	};


	class ClientNet : public Network
	{

	};
}
#endif
