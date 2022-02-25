#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include"Player.h"
#include"Stage.h"

#define STAGE_SIZE 12

class PuzzleManager {
private:
	Player player;	// プレイヤー
	Array<Player> player_log;	// プレイヤーの行動ログ

	Stage stage;	// 地図情報
	Stage stage_init;	// 地図情報(初期状態)
	Array<Stage> stage_log;	// 地図のログ

	int door_flag;	// 扉解錠フラグ
	int box_num;	// 配置場所（箱）の数をカウントする変数

	// 操作ボタン
	Rect up;
	Rect right;
	Rect down;
	Rect left;

	bool checkdoor();	// 扉が開くかの判定
	bool objstack(char, int);	// 岩、箱が動くかの判定
	bool playerstack(char, int);	// プレイヤーが動けるかの判定
	void objmove(char, int);	// 岩、箱の移動処理

public:
	PuzzleManager();	// コンストラクタ1
	PuzzleManager(int, int);	// コンストラクタ2
	int update();	// 更新
	void draw() const;	// 描画
	void readfile(String);	// ファイル読み込み
};

#endif