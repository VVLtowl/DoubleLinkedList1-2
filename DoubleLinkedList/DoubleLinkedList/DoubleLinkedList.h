#pragma once
#include "ScoreData.h"

//========== 双方向リスト ==========
class DoubleLinkedList
{
public:
	//========== ノード構造体 ==========
	struct Node
	{
		Node* pPrev = nullptr;			//目のノードへのポインタ
		Node* pNext = nullptr;			//次のノードへのポインタ
		ScoreData scoreData;			//成績データ
		bool isDummy;					//ダミーノード判断用

		Node();								//コンストラクタ　ダミーノードとして呼び出した時
		Node(int score, const char* name);	//コンストラクタ　要素ノードとして呼び出した時
	};

	//==========  コンストイテレータ ==========
	class ConstIterator
	{
	protected:
		Node* m_pNode;												// Node要素へのポインタ
		const DoubleLinkedList* m_pList;							//リストへのポインタ

	protected:
		bool IsVaild(const DoubleLinkedList* const list);			//有効なイテレータであるか
		const Node* operator&()const;								//指す要素へのポインタを取得する(const版)
	public:
		ConstIterator() :
			ConstIterator(nullptr, nullptr) {};
		ConstIterator(Node* node, const DoubleLinkedList* list) :
			m_pNode(node), m_pList(list) { };						//コンストラクタで参照を設定

		ConstIterator& operator--();								//リストの先頭に向かって一つ進める
		ConstIterator& operator++();								//リストの末尾に向かって一つ進める
		ConstIterator operator--(int i);							//リストの先頭に向かって一つ進める
		ConstIterator operator++(int i);							//リストの末尾に向かって一つ進める
		const Node& operator*()const;								//イテレータの指す要素を取得する(const版)

		ConstIterator(const ConstIterator& constIter);				//コピーを行う（コピーコンストラクタ）
		ConstIterator& operator=(const ConstIterator& constIter);	//代入を行う
		bool operator==(const ConstIterator& constIter);			//同一か比較する
		bool operator!=(const ConstIterator& constIter);			//異なるか比較する


		friend DoubleLinkedList;									//DoubleLinkedListの関数内で、有効イテレータ確認が行えるため
	};

	//========== イテレータ ==========
	class Iterator :public ConstIterator
	{
	private:
		Node* operator&();										//指す要素へのポインタを取得する(非const版)
	public:
		Iterator() :
			Iterator(nullptr, nullptr) {};
		Iterator(Node* node, const DoubleLinkedList* list) :
			ConstIterator(node, list) {};						//コンストラクタで参照を設定

		Node& operator*();										//イテレータのさす要素を取得する(非const版)
		//Node* operator&();									
	};

private:
	Node* m_pDummy;										//ノードへのポインタ 
	Node* HeadNode() const { return m_pDummy->pNext; };	//先頭ノードへのポインタを取得

public:
	~DoubleLinkedList() {								//デストラクタ定義
		delete m_pDummy;
	}
	DoubleLinkedList() {									//コンストラクタ定義
		m_pDummy = new Node();
		m_pDummy->isDummy = true;
	}

	int Count()const;									//データ数を取得する
	bool PushBack(Node* newNode);						//データを末尾後に追加
	bool Insert(ConstIterator& position, Node* newNode);//データの挿入
	bool Remove(ConstIterator& position);				//データの削除
	Iterator Begin();									//先頭イテレータ取得する
	ConstIterator CBegin()const;						//先頭コンストイテレータ取得
	Iterator End();										//末尾イテレータ取得する
	ConstIterator CEnd()const;							//末尾コンストイテレータ取得
};

