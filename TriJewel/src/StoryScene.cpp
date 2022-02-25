#include"GameScene.h"

// コンストラクタ（必ず実装）
StoryScene::StoryScene(const InitData& init) : IScene(init) {
    manager = StoryManager(getData().chapter_before, getData().story_before);
}

// 更新関数
void StoryScene::update() {
    if (manager.update() == 1) {
        AudioAsset(U"bgm_story1").stop();
        AudioAsset(U"bgm_story2").stop();

        if (getData().previous_mode == STORY_MODE) {
            changeScene(U"StorySelect");
            getData().story_flag = 1;
        }
        else {
            changeScene(U"Select");
        }
    }

    // ストーリーセレクトへ戻る
    if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
    {
        AudioAsset(U"bgm_story1").stop();
        AudioAsset(U"bgm_story2").stop();
        AudioAsset(U"se_cancel").playOneShot();

        if (getData().previous_mode == STORY_MODE) {
            changeScene(U"StorySelect");
            getData().story_flag = 1;
        }
        else {
            changeScene(U"Select");
        }
    }
}

// 描画関数 (const 修飾)
void StoryScene::draw() const {
    TextureAsset(U"story").draw(0, 0);
    Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

    manager.draw();

    SimpleGUI::Button(U"もどる", Vec2(10, 10));
}
