# include <Siv3D.hpp>
# include "src/GameScene.h"

void LoadFont();    // フォント読み込み
void LoadTexture();	// 画像読み込み
void LoadSound();	// 音読み込み

void Main() {
    Window::SetTitle(U"シロナと願いの石～みんなともだち～");

    LoadFont();
    LoadTexture();
    LoadSound();

    // シーンマネージャーを作成
    App manager;

    // シーン登録
    manager.add<TitleScene>(U"Title");
    manager.add<SelectScene>(U"Select");
    manager.add<PuzzleScene>(U"Puzzle");
    manager.add<StorySelectScene>(U"StorySelect");
    manager.add<StoryScene>(U"Story");
    manager.add<RuleScene>(U"HowToPlay");
    manager.add<StaffScene>(U"Staff");
    manager.add<ConfigScene>(U"Config");
    manager.add<DeleteScene>(U"Delete");
    manager.add<CharacterScene>(U"Character");

    while (System::Update()) {
        // 現在のシーンを実行
        if (!manager.update()) {
            break;
        }
    }
}

// フォント読み込み
void LoadFont() {
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
    FontAsset::Register(U"StoryFont", 30);
    FontAsset::Register(U"RuleFont", 25);
    FontAsset::Register(U"SmallFont", 15);
}

// 画像読み込み
void LoadTexture() {
    // タイトル画面
    TextureAsset::Register(U"title", U"Data/Image/title.png");
    TextureAsset::Register(U"logo", U"Data/Image/logo.png");

    // セレクト画面
    TextureAsset::Register(U"select", U"Data/Image/select.png");

    // ストーリー画面
    TextureAsset::Register(U"story", U"Data/Image/story.png");

    // パズル画面
    TextureAsset::Register(U"player", U"Data/Image/game/player.png");
    TextureAsset::Register(U"road", U"Data/Image/game/grass.png");
    TextureAsset::Register(U"wall", U"Data/Image/game/tree.png");
    TextureAsset::Register(U"rock", U"Data/Image/game/rock.png");
    TextureAsset::Register(U"goal", U"Data/Image/game/goal.png");
    TextureAsset::Register(U"box", U"Data/Image/game/box.png");
    TextureAsset::Register(U"place", U"Data/Image/game/place.png");
    TextureAsset::Register(U"door", U"Data/Image/game/door.png");
    TextureAsset::Register(U"button", U"Data/Image/game/button.png");
    TextureAsset::Register(U"match", U"Data/Image/game/match.png");

    // ストーリーにおけるキャラクター
    TextureAsset::Register(U"シロナ", U"Data/Image/story/sirona.png");
    TextureAsset::Register(U"リンドル", U"Data/Image/story/rindol.png");
    TextureAsset::Register(U"チャマ", U"Data/Image/story/chama.png");
    TextureAsset::Register(U"ファイ", U"Data/Image/story/phi.png");
    TextureAsset::Register(U"エメ", U"Data/Image/story/eme.png");
    TextureAsset::Register(U"メルビィ", U"Data/Image/story/meruby.png");
    TextureAsset::Register(U"next", U"Data/Image/story/next.png");

    // 操作説明
    TextureAsset::Register(U"keyboard", U"Data/Image/keyboard.png");
    TextureAsset::Register(U"mouse", U"Data/Image/mouse.png");

    // SDキャラ
    TextureAsset::Register(U"SDシロナ", U"Data/Image/sd/sd_sirona.png");
    TextureAsset::Register(U"SDリンドル", U"Data/Image/sd/sd_rindol.png");
    TextureAsset::Register(U"SDチャマ", U"Data/Image/sd/sd_chama.png");
    TextureAsset::Register(U"SDファイ", U"Data/Image/sd/sd_phi.png");
    TextureAsset::Register(U"SDエメ", U"Data/Image/sd/sd_eme.png");
    TextureAsset::Register(U"SDメルビィ", U"Data/Image/sd/sd_meruby.png");
}

// 音読み込み
void LoadSound() {
    // 効果音
    AudioAsset::Register(U"se_click", U"Data/Sound/se/click.ogg");
    AudioAsset::Register(U"se_cancel", U"Data/Sound/se/cancel.ogg");
    AudioAsset::Register(U"se_step", U"Data/Sound/se/step.ogg");
    AudioAsset::Register(U"se_select", U"Data/Sound/se/select.ogg");
    AudioAsset::Register(U"se_unlock", U"Data/Sound/se/unlock.ogg");
    AudioAsset::Register(U"se_delete", U"Data/Sound/se/delete.mp3");

    // BGM
    AudioAsset::Register(U"bgm_title", U"Data/Sound/bgm/title.ogg");
    AudioAsset::Register(U"bgm_stage1", U"Data/Sound/bgm/stage1.ogg");
    AudioAsset::Register(U"bgm_stage2", U"Data/Sound/bgm/stage2.ogg");
    AudioAsset::Register(U"bgm_stage3", U"Data/Sound/bgm/stage3.ogg");
    AudioAsset::Register(U"bgm_clear", U"Data/Sound/bgm/clear.ogg");
    AudioAsset::Register(U"bgm_story1", U"Data/Sound/bgm/story.ogg");
    AudioAsset::Register(U"bgm_story2", U"Data/Sound/bgm/story2.ogg");
    AudioAsset::Register(U"bgm_ed", U"Data/Sound/bgm/ed_theme.ogg");
}