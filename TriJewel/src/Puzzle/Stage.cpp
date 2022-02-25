#include"Stage.h"

// �R���X�g���N�^1
Stage::Stage() {
	map = Grid<int>(0, 0);
	base = Grid<int>(0, 0);
}

// �R���X�g���N�^2
Stage::Stage(Grid<int> map) {
	this->map = Grid<int>(map.width(), map.height());
	this->base = Grid<int>(map.width(), map.height());

	// �X�e�[�W�ǂݍ���
	for (int i = 0; i < map.height(); i++) {
		for (int j = 0; j < map.width(); j++) {
			this->map[i][j] = map[i][j];

			// ��Ɣ��̉��ɂ͓�������
			if (map[i][j] == ROCK || map[i][j] == BOX) {
				base[i][j] = ROAD;
			}
			else {
				base[i][j] = map[i][j];
			}
		}
	}
}

// �X�V
void Stage::update() {
	
}

// �`��
void Stage::draw() const {
	String name[] = {
		U"road",
		U"wall",
		U"rock",
		U"goal",
		U"box",
		U"place",
		U"door"
	};

	for (int i = 0; i < map.height(); i++) {
		for (int j = 0; j < map.width(); j++) {
			TextureAsset(U"road").draw(100 + j * 30, 100 + i * 30);
			TextureAsset(name[map[i][j]]).draw(100 + j * 30, 100 + i * 30);

			// ���Ɣz�u�ꏊ���d�Ȃ��Ă���
			if (map[i][j] == BOX && base[i][j] == PLACE) {
				TextureAsset(U"match").draw(100 + j * 30, 100 + i * 30);
			}
		}
	}
}

// �w����W�̃u���b�N�㏑��
void Stage::setMap(int type, int i, int j) {
	map[i][j] = type;
}

// �w����W�̃u���b�N�擾
int Stage::getMap(int i, int j) {
	return map[i][j];
}

// �w����W�̃u���b�N�擾(���n)
int Stage::getBaseMap(int i, int j) {
	return base[i][j];
}

// ��
int Stage::getWidth() {
	return map.height();
}

// ����
int Stage::getHeight() {
	return map.width();
}

// ���Ɣz�u�ꏊ���d�Ȃ��Ă��邩
bool Stage::isOverlup(int i, int j) {
	return (map[i][j] == BOX) && (base[i][j] == PLACE);
}
