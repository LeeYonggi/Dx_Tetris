// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// 20180523TetrisServ.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.

CRITICAL_SECTION cs;

CsLock::CsLock()
{
	EnterCriticalSection(&cs);
}

CsLock::~CsLock()
{
	LeaveCriticalSection(&cs);
}
