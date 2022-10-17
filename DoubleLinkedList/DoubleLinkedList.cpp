/*********************************************************
* @brief	双方向リストの詳細定義
* @date		2022/10/04
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DoubleLinkedList.h"

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
	assert(m_pList->m_Count > 0 && "pre decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev != m_pList->m_pDummy && "pre decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// リストの参照があるかの確認
	assert(m_pNode != m_pList->m_pDummy && "pre increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->m_Count > 0 && "post decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev != m_pList->m_pDummy && "post decrement: begin cant decrement");// 先頭ノードではないかの確認

	ConstIterator iter(*this);//運算前のイテレータをコピー
	m_pNode = m_pNode->pPrev;

	return iter;
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// リストの参照があるかの確認
	assert(m_pNode != m_pList->m_pDummy && "post increment: dummy cant increment");// ダミーではないかの確認

	ConstIterator iter(*this);//運算前のイテレータをコピー
	m_pNode = m_pNode->pNext;

	return iter;
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
	assert(m_pNode != m_pList->m_pDummy && "constIterator: is dummy");

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
	assert(m_pNode != m_pList->m_pDummy && "iterator: is dummy");

	return (*m_pNode).scoreData;
}


//==========  双方向リスト ==========

DoubleLinkedList::~DoubleLinkedList()
{
	//空の場合何もしない
	if (m_Count == 0)return;

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
	m_Count = 0;
	m_pDummy = new Node;

	m_pDummy->pPrev = m_pDummy;
	m_pDummy->pNext = m_pDummy;
}

bool DoubleLinkedList::Insert(ConstIterator& positionIter,const ScoreData& data)
{
	//新要素のノードを作成
	Node* newNode = new Node;
	newNode->scoreData = data;

	//イテレータ有効であるかの確認
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//挿入を行う
	Node* prev = positionIter.m_pNode->pPrev;
	Node* next = positionIter.m_pNode;
	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;
	m_Count++;
	return true;
}

bool DoubleLinkedList::Remove(ConstIterator& positionIter)
{
	//リストが空の場合、削除失敗
	if (m_Count == 0)
	{
		return false;
	}

	//イテレータ有効ではない場合、削除失敗
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//ダミーノードを指す場合、削除失敗
	if (positionIter.m_pNode == m_pDummy)
	{
		return false;
	}

	//削除を行う
	Node* prev = positionIter.m_pNode->pPrev;
	Node* next = positionIter.m_pNode->pNext;
	prev->pNext = next;
	next->pPrev = prev;
	delete positionIter.m_pNode;
	m_Count--;
	return true;
}

DoubleLinkedList::Iterator DoubleLinkedList::Begin()
{
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
	return m_Count;
}

DoubleLinkedList::ConstIterator DoubleLinkedList::CBegin() const
{
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
