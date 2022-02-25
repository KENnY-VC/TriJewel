#ifndef __PLAYER_H__
#define __PLAYER_H__

// プレイヤーの向き
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Player {
private:
	int i, j;	// 添え字
	int x, y;	// 座標
	int width, height;	// 大きさ
	int direction;	// 向き

public:
	Player();	// コンストラクタ1
	Player(int, int);	// コンストラクタ2
	void update(int);	// 更新
	void draw() const;	// 描画

	int getI();	// i
	int getJ();	// j

	void setDirection(int);	// 向きを変更
};

#endif