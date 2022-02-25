#ifndef __STAGE_H__
#define __STAGE_H__

#include<Siv3D.hpp>

// �u���b�N�̎��
#define ROAD 0
#define WALL 1
#define ROCK 2
#define GOAL 3
#define BOX 4
#define PLACE 5
#define DOOR 6

class Stage {
private:
	Grid<int> map;	// �u���b�N
	Grid<int> base;	// �u���b�N(���n)

public:
	Stage();	// �R���X�g���N�^1
	Stage(Grid<int>);	// �R���X�g���N�^2
	void update();	// �X�V
	void draw() const;	// �`��

	void setMap(int, int, int);	// �w����W�̃u���b�N�㏑��
	int getMap(int, int);	// �w����W�̃u���b�N�擾
	int getBaseMap(int, int);	// �w����W�̃u���b�N�擾(���n)

	int getWidth();	// ��
	int getHeight();	// ����

	bool isOverlup(int, int);	// ���Ɣz�u�ꏊ���d�Ȃ��Ă��邩
};

#endif
