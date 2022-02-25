#include"GameScene.h"

// コンストラクタ（必ず実装）
TitleScene::TitleScene(const InitData& init) : IScene(init) {
    getData().readSave();
    AudioAsset(U"bgm_title").setLoop(true);
    AudioAsset(U"bgm_title").play();
}

// 更新関数
void TitleScene::update() {
    int button_width = 150;

    // 「はじめる」ボタン
    if (SimpleGUI::Button(U"はじめる", Vec2(400 - button_width / 2, 250), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"Select");
        AudioAsset(U"bgm_title").stop();
    }

    // 「おはなし」ボタン
    if (SimpleGUI::Button(U"おはなし", Vec2(400 - button_width / 2, 300), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"StorySelect");
        AudioAsset(U"bgm_title").stop();
    }

    // 「あそびかた」ボタン
    if (SimpleGUI::Button(U"あそびかた", Vec2(400 - button_width / 2, 350), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"HowToPlay");
        AudioAsset(U"bgm_title").stop();
    }

    // 「せってい」ボタン
    if (SimpleGUI::Button(U"せってい", Vec2(400 - button_width / 2, 400), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"Config");
        AudioAsset(U"bgm_title").stop();
    }

    // 「おわる」ボタン
    if (SimpleGUI::Button(U"おわる", Vec2(400 - button_width / 2, 450), button_width))
    {
        AudioAsset(U"se_cancel").play();
        while (AudioAsset(U"se_cancel").isPlaying());
        System::Exit();
    }
}

// 描画関数 (const 修飾)
void TitleScene::draw() const {
    int button_width = 150;

    //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
    TextureAsset(U"title").draw(0, 0);
    TextureAsset(U"logo").drawAt(400, 120);

    SimpleGUI::Button(U"はじめる", Vec2(400 - button_width / 2, 250), button_width);
    SimpleGUI::Button(U"おはなし", Vec2(400 - button_width / 2, 300), button_width);
    SimpleGUI::Button(U"あそびかた", Vec2(400 - button_width / 2, 350), button_width);
    SimpleGUI::Button(U"せってい", Vec2(400 - button_width / 2, 400), button_width);
    SimpleGUI::Button(U"おわる", Vec2(400 - button_width / 2, 450), button_width);
}