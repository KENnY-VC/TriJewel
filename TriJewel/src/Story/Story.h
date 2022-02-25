#ifndef __STORY_H__
#define __STORY_H__

#include <siv3D.hpp>

// アクター
typedef struct {
	int id;	// 番号
	s3d::String name;	// 名前
	int x, y;	// 座標
	int width, height;	// 横の長さ、縦の長さ
}Actor;

// セリフ
typedef struct {
	int left, right;	// 左に立つキャラ、右に立つキャラ(各キャラには 0～5 の番号が割り振られます。-1の場合、キャラは表示されません)
	s3d::String text;	// セリフ
	int speaker;	// 話者(0: 誰も喋らない、1: 左のキャラ、2: 右のキャラ)
	int bgm;	// 再生するBGM(0: ほのぼの、1: フィナーレ)
}Dialogue;

// ストーリー画面管理クラス
class StoryManager {
private:
	Array<Dialogue> dialogue;	// セリフ

	int scene;	// セリフ番号

	int playing;	// セリフ再生中かどうかフラグ
	int start;	// 開始時間(セリフ再生のために必要)
	int length;	// 表示させるセリフの長さ

public:
	StoryManager();	// コンストラクタ1
	StoryManager(int, int);	// コンストラクタ2
	int update();	// 更新
	void draw() const;	// 描画
};

#endif