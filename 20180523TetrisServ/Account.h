#pragma once

#define MAX_ID 20

class Account
{
private:
	std::string id;
	std::string password;

public:
	
	Account(std::string _id, std::string _password)
	{
		id = _id;
		password = _password;
	}
	virtual ~Account();
};

