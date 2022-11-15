#pragma once
// GameDefine info go here

#define Cloud_Platform_GameObjects 90000

#pragma region WindowInfo
#define WINDOW_CLASS_NAME		L"Game Window"
#define MAIN_WINDOW_TITLE		L"01 - Skeleton"
#define WINDOW_ICON_PATH		L"brick.ico"
#define BACKGROUND_COLOR		D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.0f)
#define SCREEN_WIDTH			320
#define SCREEN_HEIGHT			240
#pragma endregion

#pragma region GameFpsRate
#define MAX_FRAME_RATE			100
#pragma endregion

#pragma region DirectInput
#define KEYBOARD_BUFFER_SIZE	1024
#pragma endregion

#define GAME_OBJECT_STATE_DIE	-9999

#pragma region Mario
#define GROUND_Y 160.0f

#define Small_Mario_Height		16.0f
#define Big_Mario_Height		28.0f
#define Small_Mario_Width		16.0f


#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X		0.0005f
#define MARIO_ACCEL_RUN_X		0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY				0.002f
#define MARIO_JUMP_DEFLECT_SPEED	0.4f

#define MARIO_UNTOUCHABLE_TIME 2500

//states
#define SMALL_MARIO					100000
#define BIG_MARIO					110000
#define CAT_MARIO					120000

#define MARIO_STATE_IDLE			0000
#define MARIO_STATE_WALKING			1000
#define MARIO_STATE_RUNNING 		2000
#define MARIO_STATE_BRAKE			3000
#define MARIO_STATE_JUMP			4000
#define MARIO_STATE_Run_Jump		4200
#define MARIO_STATE_RELEASE_JUMP    4100
#define MARIO_STATE_SIT				5000
#define MARIO_STATE_SIT_RELEASE		5100
#pragma endregion

#pragma region Goomba
#define Goomba_Walking_Speed		0.05f
#define GOOMBA_DIE_TIMEOUT			500
#define GOOMBA_STATE_IDLE			20000

#pragma endregion
