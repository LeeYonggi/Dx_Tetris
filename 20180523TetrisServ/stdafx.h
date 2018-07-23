// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
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


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
