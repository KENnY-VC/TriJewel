#include"Stage.h"

// コンストラクタ1
Stage::Stage() {
	map = Grid<int>(0, 0);
	base = Grid<int>(0, 0);
}

// コンストラクタ2
Stage::Stage(Grid<int> map) {
	this->map = Grid<int>(map.width(), map.height());
	this->base = Grid<int>(map.width(), map.height());

	// ステージ読み込み
	for (int i = 0; i < map.height(); i++) {
		for (int j = 0; j < map.width(); j++) {
			this->map[i][j] = map[i][j];

			// 岩と箱の下には道がある
			if (map[i][j] == ROCK || map[i][j] == BOX) {
				base[i][j] = ROAD;
			}
			else {
				base[i][j] = map[i][j];
			}
		}
	}
}

// 更新
void Stage::update() {
	
}

// 描画
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

			// 箱と配置場所が重なっている
			if (map[i][j] == BOX && base[i][j] == PLACE) {
				TextureAsset(U"match").draw(100 + j * 30, 100 + i * 30);
			}
		}
	}
}

// 指定座標のブロック上書き
void Stage::setMap(int type, int i, int j) {
	map[i][j] = type;
}

// 指定座標のブロック取得
int Stage::getMap(int i, int j) {
	return map[i][j];
}

// 指定座標のブロック取得(下地)
int Stage::getBaseMap(int i, int j) {
	return base[i][j];
}

// 幅
int Stage::getWidth() {
	return map.height();
}

// 高さ
int Stage::getHeight() {
	return map.width();
}

// 箱と配置場所が重なっているか
bool Stage::isOverlup(int i, int j) {
	return (map[i][j] == BOX) && (base[i][j] == PLACE);
}
