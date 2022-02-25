#include<Siv3D.hpp>
#include"Player.h"

// �R���X�g���N�^1
Player::Player() {
	i = j = 0;

	width = 30;
	height = 30;

	x = 100 + j * width;
	y = 100 + i * height;

	direction = UP;
}

// �R���X�g���N�^2
Player::Player(int i, int j) {
	this->i = i;
	this->j = j;

	width = 30;
	height = 30;

	x = 100 + j * width;
	y = 100 + i * height;

	direction = UP;
}

// �v���C���[�X�V
void Player::update(int direction) {
	switch (direction) {
	case UP:
		y -= height;
		i--;
		break;
	case RIGHT:
		x += width;
		j++;
		break;
	case DOWN:
		y += height;
		i++;
		break;
	case LEFT:
		x -= width;
		j--;
		break;
	}
}

// �v���C���[�`��
void Player::draw() const {
	TextureAsset(U"player").rotated(direction * 90_deg).draw(x, y);
}

// i
int Player::getI() {
	return i;
}

// j
int Player::getJ() {
	return j;
}

// ������ύX
void Player::setDirection(int direction) {
	this->direction = direction;
}