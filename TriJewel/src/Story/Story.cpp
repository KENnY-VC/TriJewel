#include"Story.h"

// �R���X�g���N�^1
StoryManager::StoryManager() {
	scene = 0;
	start = Scene::Time() * 1000;
	length = (int)((Scene::Time() * 1000 - start) / 50);
	playing = 0;
}

// �R���X�g���N�^2
StoryManager::StoryManager(int chapter, int story) : StoryManager() {
	// �t�@�C���ǂݍ��ݗp�ϐ�
	TextReader reader(U"Data/Story/{}/{}.txt"_fmt(chapter, story));
	String line;

	// �ǂݍ��݃f�[�^
	int left, right;
	String text;
	int speaker;

	// �t�@�C�����ǂݍ��߂Ȃ������ꍇ�A�G���[���b�Z�[�W��\��������
	if (!reader) {
		throw Error(U"Failed to open story file");
	}

	dialogue.clear();

	// �t�@�C���ǂݍ���
	while (1) {
		Dialogue d;

		reader.readLine(line);
		d.left = Parse<int>(line);

		reader.readLine(line);
		d.right = Parse<int>(line);

		reader.readLine(d.text);

		reader.readLine(line);
		d.speaker = Parse<int>(line);

		reader.readLine(line);
		d.bgm = Parse<int>(line);

		dialogue.push_back(d);

		if (!reader.readLine(line)) break;
	}

	reader.close();
}

// �X�V
int StoryManager::update() {
	s3d::Audio bgm[2] = {
		AudioAsset(U"bgm_story1"),
		AudioAsset(U"bgm_story2")
	};

	// BGM�Đ�
	if (scene == 0) {
		if (!bgm[dialogue[scene].bgm].isPlaying()) {
			bgm[dialogue[scene].bgm].setLoop(true);
			bgm[dialogue[scene].bgm].play();
		}
	}

	// BGM�ύX
	else if (dialogue[scene].bgm != dialogue[scene - 1].bgm) {
		if (!bgm[dialogue[scene].bgm].isPlaying()) {
			bgm[dialogue[scene - 1].bgm].stop();
			bgm[dialogue[scene].bgm].setLoop(true);
			bgm[dialogue[scene].bgm].play();
		}
	}

	// �N���b�N�ŉ�b��i�߂�
	if (MouseL.down()) {
		AudioAsset(U"se_select").playOneShot();

		// ���̉�b�ֈڂ�
		if (playing == 1) {

			// �Ō�̃Z���t�ɓ��B�����ꍇ�́A�I������
			if (scene == dialogue.size() - 1) {
				bgm[dialogue[scene].bgm].stop();
				return 1;
			}

			scene++;
			start = Scene::Time() * 1000;
			playing = 0;
			length = (int)((Scene::Time() * 1000 - start) / 50);
		}

		// ��b���\���r���̏ꍇ�A�S���\��������
		else {
			length = dialogue[scene].text.length();
		}
	}

	// ��b���\���r�����ǂ�������
	if (length >= dialogue[scene].text.length()) {
		playing = 1;
	}

	// ��b�̕\������
	if (playing == 0) {
		length = (int)((Scene::Time() * 1000 - start) / 50);
	}
	return 0;
}

// �`��
void StoryManager::draw() const {
	const int namebox_size = 65;
	const int chara_size = 128 * 1.5;
	const String name[6] = {
		U"�V���i",
		U"�����h��",
		U"�`���}",
		U"�t�@�C",
		U"�G��",
		U"�����r�B"
	};

	// ���̃L����
	if (dialogue[scene].left >= 0) {
		bool isRindol = dialogue[scene].left == 1;
		if (dialogue[scene].speaker != 1) {
			const ScopedColorMul2D state(ColorF(0.6, 0.6, 0.6));
			TextureAsset(name[dialogue[scene].left]).scaled(1.5).mirrored(isRindol).drawAt(Scene::Width() / 16 + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
		else {
			TextureAsset(name[dialogue[scene].left]).scaled(1.5).mirrored(isRindol).drawAt(Scene::Width() / 16 + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
	}

	// �E�̃L����
	if (dialogue[scene].right >= 0) {
		if (dialogue[scene].speaker != 2) {
			const ScopedColorMul2D state(ColorF(0.6, 0.6, 0.6));
			TextureAsset(name[dialogue[scene].right]).scaled(1.5).drawAt(Scene::Width() / 16 * 15 - chara_size + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
		else {
			TextureAsset(name[dialogue[scene].right]).scaled(1.5).drawAt(Scene::Width() / 16 * 15 - chara_size + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
	}

	// �L������
	if (dialogue[scene].speaker != 0) {
		Rect namebox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12 - namebox_size, 150, namebox_size).draw(Palette::White).drawFrame(1, 0, Palette::Black);
		FontAsset(U"StoryFont")(name[dialogue[scene].speaker == 1 ? dialogue[scene].left : dialogue[scene].right]).draw(namebox.stretched(-10), Palette::Black);
	}

	Rect textbox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12, (Scene::Width() / 16) * 14, (Scene::Height() / 16) * 3).draw(Palette::White).drawFrame(1, 0, Palette::Black);
	FontAsset(U"StoryFont")(dialogue[scene].text.substr(0, length)).draw(textbox.stretched(-10), Palette::Black);

	if (playing == 1)
		TextureAsset(U"next").draw((Scene::Width() / 16) * 14, (Scene::Height() / 16) * 14);
}