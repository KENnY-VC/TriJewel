#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
StorySelectScene::StorySelectScene(const InitData& init) : IScene(init) {
    mode = (getData().story_flag == 1 && getData().chapter_before != 0) ? 1 : 0;
    chapter = getData().chapter_before;
    story = 0;

    getData().story_flag = 0;
    getData().readCaption();
    getData().previous_mode = STORY_MODE;
}

// �X�V�֐�
void StorySelectScene::update() {
    switch (mode) {
    case 0:
        // �^�C�g���֖߂�
        if (SimpleGUI::Button(U"�^�C�g��", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();

            changeScene(U"Title");
        }

        // �v�����[�O
        if (SimpleGUI::Button(U"�͂��܂�", Vec2(100, Scene::Height() / 4 + 50), 150))
        {
            AudioAsset(U"se_click").playOneShot();

            chapter = 0;
            getData().chapter_before = chapter;
            story = 0;
            getData().story_before = story;
            //story_init(chapter, story);
            changeScene(U"Story");
        }

        // �ǂꂩ�̕��ꂪ�I�����ꂽ��A�b���I����ʂֈړ�����
        for (int i = 0; i < CHAPTER_NUM - 1; i++) {
            if (SimpleGUI::Button(getData().chap_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 180))
            {
                AudioAsset(U"se_click").playOneShot();

                mode = 1;
                chapter = i + 1;
                getData().chapter_before = chapter;
            }
        }

        // �X�^�b�t�N���W�b�g
        if (getData().total[0] + getData().total[1] + getData().total[2] == STAGE_NUM * DIFF_NUM) {
            if (SimpleGUI::Button(U"���܂�", Vec2(500, Scene::Height() / 4 * 3 - 50))) {
                AudioAsset(U"se_click").playOneShot();

                mode = 1;
                chapter = CHAPTER_NUM;
                getData().chapter_before = chapter;
            }

            if (SimpleGUI::Button(U"�X�^�b�t�N���W�b�g", Vec2(500, Scene::Height() / 4 * 3))) {
                AudioAsset(U"se_click").playOneShot();

                chapter = 0;
                getData().chapter_before = chapter;
                story = 0;
                changeScene(U"Staff");
            }
        }

        // �L�����N�^�[�Љ�
        if (SimpleGUI::Button(U"�L�����N�^�[", Vec2(100, Scene::Height() / 2 + 50))) {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"Character");
        }

        break;

    case 1:
        // �͑I����ʂ֖߂�
        if (SimpleGUI::Button(U"���ǂ�", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();

            mode = 0;
        }

        // �X�g�[���[�Đ���ʂֈړ�����
        for (int i = 0; i < STORY_NUM; i++) {
            bool cond = getData().total[getData().chapter_before - 1] / (STAGE_NUM / STORY_NUM) >= (i + 1) || getData().chapter_before == CHAPTER_NUM;

            if (SimpleGUI::Button(getData().caption[chapter - 1][i], Vec2(250, 150 + 40 * i), 300, cond))
            {
                AudioAsset(U"se_click").playOneShot();

                story = i + 1;
                getData().story_before = story;

                //story_init(chapter, story);
                changeScene(U"Story");
            }
        }
        break;

    default:
        break;
    }
}

// �`��֐� (const �C��)
void StorySelectScene::draw() const {
    TextureAsset(U"story").draw(0, 0);
    Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

    switch (mode) {
        // �͑I��
    case 0:
        // �^�C�g���֖߂�{�^��
        SimpleGUI::Button(U"�^�C�g��", Vec2(10, 10));

        SimpleGUI::Button(U"�͂��܂�", Vec2(100, Scene::Height() / 4 + 50), 150);

        // �e�̓{�^��
        for (int i = 0; i < CHAPTER_NUM - 1; i++) {
            SimpleGUI::Button(getData().chap_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 180);
        }

        if (getData().total[0] + getData().total[1] + getData().total[2] == STAGE_NUM * DIFF_NUM) {
            SimpleGUI::Button(U"���܂�", Vec2(500, Scene::Height() / 4 * 3 - 50));
            SimpleGUI::Button(U"�X�^�b�t�N���W�b�g", Vec2(500, Scene::Height() / 4 * 3));
        }

        {
            const ScopedColorMul2D state(ColorF(0, 1, 1, 1));
            SimpleGUI::Button(U"�L�����N�^�[", Vec2(100, Scene::Height() / 2 + 50));
        }

        break;

        // �b���I��
    case 1:
        // �߂�{�^��
        SimpleGUI::Button(U"���ǂ�", Vec2(10, 10));
        // �b��
        for (int i = 0; i < STORY_NUM; i++) {
            bool cond = getData().total[getData().chapter_before - 1] / (STAGE_NUM / STORY_NUM) >= (i + 1) || getData().chapter_before == CHAPTER_NUM;
            SimpleGUI::Button(getData().caption[chapter - 1][i], Vec2(250, 150 + 40 * i), 300, cond);
        }
        break;

    default:
        break;
    }

    FontAsset(U"TitleFont")(U"�X�g�[���[�Z���N�g").drawAt(404, 104, Palette::Gray);
    FontAsset(U"TitleFont")(U"�X�g�[���[�Z���N�g").drawAt(400, 100, Palette::White);
}
