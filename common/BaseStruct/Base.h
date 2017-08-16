#pragma once

class CBase
{
public:
	CBase(void);
	~CBase(void);
	
	virtual void print()
	{
		printf("CBase::print()\n");
	}
};

class CDerive:public CBase
{
public:
	CDerive();
	~CDerive();

	void print()
	{
		printf("CDerive::print()\n");
	}
};

class CObject
{
public:
	CObject()
	{
		printf("CObject::CObject()\n");
	}

	CObject(int num):m_nNum(num)
	{
		printf("CObject::CObject(int num)\n");
	}
	
	CObject(const CObject &object)
	{
		printf("Object::CObject(const CObject &object)\n");
	}

	void operator=(const  CObject &object)
	{
		printf("CObject::operator=(const CObject &object)\n");
	}

	int  m_nNum;
};

