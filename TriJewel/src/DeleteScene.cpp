#include"GameScene.h"

// コンストラクタ（必ず実装）
DeleteScene::DeleteScene(const InitData& init) : IScene(init) {
    mode = 0;
}

// 更新関数
void DeleteScene::update() {
    switch (mode) {
    case 0:
    case 1:
        if (SimpleGUI::Button(U"はい", Vec2(Scene::Width() / 2 - 50, Scene::Height() / 2), 100)) {

            // データを初期化
            if (mode == 1) {
                for (int i = 0; i < DIFF_NUM; i++) {
                    for (int j = 0; j < STAGE_NUM; j++) {
                        getData().data[i][j] = 0;
                    }
                }

                getData().updateTotal();
                getData().writeSave();
                AudioAsset(U"se_delete").playOneShot();
            }
            else {
                AudioAsset(U"se_click").playOneShot();
            }

            mode++;
        }

        if (SimpleGUI::Button(U"いいえ", Vec2(Scene::Width() / 2 - 50, Scene::Height() / 2 + 50), 100)) {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"Config");
        }

        break;

    case 2:
        if (MouseL.down()) {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"Title");
        }
        break;

    default:
        break;
    }
}

// 描画関数 (const 修飾)
void DeleteScene::draw() const {
    String text[3] = {
        U"セーブデータをけす？",
        U"ほんとうに？\n(けしたらもどりません！）",
        U"けしました"
    };

    FontAsset(U"TitleFont")(text[mode]).drawAt(Scene::Width() / 2, Scene::Height() / 2 - 100, Color(255, 150, 150));
    if (mode < 2) {
        {
            const ScopedColorMul2D state(ColorF(1, 0.5, 0.5, 1));
            SimpleGUI::Button(U"はい", Vec2(Scene::Width() / 2 - 50, Scene::Height() / 2), 100);
        }
        {
            const ScopedColorMul2D state(ColorF(0.5, 0.5, 1, 1));
            SimpleGUI::Button(U"いいえ", Vec2(Scene::Width() / 2 - 50, Scene::Height() / 2 + 50), 100);
        }
    }
}
