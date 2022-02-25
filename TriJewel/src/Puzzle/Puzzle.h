#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include"Player.h"
#include"Stage.h"

#define STAGE_SIZE 12

class PuzzleManager {
private:
	Player player;	// �v���C���[
	Array<Player> player_log;	// �v���C���[�̍s�����O

	Stage stage;	// �n�}���
	Stage stage_init;	// �n�}���(�������)
	Array<Stage> stage_log;	// �n�}�̃��O

	int door_flag;	// �������t���O
	int box_num;	// �z�u�ꏊ�i���j�̐����J�E���g����ϐ�

	// ����{�^��
	Rect up;
	Rect right;
	Rect down;
	Rect left;

	bool checkdoor();	// �����J�����̔���
	bool objstack(char, int);	// ��A�����������̔���
	bool playerstack(char, int);	// �v���C���[�������邩�̔���
	void objmove(char, int);	// ��A���̈ړ�����

public:
	PuzzleManager();	// �R���X�g���N�^1
	PuzzleManager(int, int);	// �R���X�g���N�^2
	int update();	// �X�V
	void draw() const;	// �`��
	void readfile(String);	// �t�@�C���ǂݍ���
};

#endif