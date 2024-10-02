#ifdef _WIN32
#ifdef NDEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#else
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#endif
#endif
#include "Game.h"
#include <Windows.h>  // Required for WinMain

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    auto game = std::make_unique<Game>();
//    game->Run();
//    return 0;
//}
//
// WinMain is for building the release mode.

int main()
{
    auto game = std::make_unique<Game>();
    game->Run();
    return 0;
}