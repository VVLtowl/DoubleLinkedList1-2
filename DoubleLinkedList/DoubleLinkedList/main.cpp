/**
* @brief	�o�������X�g�œǂݎ�����f�[�^��W���o�͂ɕ\��
* @date		2022/10/04
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "DoubleLinkedList.h"
using namespace std;

int main(void)
{
	//�f�[�^���i�[���邽�߂̃��X�g��p��
	DoubleLinkedList list;	

	//�t�@�C����ǂݍ��݁A�f�[�^���i�[ 
	{
		FILE* fp; 
		char fileName[] = "Scores.txt";

		/**�t�@�C�����J���A���s����ƏI��*/
		{
			fp = fopen(fileName, "r");
			if (fp == NULL) {
				cout << fileName << "file open error!" << endl;
				return -1;
			}
			else {
				cout << fileName << "file opened!" << endl;
			}
		}

		
		/**
		* ���[�v��1�s���ǂݎ�������e���f�[�^�Ɋi�[�A
		* ���e�����Ȃ��ꍇ���[�v�I��
		*/
		{
			int score;					//�X�R�A�f�[�^���ꎞ�i�[�p
			char name[WORD_SIZE];		//���O�f�[�^���ꎞ�i�[�p

			while (fscanf(fp, "%d\t%s", &score, name) != EOF) {
#if 0
				//1�s���ǂݎ�������e���m�F
				cout << name << ":" << score << endl;//test
#endif

				//�X�R�A�f�[�^���쐬���āA�f�[�^���i�[
				DoubleLinkedList::Node* newNode = new DoubleLinkedList::Node;
				strcpy(newNode->scoreData.name, name);//���O�f�[�^����
				newNode->scoreData.score = score;//�X�R�A�f�[�^����

				list.PushBack(newNode);
			}
		}
		

		//�t�@�C�������
		fclose(fp);
	}

	//�C�e���[�g���āu�i�[�������Łv�W���o�͂ɕ\��
	{
		DoubleLinkedList::Iterator it = list.Begin();
		
		for (; it != list.End(); ++it)
		{
			cout << (*it).scoreData.name
				<< (strlen((*it).scoreData.name) < 8 ? "\t\t:" : "\t:")//���񂷂邽�߂ł�
				<< (*it).scoreData.score 
				<< endl;
		}
	}

	//�G���^�[�L�[�������ďI��
	(void)getchar();
	return 0;
}

