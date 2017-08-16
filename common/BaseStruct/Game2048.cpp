#include "Game2048.h"
#include <WinUser.rh>
#include <assert.h>

ostream& operator<<(ostream& out,CChildItem &objTemp)
{
	out<<objTemp.getValue();

	return out;
}

//  bool operator==(const CChildItem&objTemp,CChildItem& obj)
// {
// 	return obj == objTemp;
// }

CChildItem::CChildItem():
isExist_(false)
,nPosX_(0)
,nPosY_(0)
,nValue_(0)
{
}

CChildItem::CChildItem(int nValue):
isExist_(false)
,nPosX_(0)
,nPosY_(0)
,nValue_(nValue)
{
}

CChildItem::CChildItem( CChildItem &obj):
isExist_(false)
,nPosX_(0)
,nPosY_(0)
,nValue_(0)
{
	isExist_ = obj.isExist();
	nPosX_ = obj.getXpos();
	nPosY_ = obj.getYpos();
	nValue_ = obj.getValue();
}

CChildItem::~CChildItem()
{
	isExist_ = false;
}

bool CChildItem::operator+(CChildItem& objTemp)
{
	if(&objTemp != this)
	{
		//assert((nPosX_ == objTemp.getXpos() && 1 == abs(nPosY_ - objTemp.getYpos())) ||
		//	(nPosY_ == objTemp.getYpos() && 1 == abs(nPosX_ - objTemp.getXpos())));

		if(nValue_ != objTemp.getValue() && nValue_ && objTemp.getValue())
		{
			return false;
		}
		
// 		if(!isExist_ && !objTemp.isExist())
// 		{
// 			return false;
// 		}

// 		if(isExist_ && !objTemp.isExist())
// 		{
// 			return false;
// 		}

		if(!objTemp.getValue())
		{
			return false;
		}

		nValue_ += objTemp.getValue();
		isExist_ = true;
		objTemp.setValue(0);
		objTemp.setExist(false);

		return true;
	}

	return false;
}

bool CChildItem::operator==(const CChildItem& objTemp)
{
	if(&objTemp != this)
	{
		return nValue_ == objTemp.getValue();
	}

	return false;
}

bool CChildItem::operator==(int nvalue)
{
	return nvalue == nValue_;
}

bool CChildItem::operator=(int nvalue)
{
	nValue_ = nvalue;
	isExist_ = true;

	return true;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CGame2048::CGame2048(void):
pChildItem(nullptr)
{
	initControlResource();
}

CGame2048::~CGame2048(void)
{
	if(pChildItem)
	{
		delete [] pChildItem;
		pChildItem = nullptr;
	}
}

void CGame2048::MainEnter()
{
	printTable();

	char ch;
	while(true)
	{
		cout<<">>输入下一条指令";
		cin>>ch;
		if('w' == ch)
		{
			cout<<"upper"<<endl;
			operatorUpper();
		}
		else if('s' == ch)
		{
			cout<<"down"<<endl;
			operatorDown();
		}
		else if('a' == ch)
		{
			cout<<"left"<<endl;
			operatorLeft();
		}
		else if('d' == ch)
		{
			cout<<"Right"<<endl;
			operatorRight();
		}
		else
		{
			cout<<"输入指令有误!!!"<<endl;
		}

		generatorRandom();
		printTable();
	}
}

void CGame2048::initControlResource()
{
	pChildItem = new CChildItem[KColumn*KROW];
	if(nullptr == pChildItem)
	{
		printf("new ChildItem failed...........\n");
	}

	for(int i = 0;  i < KROW ; i++)
	{
		for( int  j = 0; j < KColumn; j++)
		{
			pChildItem[ j + i * KColumn].setXpos(i);
			pChildItem[ j + i * KColumn].setYpos(j);
			pChildItem[ j + i * KColumn].setExist(false);
		}
	}
}

void CGame2048::operatorLeft()
{
	for(int i = 0; KROW > i; i++)
	{
		int j = 1;int kTagIndex =0;
		bool bflage = false;
		for(; KColumn > j;j++)
		{
			if(pChildItem[kTagIndex + i * KColumn] + pChildItem[ j + i * KColumn])
			{
				bflage = true;
			}
			kTagIndex ++;
			if(KColumn- 1 == kTagIndex || KColumn - 1 == j)
			{
				if(bflage)
				{
					j = 0;kTagIndex = 0;
					bflage = false;
				}
			}
		}
	}
}

void CGame2048::operatorRight()
{
	for(int i = 0; KROW > i ; i++)
	{
		int j = KColumn -2; int kTagIndex = KColumn -1;
		bool bflage = false;
		for(; 0 <= j;j--)
		{
			if(pChildItem[kTagIndex + i * KColumn] + pChildItem[j + i * KColumn])
			{
				bflage = true;
			}
			kTagIndex--;

			if(kTagIndex == 0 || j == 0)
			{
				if(bflage)
				{
					j = KColumn - 1; kTagIndex = KColumn -1;
					bflage = false;
				}
			}
		}
	}
}

void CGame2048::operatorUpper()
{
	for(int j = 0; KColumn > j;j++)
	{
		int i = 1;int kTagIndex = 0;
		bool bfalge = false;
		for(; KROW > i; i++)
		{
			if(pChildItem[kTagIndex * KROW + j] + pChildItem[i * KROW + j])
			{
				bfalge = true;
			}

			kTagIndex ++;
			if(kTagIndex == KROW - 1 || i == KROW - 1)
			{
				if(bfalge )
				{
					i = 0; kTagIndex = 0;
					bfalge = false;
				}
			}
		}
	}
}

void CGame2048::operatorDown()
{
	for(int j = 0; KColumn > j; j++)
	{
		int i = KROW - 2; int kTagIndex = KROW-1;
		bool bflage = false;
		for(; 0 <= i; i--)
		{
			if(pChildItem[kTagIndex * KROW + j] + pChildItem[i * KROW + j])
			{
				bflage = true;
			}
			kTagIndex --;

			if(kTagIndex == 0 || i == 0)
			{
				if(bflage)
				{
					i = KROW - 1; kTagIndex = KROW - 1;
					bflage = false;
				}
			}
		}
	}
}

void CGame2048::printTable()
{
	for(int i = 0;i < KROW; i++)
	{	
		cout<<"\n\t";
		for(int j = 0; j < KColumn; j++)
		{
			int value = pChildItem[i * KColumn + j].getValue();
			if(value)
			{
				pChildItem[i * KColumn + j].setExist(true);
			}
			else
			{
				pChildItem[i * KColumn + j].setExist(false);
			}
			cout<<value<<"     ";
		}
	}

	for(int i = 0;i < KROW; i++)
	{	
		cout<<"\n\t";
		for(int j = 0; j < KColumn; j++)
		{
			cout<<"("<<pChildItem[j + i * KColumn].getXpos()<<","<<pChildItem[ j + i * KColumn].getYpos()<<") " ;
		}
	}

	//cout<<"输入下一条指令";
}

void CGame2048::generatorRandom()
{
	int xPos = rand()%4;
	int yPos = rand()%4;
	
	bool isValidCmd = false;
	for(int i = 0; i < KROW; i++)
	{
		for(int j = 0; j < KColumn; j++)
		{
			if(!pChildItem[ i * KColumn + j ].getValue())
			{
				isValidCmd = true;
			}
			else if(2048 == pChildItem[i * KColumn + j])
			{
				printf("Game Is Win..\n");
			}
		}
	}

	if(!isValidCmd)
	{
		printf("Game Over........\n");
		return;
	}

	while(pChildItem[xPos * KColumn + yPos].getValue())
	{
		xPos = rand()%4;
		yPos = rand()%4;
	}
	printf("new point ( %d, %d)\n",xPos,yPos);
	pChildItem[xPos * KColumn + yPos] = 2;
	pChildItem[xPos * KColumn + yPos].setExist(true);
	pChildItem[xPos * KColumn + yPos].setXpos(xPos);
	pChildItem[xPos * KColumn + yPos].setYpos(yPos);
}