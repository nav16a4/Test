#pragma once
#include "Precompiled.h"
#include "Network.h"
#include "App.h"

void App::SetupApp()
{
	try
	{
		this->m_Network = new My::TCPserverNet;
		if (nullptr == m_Network)
		{
			std::cout << "network 클래스 생성 실패\n";
			throw 0;
		}
		m_Network->Setup();
	}
	catch (int e)
	{
		return;
	}
}

void App::StartApp()
{
	std::cout << "App::StartApp()";
}

void ServerApp::StartApp()
{
	std::cout << "ServerApp::StartApp()\n";
	std::cout << My::GetNowTime();

}
