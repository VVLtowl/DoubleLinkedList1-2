/*********************************************************
* @brief	�o�������X�g�̏ڍג�`
* @date		2022/10/04
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DoubleLinkedList.h"

//==========  �R���X�g�C�e���[�^ ==========

bool DoubleLinkedList::ConstIterator::IsVaild(const DoubleLinkedList* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//���X�g�̎Q�Ƃ����邩
	bool sameList = (m_pList == list);//�������X�g�ł��邩

	return hasReference && sameList;
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->m_Count > 0 && "pre decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev != m_pList->m_pDummy && "pre decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pPrev;

	return (*this);
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "pre increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pNext;

	return (*this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->m_Count > 0 && "post decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev != m_pList->m_pDummy && "post decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	ConstIterator iter(*this);//�^�Z�O�̃C�e���[�^���R�s�[
	m_pNode = m_pNode->pPrev;

	return iter;
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "post increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	ConstIterator iter(*this);//�^�Z�O�̃C�e���[�^���R�s�[
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
	assert(m_pNode && m_pList && "constIterator: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
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


//==========  �C�e���[�^ ==========

ScoreData& DoubleLinkedList::Iterator::operator*()
{
	assert(m_pNode && m_pList && "iterator: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "iterator: is dummy");

	return (*m_pNode).scoreData;
}


//==========  �o�������X�g ==========

DoubleLinkedList::~DoubleLinkedList()
{
	//��̏ꍇ�������Ȃ�
	if (m_Count == 0)return;

	//�擪����A�����܂Ńm�[�h���폜
	Node* del = m_pDummy->pNext;//�擪�m�[�h�擾
	Node* next = del->pNext;//���̃m�[�h���Ɏ擾
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

	//�_�~�[���폜
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
	//�V�v�f�̃m�[�h���쐬
	Node* newNode = new Node;
	newNode->scoreData = data;

	//�C�e���[�^�L���ł��邩�̊m�F
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//�}�����s��
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
	//���X�g����̏ꍇ�A�폜���s
	if (m_Count == 0)
	{
		return false;
	}

	//�C�e���[�^�L���ł͂Ȃ��ꍇ�A�폜���s
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//�_�~�[�m�[�h���w���ꍇ�A�폜���s
	if (positionIter.m_pNode == m_pDummy)
	{
		return false;
	}

	//�폜���s��
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
