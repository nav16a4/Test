#include "Precompiled.h"
#include "Network.h"
#include "Output.h"
#include "MainChat.h"
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

int My::Network::GetErrorNum()
{
	return WSAGetLastError();
}

std::string My::Network::GetErrorMsg(int _error)
{
	int& error = _error;
	
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	char* temp = reinterpret_cast<CHAR*>(lpMsgBuf);
	
	std::string str ="";
	str += temp;

	LocalFree(lpMsgBuf);
	return str;
}

void My::Network::SetFunc()
{
	Print = Singleton<My::Output>::GetInstance()->Print;
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
				"넣은 것과 다른 버전 생성\n";
			
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

void My::Network::Socket(const int _type,const int _protocol)
{
	// TCP : SOCK_STREAM ,IPPROTO_TCP
	// UDP : SOCK_DGRAM , IPPROTO_UDP
	try
	{
		this->m_Sock = ::socket(AF_INET, _type, _protocol);
		if (SOCKET_ERROR == m_Sock)
		{
			int error = this->GetErrorNum();
			throw error;
		}
		//std::cout << "Socket() 완료.\n";
		Print("Socket() 완료.\n");
	}
	catch(int _error)
	{
		std::string str = GetErrorMsg(_error);
		std::cout << str;
		return;
	}

}

void My::Network::Bind()
{
	//sockaddr 
	//sockaddr_in - ipv4에서 쓰는 sockaddr


	const int addr_len = sizeof(m_SockAddr);
	memset(&m_SockAddr, 0, sizeof(m_SockAddr));

	m_SockAddr.sin_port = htons(GetPort());
	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_SockAddr.sin_family = AF_INET;
	
	try
	{
		int error = ::bind(m_Sock,
			reinterpret_cast<sockaddr*>(&m_SockAddr),
			addr_len
		);

		if (SOCKET_ERROR == error)
		{
			throw GetErrorNum();
		}
		else
		{
			Print("Bind() 성공 \n");
		}
	}
	catch (int e)
	{
		std::string str = GetErrorMsg(e);
		Print(str);
		return;
	}
}

void My::Network::Listen()
{
	const int backlog=SOMAXCONN;
	
	try
	{
		int error = ::listen(m_Sock, backlog);

		if (SOCKET_ERROR == error)
		{
			throw GetErrorNum();
		}
		else
		{
			Print("Listen() 성공 \n");
		}
	}
	catch (int e)
	{
		std::string str = GetErrorMsg(e);
		Print(str);
	}

}

void My::Network::Accept()
{
	Print("Network::Accept()\n");
}

void My::Network::Connect()
{
	Print("Network::Connect()\n");
}

void My::TCPserverNet::Accept()
{
	SOCKET new_client;

	try
	{
		int addr_len = sizeof(m_SockAddr);
		new_client = ::accept(m_Sock,
			reinterpret_cast<sockaddr*>(&m_SockAddr),
			&addr_len);

		if (INVALID_SOCKET == new_client)
		{
			throw GetErrorNum();
		}
		else
		{
			//사용자 데이터를 메인 채팅 클래스에 입력한다.
			m_Chat->Insert(new_client);

		}
	}
	catch (int e)
	{
		std::string str = GetErrorMsg(e);
		Print(str);
	}
		
}

void My::TCPserverNet::Setup()
{
	this->SetFunc();
	

	this->Startup(2, 2);
	this->Socket(SOCK_STREAM, IPPROTO_TCP);
	this->Bind();
	this->Listen();
	this->Accept();
}

void My::ClientNet::Setup()
{
	this->SetFunc();
	//bind 함수가 없으므로 커넥트() 할 때 sockaddr_in 설정 필요
	this->Startup(2, 2);
	this->Socket(SOCK_STREAM, IPPROTO_TCP);
	this->Connect();
}

void My::ClientNet::Connect()
{
	
	const int addr_len = sizeof(m_SockAddr);
	memset(&m_SockAddr, 0, sizeof(m_SockAddr));

	m_SockAddr.sin_port = htons(GetPort());
	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_SockAddr.sin_family = AF_INET;
	//m_SockAddr.sin_addr.s_addr = inet_addr(GetIP().c_str());
	inet_pton(AF_INET,
		GetIP().c_str(),
		&m_SockAddr.sin_addr.s_addr
	);

	try
	{
		int error=::connect(m_Sock,
			reinterpret_cast<sockaddr*>(&m_SockAddr),
			addr_len);
		if (0 != error)
		{
			throw GetErrorNum();
		}
		else
		{
			Print("Connect 성공\n");
		}
	}
	catch (int e)
	{
		std::string str = GetErrorMsg(e);

		Print(str);
		return;
	}
	
	Sleep(1000);
}
