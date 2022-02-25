#ifndef __STORY_H__
#define __STORY_H__

#include <siv3D.hpp>

// �A�N�^�[
typedef struct {
	int id;	// �ԍ�
	s3d::String name;	// ���O
	int x, y;	// ���W
	int width, height;	// ���̒����A�c�̒���
}Actor;

// �Z���t
typedef struct {
	int left, right;	// ���ɗ��L�����A�E�ɗ��L����(�e�L�����ɂ� 0�`5 �̔ԍ�������U���܂��B-1�̏ꍇ�A�L�����͕\������܂���)
	s3d::String text;	// �Z���t
	int speaker;	// �b��(0: �N������Ȃ��A1: ���̃L�����A2: �E�̃L����)
	int bgm;	// �Đ�����BGM(0: �ق̂ڂ́A1: �t�B�i�[��)
}Dialogue;

// �X�g�[���[��ʊǗ��N���X
class StoryManager {
private:
	Array<Dialogue> dialogue;	// �Z���t

	int scene;	// �Z���t�ԍ�

	int playing;	// �Z���t�Đ������ǂ����t���O
	int start;	// �J�n����(�Z���t�Đ��̂��߂ɕK�v)
	int length;	// �\��������Z���t�̒���

public:
	StoryManager();	// �R���X�g���N�^1
	StoryManager(int, int);	// �R���X�g���N�^2
	int update();	// �X�V
	void draw() const;	// �`��
};

#endif