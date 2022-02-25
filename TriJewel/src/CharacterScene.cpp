#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
CharacterScene::CharacterScene(const InitData& init) : IScene(init) {
    id = 0;

    // CSV �t�@�C������f�[�^��ǂݍ���
    const CSVData csv(U"Data/character.csv");

    if (!csv) { // �����ǂݍ��݂Ɏ��s������
        throw Error(U"Failed to load `character.csv`");
    }

    Array<String> str;
    for (int i = 0; i < csv.rows(); i++) {
        text << csv[i];
    }
}

// �X�V�֐�
void CharacterScene::update() {
    // �X�g�[���[�Z���N�g�֖߂�
    if (SimpleGUI::Button(U"���ǂ�", Vec2(10, 10))) {
        AudioAsset(U"se_cancel").playOneShot();
        changeScene(U"StorySelect");
    }

    // �L�����N�^�[�I��
    for (int i = 0; i < 6; i++) {
        Rect rect(Scene::Center().x + (70 * (i - 3)), 500, 50, 50);
        if (rect.mouseOver() && MouseL.down()) {
            if (id == i) break;
            AudioAsset(U"se_click").playOneShot();
            id = i;
        }
    }
}

// �`��֐� (const �C��)
void CharacterScene::draw() const {
    // �w�i
    TextureAsset(U"story").draw(0, 0);
    Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

    // �����̔w�i
    Rect(100, 100, Scene::Width() - 200, Scene::Height() - 200).draw(ColorF(1, 1, 1, 0.75));

    // �L�����N�^�[����
    TextureAsset(text[0][id + 1]) .drawAt(200, 200);
    for (int i = 0; i < 6; i++) {
        Rect(Scene::Center().x + (70 * (i - 3)), 500, 50, 50).draw(ColorF(1, 1, (id == i) ? 0 : 1));
        TextureAsset(U"SD" + text[0][i + 1]).draw(Scene::Center().x + (70 * (i - 3)), 500);
    }

    // �e�퍀��
    for (int i = 0; i < 7; i++) {
        FontAsset(U"SmallFont")(text[i][0]).draw(300, 110 + 25 * i, Palette::Black);
        FontAsset(U"SmallFont")(text[i][id + 1]).draw(400, 110 + 25 * i, Palette::Black);
    }

    // ����
    Rect explain(150, 290, 220, 200);
    Rect magic(420, 290, 220, 200);

    explain.draw(ColorF(1, 1, 0, 0.75));
    magic.draw(ColorF(1, 1, 0, 0.75));
    FontAsset(U"SmallFont")(text[7][0] + U"\n\n" + text[7][id + 1]).draw(explain.stretched(-10), Palette::Black);
    FontAsset(U"SmallFont")(text[8][0] + U"\n\n" + text[8][id + 1]).draw(magic.stretched(-10), Palette::Black);

    SimpleGUI::Button(U"���ǂ�", Vec2(10, 10));
}