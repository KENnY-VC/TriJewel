#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
StoryScene::StoryScene(const InitData& init) : IScene(init) {
    manager = StoryManager(getData().chapter_before, getData().story_before);
}

// �X�V�֐�
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

    // �X�g�[���[�Z���N�g�֖߂�
    if (SimpleGUI::Button(U"���ǂ�", Vec2(10, 10)))
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

// �`��֐� (const �C��)
void StoryScene::draw() const {
    TextureAsset(U"story").draw(0, 0);
    Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

    manager.draw();

    SimpleGUI::Button(U"���ǂ�", Vec2(10, 10));
}
