#ifdef _WIN32
#ifdef NDEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#else
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#endif
#endif
#include "Game.h"
#ifdef _WIN32
#include <Windows.h>  // Required for WinMain
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char **argv)
#endif
{
    auto game = std::make_unique<Game>();
    game->Run();
    return 0;
}
