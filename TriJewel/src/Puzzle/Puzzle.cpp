#include"Puzzle.h"

// コンストラクタ1
PuzzleManager::PuzzleManager() {
	// ステージ読み込み
	readfile(U"./Data/Stage/{}/{:0>2}.txt"_fmt(1, 1));
	stage_init = Grid<int>(stage.getWidth(), stage.getHeight());

	door_flag = 0;
	box_num = 0;
	for (int i = 0; i < stage.getHeight(); i++) {
		for (int j = 0; j < stage.getWidth(); j++) {
			stage_init.setMap(stage.getMap(i, j), i, j);

			//	箱の数を数える
			if (stage.getMap(i, j) == PLACE) {
				box_num++;
			}
		}
	}

	// ログの初期化
	player_log.clear();
	player_log << player;

	stage_log.clear();
	stage_log << stage;

	// 操作ボタン
	up = Rect(600, 300, 100, 100);
	right = Rect(700, 400, 100, 100);
	down = Rect(600, 500, 100, 100);
	left = Rect(500, 400, 100, 100);
}

// コンストラクタ2
PuzzleManager::PuzzleManager(int diff, int stg) {
	// ステージ読み込み
	readfile(U"./Data/Stage/{}/{:0>2}.txt"_fmt(diff, stg));
	stage_init = Grid<int>(stage.getWidth(), stage.getHeight());

	door_flag = 0;
	box_num = 0;
	for (int i = 0; i < stage.getHeight(); i++) {
		for (int j = 0; j < stage.getWidth(); j++) {
			stage_init.setMap(stage.getMap(i, j), i, j);

			//	箱の数を数える
			if (stage.getMap(i, j) == PLACE) {
				box_num++;
			}
		}
	}

	// ログの初期化
	player_log.clear();
	player_log << player;

	stage_log.clear();
	stage_log << stage;

	// 操作ボタン
	up = Rect(600, 300, 100, 100);
	right = Rect(700, 400, 100, 100);
	down = Rect(600, 500, 100, 100);
	left = Rect(500, 400, 100, 100);
}

int PuzzleManager::update() {
	//プレイヤー移動
	if ((left.intersects(Cursor::Pos()) && MouseL.down()) || KeyLeft.down() || KeyA.down()) {
		AudioAsset(U"se_step").playOneShot();

		player.setDirection(LEFT);

		if (playerstack('x', -1)) {
			player.update(LEFT);
		}

		player_log << player;
		stage_log << stage;
	}
	if ((right.intersects(Cursor::Pos()) && MouseL.down()) || KeyRight.down() || KeyD.down()) {
		AudioAsset(U"se_step").playOneShot();

		player.setDirection(RIGHT);

		if (playerstack('x', 1)) {
			player.update(RIGHT);
		}

		player_log << player;
		stage_log << stage;
	}
	if ((up.intersects(Cursor::Pos()) && MouseL.down()) || KeyUp.down() || KeyW.down()) {
		AudioAsset(U"se_step").playOneShot();

		player.setDirection(UP);

		if (playerstack('y', -1)) {
			player.update(UP);
		}

		player_log << player;
		stage_log << stage;
	}
	if ((down.intersects(Cursor::Pos()) && MouseL.down()) || KeyDown.down() || KeyS.down()) {
		AudioAsset(U"se_step").playOneShot();

		player.setDirection(DOWN);

		if (playerstack('y', 1)) {
			player.update(DOWN);
		}

		player_log << player;
		stage_log << stage;
	}

	// 一歩戻る
	if (MouseR.down() && player_log.size() > 1) {
		AudioAsset(U"se_step").playOneShot();

		player_log.pop_back();
		player = player_log.back();

		stage_log.pop_back();
		stage = stage_log.back();
	}

	//扉を開ける
	if (checkdoor()) {
		if (door_flag == 0) {
			door_flag = 1;
			AudioAsset(U"se_unlock").playOneShot();
		}

		for (int i = 0; i < stage.getHeight(); i++) {
			for (int j = 0; j < stage.getWidth(); j++) {
				if (stage.getMap(i,j) == DOOR) {
					stage.setMap(ROAD, i, j);
				}
			}
		}
	}

	// 条件を満たしていない時、扉を閉める
	else {
		if (door_flag == 1) {
			door_flag = 0;
		}

		for (int i = 0; i < stage.getHeight(); i++) {
			for (int j = 0; j < stage.getWidth(); j++) {
				if (stage.getMap(i, j) == ROAD && stage.getBaseMap(i, j) == DOOR) {
					stage.setMap(DOOR, i, j);
				}
			}
		}
	}

	// クリア
	if (stage.getMap(player.getI(), player.getJ()) == GOAL) {
		return 1;
	}

	// パズルのリセット
	if (SimpleGUI::Button(U"やりなおし", Vec2(120, 10))) {
		AudioAsset(U"se_cancel").playOneShot();

		player = player_log[0];
		player_log.clear();
		player_log << player;

		stage = stage_log[0];
		stage_log.clear();
		stage_log << stage;

		for (int i = 0; i < stage.getHeight(); i++) {
			for (int j = 0; j < stage.getWidth(); j++) {
				stage.setMap(stage_init.getMap(i, j), i, j);
			}
		}
	}

	return 0;
}

void PuzzleManager::draw() const {
	{
		// 画像を少しだけ暗くする
		const ScopedColorMul2D state(ColorF(1, 0.8, 1, 1));

		// 背景
		for (int i = 0; i * 30 - 10 < Scene::Height(); i++) {
			for (int j = 0; j * 30 - 10 < Scene::Width(); j++) {
				TextureAsset(U"road").draw(j * 30 - 10, i * 30 - 10);
			}
		}

		// ステージ
		stage.draw();
	}

	// プレイヤー
	player.draw();

	// 操作ボタン
	TextureAsset(U"button").rotated(0).draw(up.x, up.y);
	TextureAsset(U"button").rotated(90_deg).draw(right.x, right.y);
	TextureAsset(U"button").rotated(90_deg * 2).draw(down.x, down.y);
	TextureAsset(U"button").rotated(90_deg * 3).draw(left.x, left.y);

	if (up.intersects(Cursor::Pos())) {
		up.draw(ColorF(1.0, 1.0, 0, 0.5));
	}
	if (right.intersects(Cursor::Pos())) {
		right.draw(ColorF(1.0, 1.0, 0, 0.5));
	}
	if (down.intersects(Cursor::Pos())) {
		down.draw(ColorF(1.0, 1.0, 0, 0.5));
	}
	if (left.intersects(Cursor::Pos())) {
		left.draw(ColorF(1.0, 1.0, 0, 0.5));
	}

	SimpleGUI::Button(U"やりなおし", Vec2(120, 10));
}

// ファイル読み込み
void PuzzleManager::readfile(String file) {
	TextReader reader;
	String line;

	if (!reader.open(file)) {
		throw Error(U"Failed to open `" + file + U"`");
	}

	std::stringstream ss;

	// ステージ(入力用)
	Grid<int> stage_input = Grid<int>(STAGE_SIZE, STAGE_SIZE);

	// プレイヤー座標(入力用)
	int player_i = 0, player_j = 0;

	int i = 0;
	while (reader.readLine(line)) {
		ss << line;
		// ステージ情報入力部
		if (i < STAGE_SIZE) {
			for (int j = 0; j < STAGE_SIZE; j++) {
				ss >> stage_input[i][j];
			}
		}

		// プレイヤー座標入力部
		else {
			ss >> player_i;
			ss >> player_j;
		}

		i++;
	}

	// ステージ情報初期化
	stage = Stage(stage_input);

	// プレイヤー情報初期化
	player = Player(player_i, player_j);

	reader.close();
}

// 扉が開くかの判定
bool PuzzleManager::checkdoor() {
	// 重なっている数
	int overlup_num = 0;

	// 箱がない場合
	if (box_num == 0) {
		return false;
	}

	// カウント
	for (int i = 0; i < stage.getHeight(); i++) {
		for (int j = 0; j < stage.getWidth(); j++) {
			if (stage.isOverlup(i, j)) {
				overlup_num++;
			}
		}
	}

	// 全ての箱が配置場所に重なっている時に、扉を開ける
	if (box_num == overlup_num) {
		return true;
	}
	else {
		return false;
	}
}

// 岩、箱が動くかの判定
bool PuzzleManager::objstack(char t, int n) {
	int data = -1;

	int player_i = player.getI();
	int player_j = player.getJ();

	// 横方向
	if (t == 'x') {
		if (n > 0) {
			data = stage.getMap(player_i, player_j + 2);
		}
		else {
			data = stage.getMap(player_i, player_j - 2);
		}
	}

	// 縦方向
	else if (t == 'y') {
		if (n > 0) {
			data = stage.getMap(player_i + 2, player_j);
		}
		else {
			data = stage.getMap(player_i - 2, player_j);
		}
	}

	// 移動先に壁などがなければ、動かす
	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}
	else {
		return false;
	}
}

// プレイヤーが動けるかの判定
bool PuzzleManager::playerstack(char t, int n) {
	int data = -1;

	int player_i = player.getI();
	int player_j = player.getJ();

	// 横方向
	if (t == 'x') {
		if (n > 0) {
			data = stage.getMap(player_i, player_j + 1);
		}
		else {
			data = stage.getMap(player_i, player_j - 1);
		}
	}

	// 縦方向
	else if (t == 'y') {
		if (n > 0) {
			data = stage.getMap(player_i + 1, player_j);
		}
		else {
			data = stage.getMap(player_i - 1, player_j);
		}
	}

	// それ意外の場合、移動しない
	else
		return false;

	// 移動先に壁などがなければ、移動する
	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}

	// 移動先に岩・箱があれば、動かす
	else if (data == ROCK || data == BOX) {
		if (objstack(t, n)) {
			objmove(t, n);
			return true;
		}
		else {
			return false;
		}
	}

	// それ意外の場合、移動しない
	return false;
}

// 岩、箱の移動処理
void PuzzleManager::objmove(char t, int n) {
	int player_i = player.getI();
	int player_j = player.getJ();

	if (objstack(t, n)) {
		// 横方向
		if (t == 'x') {
			if (n > 0) {
				stage.setMap(stage.getMap(player_i, player_j + 1), player_i, player_j + 2);
				stage.setMap(stage.getBaseMap(player_i, player_j + 1), player_i, player_j + 1);
			}
			else {
				stage.setMap(stage.getMap(player_i, player_j - 1), player_i, player_j - 2);
				stage.setMap(stage.getBaseMap(player_i, player_j - 1), player_i, player_j - 1);
			}
		}

		// 縦方向
		else if (t == 'y') {
			if (n > 0) {
				stage.setMap(stage.getMap(player_i + 1, player_j), player_i + 2, player_j);
				stage.setMap(stage.getBaseMap(player_i + 1, player_j), player_i + 1, player_j);
			}
			else {
				stage.setMap(stage.getMap(player_i - 1, player_j), player_i - 2, player_j);
				stage.setMap(stage.getBaseMap(player_i - 1, player_j), player_i - 1, player_j);
			}
		}
	}
}