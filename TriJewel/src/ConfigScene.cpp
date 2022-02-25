#include"GameScene.h"

// コンストラクタ（必ず実装）
ConfigScene::ConfigScene(const InitData& init) : IScene(init) {

}

// 更新関数
void ConfigScene::update() {
    constexpr std::array<Size, 3> resolutions = {
        Size(640, 480), Size(800, 600), Size(1024, 768)
    };

    // タイトルへ戻る
    if (SimpleGUI::Button(U"タイトル", Vec2(10, 10))) {
        AudioAsset(U"se_cancel").playOneShot();
        changeScene(U"Title");
    }

    // ウィンドウサイズを変更
    if (SimpleGUI::RadioButtons(getData().index, { U"640x480", U"800x600", U"1024x768", U"フルスクリーン" }, Vec2(Scene::Center().x - 75, 150))) {
        AudioAsset(U"se_click").playOneShot();

        if (getData().index == 3) {
            Window::Maximize();
        }
        else {
            Window::Resize(resolutions[getData().index], WindowResizeOption::KeepSceneSize);
        }
    }

    // セーブデータ削除
    if (SimpleGUI::Button(U"データをけす", Vec2(Scene::Center().x - 75, 400))) {
        AudioAsset(U"se_click").playOneShot();
        changeScene(U"Delete");
    }
}

// 描画関数 (const 修飾)
void ConfigScene::draw() const {
    TextureAsset(U"title").draw(0, 0);

    // タイトルへ戻るボタン
    SimpleGUI::Button(U"タイトル", Vec2(10, 10));

    // ウィンドウサイズ
    SimpleGUI::RadioButtons(getData().index, { U"640x480", U"800x600", U"1024x768", U"フルスクリーン"}, Vec2(Scene::Center().x - 75, 150));

    // セーブデータ削除ボタン
    {
        const ScopedColorMul2D state(ColorF(1, 0.5, 0.5, 1));
        SimpleGUI::Button(U"データをけす", Vec2(Scene::Center().x - 75, 400));
    }

    FontAsset(U"TitleFont")(U"せってい").drawAt(Scene::Center().x, 104, Palette::Gray);
    FontAsset(U"TitleFont")(U"せってい").drawAt(Scene::Center().x, 100);
}
