#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include<Siv3D.hpp>
#include"Story/Story.h"
#include"Puzzle/Puzzle.h"

#define DIFF_NUM 3  // ��Փx��
#define STAGE_NUM 30    // �X�e�[�W��

#define CHAPTER_NUM 4   // �͂̐�
#define STORY_NUM 10    // ����̐�

#define STORY_MODE 0    // �X�g�[���[���[�h
#define PUZZLE_MODE 1   // �p�Y�����[�h

// �Z�[�u�f�[�^�y�ы��L�f�[�^
struct SaveData {
    int data[DIFF_NUM][STAGE_NUM];  // �X�e�[�W�̃N���A��
    int total[DIFF_NUM];    // �N���A�����X�e�[�W�̍��v(��Փx��)
    int clear_flag = 0;  // �N���A�t���O

    int diff_before = 0;    // ���O�ɑI�΂�Ă�����Փx
    int stage_before = 0;   // ���O�ɑI�΂�Ă����X�e�[�W

    int story_flag = 0; // �X�g�[���[�Đ��t���O
    int chapter_before = 0; // ���O�ɑI�΂�Ă�����
    int story_before = 0;   // ���O�ɑI�΂�Ă�������
    String chap_str[CHAPTER_NUM];   // �͂�\��������
    String caption[CHAPTER_NUM][STORY_NUM]; // �����\��������

    size_t index = 1;   // ��ʃT�C�Y�̔ԍ�
    int previous_mode;  // ���O�ɑI�΂�Ă����Q�[�����[�h

    void readSave();     // �Z�[�u�f�[�^�ǂݍ���
    void writeSave();   // �Z�[�u�f�[�^�㏑��
    void updateTotal(); // �N���A�����X�e�[�W�̍��v(��Փx��)
    void readCaption(); // ����f�[�^�ǂݍ���
    void clearRecord();   // �p�Y���N���A���̏���
};

using App = SceneManager<String, SaveData>;

// �^�C�g���V�[��
class TitleScene : public App::Scene
{
public:

    // �R���X�g���N�^�i�K�������j
    TitleScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �X�e�[�W�Z���N�g�V�[��
class SelectScene : public App::Scene
{
private:
    int mode;   // �V�[�������[�h�Ǘ�(���x���I�� <---> �X�e�[�W�I��)
    int difficult;  // ��Փx
    int stage;      // �X�e�[�W�ԍ�

    s3d::String diff_str[DIFF_NUM];   // ��Փx��\��������

    const int init_stage = 6;   // �ŏ�����J������Ă���X�e�[�W

public:

    // �R���X�g���N�^�i�K�������j
    SelectScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �p�Y���V�[��
class PuzzleScene : public App::Scene
{
private:
    PuzzleManager manager;  // �p�Y����ʊǗ�
    int puzzle_state;   // �p�Y���̃N���A��
    int pause;  // ���������ʕ\���t���O
    s3d::Audio bgm; // BGM

public:

    // �R���X�g���N�^�i�K�������j
    PuzzleScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �X�g�[���[�Z���N�g�V�[��
class StorySelectScene : public App::Scene
{
private:
    int mode;   // �V�[�������[�h�Ǘ�(�͑I�� <---> �b���I��)
    int chapter;    // �͔ԍ�
    int story;  // �b��

public:

    // �R���X�g���N�^�i�K�������j
    StorySelectScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �X�g�[���[�Đ��V�[��
class StoryScene : public App::Scene
{
private:
    StoryManager manager;   // �X�g�[���[��ʊǗ�

public:

    // �R���X�g���N�^�i�K�������j
    StoryScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// ���[�������V�[��
class RuleScene : public App::Scene
{
public:

    // �R���X�g���N�^�i�K�������j
    RuleScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �X�^�b�t�N���W�b�g�V�[��
class StaffScene : public App::Scene
{
private:
    Array<String> credit;   // �X�^�b�t�N���W�b�g(��s���i�[����)
    int scroll;   // �X�N���[���ʒu(y���W)

public:

    // �R���X�g���N�^�i�K�������j
    StaffScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �ݒ�V�[��
class ConfigScene : public App::Scene
{
public:

    // �R���X�g���N�^�i�K�������j
    ConfigScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �Z�[�u�f�[�^�폜�V�[��
class DeleteScene : public App::Scene
{
private:
    int mode;

public:

    // �R���X�g���N�^�i�K�������j
    DeleteScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

// �L�����N�^�[�Љ�V�[��
class CharacterScene : public App::Scene
{
private:
    int id;
    Array<Array<String>> text;
public:

    // �R���X�g���N�^�i�K�������j
    CharacterScene(const InitData& init);

    // �X�V�֐�
    void update() override;

    // �`��֐� (const �C��)
    void draw() const override;
};

#endif