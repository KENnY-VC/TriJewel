#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
SelectScene::SelectScene(const InitData& init) : IScene(init) {
    mode = getData().clear_flag == 1 ? 1 : 0;
    difficult = getData().diff_before;

    diff_str[0] = U"���񂽂�";
    diff_str[1] = U"�ӂ�";
    diff_str[2] = U"�ނ�������";

    getData().clear_flag = 0;
    getData().previous_mode = PUZZLE_MODE;
}

// �X�V�֐�
void SelectScene::update() {
    switch (mode) {
        // ���x���I��
    case 0:
        // �^�C�g���֖߂�
        if (SimpleGUI::Button(U"�^�C�g��", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();
            changeScene(U"Title");
        }

        // �ǂꂩ�̃��x�����I�����ꂽ��A�X�e�[�W�I���ֈړ�����
        for (int i = 0; i < DIFF_NUM; i++) {
            if (SimpleGUI::Button(diff_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150))
            {
                AudioAsset(U"se_click").playOneShot();

                mode = 1;
                difficult = i + 1;
                getData().diff_before = difficult;
            }
        }

        break;

        // �X�e�[�W�I��
    case 1:
        // ���x���I���֖߂�
        if (SimpleGUI::Button(U"���ǂ�", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();
            mode = 0;
        }

        // �p�Y����ʂֈړ�����
        for (int i = 0; i < STAGE_NUM; i++) {
            bool cond = (getData().total[getData().diff_before - 1] > i - init_stage);

            if (SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 100 * (i % init_stage), 200 + 50 * (i / init_stage)), unspecified, cond))
            {
                AudioAsset(U"se_click").playOneShot();

                stage = i + 1;
                getData().stage_before = stage;
                changeScene(U"Puzzle");
            }
        }
        break;

    default:
        break;
    }
}

// �`��֐� (const �C��)
void SelectScene::draw() const {
    TextureAsset(U"select").draw(0, 0);

    switch (mode) {
        // ���x���I��
    case 0:
        // �^�C�g���֖߂�{�^��
        SimpleGUI::Button(U"�^�C�g��", Vec2(10, 10));

        // ��Փx�{�^��
        for (int i = 0; i < DIFF_NUM; i++) {
            SimpleGUI::Button(diff_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150);
        }
        break;

        // �X�e�[�W�I��
    case 1:
        // �߂�{�^��
        SimpleGUI::Button(U"���ǂ�", Vec2(10, 10));
        // �X�e�[�W�ԍ�
        for (int i = 0; i < STAGE_NUM; i++) {
            bool cond = (getData().total[getData().diff_before - 1] > i - init_stage);
            SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 100 * (i % init_stage), 200 + 50 * (i / init_stage)), unspecified, cond);
            if (getData().data[getData().diff_before - 1][i] == 1) {
                Rect(100 + 100 * (i % init_stage), 200 + 50 * (i / init_stage), 65, 35).draw(ColorF(1, 1, 0, 0.5));
            }
        }

        FontAsset(U"StoryFont")(diff_str[difficult - 1]).drawAt(Scene::Width() / 2, 162, Palette::Gray);
        FontAsset(U"StoryFont")(diff_str[difficult - 1]).drawAt(Scene::Width() / 2, 160, Palette::Lightgreen);
        break;

    default:
        break;
    }

    FontAsset(U"TitleFont")(U"�X�e�[�W�Z���N�g").draw(184, 64, Palette::Gray);
    FontAsset(U"TitleFont")(U"�X�e�[�W�Z���N�g").draw(180, 60, Palette::Lightgreen);
}
