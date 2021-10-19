#include "DxLib.h"
#include <vector>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int MovieGraphHandle;
    int FileHandle;
    char StringBuffer[1080];
    std::vector<char> vect;
    FileHandle = FileRead_open("lyrics.txt");
    if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
    {
        return -1;    // エラーが発生したら終了
    }
    SetGraphMode(1920, 1080, 32);
    // ムービーファイルをロードします。
    MovieGraphHandle = LoadGraph("C:\\Users\\student\\Downloads\\godzilla.mp4");

    // ムービーを再生状態にします
    PlayMovieToGraph(MovieGraphHandle);
    
    while (FileRead_eof(FileHandle) == 0)	// ファイルの終端に到達するまでループ
    {
        FileRead_gets(StringBuffer, sizeof(StringBuffer), FileHandle);
    }

    // ループ、GetMovieStateToGraph 関数はムービーの再生状態を得る関数です
    // 戻り値が１の間は再生状態ですのでループを続けます

    while (ProcessMessage() == 0 && GetMovieStateToGraph(MovieGraphHandle) == 1)
    {
        // ムービー映像を画面いっぱいに描画します
        DrawGraph(0,0, MovieGraphHandle, false);

        // ウエイトをかけます、あまり速く描画すると画面がちらつくからです
        WaitTimer(17);
    }

    // 読み込んだムービーファイルのグラフィックハンドルの削除
    DeleteGraph(MovieGraphHandle);

    DxLib_End();        // ＤＸライブラリ使用の終了処理

    return 0;        // ソフトの終了
}