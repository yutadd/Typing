#include "DxLib.h"
#include <vector>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int MovieGraphHandle;
    int FileHandle;
    char StringBuffer[1080];
    std::vector<char> vect;
    FileHandle = FileRead_open("lyrics.txt");
    if (DxLib_Init() == -1)    // �c�w���C�u��������������
    {
        return -1;    // �G���[������������I��
    }
    SetGraphMode(1920, 1080, 32);
    // ���[�r�[�t�@�C�������[�h���܂��B
    MovieGraphHandle = LoadGraph("C:\\Users\\student\\Downloads\\godzilla.mp4");

    // ���[�r�[���Đ���Ԃɂ��܂�
    PlayMovieToGraph(MovieGraphHandle);
    
    while (FileRead_eof(FileHandle) == 0)	// �t�@�C���̏I�[�ɓ��B����܂Ń��[�v
    {
        FileRead_gets(StringBuffer, sizeof(StringBuffer), FileHandle);
    }

    // ���[�v�AGetMovieStateToGraph �֐��̓��[�r�[�̍Đ���Ԃ𓾂�֐��ł�
    // �߂�l���P�̊Ԃ͍Đ���Ԃł��̂Ń��[�v�𑱂��܂�

    while (ProcessMessage() == 0 && GetMovieStateToGraph(MovieGraphHandle) == 1)
    {
        // ���[�r�[�f������ʂ����ς��ɕ`�悵�܂�
        DrawGraph(0,0, MovieGraphHandle, false);

        // �E�G�C�g�������܂��A���܂葬���`�悷��Ɖ�ʂ����������ł�
        WaitTimer(17);
    }

    // �ǂݍ��񂾃��[�r�[�t�@�C���̃O���t�B�b�N�n���h���̍폜
    DeleteGraph(MovieGraphHandle);

    DxLib_End();        // �c�w���C�u�����g�p�̏I������

    return 0;        // �\�t�g�̏I��
}