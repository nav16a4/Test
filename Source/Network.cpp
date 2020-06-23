#include "Precompiled.h"
#include "Network.h"

std::string My::Network::GetIP()
{
	//기본적인 연결작업이 끝난 후
	//별도로 입력 받는 방법으로 교체

	std::string ip = std::string(IP);
	return ip;
}

int My::Network::GetPort()
{
	//기본적인 연결작업이 끝난 후
	//별도로 입력 받는 방법으로 교체
	int port = PORT;
	return port;
}

void My::Network::Setup()
{
	std::string str = std::string(__FILE__) + std::string(__FUNCTION__) + std::to_string(__LINE__);
	std::cout << str;

}

std::string My::Network::GetErrorMsg(int _error)
{
	int& error = _error;
	std::string str = ("");

	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	str = reinterpret_cast<CHAR*>(lpMsgBuf);

	LocalFree(lpMsgBuf);
	return str;
}

void My::Network::Startup(int _major,int _minor)
{
	const int& major = _major;
	const int& minor = _minor;
	
	WORD version = MAKEWORD(major, minor);
	try
	{
		int error = ::WSAStartup(version, &(this->m_WsaData));
		if (SOCKET_ERROR == error)
		{
			std::string to_print = "윈도우 소켓을 초기화 할 수 없습니다.\n";
			std::cout << to_print;
			throw 0;
		}

		else if (major != LOBYTE(m_WsaData.wVersion) ||
			minor != HIBYTE(m_WsaData.wVersion)
			)
		{
			std::string to_print =
				"wsa 버전 " + std::to_string(LOBYTE(m_WsaData.wVersion)) + "." + std::to_string(HIBYTE(m_WsaData.wVersion)) + "\n";
			
			std::cout << to_print;
		}

		std::string to_print =
			"wsa 버전 " + std::to_string(LOBYTE(m_WsaData.wVersion)) + "." + std::to_string(HIBYTE(m_WsaData.wVersion)) + "\n";

		std::cout << to_print;

	}
	catch (int a)
	{
		return;
	}
}

void My::TCPserverNet::Setup()
{
	this->Startup(2, 2);
}
