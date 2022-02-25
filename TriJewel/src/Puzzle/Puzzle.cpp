#include"Puzzle.h"

// �R���X�g���N�^1
PuzzleManager::PuzzleManager() {
	// �X�e�[�W�ǂݍ���
	readfile(U"./Data/Stage/{}/{:0>2}.txt"_fmt(1, 1));
	stage_init = Grid<int>(stage.getWidth(), stage.getHeight());

	door_flag = 0;
	box_num = 0;
	for (int i = 0; i < stage.getHeight(); i++) {
		for (int j = 0; j < stage.getWidth(); j++) {
			stage_init.setMap(stage.getMap(i, j), i, j);

			//	���̐��𐔂���
			if (stage.getMap(i, j) == PLACE) {
				box_num++;
			}
		}
	}

	// ���O�̏�����
	player_log.clear();
	player_log << player;

	stage_log.clear();
	stage_log << stage;

	// ����{�^��
	up = Rect(600, 300, 100, 100);
	right = Rect(700, 400, 100, 100);
	down = Rect(600, 500, 100, 100);
	left = Rect(500, 400, 100, 100);
}

// �R���X�g���N�^2
PuzzleManager::PuzzleManager(int diff, int stg) {
	// �X�e�[�W�ǂݍ���
	readfile(U"./Data/Stage/{}/{:0>2}.txt"_fmt(diff, stg));
	stage_init = Grid<int>(stage.getWidth(), stage.getHeight());

	door_flag = 0;
	box_num = 0;
	for (int i = 0; i < stage.getHeight(); i++) {
		for (int j = 0; j < stage.getWidth(); j++) {
			stage_init.setMap(stage.getMap(i, j), i, j);

			//	���̐��𐔂���
			if (stage.getMap(i, j) == PLACE) {
				box_num++;
			}
		}
	}

	// ���O�̏�����
	player_log.clear();
	player_log << player;

	stage_log.clear();
	stage_log << stage;

	// ����{�^��
	up = Rect(600, 300, 100, 100);
	right = Rect(700, 400, 100, 100);
	down = Rect(600, 500, 100, 100);
	left = Rect(500, 400, 100, 100);
}

int PuzzleManager::update() {
	//�v���C���[�ړ�
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

	// ����߂�
	if (MouseR.down() && player_log.size() > 1) {
		AudioAsset(U"se_step").playOneShot();

		player_log.pop_back();
		player = player_log.back();

		stage_log.pop_back();
		stage = stage_log.back();
	}

	//�����J����
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

	// �����𖞂����Ă��Ȃ����A����߂�
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

	// �N���A
	if (stage.getMap(player.getI(), player.getJ()) == GOAL) {
		return 1;
	}

	// �p�Y���̃��Z�b�g
	if (SimpleGUI::Button(U"���Ȃ���", Vec2(120, 10))) {
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
		// �摜�����������Â�����
		const ScopedColorMul2D state(ColorF(1, 0.8, 1, 1));

		// �w�i
		for (int i = 0; i * 30 - 10 < Scene::Height(); i++) {
			for (int j = 0; j * 30 - 10 < Scene::Width(); j++) {
				TextureAsset(U"road").draw(j * 30 - 10, i * 30 - 10);
			}
		}

		// �X�e�[�W
		stage.draw();
	}

	// �v���C���[
	player.draw();

	// ����{�^��
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

	SimpleGUI::Button(U"���Ȃ���", Vec2(120, 10));
}

// �t�@�C���ǂݍ���
void PuzzleManager::readfile(String file) {
	TextReader reader;
	String line;

	if (!reader.open(file)) {
		throw Error(U"Failed to open `" + file + U"`");
	}

	std::stringstream ss;

	// �X�e�[�W(���͗p)
	Grid<int> stage_input = Grid<int>(STAGE_SIZE, STAGE_SIZE);

	// �v���C���[���W(���͗p)
	int player_i = 0, player_j = 0;

	int i = 0;
	while (reader.readLine(line)) {
		ss << line;
		// �X�e�[�W�����͕�
		if (i < STAGE_SIZE) {
			for (int j = 0; j < STAGE_SIZE; j++) {
				ss >> stage_input[i][j];
			}
		}

		// �v���C���[���W���͕�
		else {
			ss >> player_i;
			ss >> player_j;
		}

		i++;
	}

	// �X�e�[�W��񏉊���
	stage = Stage(stage_input);

	// �v���C���[��񏉊���
	player = Player(player_i, player_j);

	reader.close();
}

// �����J�����̔���
bool PuzzleManager::checkdoor() {
	// �d�Ȃ��Ă��鐔
	int overlup_num = 0;

	// �����Ȃ��ꍇ
	if (box_num == 0) {
		return false;
	}

	// �J�E���g
	for (int i = 0; i < stage.getHeight(); i++) {
		for (int j = 0; j < stage.getWidth(); j++) {
			if (stage.isOverlup(i, j)) {
				overlup_num++;
			}
		}
	}

	// �S�Ă̔����z�u�ꏊ�ɏd�Ȃ��Ă��鎞�ɁA�����J����
	if (box_num == overlup_num) {
		return true;
	}
	else {
		return false;
	}
}

// ��A�����������̔���
bool PuzzleManager::objstack(char t, int n) {
	int data = -1;

	int player_i = player.getI();
	int player_j = player.getJ();

	// ������
	if (t == 'x') {
		if (n > 0) {
			data = stage.getMap(player_i, player_j + 2);
		}
		else {
			data = stage.getMap(player_i, player_j - 2);
		}
	}

	// �c����
	else if (t == 'y') {
		if (n > 0) {
			data = stage.getMap(player_i + 2, player_j);
		}
		else {
			data = stage.getMap(player_i - 2, player_j);
		}
	}

	// �ړ���ɕǂȂǂ��Ȃ���΁A������
	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}
	else {
		return false;
	}
}

// �v���C���[�������邩�̔���
bool PuzzleManager::playerstack(char t, int n) {
	int data = -1;

	int player_i = player.getI();
	int player_j = player.getJ();

	// ������
	if (t == 'x') {
		if (n > 0) {
			data = stage.getMap(player_i, player_j + 1);
		}
		else {
			data = stage.getMap(player_i, player_j - 1);
		}
	}

	// �c����
	else if (t == 'y') {
		if (n > 0) {
			data = stage.getMap(player_i + 1, player_j);
		}
		else {
			data = stage.getMap(player_i - 1, player_j);
		}
	}

	// ����ӊO�̏ꍇ�A�ړ����Ȃ�
	else
		return false;

	// �ړ���ɕǂȂǂ��Ȃ���΁A�ړ�����
	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}

	// �ړ���Ɋ�E��������΁A������
	else if (data == ROCK || data == BOX) {
		if (objstack(t, n)) {
			objmove(t, n);
			return true;
		}
		else {
			return false;
		}
	}

	// ����ӊO�̏ꍇ�A�ړ����Ȃ�
	return false;
}

// ��A���̈ړ�����
void PuzzleManager::objmove(char t, int n) {
	int player_i = player.getI();
	int player_j = player.getJ();

	if (objstack(t, n)) {
		// ������
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

		// �c����
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