#pragma once

const int WORD_SIZE = 50;/**<文字列読み取の上限*/

/**成績データ構造体*/
struct ScoreData
{
	int score;				/**<スコア*/
	char name[WORD_SIZE];	/**<ユーザー名*/

	/**コンストラクタで　データを初期設定*/
	ScoreData() :
		score(0),
		name("test name") {};
};