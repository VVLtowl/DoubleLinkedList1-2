/*********************************************************
* @brief		�o�������X�g�P�̃e�X�g(�蓮�e�X�g)
* @date			2022/10/14
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "ManualTest_DoubleLinkedList.h"

namespace ex01_DoubleLinkedList
{
	/*********************************************************
	* @brief		const�̃��\�b�h�ł��邩
	* @details		ID:0-8
	*				const�̃��X�g����Ăяo���āA
	* 				�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N���܂��B�i�蓮�e�X�g�j
	********************************************************/
	TEST(ListCountTest, IsConst)
	{
#ifdef MANUAL_TEST_LIST_COUNT_IS_CONST
		const DoubleLinkedList list;
		list.Count();
#else
		SUCCEED();
#endif // 
	}

	/*********************************************************
	* @brief		��const�̃��\�b�h�ł��邩
	* @details		ID:0-15
	*				const�̃��X�g����Ăяo���āA
	* 				�R���p�C���G���[�ƂȂ邩���`�F�b�N���܂��B�i�蓮�e�X�g�j
	********************************************************/
	TEST(ListInsertTest, NotConst)
	{
#ifdef  MANUAL_TEST_LIST_INSERT_NOT_CONST
		const DoubleLinkedList list;
		auto iter = list.CBegin();
		list.Insert(iter, ScoreData(20, "newElement"));
#else
		SUCCEED();
#endif //  
	}

	/*********************************************************
	* @brief		��const�̃��\�b�h�ł��邩
	* @details		ID:0-22
	*				const�̃��X�g����Ăяo���āA
	* 				�R���p�C���G���[�ƂȂ邩���`�F�b�N���܂��B�i�蓮�e�X�g�j
	********************************************************/
	TEST(ListRemoveTest, NotConst)
	{
#ifdef  MANUAL_TEST_LIST_REMOVE_NOT_CONST
		const DoubleLinkedList list;
		list.Remove(DoubleLinkedList::Iterator());
#else
		SUCCEED();
#endif //  
	}

	/*********************************************************
	* @brief		const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N
	* @details		ID:0-28
	* 				const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N
	*				�R���p�C���G���[�ɂȂ邩���`�F�b�N���܂��i�蓮�e�X�g�j
	********************************************************/
	TEST(ListBeginTest, NotConst)
	{
#ifdef MANUAL_TEST_LIST_BEGIN_NOT_CONST
		const DoubleLinkedList constList;
		constList.Begin();
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N
	* @details		ID:0-34
	* 				const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N
	*				�蓮�e�X�g
	********************************************************/
	TEST(ListCBeginTest, IsConst)
	{
#ifdef MANUAL_TEST_LIST_CBEGIN_IS_CONST
		const DoubleLinkedList constList;
		constList.CBegin();
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N
	* @details		ID:0-40
	* 				const�̃��X�g����AConstIterator�łȂ�Iterator�̎擾���s���Ȃ������`�F�b�N
	*				�R���p�C���G���[�ɂȂ邩���`�F�b�N���܂��i�蓮�e�X�g�j�蓮�e�X�g
	********************************************************/
	TEST(ListEndTest, NotConst)
	{
#ifdef MANUAL_TEST_LIST_END_NOT_CONST
		const DoubleLinkedList constList;
		constList.End();
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N
	* @details		ID:0-46
	* 				const�̃��X�g����Ăяo���āA�R���p�C���G���[�ƂȂ�Ȃ������`�F�b�N
	*				�蓮�e�X�g
	********************************************************/
	TEST(ListCEndTest, IsConst)
	{
#ifdef MANUAL_TEST_LIST_CEND_IS_CONST
		const DoubleLinkedList constList;
		constList.CEnd();
#else
		SUCCEED();
#endif
	}
}


