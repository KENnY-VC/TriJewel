#include"GameScene.h"

// コンストラクタ（必ず実装）
CharacterScene::CharacterScene(const InitData& init) : IScene(init) {
    id = 0;

    // CSV ファイルからデータを読み込む
    const CSVData csv(U"Data/character.csv");

    if (!csv) { // もし読み込みに失敗したら
        throw Error(U"Failed to load `character.csv`");
    }

    Array<String> str;
    for (int i = 0; i < csv.rows(); i++) {
        text << csv[i];
    }
}

// 更新関数
void CharacterScene::update() {
    // ストーリーセレクトへ戻る
    if (SimpleGUI::Button(U"もどる", Vec2(10, 10))) {
        AudioAsset(U"se_cancel").playOneShot();
        changeScene(U"StorySelect");
    }

    // キャラクター選択
    for (int i = 0; i < 6; i++) {
        Rect rect(Scene::Center().x + (70 * (i - 3)), 500, 50, 50);
        if (rect.mouseOver() && MouseL.down()) {
            if (id == i) break;
            AudioAsset(U"se_click").playOneShot();
            id = i;
        }
    }
}

// 描画関数 (const 修飾)
void CharacterScene::draw() const {
    // 背景
    TextureAsset(U"story").draw(0, 0);
    Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

    // 説明の背景
    Rect(100, 100, Scene::Width() - 200, Scene::Height() - 200).draw(ColorF(1, 1, 1, 0.75));

    // キャラクター説明
    TextureAsset(text[0][id + 1]) .drawAt(200, 200);
    for (int i = 0; i < 6; i++) {
        Rect(Scene::Center().x + (70 * (i - 3)), 500, 50, 50).draw(ColorF(1, 1, (id == i) ? 0 : 1));
        TextureAsset(U"SD" + text[0][i + 1]).draw(Scene::Center().x + (70 * (i - 3)), 500);
    }

    // 各種項目
    for (int i = 0; i < 7; i++) {
        FontAsset(U"SmallFont")(text[i][0]).draw(300, 110 + 25 * i, Palette::Black);
        FontAsset(U"SmallFont")(text[i][id + 1]).draw(400, 110 + 25 * i, Palette::Black);
    }

    // 説明
    Rect explain(150, 290, 220, 200);
    Rect magic(420, 290, 220, 200);

    explain.draw(ColorF(1, 1, 0, 0.75));
    magic.draw(ColorF(1, 1, 0, 0.75));
    FontAsset(U"SmallFont")(text[7][0] + U"\n\n" + text[7][id + 1]).draw(explain.stretched(-10), Palette::Black);
    FontAsset(U"SmallFont")(text[8][0] + U"\n\n" + text[8][id + 1]).draw(magic.stretched(-10), Palette::Black);

    SimpleGUI::Button(U"もどる", Vec2(10, 10));
}