#pragma once
// GameDefine info go here
#pragma region WindowInfo
#define WINDOW_CLASS_NAME L"Game Window"
#define MAIN_WINDOW_TITLE L"01 - Skeleton"
#define WINDOW_ICON_PATH L"brick.ico"
#define BACKGROUND_COLOR D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#pragma endregion

#pragma region GameFpsRate
#define MAX_FRAME_RATE 100
#pragma endregion

#pragma region DirectInput
#define KEYBOARD_BUFFER_SIZE 1024
#pragma endregion




#define TEXTURE_PATH_BRICK L"brick.png"

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"


#define ID_TEX_MARIO "0"
#define ID_TEX_ENEMY "10"
#define ID_TEX_MISC "20"




#define MARIO_START_X 10.0f
#define MARIO_START_Y 100.0f
#define MARIO_START_VX 0.1f
#define MARIO_START_VY 0.1f


#define BRICK_X 10.0f
#define BRICK_Y 120.0f
