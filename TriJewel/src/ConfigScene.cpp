#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
ConfigScene::ConfigScene(const InitData& init) : IScene(init) {

}

// �X�V�֐�
void ConfigScene::update() {
    constexpr std::array<Size, 3> resolutions = {
        Size(640, 480), Size(800, 600), Size(1024, 768)
    };

    // �^�C�g���֖߂�
    if (SimpleGUI::Button(U"�^�C�g��", Vec2(10, 10))) {
        AudioAsset(U"se_cancel").playOneShot();
        changeScene(U"Title");
    }

    // �E�B���h�E�T�C�Y��ύX
    if (SimpleGUI::RadioButtons(getData().index, { U"640x480", U"800x600", U"1024x768", U"�t���X�N���[��" }, Vec2(Scene::Center().x - 75, 150))) {
        AudioAsset(U"se_click").playOneShot();

        if (getData().index == 3) {
            Window::Maximize();
        }
        else {
            Window::Resize(resolutions[getData().index], WindowResizeOption::KeepSceneSize);
        }
    }

    // �Z�[�u�f�[�^�폜
    if (SimpleGUI::Button(U"�f�[�^������", Vec2(Scene::Center().x - 75, 400))) {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"Delete");
    }
}

// �`��֐� (const �C��)
void ConfigScene::draw() const {
    TextureAsset(U"title").draw(0, 0);

    // �^�C�g���֖߂�{�^��
    SimpleGUI::Button(U"�^�C�g��", Vec2(10, 10));

    // �E�B���h�E�T�C�Y
    SimpleGUI::RadioButtons(getData().index, { U"640x480", U"800x600", U"1024x768", U"�t���X�N���[��"}, Vec2(Scene::Center().x - 75, 150));

    // �Z�[�u�f�[�^�폜�{�^��
    {
        const ScopedColorMul2D state(ColorF(1, 0.5, 0.5, 1));
        SimpleGUI::Button(U"�f�[�^������", Vec2(Scene::Center().x - 75, 400));
    }

    FontAsset(U"TitleFont")(U"�����Ă�").drawAt(Scene::Center().x, 104, Palette::Gray);
    FontAsset(U"TitleFont")(U"�����Ă�").drawAt(Scene::Center().x, 100);
}
