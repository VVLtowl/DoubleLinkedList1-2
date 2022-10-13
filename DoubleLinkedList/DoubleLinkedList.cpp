/*********************************************************
* @brief	双方向リストの詳細定義
* @date		2022/10/04
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DoubleLinkedList.h"

//==========  ノード構造体 ==========

DoubleLinkedList::Node::Node() :
	pPrev(nullptr),
	pNext(nullptr)
{
}

DoubleLinkedList::Node::Node(const ScoreData& _data) :
	pPrev(nullptr),
	pNext(nullptr)
{
	scoreData.score = _data.score;
	scoreData.name = _data.name;
}


//==========  コンストイテレータ ==========

bool DoubleLinkedList::ConstIterator::IsVaild(const DoubleLinkedList* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//リストの参照があるか
	bool sameList = (m_pList == list);//同じリストであるか

	return hasReference && sameList;
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev->scoreData.name != "dummy" && "pre decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// リストの参照があるかの確認
	assert(m_pNode->scoreData.name != "dummy" && "pre increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev->scoreData.name != "dummy" && "post decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// リストの参照があるかの確認
	assert(m_pNode->scoreData.name != "dummy" && "post increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

DoubleLinkedList::ConstIterator::ConstIterator(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator=(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;

	return *this;
}


const ScoreData& DoubleLinkedList::ConstIterator::operator*() const
{
	assert(m_pNode && m_pList && "constIterator: no reference");// リストの参照があるかの確認
	assert(m_pNode->scoreData.name != "dummy" && "constIterator: is dummy");

	return (*m_pNode).scoreData;
}

bool DoubleLinkedList::ConstIterator::operator==(const ConstIterator& iter)const
{
	return m_pNode == iter.m_pNode;
}

bool DoubleLinkedList::ConstIterator::operator!=(const ConstIterator& iter)const
{
	return m_pNode != iter.m_pNode;
}


//==========  イテレータ ==========

ScoreData& DoubleLinkedList::Iterator::operator*()
{
	assert(m_pNode && m_pList && "iterator: no reference");// リストの参照があるかの確認
	assert(m_pNode->scoreData.name != "dummy" && "iterator: is dummy");

	return (*m_pNode).scoreData;
}


//==========  双方向リスト ==========
DoubleLinkedList::~DoubleLinkedList()
{
	//空の場合何もしない
	if (Count() == 0)return;

	//先頭から、末尾までノードを削除
	Node* del = m_pDummy->pNext;//先頭ノード取得
	Node* next = del->pNext;//次のノードを先に取得
	while (true)
	{
		delete del;
		del = nullptr;
		if (next == m_pDummy)
		{
			break;
		}
		else
		{
			del = next;
			next = next->pNext;
		}
	}

	//ダミーを削除
	delete m_pDummy;
}

DoubleLinkedList::DoubleLinkedList()
{
	m_pDummy = new Node;
}

bool DoubleLinkedList::Insert(ConstIterator& positionIter,const ScoreData& data)
{
	//データがない場合、挿入失敗
	if (data.name == "dummy")
		return false;

	//新要素のノードを作成
	Node* newNode = new Node(data);

	//リストが空の場合末尾へ挿入
	if (Count() == 0)
	{
		m_pDummy->pNext = newNode;//新要素を先頭要素に設定
		newNode->pPrev = m_pDummy;
		newNode->pNext = m_pDummy;
		m_pDummy->pPrev = newNode;
		return true;
	}

	//イテレータ有効であるかの確認
	if (positionIter.IsVaild(this) == false)
		return false;

	//挿入を行う
	Node* prev = positionIter.GetNode()->pPrev;
	Node* next = positionIter.GetNode();
	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;
	return true;
}

bool DoubleLinkedList::Remove(ConstIterator& positionIter)
{
	//リストが空の場合、削除失敗
	if (Count() == 0)
		return false;

	//イテレータ有効ではない場合、削除失敗
	if (positionIter.IsVaild(this) == false)
		return false;

	//ダミーノードを指す場合、削除失敗
	if (positionIter.GetNode()->scoreData.name == "dummy")
		return false;

	//削除を行う
	Node* prev = positionIter.GetNode()->pPrev;
	Node* next = positionIter.GetNode()->pNext;
	prev->pNext = next;
	next->pPrev = prev;
	return true;
}

DoubleLinkedList::Iterator DoubleLinkedList::Begin()
{
	//リストが空である場合
	if (Count() == 0)
	{
		Iterator iter;
		iter.m_pNode = m_pDummy;
		iter.m_pList = this;
		return iter;
	}

	Iterator iter;
	iter.m_pNode = m_pDummy->pNext;
	iter.m_pList = this;
	return iter;
}

DoubleLinkedList::Iterator DoubleLinkedList::End()
{
	Iterator iter;
	iter.m_pNode = m_pDummy;
	iter.m_pList = this;
	return iter;
}


int DoubleLinkedList::Count() const
{
	//先頭要素がない場合、0を返す
	if (m_pDummy->pNext == nullptr)
		return 0;

	//データ数計算
	int count = 0;
	Node* node = m_pDummy->pNext;//先頭要素へのポインタを取得
	while (node != m_pDummy)
	{
		count++;
		node = node->pNext;
	}
	return count;
}

DoubleLinkedList::ConstIterator DoubleLinkedList::CBegin() const
{
	//リストが空である場合、ダミーイテレータを返す
	if (Count() == 0)
	{
		ConstIterator constIter;
		constIter.m_pNode = m_pDummy;
		constIter.m_pList = this;
		return constIter;
	}

	ConstIterator constIter;
	constIter.m_pNode = m_pDummy->pNext;
	constIter.m_pList = this;
	return constIter;
}

DoubleLinkedList::ConstIterator DoubleLinkedList::CEnd() const
{
	ConstIterator constIter;
	constIter.m_pNode = m_pDummy;
	constIter.m_pList = this;
	return constIter;
}
