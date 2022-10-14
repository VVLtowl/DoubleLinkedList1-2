/*********************************************************
* @brief		�C�e���[�^�P�̃e�X�g(�蓮�e�X�g)
* @date			2022/10/14
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "ManualTest_ConstIterator.h"

namespace ex02_ConstIterator
{
	/*********************************************************
	* @brief		ConstIterator����擾�����v�f�ɑ΂��āA�l�̑�����s���Ȃ������`�F�b�N
	* @details		ID:1-2
	*				ConstIterator����擾�����v�f�ɑ΂��āA
	*				�l�̑�����s���Ȃ������`�F�b�N���܂��B
	*				�R���p�C���G���[�ɂȂ邱�Ƃ��`�F�b�N���܂��B(�蓮�e�X�g)
	********************************************************/
	TEST(IteratorGetDataTest, WhenEmptyList_GetFromBegin)
	{
#ifdef MANUAL_TEST_ITERATOR_CANT_ASSIGN_CONSTITERATOR
		DoubleLinkedList list;

		//Iterator����擾�����v�f�ɒl����
		auto iter = list.Begin();
		(*iter).score = 10;

		//ConstIterator����擾�����v�f�ɒl����
		auto constIter = list.CBegin();
		(*constIter).score = 10;
#else
		SUCCEED();
#endif // GT_MANUAL_TEST_ITERATOR
	}

	/*********************************************************
	* @brief		ConstIterator����AIterator�̃R�s�[���쐬����Ȃ������`�F�b�N
	* @details		ID:1-17
	* 				ConstIterator����AIterator�̃R�s�[���쐬����Ȃ������`�F�b�N���܂��B
	*				�R���p�C���G���[�ɂȂ邱�Ƃ��m�F���܂��B(�蓮�e�X�g)
	********************************************************/
	TEST(IteratorCopyTest, ConstIteratorCopyIterator)
	{
#ifdef MANUAL_TEST_ITERATOR_CONSTITERATOR_CANT_COPY_ITERATOR
		DoubleLinkedList::Iterator iter;
		DoubleLinkedList::ConstIterator constIter;
		DoubleLinkedList::ConstIterator constIter1(iter);//Iterator����AConstIterator�̃R�s�[���쐬
		DoubleLinkedList::Iterator iter1(constIter);//ConstIterator����AIterator�̃R�s�[���쐬
#else
		SUCCEED();
#endif //
	}

	/*********************************************************
	* @brief		Iterator��ConstIterator�����ł��Ȃ������`�F�b�N
	* @details		ID:1-19
	* 				Iterator��ConstIterator�����ł��Ȃ������`�F�b�N���܂��B
	*				�R���p�C���G���[�ɂȂ邱�Ƃ��m�F���܂��B(�蓮�e�X�g)
	********************************************************/
	TEST(IteratorAssignTest, AssginConstIteratorToIterator)
	{
#ifdef MANUAL_TEST_ITERATOR_CANT_ASSIGN_CONSTITERATOR_TO_ITERATOR
		DoubleLinkedList::ConstIterator constIter;
		DoubleLinkedList::Iterator iter;
		constIter = iter;//ConstIterator��Iterator����
		iter = constIter;//Iterator��ConstIterator����
#else
		SUCCEED();
#endif
	}

}