#include"GameScene.h"

// コンストラクタ（必ず実装）
StaffScene::StaffScene(const InitData& init) : IScene(init) {
    scroll = Scene::Height() / 2 + 200;

    TextReader reader;
    String line;

    if (!reader.open(U"Data/staff.txt")) {
        throw Error(U"Failed to open staff.txt");
    }

    // スタッフクレジット情報の読み込み
    while (reader.readLine(line)) {
        // 空行は大きなスペース
        if (line.isEmpty()) {
            for (int i = 0; i < 3; i++) {
                credit << U"";
            }
        }

        // 一行ずつ読み込む
        else {
            credit << line;
        }
    }

    reader.close();

    AudioAsset(U"bgm_ed").play();
}

// 更新関数
void StaffScene::update() {
    scroll -= 1;

    // ストーリー選択画面へ戻る
    if (MouseR.down() || !AudioAsset(U"bgm_ed").isPlaying())
    {
        AudioAsset(U"bgm_ed").stop();
        changeScene(U"StorySelect");
    }
}

// 描画関数 (const 修飾)
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
