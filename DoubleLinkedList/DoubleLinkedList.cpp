/*********************************************************
* @brief	�o�������X�g�̏ڍג�`
* @date		2022/10/04
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DoubleLinkedList.h"


//==========  �m�[�h�\���� ==========

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
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev->isDummy == false && "pre decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pPrev;

	return (*this);
}

DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "pre increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pNext;

	return (*this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev->isDummy == false && "post decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pPrev;

	return (*this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "post increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

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
	assert(m_pNode && m_pList && "constIterator: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "constIterator: is dummy");

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
	assert(m_pNode->isDummy == false && "iterator: is dummy");

	return (*m_pNode).scoreData;
}


//==========  �o�������X�g ==========
DoubleLinkedList::~DoubleLinkedList()
{
	//��̏ꍇ�������Ȃ�
	if (Count() == 0)return;

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
	m_pDummy = new Node;
}

bool DoubleLinkedList::Insert(ConstIterator& positionIter,const ScoreData& data)
{
	//�V�v�f�̃m�[�h���쐬
	Node* newNode = new Node(data);

	//���X�g����̏ꍇ�����֑}��
	if (Count() == 0)
	{
		m_pDummy->pNext = newNode;//�V�v�f��擪�v�f�ɐݒ�
		newNode->pPrev = m_pDummy;
		newNode->pNext = m_pDummy;
		m_pDummy->pPrev = newNode;
		return true;
	}

	//�C�e���[�^�L���ł��邩�̊m�F
	if (positionIter.IsVaild(this) == false)
		return false;

	//�}�����s��
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
	//���X�g����̏ꍇ�A�폜���s
	if (Count() == 0)
		return false;

	//�C�e���[�^�L���ł͂Ȃ��ꍇ�A�폜���f�N�������g�s�C���N�������g
	if (positionIter.IsVaild(this) == false)
		return false;

	//�_�~�[�m�[�h���w���ꍇ�A�폜���s
	if (positionIter.GetNode()->scoreData.name == "dummy")
		return false;

	//�폜���s��
	Node* prev = positionIter.GetNode()->pPrev;
	Node* next = positionIter.GetNode()->pNext;
	prev->pNext = next;
	next->pPrev = prev;
	return true;
}

DoubleLinkedList::Iterator DoubleLinkedList::Begin()
{
	//���X�g����ł���ꍇ
	if (Count() == 0)
		return Iterator(m_pDummy, this);

	return Iterator(m_pDummy->pNext, this);
}

DoubleLinkedList::Iterator DoubleLinkedList::End()
{
	return Iterator(m_pDummy, this);
}


int DoubleLinkedList::Count() const
{
	//�擪�v�f���Ȃ��ꍇ�A0��Ԃ�
	if (m_pDummy->pNext == nullptr)
		return 0;

	//�f�[�^���v�Z
	int count = 0;
	Node* node = m_pDummy->pNext;//�擪�v�f�ւ̃|�C���^���擾
	while (node != m_pDummy)
	{
		count++;
		node = node->pNext;
	}
	return count;
}

DoubleLinkedList::ConstIterator DoubleLinkedList::CBegin() const
{
	//���X�g����ł���ꍇ�A�_�~�[�C�e���[�^��Ԃ�
	if (Count() == 0)
		return ConstIterator(m_pDummy, this);

	return ConstIterator(m_pDummy->pNext, this);
}

DoubleLinkedList::ConstIterator DoubleLinkedList::CEnd() const
{
	return ConstIterator(m_pDummy, this);
}
