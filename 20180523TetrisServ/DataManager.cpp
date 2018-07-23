#include "stdafx.h"
#include "DataManager.h"


ACCOUNT_RETURN DataManager::AddAccount(std::string id, std::string password)
{
	auto iter = m_Account.find(id);
	if (iter != m_Account.end()) return ACCOUNT_RETURN::EXIST;

	{ CsLock temp;
		m_Account.insert(make_pair(id, new Account(id, password)));
	}
	
	return ACCOUNT_RETURN::MAKE_ACCOUND;
}


