#ifndef MAINCHAT_H
#define MAINCHAT_H


//class SOCKET;
namespace My
{
	struct User
	{
		SOCKET m_Sock;
		

	};

	struct Room
	{
		std::vector<SOCKET> m_Users;


	};

	class MainChat
	{
	public:
		void Insert(SOCKET _sock);
	private:
		
	};
}




#endif