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

#pragma region Mario
#define GROUND_Y 160.0f

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f
//states
#define MARIO_STATE_IDLE			10000
#define MARIO_STATE_WALKING			11000
#define MARIO_STATE_RUNNING 		12000
#define MARIO_STATE_JUMP			13000
#define MARIO_STATE_RELEASE_JUMP    14000
#define MARIO_STATE_SIT				15000
#define MARIO_STATE_SIT_RELEASE		16000

#pragma endregion

