#ifndef  SINGLETON_H
#define	 SINGLETON_H

template <class Type>
class Singleton
{
private:
	static Type* m_Instance;
public:
	static Type* GetInstance(void)
	{
		if (nullptr == m_Instance)
		{
			m_Instance = new Type;
		}
		return m_Instance;
	}
	static void DistroyInstance(void)
	{
		if (nullptr != m_Instance)
		{
			delete m_Instance;
		}
		m_Instance = nullptr;
	}
protected:
	Singleton()
	{

	}
	virtual ~Singleton()
	{

	}
};


template <class Type>
Type* Singleton<Type>::m_Instance = nullptr;



#endif // ! SINGLETON_H