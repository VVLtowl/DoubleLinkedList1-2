#pragma once

const int WORD_SIZE = 50;/**<������ǂݎ�̏��*/

/**���уf�[�^�\����*/
struct ScoreData
{
	int score;				/**<�X�R�A*/
	char name[WORD_SIZE];	/**<���[�U�[��*/

	/**�R���X�g���N�^�Ł@�f�[�^�������ݒ�*/
	ScoreData() :
		score(0),
		name("test name") {};
};