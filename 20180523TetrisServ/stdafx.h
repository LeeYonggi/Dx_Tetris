// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <thread>

#include <WinSock2.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"ws2_32")
#include <iostream>

#include <vector>
#include <map>
#include "Account.h"
#include "DataManager.h"

class CsLock
{
public:
	CsLock();
	~CsLock();
};


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
