#include "stdafx.h"
#include "Singleton.h"

CRITICAL_SECTION m_cs;

template<class T>
inline void Singleton<T>::ReleaseSingleton()
{
	if (instance) delete instance;
}

template<class T>
Singleton<T>::Singleton()
{
	m_cl.InitSection(&m_cs);
}

template<class T>
Singleton<T>::~Singleton()
{
	m_cl.DeleteSection(&m_cs);
}