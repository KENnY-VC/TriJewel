#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include<Siv3D.hpp>
#include"Story/Story.h"
#include"Puzzle/Puzzle.h"

#define DIFF_NUM 3  // 難易度数
#define STAGE_NUM 30    // ステージ数

#define CHAPTER_NUM 4   // 章の数
#define STORY_NUM 10    // 物語の数

#define STORY_MODE 0    // ストーリーモード
#define PUZZLE_MODE 1   // パズルモード

// セーブデータ及び共有データ
struct SaveData {
    int data[DIFF_NUM][STAGE_NUM];  // ステージのクリア状況
    int total[DIFF_NUM];    // クリアしたステージの合計(難易度別)
    int clear_flag = 0;  // クリアフラグ

    int diff_before = 0;    // 直前に選ばれていた難易度
    int stage_before = 0;   // 直前に選ばれていたステージ

    int story_flag = 0; // ストーリー再生フラグ
    int chapter_before = 0; // 直前に選ばれていた章
    int story_before = 0;   // 直前に選ばれていた物語
    String chap_str[CHAPTER_NUM];   // 章を表す文字列
    String caption[CHAPTER_NUM][STORY_NUM]; // 物語を表す文字列

    size_t index = 1;   // 画面サイズの番号
    int previous_mode;  // 直前に選ばれていたゲームモード

    void readSave();     // セーブデータ読み込み
    void writeSave();   // セーブデータ上書き
    void updateTotal(); // クリアしたステージの合計(難易度別)
    void readCaption(); // 物語データ読み込み
    void clearRecord();   // パズルクリア時の処理
};

using App = SceneManager<String, SaveData>;

// タイトルシーン
class TitleScene : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    TitleScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// ステージセレクトシーン
class SelectScene : public App::Scene
{
private:
    int mode;   // シーン内モード管理(レベル選択 <---> ステージ選択)
    int difficult;  // 難易度
    int stage;      // ステージ番号

    s3d::String diff_str[DIFF_NUM];   // 難易度を表す文字列

    const int init_stage = 6;   // 最初から開放されているステージ

public:

    // コンストラクタ（必ず実装）
    SelectScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// パズルシーン
class PuzzleScene : public App::Scene
{
private:
    PuzzleManager manager;  // パズル画面管理
    int puzzle_state;   // パズルのクリア状況
    int pause;  // 操作説明画面表示フラグ
    s3d::Audio bgm; // BGM

public:

    // コンストラクタ（必ず実装）
    PuzzleScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// ストーリーセレクトシーン
class StorySelectScene : public App::Scene
{
private:
    int mode;   // シーン内モード管理(章選択 <---> 話数選択)
    int chapter;    // 章番号
    int story;  // 話数

public:

    // コンストラクタ（必ず実装）
    StorySelectScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// ストーリー再生シーン
class StoryScene : public App::Scene
{
private:
    StoryManager manager;   // ストーリー画面管理

public:

    // コンストラクタ（必ず実装）
    StoryScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// ルール説明シーン
class RuleScene : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    RuleScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// スタッフクレジットシーン
class StaffScene : public App::Scene
{
private:
    Array<String> credit;   // スタッフクレジット(一行ずつ格納する)
    int scroll;   // スクロール位置(y座標)

public:

    // コンストラクタ（必ず実装）
    StaffScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// 設定シーン
class ConfigScene : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    ConfigScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// セーブデータ削除シーン
class DeleteScene : public App::Scene
{
private:
    int mode;

public:

    // コンストラクタ（必ず実装）
    DeleteScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

// キャラクター紹介シーン
class CharacterScene : public App::Scene
{
private:
    int id;
    Array<Array<String>> text;
public:

    // コンストラクタ（必ず実装）
    CharacterScene(const InitData& init);

    // 更新関数
    void update() override;

    // 描画関数 (const 修飾)
    void draw() const override;
};

#endif