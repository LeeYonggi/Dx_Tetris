#pragma once
#include "Singleton.h"

enum ACCOUNT_RETURN
{
	NOT_FIND,
	FIND,
	EXIST,
	MAKE_ACCOUND
};
class DataManager :
	public Singleton<DataManager>
{
private:
	std::map<std::string, Account*> m_Account;

public:
	ACCOUNT_RETURN AddAccount(std::string id, std::string password);

	DataManager() {}
	virtual ~DataManager(){}
};

#define DATAMANAGER DataManager::GetSingleton()