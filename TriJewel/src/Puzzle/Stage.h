#ifndef __STAGE_H__
#define __STAGE_H__

#include<Siv3D.hpp>

// ブロックの種類
#define ROAD 0
#define WALL 1
#define ROCK 2
#define GOAL 3
#define BOX 4
#define PLACE 5
#define DOOR 6

class Stage {
private:
	Grid<int> map;	// ブロック
	Grid<int> base;	// ブロック(下地)

public:
	Stage();	// コンストラクタ1
	Stage(Grid<int>);	// コンストラクタ2
	void update();	// 更新
	void draw() const;	// 描画

	void setMap(int, int, int);	// 指定座標のブロック上書き
	int getMap(int, int);	// 指定座標のブロック取得
	int getBaseMap(int, int);	// 指定座標のブロック取得(下地)

	int getWidth();	// 幅
	int getHeight();	// 高さ

	bool isOverlup(int, int);	// 箱と配置場所が重なっているか
};

#endif
