// BaseStruct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
#include <Windows.h>
#include "Game2048.h"
#include "Base.h"

CObject getObject()
{
	CObject object;
	return object;
}


int _tmain(int argc, _TCHAR* argv[])
{
// 	CGame2048 game2048;int i = 0;
// 	game2048.MainEnter();

	CDerive deriveObj;
	CBase baseObj;
	baseObj.print();
	deriveObj.print();

	CBase* pBase = &baseObj;
	CBase* pBaseDerive = &deriveObj;
	pBase->print();
	pBaseDerive->print();

	cout<<"CBase sizes: "<<sizeof(CBase)<<endl;
	cout<<"CDerive sizes: "<<sizeof(CDerive)<<endl;

	CObject object;
	CObject object1 = object;
	object1 = object;
	CObject object2 = getObject();

	system("pause");
	return 0;
}

