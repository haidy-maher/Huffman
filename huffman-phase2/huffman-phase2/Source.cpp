#include <iostream>
#include <conio.h>
using namespace std;
class cList;
class cNodeR {
public:
	int info, code;
	cNodeR* left, * right;
	char L;
};
class cNodeL
{ public:
	char L;
	int info;
	cNodeL* pNext;
	cNodeR* tree;
};
class cNode {
public:
	int length, pInfo;
	char letter = ' ';
	int* codeArr;
	cNode* pNext;
};
class cListt {
public:
	cNode* pHead, * pTail;
	cListt()
	{ pHead = NULL, pTail = NULL;
	}
	~cListt() {
		cNode* pTrav;
		pTrav = pHead;
		while (pTrav != NULL)
		{   pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}
	void attach(cNode* pnn)
	{   if (pHead == NULL)
		{   pHead = pnn;
			pTail = pnn;
		}
		else
		{   pTail->pNext = pnn;
			pTail = pnn;
		}
	}
	void display()
	{   cNode* pTrav;
		pTrav = pHead;
		cout << "==========================================================" << endl;
		while (pTrav != NULL)
		{   for (int j = 0; j < pTrav->length; j++)
			{
				if (j == 0)
				{
					cout << pTrav->letter << ':' << ' ';
				}
				cout << pTrav->codeArr[j] << ' ';
			}
			cout << endl;
			pTrav = pTrav->pNext;
		}
		cout << "==========================================================" << endl;
	}
	void display2()
	{   cNode* pTrav;
		pTrav = pHead;
		while (pTrav != NULL)
		{
			cout << pTrav->pInfo << ' ';
			pTrav = pTrav->pNext;
		}
	}
};
class cList
{
public:
	cNodeL* pHead;
	cList()
	{
		pHead = NULL;
	}
	~cList() {
		cNodeL* pTrav;
		pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}
	void Insert(cNodeL* pnn)
	{   if (pHead == NULL)
		{	pHead = pnn;
		}
		else
		{
			cNodeL* PB = NULL, * pTrv = pHead;
			while (pTrv != NULL)
			{   if (pTrv->info > pnn->info)
				{  break;
				}
				PB = pTrv;
				pTrv = pTrv->pNext;
			}
			if (PB == NULL)
			{   pnn->pNext = pTrv;
				pHead = pnn;
			}
			else
			{   pnn->pNext = pTrv;
				PB->pNext = pnn;
			}
		}
	}
	void display()
	{   cNodeL* pTrv = pHead;
		while (pTrv != NULL)
		{
			cout << pTrv->info << pTrv->L << '|';
			pTrv = pTrv->pNext;
		}
		cout << endl;
	}
	int CountNodes()
	{  cNodeL* pTrv = pHead;
		int ct = 0;
		while (pTrv != NULL)
		{
			ct++;
			pTrv = pTrv->pNext;
		}
		return ct;
	}
	cNodeL* getFirstNode()
	{   cNodeL* node;
		if (pHead != NULL)
		{	node = pHead;
			pHead = pHead->pNext;
			return node;
		}
	}
};
int isRepeated(char letter, char all[52])
{   for (int i = 0; i < 52; i++)
	{   if (letter == all[i])
			return 1;
	}
	return 0;
}
int SortLetters(char message[500], cList& L)
{   int numLetters = 0;
	char letter;
	cNodeL* pnn;
	char all[52] = { ' ' };
	int a = 0;
	for (int i = 0; message[i] != '\0'; i++)
	{   letter = message[i];
		int ct = 0;
		if (!isRepeated(letter, all))
		{   for (int j = 0; message[j] != '\0'; j++)
			{
				if (letter == message[j])
				{
					ct++;
					if (ct == 98599)
					{
						cout << letter << endl;
					}
				}
			}
			all[a] = letter;
			a++;
			pnn = new cNodeL;
			pnn->pNext = NULL;
			pnn->tree = NULL;
			pnn->info = ct;
			pnn->L = letter;
			L.Insert(pnn);
			numLetters++;
		}
	}
	L.display();
	return numLetters;
}
void CreateTree(cList& L, cNodeL*& pnn, cNodeL*& one, cNodeL*& two)
{   cNodeR* tree = new cNodeR;
	tree->code = tree->L = ' ';
	tree->info = pnn->info;
	if (one->tree == NULL)
	{   cNodeR* tree1 = new cNodeR;
		tree1->code = 0;
		tree1->info = one->info;
		tree1->left = tree1->right = NULL;
		tree1->L = one->L;
		tree->left = tree1;
	}
	else
	{   one->tree->code = 0;
		tree->left = one->tree;
	}
	if (two->tree == NULL)
	{   cNodeR* tree2 = new cNodeR;
		tree2->code = 1;
		tree2->info = two->info;
		tree2->left = tree2->right = NULL;
		tree2->L = two->L;
		tree->right = tree2;
	}
	else
	{   two->tree->code = 1;
		tree->right = two->tree;
	}
	pnn->tree = tree;
	L.Insert(pnn);
}
void TwoMinimum(cList& L)
{   cNodeL* one, * two, * pnn;
	one = L.getFirstNode();
	two = L.getFirstNode();
	pnn = new cNodeL;
	pnn->pNext = NULL;
	pnn->info = one->info + two->info;
	pnn->tree = NULL;
	pnn->L = ' ';
	CreateTree(L, pnn, one, two);
}
void CodeGenerator(cNodeR* pTrv, int ArrN[], int pos, cListt& BooCode)
{   if (pTrv == NULL)
		return;
	if (pos != -1)
		ArrN[pos] = pTrv->code;
	if (pTrv->left == NULL && pTrv->right == NULL)
	{  cNode* pnn = new cNode;
		pnn->letter = pTrv->L;
		pnn->length = pos + 1;
		pnn->codeArr = new int[pos+1];
		pnn->pInfo = 0;
		pnn->pNext = NULL;
		for (int j = 0; j < pos+1; j++)
		{ pnn->codeArr[j] = ArrN[j];
		}
		BooCode.attach(pnn);
	}
	CodeGenerator(pTrv->left, ArrN, pos + 1, BooCode);
	CodeGenerator(pTrv->right, ArrN, pos + 1, BooCode);
}
void makeArrayLetters(cList& L, char Letters[])
{   cNodeL* pTrv = L.pHead;
	int i = 0;
	while (pTrv != NULL)
	{	Letters[i] = pTrv->L;
		pTrv = pTrv->pNext;
		i++;
	}
}
void compression(char message[], char compressedMessage[], cListt& BooCode , int &comp_i)
{   int mess_i = 0, mask_i = 7, last = 0;
	char mask = 1, temp = 0;
	cNode* foundedLetter = BooCode.pHead;
	for(;message[mess_i]!='\0';)
	{
		if (foundedLetter->pInfo == foundedLetter->length || mess_i == 0)
		{
			foundedLetter->pInfo = 0;
			foundedLetter = BooCode.pHead;
			while (foundedLetter!= NULL && foundedLetter->letter != message[mess_i])
			{
				foundedLetter = foundedLetter->pNext;
			}
			mess_i++;
		}
		if (foundedLetter->codeArr[foundedLetter->pInfo] == 1)
		{   temp = temp | (mask << mask_i);
		}
		mask_i--;
		foundedLetter->pInfo++;
		if (mask_i < 0)
		{   compressedMessage[comp_i] = temp;
			comp_i++;
			mask_i = 7;
			temp = 0;
		}
	}
	if (temp == 0)
		cout << "000" << endl;
	cout << "l:" << message[mess_i-1]<<' '<< "m:" << mask_i << endl;
	if (mask_i!=0)
	{
		cout << foundedLetter->codeArr[foundedLetter->pInfo]<<"boo" << endl;
		//compressedMessage[comp_i] = temp;
		//comp_i++;
		//cNode* pnn = new cNode;
		//pnn->length = mask_i; pnn->letter = ' ';pnn->pNext = NULL;pnn->pInfo = ' ';pnn->codeArr = new int;pnn->codeArr[0] = ' ';
		//BooCode.attach(pnn);
	}
	cout <<"compression:"<< comp_i << endl;
}
void isEqual(cListt& BooCode, cListt& check,char decompressedMessage[],int &ct, int &dmess_i)
{   cNode* pTrav = BooCode.pHead;
	int ct1 ;
	while (pTrav!=NULL)
	{   if (ct == pTrav->length)
		{
			cNode* pTrav2 = check.pHead;
			int i = 0; 
			ct1 = 0;
			while (pTrav2 != NULL)
			{   if (pTrav2->pInfo!=pTrav->codeArr[i])
				{	ct1++;
				}
				i++;
				pTrav2 = pTrav2->pNext;
			}
			pTrav->pInfo = 0;
			if (ct1==0)
			{
				check.display2();
				decompressedMessage[dmess_i] = pTrav->letter;
				dmess_i++;
				ct = 0;
				cNode* pTrav2;
				pTrav2 = check.pHead;
				while (pTrav2 != NULL)
				{   check.pHead = check.pHead->pNext;
					delete pTrav2;
					pTrav2 = check.pHead;
				}
			}
		}
		pTrav = pTrav->pNext;
	}
}
void decompression(char compressedMessage[], char decompressedMessage[], cListt& BooCode,int comp_i,int& dmess_i)
{   cListt check;
	cNode* pnn,*last=BooCode.pHead;
	while (last->pNext!=NULL)
	{
		last = last->pNext;
	}
	int mess_i = 0,mask_i=7,ct=0,flag,ct1=0;
	char temp=0,mask=1,Result;
	for (;mess_i< comp_i;)
	{   if (mask_i < 0)
	   {
		  if (mess_i == comp_i-1)
		  {
		     mask_i =last->length;
		  }
		  else
		  {
			  mask_i = 7;
		  }
        	mess_i++;
		}
		temp = compressedMessage[mess_i];
		Result = temp & mask << mask_i;
		mask_i--;
		pnn = new cNode;
		pnn->pNext = NULL;
		pnn->codeArr = NULL;
		pnn->letter = ' ';
		if (Result != 0)
		{	pnn->pInfo = 1;
		}
		else
		{ pnn->pInfo = 0;
		}
		check.attach(pnn);
		ct++;
		isEqual(BooCode, check, decompressedMessage,ct, dmess_i);		
	}
	cout << endl <<"decompression:"<< dmess_i << endl;
}
void main()
{   cList L;
	cListt BooCode;
	char message[100000], compressedMessage[100000], decompressedMessage[100000], * LettersArray, Letter = ' ';
	gets_s(message);
	int  ArrN[255], pos = -1, NL = SortLetters(message, L), num = 0, comp_i = 0, dmess_i = 0;
	int** CodeArray;
	LettersArray = new char[NL];
	CodeArray = new int* [NL];
	for (int i = 0; i < NL; i++)
	{
		CodeArray[i] = new int[255];
	}
	makeArrayLetters(L, LettersArray);
	for (int i = 0; ; i++)
	{
		num = L.CountNodes();
		if (num <= 1)
			break;
		TwoMinimum(L);
	}
	cNodeR* pTrv = L.pHead->tree;
	num = L.CountNodes();
	CodeGenerator(pTrv, ArrN, pos, BooCode);
	BooCode.display();
	compression(message, compressedMessage, BooCode,comp_i);
	for(int i=0;i<comp_i;i++)
		cout << compressedMessage[i];
	cout <<endl<< "==========================================================" << endl;
	decompression(compressedMessage,decompressedMessage,BooCode, comp_i, dmess_i);
	for(int i=0;i<dmess_i;i++)
		cout <<decompressedMessage[i];
	cout << endl;
}
// tell me do you bleed 
//boo!!

