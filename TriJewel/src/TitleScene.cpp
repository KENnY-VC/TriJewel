#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
TitleScene::TitleScene(const InitData& init) : IScene(init) {
    getData().readSave();
    AudioAsset(U"bgm_title").setLoop(true);
    AudioAsset(U"bgm_title").play();
}

// �X�V�֐�
void TitleScene::update() {
    int button_width = 150;

    // �u�͂��߂�v�{�^��
    if (SimpleGUI::Button(U"�͂��߂�", Vec2(400 - button_width / 2, 250), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"Select");
        AudioAsset(U"bgm_title").stop();
    }

    // �u���͂Ȃ��v�{�^��
    if (SimpleGUI::Button(U"���͂Ȃ�", Vec2(400 - button_width / 2, 300), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"StorySelect");
        AudioAsset(U"bgm_title").stop();
    }

    // �u�����т����v�{�^��
    if (SimpleGUI::Button(U"�����т���", Vec2(400 - button_width / 2, 350), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"HowToPlay");
        AudioAsset(U"bgm_title").stop();
    }

    // �u�����Ă��v�{�^��
    if (SimpleGUI::Button(U"�����Ă�", Vec2(400 - button_width / 2, 400), button_width))
    {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"Config");
        AudioAsset(U"bgm_title").stop();
    }

    // �u�����v�{�^��
    if (SimpleGUI::Button(U"�����", Vec2(400 - button_width / 2, 450), button_width))
    {
        AudioAsset(U"se_cancel").play();
        while (AudioAsset(U"se_cancel").isPlaying());
        System::Exit();
    }
}

// �`��֐� (const �C��)
void TitleScene::draw() const {
    int button_width = 150;

    //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
    TextureAsset(U"title").draw(0, 0);
    TextureAsset(U"logo").drawAt(400, 120);

    SimpleGUI::Button(U"�͂��߂�", Vec2(400 - button_width / 2, 250), button_width);
    SimpleGUI::Button(U"���͂Ȃ�", Vec2(400 - button_width / 2, 300), button_width);
    SimpleGUI::Button(U"�����т���", Vec2(400 - button_width / 2, 350), button_width);
    SimpleGUI::Button(U"�����Ă�", Vec2(400 - button_width / 2, 400), button_width);
    SimpleGUI::Button(U"�����", Vec2(400 - button_width / 2, 450), button_width);
}