#include"GameScene.h"

// �R���X�g���N�^�i�K�������j
PuzzleScene::PuzzleScene(const InitData& init) : IScene(init) {
	manager = PuzzleManager(getData().diff_before, getData().stage_before);

	puzzle_state = 0;
    pause = 0;
	bgm = AudioAsset(U"bgm_stage{}"_fmt(getData().diff_before));

	bgm.setLoop(true);
	bgm.play();

    getData().readCaption();
}

// �X�V�֐�
void PuzzleScene::update() {
    // �N���A���Ă��Ȃ��ԁA�p�Y����V�ׂ�
    if (puzzle_state == 0) {

        // ����������J�� / ����
        if (SimpleGUI::Button(U"�w���v", Vec2(Scene::Width() - 120, 10))) {
            AudioAsset(pause == 0 ? U"se_click" : U"se_cancel").playOneShot();
            pause = (pause + 1) % 2;
        }

        if (pause == 1) return;

        puzzle_state = manager.update();

        // �X�e�[�W�Z���N�g�֖߂�
        if (SimpleGUI::Button(U"���ǂ�", Vec2(10, 10))) {
            if (bgm.isPlaying()) {
                bgm.stop();
            }

            AudioAsset(U"se_cancel").playOneShot();

            getData().clear_flag = 1;

            changeScene(U"Select");
        }
    }

    // �N���A������A�X�e�[�W�Z���N�g�֖߂�
    else {
        if (bgm.isPlaying()) {
            bgm.stop();
        }

        if (puzzle_state == 1) {
            AudioAsset(U"bgm_clear").play();
            puzzle_state = 2;
        }

        // ���͂Ȃ����[�h�֑J��
        if (getData().data[getData().diff_before - 1][getData().stage_before - 1] == 0 && (getData().total[getData().diff_before - 1] + 1) % 3 == 0) {
            if (SimpleGUI::Button(U"���͂Ȃ����݂�", Vec2(Scene::Center().x - 150 / 2, Scene::Center().y + 150), 150)) {
                getData().clearRecord();
                getData().chapter_before = getData().diff_before;
                getData().story_before = (getData().total[getData().diff_before - 1] + 1) / 3;
                changeScene(U"Story");
            }

            // �{�^���ȊO�̏ꏊ���N���b�N���ꂽ��A�X�e�[�W�Z���N�g�֑J��
            else if (MouseL.down()) {
                getData().clearRecord();
                changeScene(U"Select");
            }
        }

        // �X�e�[�W�Z���N�g�֑J��
        else if (MouseL.down()) {
            getData().clearRecord();
            changeScene(U"Select");
        }
    }
}

// �`��֐� (const �C��)
void PuzzleScene::draw() const {
    String chapter[CHAPTER_NUM] = {
            U"�V���i�̂˂���",
            U"�����h���̂˂���",
            U"�`���}�̂˂���"
    };

    // �p�Y���V�[���`��
    manager.draw();

    SimpleGUI::Button(U"���ǂ�", Vec2(10, 10));

    if (pause == 1) {
        Rect(0, 0, Scene::Width(), Scene::Height()).draw(Color(150, 150, 150, 150));;

        TextureAsset(U"keyboard").scaled(0.4).drawAt(Scene::Center().x, 200);
        TextureAsset(U"mouse").scaled(0.5).drawAt(Scene::Center().x, 450);

        Point point_l = Point(Scene::Center().x - 200, 400);
        Point point_r = Point(Scene::Center().x + 200, 400);

        Rect rect_l = FontAsset(U"StoryFont")(U" �{�^�������� ").regionAt(point_l);
        Rect rect_r = FontAsset(U"StoryFont")(U" �����������ǂ� ").regionAt(point_r);

        Line(point_l, Point(Scene::Center().x - 20, 420)).draw(LineStyle::RoundDot, 2, Palette::Black);
        Line(point_r, Point(Scene::Center().x + 20, 420)).draw(LineStyle::RoundDot, 2, Palette::Black);

        rect_l.draw();
        rect_r.draw();

        FontAsset(U"StoryFont")(U" �{�^�������� ").drawAt(point_l, Palette::Black);
        FontAsset(U"StoryFont")(U" �����������ǂ� ").drawAt(point_r, Palette::Black);
    }

    SimpleGUI::Button(pause == 0 ? U"�w���v" : U"�Ƃ���", Vec2(Scene::Width() - 120, 10));

    // �N���A���̕`��
    if (puzzle_state != 0) {
        FontAsset(U"TitleFont")(U"�N���A�I").drawAt(Scene::Center().x + 4, Scene::Center().y + 4, Palette::Gray);
        FontAsset(U"TitleFont")(U"�N���A�I").drawAt(Scene::Center());

        if (getData().data[getData().diff_before - 1][getData().stage_before - 1] == 0 && (getData().total[getData().diff_before - 1] + 1) % 3 == 0) {
            FontAsset(U"StoryFont")(U"���͂Ȃ����ӂ�����I").drawAt(Scene::Center().x + 4, Scene::Center().y + 52, Palette::Gray);
            FontAsset(U"StoryFont")(U"���͂Ȃ����ӂ�����I").drawAt(Scene::Center().x, Scene::Center().y + 50);

            String story = U"�@" + chapter[getData().diff_before - 1] + U"�u" + getData().caption[getData().diff_before - 1][(getData().total[getData().diff_before - 1] + 1) / 3 - 1] + U"�v�@";

            FontAsset(U"StoryFont")(story).drawAt(Scene::Center().x, Scene::Center().y + 90).draw(Palette::White).drawFrame(1, Palette::Black);
            FontAsset(U"StoryFont")(story).drawAt(Scene::Center().x, Scene::Center().y + 90, Palette::Green);

           SimpleGUI::Button(U"���͂Ȃ����݂�", Vec2(Scene::Center().x - 150/2, Scene::Center().y + 150), 150);
        }
    }

}
