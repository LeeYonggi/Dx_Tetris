#pragma once


struct CRITICAL_LOCK
{
	void InitSection(CRITICAL_SECTION *section)
	{
		InitializeCriticalSection(section);
	}
	void DeleteSection(CRITICAL_SECTION *section)
	{
		DeleteCriticalSection(section);
	}
};

CRITICAL_LOCK m_cl;

template<class T>
class Singleton
{
private:
	static T *instance;

public:
	static T* GetInstance()
	{
		EnterCriticalSection(m_cs);
		if (!instance)
			instance = new T;
		LeaveCriticalSection(m_cs);
		return instance;
	}
	static void ReleaseSingleton();

	Singleton();
	virtual ~Singleton();
};

template<class T>
T *Singleton<T>::instance = nullptr;
