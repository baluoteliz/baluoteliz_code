#ifndef __GAME2048_H__
#define __GAME2048_H__

#include <iostream>
using namespace std;

class CChildItem
{
public:
	friend ostream& operator<<(ostream& out,const CChildItem &objTemp);
	//friend bool operator==(const CChildItem&objTemp,CChildItem& obj);

public:
	CChildItem();
	CChildItem(int nValue);
	CChildItem( CChildItem &obj);
	~CChildItem();

public:

	bool operator+(CChildItem& objTemp);
	bool operator==(const CChildItem& objTemp);
	bool operator==(int nvalue);
	bool operator=(int nvalue);
	operator int(){return nValue_;}

	int getXpos()const {return nPosX_;}
	int getYpos()const {return nPosY_;}
	int getValue()const {return nValue_;}
	bool isExist()const {return isExist_;}
	void setXpos(int nPosx){nPosX_ = nPosx;}
	void setYpos(int nPosy){nPosY_ = nPosy;}
	void setValue(int nValue){nValue_ = nValue;}
	void setExist(bool isexist){isExist_ = isexist;}

	enum enumColorType
	{
		type_Yellow = 0x01,
		type_Red,
		type_White,
		type_Blue,
		type_Gray,
	};

	enum enumOperatorType
	{
		type_Left,
		type_upper,
		type_down,
		type_right,
	};

private:
	bool isExist_;
	int nPosX_;
	int nPosY_;
	int nValue_;
};

class CGame2048
{
public:
	CGame2048(void);
	~CGame2048(void);

	void MainEnter();

private:
	inline void initControlResource();

	void operatorLeft();
	void operatorRight();
	void operatorUpper();
	void operatorDown();

	void printTable();
	void generatorRandom();

private:
	CChildItem* pChildItem;
	const static int KROW = 4;
	const static int KColumn = 4;
};

#endif