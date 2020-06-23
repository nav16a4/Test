#include "Precompiled.h"
#include "Network.h"

std::string My::Network::GetIP()
{
	//�⺻���� �����۾��� ���� ��
	//������ �Է� �޴� ������� ��ü

	std::string ip = std::string(IP);
	return ip;
}

int My::Network::GetPort()
{
	//�⺻���� �����۾��� ���� ��
	//������ �Է� �޴� ������� ��ü
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
			std::string to_print = "������ ������ �ʱ�ȭ �� �� �����ϴ�.\n";
			std::cout << to_print;
			throw 0;
		}

		else if (major != LOBYTE(m_WsaData.wVersion) ||
			minor != HIBYTE(m_WsaData.wVersion)
			)
		{
			std::string to_print =
				"wsa ���� " + std::to_string(LOBYTE(m_WsaData.wVersion)) + "." + std::to_string(HIBYTE(m_WsaData.wVersion)) + "\n";
			
			std::cout << to_print;
		}

		std::string to_print =
			"wsa ���� " + std::to_string(LOBYTE(m_WsaData.wVersion)) + "." + std::to_string(HIBYTE(m_WsaData.wVersion)) + "\n";

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
