/*********************************************************
* @brief	双方向リストで読み取ったデータを標準出力に表示
* @date		2022/10/04
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "DoubleLinkedList.h"

int main(void)
{
	//データを格納するためのリストを用意
	DoubleLinkedList list;	

	//ファイルを読み込み、データを格納 
	{
		FILE* fp; 
		char fileName[] = "Scores.txt";

		//ファイルを開く、失敗すると終了
		{
			fp = fopen(fileName, "r");
			if (fp == NULL) {
				std::cout << fileName << " : file open error!" << std::endl;
				return -1;
			}
			else {
				std::cout << fileName << " : file opened!" << std::endl;
			}
		}

		
		//ループで1行ずつ読み取った内容をデータに格納、
		//内容が取らない場合ループ終了
		{
			int score;					//スコアデータを一時格納用
			char name[WORD_SIZE];		//名前データを一時格納用

			while (fscanf(fp, "%d\t%s", &score, name) != EOF) {
#if 0
				//1行ずつ読み取った内容を確認
				std::cout << name << ":" << score << std::endl;//test
#endif

				//スコアデータを作成して、データを格納
				ScoreData data(score, name);

				DoubleLinkedList::ConstIterator end = list.End();
				list.Insert(end, data);
			}
		}
		
		//ファイルを閉じる
		fclose(fp);
	}


	//イテレートして「格納した順で」標準出力に表示
	{
		DoubleLinkedList::Iterator it = list.Begin();
		
		for (; it != list.End(); ++it)
		{
			std::cout << (*it).name
				<< ((*it).name.size() < 8 ? "\t\t:" : "\t:")//整列するためです
				<< (*it).score 
				<< std::endl;
		}
	}

	//エンターキーを押して終了
	(void)getchar();
	return 0;
}

