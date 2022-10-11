/*********************************************************
* @brief		イテレータ単体テストのテスト 
* @date			2022/10/06
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList1-2/DoubleLinkedList/DoubleLinkedList.h"

//イテレータの単体テスト
#define GT_TEST_ITERATOR

#if defined GT_TEST_ITERATOR
namespace iterator_auto_test
{
	//========== イテレータの指す要素を取得するテスト ==========
	namespace iterator_getNode_test
	{
		/*********************************************************
		* @brief		リストの参照がない状態で呼び出した際の挙動
		* @detail		ID:1-0
		* 				リストの参照がない状態で呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorGetNodeTest, WhenNoReference)
		{
#ifdef _DEBUG
			DoubleLinkedList::Node node;
			DoubleLinkedList::Iterator iter(&node, nullptr);//リストの参照がないイテレータを作成

			EXPECT_DEATH((*iter), "iterator: no reference");
#else
			SUCCEED();
#endif
		}

		/*********************************************************
		* @brief		Iteratorから取得した要素に対して、値の代入が行えるかをチェック
		* @detail		ID:1-1
		*				Iteratorから取得した要素に対して、
		*				値の代入が行えるかをチェックします。
		********************************************************/
		TEST(IteratorGetNodeTest, AfterAssignNodeData)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			//初期値を取得
			int initScore = node.scoreData.score;
			char initName[WORD_SIZE];
			strcpy(initName, node.scoreData.name);

			//変更前は初期値と同じ
			EXPECT_EQ(initScore, node.scoreData.score);
			EXPECT_EQ(0, strcmp(initName, node.scoreData.name));

			//Iteratorから取得した要素に対して、値を代入
			DoubleLinkedList::Iterator iter = list.Begin();
			(*iter).scoreData.score = 10;
			strcpy((*iter).scoreData.name, "Test1-1");

			//変更後は初期値と異なる
			EXPECT_NE(initScore, node.scoreData.score);
			EXPECT_NE(0, strcmp(initName, node.scoreData.name));
		}

		/*********************************************************
		* @brief		ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
		* @detail		ID:1-2
		*				ConstIteratorから取得した要素に対して、
		*				値の代入が行えないかをチェックします。
		*				コンパイルエラーになることをチェックします。(手動テスト)
		********************************************************/
		//TEST(IteratorGetNodeTest, WhenEmptyList_GetFromBegin)
		//{
		//	DoubleLinkedList list;
		//	DoubleLinkedList::Node node;
		//	list.PushBack(&node);
		//
		//	//Iteratorから取得した要素に値を代入
		//	DoubleLinkedList::Iterator iter = list.Begin();
		//	(*iter).scoreData.score = 10;
		//
		//	//ConstIteratorから取得した要素に値を代入
		//	DoubleLinkedList::ConstIterator constIter = list.Begin();
		//	(*constIter).scoreData.score = 10;
		//}

		/*********************************************************
		* @brief		リストが空の際の、先頭イテレータに対して呼び出した際の挙動
		* @detail		ID:1-3
		*				リストが空の際の、先頭イテレータに対して呼び出した際に、
		* 				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorGetNodeTest, WhenEmptyList_GetFromBegin)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			EXPECT_EQ(0, list.Count());//リストが空であるかをチェック
			DoubleLinkedList::Iterator iter = list.Begin();
			EXPECT_DEATH((*iter), "iterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG

		}

		/*********************************************************
		* @brief		末尾イテレータに対して呼び出した際の挙動
		* @detail		ID:1-4
		*				末尾イテレータに対して呼び出した際に、
		* 				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorGetNodeTest, GetFromEnd)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Iterator iter = list.End();
			EXPECT_DEATH((*iter), "iterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}
	}
	//========== イテレータをリストの末尾に向かって一つ進めるテスト ==========
	namespace iterator__increment_test
	{
		/*********************************************************
		* @brief		リストの参照がない状態で呼び出した際の挙動
		* @detail		ID:1-5
		* 				リストの参照がない状態で呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorIncrementTest, WhenNoReference)
		{
#ifdef _DEBUG
			DoubleLinkedList::Node node;
			DoubleLinkedList::Iterator iter(&node, nullptr);
			EXPECT_DEATH((++iter), "pre increment: no reference");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストが空の際の、先頭イテレータに対して呼び出した際の挙動
		* @detail		ID:1-6
		* 				リストが空の際の、先頭イテレータに対して呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorIncrementTest, WhenEmptyList_IncrementBegin)
		{
#ifdef _DEBUG
			DoubleLinkedList list;//空リストを作成
			DoubleLinkedList::Iterator iter = list.Begin();
			EXPECT_DEATH((++iter), "pre increment: dummy cant increment");
#else
			SUCCEED();
#endif // DEBUG

		}

		/*********************************************************
		* @brief		末尾イテレータに対して呼び出した際の挙動
		* @detail		ID:1-7
		* 				末尾イテレータに対して呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorIncrementTest, IncrementEnd)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Iterator iter = list.End();
			EXPECT_DEATH((++iter), "pre increment: dummy cant increment");
#else
			SUCCEED();
#endif // DEBUG
		}

		/*********************************************************
		* @brief		リストに二つ以上の要素がある場合に呼び出した際の挙動
		* @detail		ID:1-8
		* 				リストに二つ以上の要素がある場合に呼び出した際に、
		*				次の要素を指すのかを確認します。
		********************************************************/
		TEST(IteratorIncrementTest, WhenManyElements)
		{
			//二つ以上の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2, node3;
			list.PushBack(&node1);
			list.PushBack(&node2);
			list.PushBack(&node3);

			//リストの先頭から末尾まで呼び出しを行い、
			//期待されている要素が格納されているかを確認
			DoubleLinkedList::Iterator iter = list.Begin();
			while (1)
			{
				//次の要素へのポインタを先に取得、
				//イテレータが末尾を向って一つ進めた後指した要素と比較する
				DoubleLinkedList::Node* next = (&(*iter))->pNext;
				++iter;
				if (iter == list.CEnd())break;
				else EXPECT_EQ(next, &(*iter));
			}
		}

		/*********************************************************
		* @brief		前置インクリメントを行った際の挙動
		* @detail		ID:1-9
		* 				前置インクリメントを行った際に、
		*				次の要素を指すのかを確認します。
		********************************************************/
		TEST(IteratorIncrementTest, PreIncrement)
		{
			//二つ以上の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			DoubleLinkedList::Iterator iter = list.Begin();

			//次の要素へのポインタを先に取得し、
			//イテレータが末尾を向って一つ進めた後指した要素と比較する
			DoubleLinkedList::Node* next = (&(*iter))->pNext;
			++iter;
			EXPECT_EQ(next, (&(*iter)));
		}

		/*********************************************************
		* @brief		後置インクリメントを行った際の挙動
		* @detail		ID:1-10
		* 				後置インクリメントを行った際に、
		*				次の要素を指すのかを確認します。
		********************************************************/
		TEST(IteratorIncrementTest, PostIncrement)
		{
			//二つ以上の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			DoubleLinkedList::Iterator iter = list.Begin();

			//次の要素へのポインタを先に取得、
			//イテレータが末尾を向って一つ進めた後指した要素と比較する
			DoubleLinkedList::Node* next = (&(*iter))->pNext;
			++iter;
			EXPECT_EQ(next, (&(*iter)));
		}
	}
	//========== イテレータをリストの先頭に向かって一つ進めるテスト ==========
	namespace iterator_decrement_test
	{
		/*********************************************************
		* @brief		リストの参照がない状態で呼び出した際の挙動
		* @detail		ID:1-11
		* 				リストの参照がない状態で呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorDecrementTest, WhenNoReference)
		{
#ifdef _DEBUG
			DoubleLinkedList::Node node;
			DoubleLinkedList::Iterator iter(&node, nullptr);
			EXPECT_DEATH((--iter), "pre decrement: no reference");
#else
			SUCCEED();
#endif // DEBUG
		}

		/*********************************************************
		* @brief		リストが空の際の、末尾イテレータに対して呼び出した際の挙動
		* @detail		ID:1-12
		* 				リストが空の際の、末尾イテレータに対して呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorDecrementTest, WhenEmptyList_DecrementEnd)
		{
#ifdef _DEBUG
			DoubleLinkedList list;//空であるリストを作成
			DoubleLinkedList::Iterator iter = list.End();
			EXPECT_DEATH((--iter), "pre decrement: list is empty");
#else
			SUCCEED();
#endif // DEBUG
		}

		/*********************************************************
		* @brief		先頭イテレータに対して呼び出した際の挙動
		* @detail		ID:1-13
		* 				先頭イテレータに対して呼び出した際に、
		*				assert発生するかを確認します。
		********************************************************/
		TEST(IteratorDecrementTest, DecrementBegin)
		{
#ifdef _DEBUG
			//要素のあるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			//ダミーではない先頭イテレータを取得
			DoubleLinkedList::Iterator iter = list.Begin();

			EXPECT_DEATH((--iter), "pre decrement: begin cant decrement");
#else
			SUCCEED();
#endif // DEBUG
		}

		/*********************************************************
		* @brief		リストに二つ以上の要素がある場合に呼び出した際の挙動
		* @detail		ID:1-14
		* 				リストに二つ以上の要素がある場合に呼び出した際に、
		*				前の要素を指すのかを確認します。
		********************************************************/
		TEST(IteratorDecrementTest, WhenManyElements)
		{
			//二つ以上の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2, node3;
			list.PushBack(&node1);
			list.PushBack(&node2);
			list.PushBack(&node3);

			//リストの末尾から先頭まで呼び出しを行い、
			//期待されている要素が格納されているかを確認
			DoubleLinkedList::Iterator iter = list.End();
			--iter;//ダミーノードでなく、最後のノードから
			while (1)
			{
				//前の要素へのポインタを先に取得、
				//イテレータが先頭を向って一つ進めた後指した要素と比較する
				DoubleLinkedList::Node* prev = (&(*iter))->pPrev;
				--iter;
				EXPECT_EQ(prev, (&(*iter)));

				//指した要素が先頭である場合、すべて確認完了
				if (iter == list.Begin())
				{
					break;
				}
			}
		}

		/*********************************************************
		* @brief		前置インクリメントを行った際の挙動
		* @detail		ID:1-15
		* 				前置インクリメントを行った際に、
		*				前の要素を指すのかを確認します。
		********************************************************/
		TEST(IteratorDecrementTest, PreDecrement)
		{
			//二つ以上の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			DoubleLinkedList::Iterator iter = list.End();
			--iter;//ダミーノードでなく、最後のノードから

			//前の要素へのポインタを先に取得、
			//イテレータが先頭を向って一つ進めた後指した要素と比較する
			DoubleLinkedList::Node* prev = (&(*iter))->pPrev;
			--iter;
			EXPECT_EQ(prev, (&(*iter)));
		}

		/*********************************************************
		* @brief		後置インクリメントを行った際の挙動
		* @detail		ID:1-10
		* 				後置インクリメントを行った際に、
		*				前の要素を指すのかを確認します。
		********************************************************/
		TEST(IteratorDecrementTest, PostDecrement)
		{
			//二つ以上の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			DoubleLinkedList::Iterator iter = list.End();
			iter--;//ダミーノードでなく、最後のノードから
			
			//前の要素へのポインタを先に取得、
			//イテレータが先頭を向って一つ進めた後指した要素と比較する
			DoubleLinkedList::Node* prev = (&(*iter))->pPrev;
			iter--;
			EXPECT_EQ(prev, (&(*iter)));
		}
	}
	//========== イテレータのコピーを行うテスト ==========
	namespace iterator_copy_test
	{
		/*********************************************************
		* @brief		ConstIteratorから、Iteratorのコピーが作成されないかをチェック
		* @detail		ID:1-17
		* 				ConstIteratorから、Iteratorのコピーが作成されないかをチェックします。
		*				コンパイルエラーになることを確認します。(手動テスト)
		********************************************************/
		//TEST(IteratorCopyTest, ConstIteratorCopyIterator)
		//{
		//	DoubleLinkedList::Iterator iter();
		//	DoubleLinkedList::ConstIterator constIter = iter;//ConstIteratorから、Iteratorのコピーを作成
		//}

		/*********************************************************
		* @brief		コピーコンストラクト後の値がコピー元と等しいことをチェック
		* @detail		ID:1-18
		* 				コピーコンストラクト後の値がコピー元と等しいことをチェックします。
		********************************************************/
		TEST(IteratorCopyTest, AfterCopy_CheckDataEqual)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node(15,"Test1-18");	//初期値ではない要素を作成
			list.PushBack(&node);
			DoubleLinkedList::Iterator iter1(&node, &list);//コピー元を作成

			//コピーコンストラクトから、イテレータを作成
			DoubleLinkedList::Iterator iter2(iter1);

			//コピーとコピー元の値を比較
			EXPECT_EQ(
				(*iter1).scoreData.score,
				(*iter2).scoreData.score);
			int cmp = strcmp(
				(*iter1).scoreData.name,
				(*iter2).scoreData.name);
			EXPECT_EQ(0, cmp);
		}
	}
	//========== イテレータの代入を行うテスト ==========
	namespace iterator_assign_test
	{
		/*********************************************************
		* @brief		IteratorにConstIteratorを代入できない事をチェック
		* @detail		ID:1-19
		* 				IteratorにConstIteratorを代入できない事をチェックします。
		*				コンパイルエラーになることを確認します。(手動テスト)
		********************************************************/
		//TEST(IteratorAssignTest, AssginConstIteratorToIterator)
		//{
		//	DoubleLinkedList::ConstIterator constIter;
		//	DoubleLinkedList::Iterator iter;
		//	constIter = iter;
		//	iter = constIter;
		//}

		/*********************************************************
		* @brief		代入後の値がコピー元と等しいことをチェック
		* @detail		ID:1-20
		* 				代入後の値がコピー元と等しいことをチェックします。
		********************************************************/
		TEST(IteratorAssignTest, AfterAssign_CheckDataEqual)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node(15, "Test1-20");//初期値ではない要素を作成
			list.PushBack(&node);
			DoubleLinkedList::Iterator iter1(&node, &list);//コピー元を作成

			//代入で、イテレータをコピー
			DoubleLinkedList::Iterator iter2;
			iter2 = iter1;

			//コピーとコピー元の値を比較
			EXPECT_EQ(
				(*iter1).scoreData.score,
				(*iter2).scoreData.score);
			int cmp = strcmp(
				(*iter1).scoreData.name,
				(*iter2).scoreData.name);
			EXPECT_EQ(0, cmp);
		}
	}
	//========== 二つのイテレータが同一のものであるか、比較を行うテスト ==========
	namespace iterator_equal_test
	{
		/*********************************************************
		* @brief		リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
		* @detail		ID:1-21
		* 				リストが空の状態での先頭イテレータと末尾イテレータを比較した際に、
		*				trueが返る場合成功です。
		********************************************************/
		TEST(IteratorEqualTest, WhenEmptyList_CheckBeginAndEnd)
		{
			DoubleLinkedList list;

			//リストが空の状態で、先頭も末尾もダミーである
			DoubleLinkedList::Iterator begin = list.Begin();
			DoubleLinkedList::Iterator end = list.End();

			EXPECT_TRUE(begin == end);
		}

		/*********************************************************
		* @brief		同一のイテレータを比較した際の挙動
		* @detail		ID:1-22
		* 				同一のイテレータを比較した際に、
		*				trueが返る場合成功です。
		********************************************************/
		TEST(IteratorEqualTest, WhenEmptyList_CheckSame)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			//同じ要素を指す二つのイテレータを作成
			DoubleLinkedList::Iterator iter1(&node, &list);
			DoubleLinkedList::Iterator iter2(&node, &list);

			EXPECT_TRUE(iter1 == iter2);
		}

		/*********************************************************
		* @brief		異なるイテレータを比較した際の挙動
		* @detail		ID:1-23
		* 				異なるイテレータを比較した際に、
		*				falseが返る場合成功です。
		********************************************************/
		TEST(IteratorEqualTest, WhenEmptyList_CheckDifferent)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1,node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//異なる要素を指す二つのイテレータを作成
			DoubleLinkedList::Iterator iter1(&node1, &list);
			DoubleLinkedList::Iterator iter2(&node2, &list);

			EXPECT_FALSE(iter1 == iter2);
		}
	}
	//========== 二つのイテレータが異なるものであるか、比較を行うテスト ==========
	namespace iterator_notEqual_test
	{
		/*********************************************************
		* @brief		リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
		* @detail		ID:1-24
		* 				リストが空の状態での先頭イテレータと末尾イテレータを比較した際に、
		*				trueが返る場合成功です。
		********************************************************/
		TEST(IteratorNotEqualTest, WhenEmptyList_CheckBeginAndEnd)
		{
			DoubleLinkedList list;

			//リストが空の状態で、先頭も末尾もダミーである
			DoubleLinkedList::Iterator begin = list.Begin();
			DoubleLinkedList::Iterator end = list.End();

			EXPECT_FALSE(begin != end);
		}

		/*********************************************************
		* @brief		同一のイテレータを比較した際の挙動
		* @detail		ID:1-25
		* 				同一のイテレータを比較した際に、
		*				trueが返る場合成功です。
		********************************************************/
		TEST(IteratorNotEqualTest, WhenEmptyList_CheckSame)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			//同じ要素を指す二つのイテレータを作成
			DoubleLinkedList::Iterator iter1(&node, &list);
			DoubleLinkedList::Iterator iter2(&node, &list);

			EXPECT_FALSE(iter1 != iter2);
		}

		/*********************************************************
		* @brief		異なるイテレータを比較した際の挙動
		* @detail		ID:1-26
		* 				異なるイテレータを比較した際に、
		*				falseが返る場合成功です。
		********************************************************/
		TEST(IteratorNotEqualTest, WhenEmptyList_CheckDifferent)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//異なる要素を指す二つのイテレータを作成
			DoubleLinkedList::Iterator iter1(&node1, &list);
			DoubleLinkedList::Iterator iter2(&node2, &list);

			EXPECT_TRUE(iter1 != iter2);
		}
	}
}
#endif