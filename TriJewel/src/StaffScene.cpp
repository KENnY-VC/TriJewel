#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
StaffScene::StaffScene(const InitData& init) : IScene(init) {
    scroll = Scene::Height() / 2 + 200;

    TextReader reader;
    String line;

    if (!reader.open(U"Data/staff.txt")) {
        throw Error(U"Failed to open staff.txt");
    }

    // �X�^�b�t�N���W�b�g���̓ǂݍ���
    while (reader.readLine(line)) {
        // ��s�͑傫�ȃX�y�[�X
        if (line.isEmpty()) {
            for (int i = 0; i < 3; i++) {
                credit << U"";
            }
        }

        // ��s���ǂݍ���
        else {
            credit << line;
        }
    }

    reader.close();

    AudioAsset(U"bgm_ed").play();
}

// �X�V�֐�
void StaffScene::update() {
    scroll -= 1;

    // �X�g�[���[�I����ʂ֖߂�
    if (MouseR.down() || !AudioAsset(U"bgm_ed").isPlaying())
    {
        AudioAsset(U"bgm_ed").stop();
        changeScene(U"StorySelect");
    }
}

// �`��֐� (const �C��)
void StaffScene::draw() const {
    String fontName;
    Color color;

    TextureAsset(U"logo").drawAt(Scene::Width() / 2, scroll - 200);

    for (int i = 0; i < credit.size(); i++) {
        if (credit[i][0] == '(')
            fontName = U"StoryFont";
        else
            fontName = U"TitleFont";

        if (credit[i][0] == '<')
            color = Palette::Lightgreen;
        else
            color = Palette::White;

        FontAsset(fontName)(credit[i]).drawAt(Scene::Width() / 2, scroll + 60 * i, color);
    }
}
