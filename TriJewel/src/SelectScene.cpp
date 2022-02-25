#include"GameScene.h"

// コンストラクタ（必ず実装）
SelectScene::SelectScene(const InitData& init) : IScene(init) {
    mode = getData().clear_flag == 1 ? 1 : 0;
    difficult = getData().diff_before;

    diff_str[0] = U"かんたん";
    diff_str[1] = U"ふつう";
    diff_str[2] = U"むずかしい";

    getData().clear_flag = 0;
    getData().previous_mode = PUZZLE_MODE;
}

// 更新関数
void SelectScene::update() {
    switch (mode) {
        // レベル選択
    case 0:
        // タイトルへ戻る
        if (SimpleGUI::Button(U"タイトル", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();
            changeScene(U"Title");
        }

        // どれかのレベルが選択されたら、ステージ選択へ移動する
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

        // ステージ選択
    case 1:
        // レベル選択へ戻る
        if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();
            mode = 0;
        }

        // パズル画面へ移動する
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

// 描画関数 (const 修飾)
void SelectScene::draw() const {
    TextureAsset(U"select").draw(0, 0);

    switch (mode) {
        // レベル選択
    case 0:
        // タイトルへ戻るボタン
        SimpleGUI::Button(U"タイトル", Vec2(10, 10));

        // 難易度ボタン
        for (int i = 0; i < DIFF_NUM; i++) {
            SimpleGUI::Button(diff_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150);
        }
        break;

        // ステージ選択
    case 1:
        // 戻るボタン
        SimpleGUI::Button(U"もどる", Vec2(10, 10));
        // ステージ番号
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

    FontAsset(U"TitleFont")(U"ステージセレクト").draw(184, 64, Palette::Gray);
    FontAsset(U"TitleFont")(U"ステージセレクト").draw(180, 60, Palette::Lightgreen);
}
