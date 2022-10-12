/*********************************************************
* @brief		双方向リストの単体テスト
* @date			2022/10/05
********************************************************/

#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"

//双方向リストの単体テスト
#define GT_TEST_DOUBLE_LINKED_LIST

#if defined GT_TEST_DOUBLE_LINKED_LIST
namespace doubleLinkedList_test
{
	//========== データ数の取得のテスト ==========
	namespace list_count_test
	{
		/*********************************************************
		* @brief		リストが空である場合の戻り値
		* @detail		ID:0-0
		* 				リストが空である場合、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が0の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenEmptyList)
		{
			DoubleLinkedList list;
			EXPECT_EQ(0, list.Count());
		}

		/*********************************************************
		* @brief		リスト末尾への挿入を行った際の戻り値
		* @detail		ID:0-1
		* 				リスト末尾への挿入を行った際に、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が1の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenPushBackSucceed)
		{
			DoubleLinkedList list;

			//末尾への挿入を成功させる
			DoubleLinkedList::Node node;
			EXPECT_TRUE(list.PushBack(&node));

			EXPECT_EQ(1, list.Count());
		}

		/*********************************************************
		* @brief		リスト末尾への挿入が失敗した際の戻り値
		* @detail		ID:0-2
		* 				リスト末尾への挿入が失敗した際に、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が0の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenPushBackFailed)
		{
			DoubleLinkedList list;

			//末尾への挿入を失敗させる
			DoubleLinkedList::Node* node = nullptr;
			EXPECT_FALSE(list.PushBack(node));
			
			EXPECT_EQ(0, list.Count());
		}

		/*********************************************************
		* @brief		データの挿入を行った際の戻り値
		* @detail		ID:0-3
		* 				データの挿入を行った際に、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が1の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenInsertSucceed)
		{
			DoubleLinkedList list;

			//挿入を行った
			DoubleLinkedList::Iterator head = list.Begin();
			DoubleLinkedList::Node node;
			EXPECT_TRUE(list.Insert(head, &node));

			EXPECT_EQ(1, list.Count());
		}

		/*********************************************************
		* @brief		データの挿入に失敗した際の戻り値
		* @detail		ID:0-4
		* 				データの挿入に失敗した際に、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が0の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenInsertFailed)
		{
			DoubleLinkedList list;

			//挿入を失敗させる
			DoubleLinkedList::Iterator head = list.Begin();
			DoubleLinkedList::Node* node = nullptr;
			EXPECT_FALSE(list.Insert(head, node));
			
			EXPECT_EQ(0, list.Count());
		}

		/*********************************************************
		* @brief		データの削除を行った際の戻り値
		* @detail		ID:0-5
		* 				データの削除を行った際に、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が0の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenRemoveSucceed)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			//削除を行った
			DoubleLinkedList::Iterator head = list.Begin();
			EXPECT_TRUE(list.Remove(head));

			EXPECT_EQ(0, list.Count());
		}

		/*********************************************************
		* @brief		データの削除が失敗した際の戻り値
		* @detail		ID:0-6
		* 				データを挿入した後、削除した場合、削除が失敗した際に、
		*				データ数の取得取得関数の戻り値を確認します。
		*				戻り値が1の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenRemoveFailed)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			//不正なイテレータから、削除を失敗させる
			DoubleLinkedList::Iterator wrong(nullptr, nullptr); 
			EXPECT_FALSE(list.Remove(wrong));

			EXPECT_EQ(1, list.Count());
		}

		/*********************************************************
		* @brief		リストが空である場合に、データの削除を行った際の戻り値
		* @detail		ID:0-7
		*				マイナスにならないかを確認するため、
		* 				リストが空である場合に、データの削除を行った際に、
		*				データ数の取得関数の戻り値を確認します。
		*				戻り値が0の場合成功です。
		********************************************************/
		TEST(ListCountTest, WhenEmptyListAndRemove)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Iterator iter=list.Begin();
			EXPECT_FALSE(list.Remove(iter));

			EXPECT_EQ(0, list.Count());
		}

		/*********************************************************
		* @brief		constのメソッドであるか
		* @detail		ID:0-8
		*				constのリストから呼び出して、
		* 				コンパイルエラーとならないかをチェックします。（手動テスト）
		********************************************************/
		//TEST(ListCountTest, IsConst)
		//{
		//	const DoubleLinkedList list;
		//	list.Count();
		//}
	}

	//========== データの挿入のテスト ==========
	namespace list_insert_test
	{
		/*********************************************************
		* @brief		リストが空である場合に、挿入した際の挙動
		* @detail		ID:0-9
		* 				リストが空である場合に、新要素をイテレータの指す位置に挿入します。
		*				先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックします。
		*				データの挿入関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListInsertTest, WhenEmptyList)
		{
			//先頭イテレータの指す位置に挿入
			DoubleLinkedList list1;
			DoubleLinkedList::Iterator head = list1.Begin();
			DoubleLinkedList::Node node1;
			EXPECT_TRUE(list1.Insert(head, &node1));

			//末尾イテレータの指す位置に挿入
			DoubleLinkedList list2;
			DoubleLinkedList::Iterator tail = list2.End();
			DoubleLinkedList::Node node2;
			EXPECT_TRUE(list2.Insert(tail, &node2));
		}

		/*********************************************************
		* @brief		リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
		* @detail		ID:0-10
		* 				リストに複数の要素がある場合に、先頭イテレータを渡して、挿入します。
		*				先頭に要素が挿入され、元々先頭だった要素が２番目になります。
		*				データの挿入関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListInsertTest, WhenNotEmptyList_InsertToHead)
		{
			//複数要素のあるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node headNode,node2;
			list.PushBack(&headNode);
			list.PushBack(&node2);

			//先頭イテレータを渡して、新要素を挿入
			DoubleLinkedList::Iterator head = list.Begin();
			EXPECT_TRUE(list.Insert(head, new DoubleLinkedList::Node));

			//元々先頭だった要素が２番目になってるかをチェック
			DoubleLinkedList::Iterator iter = list.Begin();
			++iter;
			EXPECT_EQ(&headNode, &(*iter));
		}

		/*********************************************************
		* @brief		リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
		* @detail		ID:0-11
		* 				リストに複数の要素がある場合に、末尾イテレータを渡して、挿入します。
		*				イテレータの指す位置に要素が挿入されます。
		*				データの挿入関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListInsertTest, WhenNotEmptyList_InsertToTail)
		{
			//複数要素のあるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//末尾イテレータを渡して、新要素を挿入
			DoubleLinkedList::Iterator tail = list.End();
			EXPECT_TRUE(list.Insert(tail, new DoubleLinkedList::Node));
		}

		/*********************************************************
		* @brief		リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
		* @detail		ID:0-12
		* 				リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して、挿入します。
		*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれます。
		*				データの挿入関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListInsertTest, WhenNotEmptyList_InsertToMiddle)
		{
			//複数要素のあるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//中央イテレータを渡して、新要素を挿入
			DoubleLinkedList::Node newNode;
			DoubleLinkedList::Iterator middle(&node2, &list);
			EXPECT_TRUE(list.Insert(middle, new DoubleLinkedList::Node));
		}

		/*********************************************************
		* @brief		ConstIteratorを指定して挿入を行った際の挙動
		* @detail		ID:0-13
		* 				ConstIteratorを指定して、挿入します。
		*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれます。
		*				データの挿入関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		* 
		*				格納済みの要素に影響がないか、期待される位置に要素が格納されているか。
		*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListInsertTest, WhenNotEmptyList_InsertByConstIterator)
		{
			DoubleLinkedList listA;
			DoubleLinkedList::Node node1, node2;
			listA.PushBack(&node1);
			listA.PushBack(&node2);

			//先頭イテレータを渡して、新要素を挿入
			DoubleLinkedList::ConstIterator  constHead = listA.CBegin();
			EXPECT_TRUE(listA.Insert(constHead, new DoubleLinkedList::Node));

			//中央イテレータを渡して、新要素を挿入
			DoubleLinkedList::ConstIterator  constMiddle(&node2, &listA);
			EXPECT_TRUE(listA.Insert(constMiddle, new DoubleLinkedList::Node));

			//末尾イテレータを渡して、新要素を挿入
			DoubleLinkedList::ConstIterator  constTail = listA.CEnd();
			EXPECT_TRUE(listA.Insert(constTail, new DoubleLinkedList::Node));

		}

		/*********************************************************
		* @brief		不正なイテレータを渡して、挿入した場合の挙動
		* @detail		ID:0-14
		* 				リストの参照がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動などを確認します。
		*				リストの参照がないイテレータを指定したり、
		*				別リストの要素を指すイテレータを渡したりして、挿入します。
		*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれます。
		*				データの挿入関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		*
		********************************************************/
		TEST(ListInsertTest, WhenNotEmptyList_InsertWrongIterator)
		{
			DoubleLinkedList listA;
			DoubleLinkedList::Node node1, node2;
			listA.PushBack(&node1);
			listA.PushBack(&node2);

			DoubleLinkedList listB;				//別リスト
			DoubleLinkedList::Node node3;		//別リストの要素
			EXPECT_TRUE(listB.PushBack(&node3));

			//リストの参照がないイテレータ
			DoubleLinkedList::Iterator noReference(nullptr, nullptr);
			DoubleLinkedList::Node newNode1;
			EXPECT_FALSE(listA.Insert(noReference, &newNode1));

			//別リストの要素を指すイテレータ
			DoubleLinkedList::Iterator wrongList(&node3,&listB);
			DoubleLinkedList::Node newNode2;
			EXPECT_FALSE(listA.Insert(wrongList, &newNode2));
		}

		/*********************************************************
		* @brief		非constのメソッドであるか
		* @detail		ID:0-15
		*				constのリストから呼び出して、
		* 				コンパイルエラーとなるかをチェックします。（手動テスト）
		********************************************************/
		//TEST(ListInsertTest, NotConst)
		//{
		//	const DoubleLinkedList list;
		//	list.Insert(DoubleLinkedList::Iterator(), new DoubleLinkedList::Node);
		//}
	}

	//========== データの削除のテスト ==========
	namespace list_remove_test 
	{
		/*********************************************************
		* @brief		リストが空である場合に、削除した際の挙動
		* @detail		ID:0-16
		* 				リストが空である場合に、新要素をイテレータの指す位置に挿入します。
		*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
		*				データの削除関数の戻り値を確認します。
		*				戻り値がfalseの場合成功です。
		********************************************************/
		TEST(ListRemoveTest, WhenEmptyList)
		{
			//先頭要素を削除
			DoubleLinkedList list1;
			DoubleLinkedList::Iterator head = list1.Begin();
			EXPECT_FALSE(list1.Remove(head));

			//末尾要素を削除
			DoubleLinkedList list2;
			DoubleLinkedList::Iterator tail = list2.End();
			EXPECT_FALSE(list2.Remove(tail));
		}

		/*********************************************************
		* @brief		先頭要素の削除の挙動
		* @detail		ID:0-17
		* 				リストに複数の要素がある場合に、先頭イテレータを渡して、削除します。
		*				先頭要素が削除されたかを確認します。
		*				データの削除関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListRemoveTest, WhenNotEmptyList_RemoveHead)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			DoubleLinkedList::Iterator head = list.Begin();
			EXPECT_TRUE(list.Remove(head));
		}

		/*********************************************************
		* @brief		末尾要素を削除した際の挙動
		* @detail		ID:0-18
		* 				リストに複数の要素がある場合に、末尾イテレータを渡して、削除します。
		*				末尾はダミーノードなので、削除は失敗するはずです。
		*				データの削除関数の戻り値を確認します。
		*				戻り値がfalseの場合成功です。
		********************************************************/
		TEST(ListRemoveTest, WhenNotEmptyList_RemoveEnd)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			DoubleLinkedList::Iterator tail = list.End();
			EXPECT_FALSE(list.Remove(tail));
		}

		/*********************************************************
		* @brief		中間要素を削除した際の挙動
		* @detail		ID:0-19
		* 				リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際に、
		*				イテレータに指された要素が削除されたかを確認します。
		*				データの削除関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListRemoveTest, WhenNotEmptyList_RemoveMiddle)
		{
			//複数の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			DoubleLinkedList::Iterator middle(&node2, &list);//中央要素を指すイテレータを作成
			EXPECT_TRUE(list.Remove(middle));
		}

		/*********************************************************
		* @brief		ConstIteratorを指定して削除を行った際の挙動
		* @detail		ID:0-20
		* 				リストに複数の要素がある場合に、ConstIteratorを指定してした際に、
		*				ConstIteratorに指された要素が削除されたかを確認します。
		*				データの削除関数の戻り値を確認します。
		*				戻り値がtrueの場合成功です。
		********************************************************/
		TEST(ListRemoveTest, WhenNotEmptyList_RemoveByConstIterator)
		{
			//複数の要素があるリストを作成
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			DoubleLinkedList::ConstIterator constMiddle(&node2, &list);//中央要素を指すコンストイテレータを作成
			EXPECT_TRUE(list.Remove(constMiddle));
		}

		/*********************************************************
		* @brief		不正なイテレータを渡して、削除した場合の挙動
		* @detail		ID:0-21
		* 				リストの参照がないイテレータ、別リストの要素を指すイテレータなど
		*				不正なイテレータを渡した際に、
		*				データの削除関数の戻り値を確認します。
		*				戻り値がfalseの場合成功です。
		********************************************************/
		TEST(ListRemoveTest, WhenNotEmptyList_RemoveByWrongIterator)
		{
			DoubleLinkedList listA;
			DoubleLinkedList::Node node1, node2;
			listA.PushBack(&node1);
			listA.PushBack(&node2);

			DoubleLinkedList listB;			//別リスト
			DoubleLinkedList::Node node3;	//別リストの要素
			listB.PushBack(&node3);

			//リストの参照がないイテレータ
			DoubleLinkedList::Iterator noReference(nullptr, nullptr);
			EXPECT_FALSE(listA.Remove(noReference));

			//別リストの要素を指すイテレータ
			DoubleLinkedList::Iterator wrongList(&node3, &listB);
			EXPECT_FALSE(listA.Remove(wrongList));
		}

		/*********************************************************
		* @brief		非constのメソッドであるか
		* @detail		ID:0-22
		*				constのリストから呼び出して、
		* 				コンパイルエラーとなるかをチェックします。（手動テスト）
		********************************************************/
		//TEST(ListRemoveTest, NotConst)
		//{
		//	const DoubleLinkedList list;
		//	list.Remove(DoubleLinkedList::Iterator());
		//}
	}

	//========== 先頭イテレータの取得のテスト ==========
	namespace list_begin_test 
	{
		/*********************************************************
		* @brief		リストが空である場合に、呼び出した際の挙動
		* @detail		ID:0-23
		* 				リストが空である場合に、呼び出した際に、
		*				戻り値はダミーノードを指すイテレータの場合成功です。
		********************************************************/
		TEST(ListBeginTest, WhenEmptyList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.Begin(), "iterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストに要素が一つある場合に、呼び出した際の挙動
		* @detail		ID:0-24
		* 				リストに要素が一つある場合に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListBeginTest, WhenOneElementList)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			EXPECT_EQ(1, list.Count());//リストに要素が一つあるかをチェック
			EXPECT_TRUE((&node) == &(*list.Begin()));
		}

		/*********************************************************
		* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
		* @detail		ID:0-25
		* 				リストに二つ以上の要素がある場合に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListBeginTest, WhenManyElementsList)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1,node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			EXPECT_LE(2, list.Count());//リストに要素が二つ以上あるかをチェック
			EXPECT_TRUE((&node1) == &(*list.Begin()));
		}

		/*********************************************************
		* @brief		データの挿入を行った後に、呼び出した際の挙動
		* @detail		ID:0-26
		* 				データの挿入を行った後に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListBeginTest, AfterInsert)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//先頭に挿入
			DoubleLinkedList::Iterator head = list.Begin();
			DoubleLinkedList::Node headNode;
			EXPECT_TRUE(list.Insert(head, &headNode));
			EXPECT_TRUE((&headNode) == &(*list.Begin()));

			//中央に挿入
			DoubleLinkedList::Iterator middle(&node2,&list);
			DoubleLinkedList::Node newNode2;
			EXPECT_TRUE(list.Insert(middle, &newNode2));
			EXPECT_TRUE((&headNode) == &(*list.Begin()));

			//末尾に挿入
			DoubleLinkedList::Iterator tail = list.End();
			DoubleLinkedList::Node newNode3;
			EXPECT_TRUE(list.Insert(tail, &newNode3));
			EXPECT_TRUE((&headNode) == &(*list.Begin()));
		}

		/*********************************************************
		* @brief		データの削除を行った後に、呼び出した際の挙動
		* @detail		ID:0-27
		* 				データの削除を行った後に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListBeginTest, AfterRemove)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2, node3, node4;
			list.PushBack(&node1);
			list.PushBack(&node2);
			list.PushBack(&node3);
			list.PushBack(&node4);

			//末尾要素を削除
			DoubleLinkedList::Iterator last = list.End();//ダミーノード
			--last;//末尾ノード
			EXPECT_TRUE(list.Remove(last));
			EXPECT_TRUE((&node1) == &(*list.Begin()));

			//中央を削除
			DoubleLinkedList::Iterator middle(&node3, &list);
			EXPECT_TRUE(list.Remove(middle));
			EXPECT_TRUE((&node1) == &(*list.Begin()));

			//先頭を削除
			DoubleLinkedList::Iterator head = list.Begin();
			EXPECT_TRUE(list.Remove(head));
			EXPECT_TRUE((&node2) == &(*list.Begin()));
		}

		/*********************************************************
		* @brief		constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
		* @detail		ID:0-28
		* 				constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
		*				手動テスト
		********************************************************/
		//TEST(ListBeginTest, NotConst)
		//{
		//	DoubleLinkedList list;
		//	DoubleLinkedList::Node node;
		//	list.PushBack(&node);
		//	const DoubleLinkedList constList = list;
		//	constList.Begin();
		//}
	}

	//========== 先頭コンストイテレータの取得のテスト ==========
	namespace list_constBegin_test
	{
		/*********************************************************
		* @brief		リストが空である場合に、呼び出した際の挙動
		* @detail		ID:0-29
		* 				リストが空である場合に、呼び出した際に、
		*				戻り値はダミーノードを指すイテレータの場合成功です。
		********************************************************/
		TEST(ListCBeginTest, WhenEmptyList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;

			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.CBegin(), "constIterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストに要素が一つある場合に、呼び出した際の挙動
		* @detail		ID:0-30
		* 				リストに要素が一つある場合に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListCBeginTest, WhenOneElementList)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			EXPECT_EQ(1, list.Count());//リストに要素が一つあるかをチェック
			EXPECT_TRUE((&node) == &(*list.CBegin()));
		}

		/*********************************************************
		* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
		* @detail		ID:0-31
		* 				リストに二つ以上の要素がある場合に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListCBeginTest, WhenManyElementsList)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			EXPECT_LE(2, list.Count());//リストに要素が二つ以上あるかをチェック
			EXPECT_TRUE((&node1) == &(*list.CBegin()));
		}

		/*********************************************************
		* @brief		データの挿入を行った後に、呼び出した際の挙動
		* @detail		ID:0-32
		* 				データの挿入を行った後に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListCBeginTest, AfterInsert)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//先頭に挿入
			DoubleLinkedList::Iterator head = list.Begin();
			DoubleLinkedList::Node headNode;
			EXPECT_TRUE(list.Insert(head, &headNode));
			EXPECT_TRUE((&headNode) == &(*list.CBegin()));

			//中央に挿入
			DoubleLinkedList::Iterator middle(&node2, &list);
			DoubleLinkedList::Node newNode2;
			EXPECT_TRUE(list.Insert(middle, &newNode2));
			EXPECT_TRUE((&headNode) == &(*list.CBegin()));

			//末尾に挿入
			DoubleLinkedList::Iterator tail = list.End();
			DoubleLinkedList::Node newNode3;
			EXPECT_TRUE(list.Insert(tail, &newNode3));
			EXPECT_TRUE((&headNode) == &(*list.CBegin()));
		}

		/*********************************************************
		* @brief		データの削除を行った後に、呼び出した際の挙動
		* @detail		ID:0-33
		* 				データの削除を行った後に、呼び出した際に、
		*				先頭要素を指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListCBeginTest, AfterRemove)
		{
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2, node3, node4;
			list.PushBack(&node1);
			list.PushBack(&node2);
			list.PushBack(&node3);
			list.PushBack(&node4);

			//末尾要素を削除
			DoubleLinkedList::Iterator last = list.End();//ダミーノード
			--last;//ダミーでなく、末尾ノード
			EXPECT_TRUE(list.Remove(last));
			EXPECT_TRUE((&node1) == &(*list.CBegin()));

			//中央を削除
			DoubleLinkedList::Iterator middle(&node3, &list);
			EXPECT_TRUE(list.Remove(middle));
			EXPECT_TRUE((&node1) == &(*list.CBegin()));

			//先頭を削除
			DoubleLinkedList::Iterator head = list.Begin();
			list.Remove(head);
			EXPECT_TRUE((&node2) == &(*list.CBegin()));

		}

		/*********************************************************
		* @brief		constのリストから呼び出して、コンパイルエラーとならないかをチェック
		* @detail		ID:0-34
		* 				constのリストから呼び出して、コンパイルエラーとならないかをチェック
		*				手動テスト
		********************************************************/
		//TEST(ListCBeginTest, IsConst)
		//{
		//	DoubleLinkedList list;
		//	DoubleLinkedList::Node node;
		//	list.PushBack(&node);
		//	const DoubleLinkedList constList = list;
		//	constList.CBegin();//コンパイルエラーにならない
		//}
	}

	//========== 末尾イテレータの取得のテスト ==========
	namespace list_end_test
	{
		/*********************************************************
		* @brief		リストが空である場合に、呼び出した際の挙動
		* @detail		ID:0-35
		* 				リストが空である場合に、呼び出した際に、
		*				戻り値はダミーノードを指すイテレータの場合成功です。
		********************************************************/
		TEST(ListEndTest, WhenEmptyList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;

			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.End(), "iterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストに要素が一つある場合に、呼び出した際の挙動
		* @detail		ID:0-36
		* 				リストに要素が一つある場合に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListEndTest, WhenOneElementList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			EXPECT_EQ(1, list.Count());//リストに要素が一つあるかをチェック

			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.End(), "iterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
		* @detail		ID:0-37
		* 				リストに二つ以上の要素がある場合に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListEndTest, WhenManyElementsList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			EXPECT_LE(2, list.Count());//リストに要素が二つ以上あるかをチェック

			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.End(), "iterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		データの挿入を行った後に、呼び出した際の挙動
		* @detail		ID:0-38
		* 				データの挿入を行った後に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListEndTest, AfterInsert)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//先頭に挿入
			DoubleLinkedList::Iterator head = list.Begin();
			DoubleLinkedList::Node newNode1;
			EXPECT_TRUE(list.Insert(head, &newNode1));
			EXPECT_DEATH(*list.End(), "iterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//中央に挿入
			DoubleLinkedList::Iterator middle(&node2, &list);
			DoubleLinkedList::Node newNode2;
			EXPECT_TRUE(list.Insert(middle, &newNode2));
			EXPECT_DEATH(*list.End(), "iterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//末尾に挿入
			DoubleLinkedList::Iterator tail = list.End();
			DoubleLinkedList::Node newNode3;
			EXPECT_TRUE(list.Insert(tail, &newNode3));
			EXPECT_DEATH(*list.End(), "iterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		データの削除を行った後に、呼び出した際の挙動
		* @detail		ID:0-39
		* 				データの削除を行った後に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListEndTest, AfterRemove)
		{

#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2, node3, node4;
			list.PushBack(&node1);
			list.PushBack(&node2);
			list.PushBack(&node3);
			list.PushBack(&node4);

			//末尾要素を削除
			DoubleLinkedList::Iterator last = list.End();//ダミーノード
			--last;//末尾ノード
			EXPECT_TRUE(list.Remove(last));
			EXPECT_DEATH(*list.End(), "iterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//中央を削除
			DoubleLinkedList::Iterator middle(&node3, &list);
			EXPECT_TRUE(list.Remove(middle));
			EXPECT_DEATH(*list.End(), "iterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//先頭を削除
			DoubleLinkedList::Iterator head = list.Begin();
			EXPECT_TRUE(list.Remove(head));
			EXPECT_DEATH(*list.End(), "iterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
		* @detail		ID	:0-40
		* 				constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
		*					手動テスト
		********************************************************/
		//TEST(ListEndTest, NotConst)
		//{
		//	DoubleLinkedList list;
		//	DoubleLinkedList::Node node;
		//	list.PushBack(&node);
		//	const DoubleLinkedList constList = list;
		//	//constList.End();//コンパイルエラー
		//	SUCCEED();
		//}
	}

	//========== 末尾コンストイテレータの取得のテスト ==========
	namespace list_constEnd_test
	{
		/*********************************************************
		* @brief		リストが空である場合に、呼び出した際の挙動
		* @detail		ID:0-41
		* 				リストが空である場合に、呼び出した際に、
		*				戻り値はダミーノードを指すイテレータの場合成功です。
		********************************************************/
		TEST(ListCEndTest, WhenEmptyList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			
			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストに要素が一つある場合に、呼び出した際の挙動
		* @detail		ID:0-42
		* 				リストに要素が一つある場合に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListCEndTest, WhenOneElementList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node;
			list.PushBack(&node);

			EXPECT_EQ(1, list.Count());//リストに要素が一つあるかをチェック

			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
		* @detail		ID:0-43
		* 				リストに二つ以上の要素がある場合に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		********************************************************/
		TEST(ListCEndTest, WhenManyElementsList)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			EXPECT_LE(2, list.Count());//リストに要素が二つ以上あるかをチェック

			//ダミーノードの場合要素を取得する際にAssert発生
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		データの挿入を行った後に、呼び出した際の挙動
		* @detail		ID:0-44
		* 				データの挿入を行った後に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListCEndTest, AfterInsert)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2;
			list.PushBack(&node1);
			list.PushBack(&node2);

			//先頭に挿入
			DoubleLinkedList::Iterator head = list.Begin();
			DoubleLinkedList::Node newNode1;
			EXPECT_TRUE(list.Insert(head, &newNode1));
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//中央に挿入
			DoubleLinkedList::Iterator middle(&node2, &list);
			DoubleLinkedList::Node newNode2;
			EXPECT_TRUE(list.Insert(middle, &newNode2));
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//末尾に挿入
			DoubleLinkedList::Iterator tail = list.End();
			DoubleLinkedList::Node newNode3;
			EXPECT_TRUE(list.Insert(tail, &newNode3));
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		データの削除を行った後に、呼び出した際の挙動
		* @detail		ID:0-45
		* 				データの削除を行った後に、呼び出した際に、
		*				ダミーノードを指すイテレータが返る場合成功です。
		*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
		********************************************************/
		TEST(ListCEndTest, AfterRemove)
		{
#ifdef _DEBUG
			DoubleLinkedList list;
			DoubleLinkedList::Node node1, node2, node3, node4;
			list.PushBack(&node1);
			list.PushBack(&node2);
			list.PushBack(&node3);
			list.PushBack(&node4);

			//末尾要素を削除
			DoubleLinkedList::Iterator last = list.End();//ダミーノード
			--last;//末尾ノード
			EXPECT_TRUE(list.Remove(last));
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//中央を削除
			DoubleLinkedList::Iterator middle(&node3, &list);
			EXPECT_TRUE(list.Remove(middle));
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生

			//先頭を削除
			DoubleLinkedList::Iterator head = list.Begin();
			EXPECT_TRUE(list.Remove(head));
			EXPECT_DEATH(*list.CEnd(), "constIterator: is dummy");//ダミーノードの場合要素を取得する際にAssert発生
#else
			SUCCEED();
#endif // _DEBUG
		}

		/*********************************************************
		* @brief		constのリストから呼び出して、コンパイルエラーとならないかをチェック
		* @detail		ID:0-46
		* 				constのリストから呼び出して、コンパイルエラーとならないかをチェック
		*				手動テスト
		********************************************************/
		//TEST(ListCEndTest, IsConst)
		//{
		//	DoubleLinkedList list;
		//	DoubleLinkedList::Node node;
		//	list.PushBack(&node);
		//	const DoubleLinkedList constList = list;
		//	constList.CEnd();//コンパイルエラーにならない
		//}
	}

}
#endif