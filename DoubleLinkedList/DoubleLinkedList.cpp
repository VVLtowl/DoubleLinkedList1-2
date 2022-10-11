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
/*********************************************************
* @brief	�R���X�g���N�^�@
********************************************************/
DoubleLinkedList::Node::Node() :
	pPrev(nullptr),
	pNext(nullptr),
	isDummy(false)
{
}

/*********************************************************
* @brief	�R���X�g���N�^�@�X�R�A�f�[�^����ꍇ
********************************************************/
DoubleLinkedList::Node::Node(int score, const char* name) :
	pPrev(nullptr),
	pNext(nullptr),
	isDummy(false)
{
	scoreData.score = score;
	strcpy(scoreData.name, name);
}


//==========  �R���X�g�C�e���[�^ ==========
/*********************************************************
* @brief	�L���ȃC�e���[�^�ł��邩
* @detail	���X�g�̎Q�Ƃ�����A
*			�������X�g�ł��邱�Ƃ��m�F����B
* @return	�S�����������ꍇtrue��Ԃ��A�ق��̏ꍇfalse��Ԃ�
********************************************************/
bool DoubleLinkedList::ConstIterator::IsVaild(const DoubleLinkedList* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//���X�g�̎Q�Ƃ����邩
	bool sameList = (m_pList == list);//�������X�g�ł��邩

	return hasReference && sameList;
}

/*********************************************************
* @brief	���X�g�̐擪�Ɍ������Ĉ�i�߂�i�O�u�f�N�������g�j
* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
*			���X�g����ł���ꍇ���s�ɂȂ�B
*			���O�m�[�h�͐擪�m�[�h�̏ꍇ���s�ɂȂ�B
* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev->isDummy == false && "pre decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pPrev;

	return (*this);
}

/*********************************************************
* @brief	���X�g�̖����Ɍ������Ĉ�i�߂�i�O�u�C���N�������g�j
* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
*			�m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "pre increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pNext;

	return (*this);
}

/*********************************************************
* @brief	���X�g�̖����Ɍ������Ĉ�i�߂�i��u�C���N�������g�j
* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
*			���X�g����ł���ꍇ���s�ɂȂ�B
*			�m�[�h�͐擪�m�[�h�̏ꍇ���s�ɂȂ�B
* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev->isDummy == false && "post decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pPrev;

	return (*this);
}

/*********************************************************
* @brief	���X�g�̖����Ɍ������Ĉ�i�߂�i��u�C���N�������g�j
* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
*			����m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "post increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pNext;

	return (*this);
}


/*********************************************************
* @brief	�C�e���[�^�̎w���v�f���擾����(const��)
* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
* 			�m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
* @return	�w�����v�f��Ԃ�
********************************************************/
const DoubleLinkedList::Node& DoubleLinkedList::ConstIterator::operator*() const
{
	assert(m_pNode && m_pList && "constIterator: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "constIterator: is dummy");

	return (*m_pNode);
}

/*********************************************************
* @brief	�w���v�f�ւ̃|�C���^���擾����(const��)
* @detail	(*ConstIterator)�̏ꍇ�A�_�~�[�̕���assert���N�������߁A
*			�|�C���^��p�ӂ���B
* @return	�v�f�ւ̃|�C���^��Ԃ�
********************************************************/
const DoubleLinkedList::Node* DoubleLinkedList::ConstIterator::operator&() const
{
	return m_pNode;
}

/*********************************************************
* @brief	�R�s�[���s���i�R�s�[�R���X�g���N�^�j
* @detail	�錾���A�����A�߂�l��3�̓���ŃR�s�[���Ƃ�ꂽ���Ɏ��s�����B
********************************************************/
DoubleLinkedList::ConstIterator::ConstIterator(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;
}

/*********************************************************
* @brief	������s��
* @return	������s�����̃C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator& DoubleLinkedList::ConstIterator::operator=(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;

	return *this;
}

/*********************************************************
* @brief	���ꂩ��r����
* @return	����̏ꍇtrue��Ԃ��A�قȂ�ꍇfalse��Ԃ�
********************************************************/
bool DoubleLinkedList::ConstIterator::operator==(const ConstIterator& iter)
{
	return m_pNode == iter.m_pNode;
}

/*********************************************************
* @brief	�قȂ邩��r����
* @return	�قȂ�ꍇtrue��Ԃ��A����̏ꍇfalse��Ԃ�
********************************************************/
bool DoubleLinkedList::ConstIterator::operator!=(const ConstIterator& iter)
{
	return m_pNode != iter.m_pNode;
}

//==========  �C�e���[�^ ==========
/*********************************************************
* @brief	�C�e���[�^�̎w���v�f���擾����(��const��)
* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
* 			�m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
* @return	�w�����v�f��Ԃ�
********************************************************/
DoubleLinkedList::Node& DoubleLinkedList::Iterator::operator*()
{
	assert(m_pNode && m_pList && "iterator: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode->isDummy == false && "iterator: is dummy");

	return *m_pNode;
}

/*********************************************************
* @brief	�w���v�f�ւ̃|�C���^���擾����(��const��)
* @detail	(*Iterator)�̏ꍇ�A�_�~�[�̕���assert���N�������߁A�|�C���^��p�ӂ���B
* @return	�v�f�ւ̃|�C���^��Ԃ�
********************************************************/
DoubleLinkedList::Node* DoubleLinkedList::Iterator::operator&()
{
	return m_pNode;
}

//==========  �o�������X�g ==========
/*********************************************************
* @brief	�f�[�^�𖖔���ɒǉ�
* @detail	�擪�m�[�h�|�C���^�̎w���Ƃ��낪��̏ꍇ�A�V�����m�[�h�֎w���B
*			�w���Ƃ���Ώۂ�������ꍇ�A�����m�[�h�ƐV�m�[�h��o���������N��ݒ肵�A
*			�����m�[�h�|���^��V�m�[�g�֎w���B
* @return	�ǉ������̏ꍇtrue��Ԃ�
*			�ǉ����s�̏ꍇfalse��Ԃ�
********************************************************/
bool DoubleLinkedList::PushBack(DoubleLinkedList::Node* newNode)
{
	ConstIterator iter = CEnd();
	return Insert(iter, newNode);
}


/*********************************************************
* @brief	�f�[�^�����擾����
* @detail	���[�v�ŉ��Z���āA�f�[�^�����v�Z����B
*			const���\�b�h�ł���B
* @return	�f�[�^����Ԃ�
********************************************************/
int DoubleLinkedList::Count() const
{
	//�v�f���Ȃ��ꍇ�A0��Ԃ�
	if (HeadNode() == nullptr)
		return 0;

	//�f�[�^���v�Z
	int count = 0;
	Node* node = HeadNode();
	while (node != m_pDummy)
	{
		count++;
		node = node->pNext;
	}
	return count;
}

/*********************************************************
* @brief	�f�[�^�̑}��
* @detail	���X�g����̏ꍇ�����֑}���A
*			��ł͂Ȃ��ꍇ�C�e���[�^���L���ł��邩���m�F�A
*			�L���ł͂Ȃ��ꍇ�A�}�����s�B
* @return	�}�������̏ꍇtrue��Ԃ�
*			�}�����s�̏ꍇfalse��Ԃ�
********************************************************/
bool DoubleLinkedList::Insert(ConstIterator& positionIter, Node* newNode)
{
	//�v�f���Ȃ��ꍇ�A�}�����s
	if (newNode == nullptr)
		return false;

	//if (newNode->pPrev != nullptr ||
	//	newNode->pNext != nullptr)
	//	return false;

	//���X�g����̏ꍇ�����֑}��
	if (Count() == 0)
	{
		m_pDummy->pNext = newNode;
		newNode->pPrev = m_pDummy;
		newNode->pNext = m_pDummy;
		m_pDummy->pPrev = newNode;

		return true;
	}

	//�C�e���[�^�L���ł��邩�̊m�F
	if (positionIter.IsVaild(this) == false)
		return false;

	//�}�����s��
	Node* prev = (&positionIter)->pPrev;//position�̓_�~�[���w���C�e���[�^�̉\��������
	Node* next = prev->pNext;

	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;

	return true;
}

/*********************************************************
* @brief	�f�[�^�̍폜
* @detail	���X�g����ł͂Ȃ����̊m�F�A
*			��ł͂Ȃ��ꍇ�C�e���[�^���L���ł��邩�̊m�F�A
*			�L���̏ꍇ�_�~�[�ł͂Ȃ����̊m�F�B
* @return	�폜�����̏ꍇtrue��Ԃ�
*			�폜���s�̏ꍇfalse��Ԃ�
********************************************************/
bool DoubleLinkedList::Remove(ConstIterator& positionIter)
{
	//���X�g����̏ꍇ�A�폜���s
	if (Count() == 0)
		return false;

	//�C�e���[�^�L���ł͂Ȃ��ꍇ�A�폜���f�N�������g�s�C���N�������g
	if (positionIter.IsVaild(this) == false)
		return false;

	//�_�~�[�m�[�h���w���ꍇ�A�폜���s
	if ((&positionIter)->isDummy == true)//(*positionIter)�̏ꍇ�A�_�~�[�̕���assert���N����
		return false;

	//�폜���s��
	Node* prev = (&positionIter)->pPrev;//(*positionIter)�̏ꍇ�A�_�~�[�̕���assert���N����
	Node* next = (&positionIter)->pNext;//(*positionIter)�̏ꍇ�A�_�~�[�̕���assert���N����

	prev->pNext = next;
	next->pPrev = prev;

	return true;
}


/*********************************************************
* @brief	�擪�C�e���[�^�擾����
* @detail	���X�g����ł���ꍇ�A�_�~�[�m�[�h���w���C�e���[�^��Ԃ��A
*			��ł͂Ȃ��ꍇ�A�擪�m�[�h���w���C�e���[�^��Ԃ��B
* @return	�擪�C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::Iterator DoubleLinkedList::Begin()
{
	//���X�g����ł���ꍇ
	if (Count() == 0)
		return Iterator(m_pDummy, this);

	return Iterator(m_pDummy->pNext, this);
}

/*********************************************************
* @brief	�擪�R���X�g�C�e���[�^�擾����
* @detail	���X�g����ł���ꍇ�A�_�~�[�m�[�h���w���R���X�g�C�e���[�^��Ԃ�
*			��ł͂Ȃ��ꍇ�A�擪�m�[�h���w���R���X�g�C�e���[�^��Ԃ��B
* @return	�擪�R���X�g�C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator DoubleLinkedList::CBegin() const
{
	//���X�g����ł���ꍇ
	if (Count() == 0)
		return ConstIterator(m_pDummy, this);

	return ConstIterator(HeadNode(), this);
}

/*********************************************************
* @brief	�����C�e���[�^�擾����
* @detail	�_�~�[�m�[�h���w���C�e���[�^��Ԃ��B
* @return	�����C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::Iterator DoubleLinkedList::End()
{
	return Iterator(m_pDummy, this);
}

/*********************************************************
* @brief	�����C�e���[�^�擾����
* @detail	�_�~�[�m�[�h���w���R���X�g�C�e���[�^��Ԃ��B
* @return	�����R���X�g�C�e���[�^��Ԃ�
********************************************************/
DoubleLinkedList::ConstIterator DoubleLinkedList::CEnd() const
{
	return ConstIterator(m_pDummy, this);
}
