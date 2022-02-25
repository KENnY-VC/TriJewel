#include"GameScene.h"

// セーブデータ読み込み
void SaveData::readSave() {
    TextReader reader;
    String line;

    if (!reader.open(U"Data/Save/save.txt")) {
        throw Error(U"Failed to open save.txt");
    }

    std::stringstream ss;

    // ステージクリア状況
    for (int i = 0; i < DIFF_NUM; i++) {
        reader.readLine(line);
        ss << line;
        for (int j = 0; j < STAGE_NUM; j++) {
            ss >> data[i][j];
        }
    }

    reader.close();

    // クリアしたステージの合計(難易度別)
    for (int i = 0; i < DIFF_NUM; i++) {
        total[i] = 0;
        for (int j = 0; j < STAGE_NUM; j++) {
            total[i] += data[i][j];
        }
    }
}

// セーブデータ上書き
void SaveData::writeSave() {
    TextWriter writer;
    String line;

    if (!writer.open(U"Data/Save/save.txt")) {
        throw Error(U"Failed to open save.txt");
    }

    std::stringstream ss;

    // ステージクリア状況
    for (int i = 0; i < DIFF_NUM; i++) {
        for (int j = 0; j < STAGE_NUM; j++) {
            writer.write(U"{} "_fmt(data[i][j]));
        }
        writer.writeln(U"");
    }

    writer.close();
}

// クリアしたステージの合計(難易度別)
void SaveData::updateTotal() {
    for (int i = 0; i < DIFF_NUM; i++) {
        total[i] = 0;
        for (int j = 0; j < STAGE_NUM; j++) {
            total[i] += data[i][j];
        }
    }
}

// 物語データ読み込み
void SaveData::readCaption() {
    chap_str[0] = U"シロナのねがい";
    chap_str[1] = U"リンドルのねがい";
    chap_str[2] = U"チャマのねがい";
    chap_str[3] = U"おまけ";

    TextReader reader;

    for (int i = 0; i < CHAPTER_NUM; i++) {
        if (!reader.open(U"Data/Story/{}/caption.txt"_fmt(i + 1))) {
            throw Error(U"Failed to open caption.txt");
        }

        for (int j = 0; j < STORY_NUM; j++) {
            reader.readLine(caption[i][j]);
        }

        reader.close();
    }
}

// パズルクリア時の処理
void SaveData::clearRecord() {
    AudioAsset(U"bgm_clear").stop();
    AudioAsset(U"se_click").playOneShot();

    data[diff_before - 1][stage_before - 1] = 1;
    updateTotal();
    writeSave();

    clear_flag = 1;
}