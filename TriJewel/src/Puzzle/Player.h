#ifndef __PLAYER_H__
#define __PLAYER_H__

// �v���C���[�̌���
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Player {
private:
	int i, j;	// �Y����
	int x, y;	// ���W
	int width, height;	// �傫��
	int direction;	// ����

public:
	Player();	// �R���X�g���N�^1
	Player(int, int);	// �R���X�g���N�^2
	void update(int);	// �X�V
	void draw() const;	// �`��

	int getI();	// i
	int getJ();	// j

	void setDirection(int);	// ������ύX
};

#endif