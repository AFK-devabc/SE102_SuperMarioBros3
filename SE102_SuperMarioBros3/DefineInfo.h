#pragma once
// GameDefine info go here
#pragma region WindowInfo
#define WINDOW_CLASS_NAME		L"Game Window"
#define MAIN_WINDOW_TITLE		L"01 - Skeleton"
#define WINDOW_ICON_PATH		L"brick.ico"
#define SCREEN_WIDTH			320
#define SCREEN_HEIGHT			275
#define GAMEPLAY_SCREEN_WIDTH	305
#define GAMEPLAY_SCREEN_HEIGHT	202
#pragma endregion

#pragma region GameFpsRate
#define MAX_FRAME_RATE			50
#pragma endregion

#pragma region DirectInput
#define KEYBOARD_BUFFER_SIZE	1024
#pragma endregion

#define GAME_OBJECT_STATE_DIE	-9999
#define GAME_OBJECT_STATE_HITTED	-8888
#define BLOCK_PUSH_FACTOR 0.4f
#define GRAVITY				0.0008f


#pragma region Mario

#define Small_Mario_Height		14.0f
#define Big_Mario_Height		28.0f
#define Small_Mario_Width		14.0f

#define MARIO_TAIL_WIDTH		12
#define MARIO_TAIL_HEIGHT		6

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X		0.0001f
#define MARIO_ACCEL_RUN_X		0.00005f

#define MARIO_JUMP_SPEED_Y			0.4f
#define MARIO_FLY_DROPDOWN_SPEED	0.1f
#define MARIO_JUMP_RUN_SPEED_Y		0.9f

#define MARIO_GRAVITY				0.001f
#define MARIO_JUMP_DEFLECT_SPEED	0.2f
#define MARIO_FLYING_DROPDOWN_SPEED	0.08f
#define MARIO_SIT_HEIGHT_ADJUST ((Big_Mario_Height-Small_Mario_Height)/2)


#define MARIO_UNTOUCHABLE_TIME		2000
#define MARIO_FLYUP_TIME			5000

#define MARIO_DAMATE_TIME_START		100
#define MARIO_FLYING_TIME			400

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
#define MARIO_STATE_FLYING_DROPDOWN 6000
#define MARIO_STATE_IDLE_HOLDING	8000
#define MARIO_STATE_WALKING_HOLDING	9000

#pragma endregion

#pragma region Goomba
#define Goomba_Walking_Speed		0.02f
#define GOOMBA_JUMP_DEFLECT_SPEED	0.2f
#define GOOMBA_WIDTH				16
#define GOOMBA_HEIGHT				16
#define GOOMBA_DIE_TIMEOUT			1000
#define GOOMBA_STATE_WALKING		20000
#define GOOMBA_STATE_WING			22000
#define GOOMBA_STATE_DYING			21000
#define PLANT_BULLET_SIZE			8.0f
#define GOOMBA_JUMP_DELAY			2000

#pragma endregion

#pragma region Plant
#define PLANT_WIDTH					16
#define PLANT_HEIGHT				22
#define PLANT_SPEED					0.05f
#define BULLET_SPEED_X				0.1f
#define BULLET_SPEED_Y				0.05f
#define PLANT_DELAY_TIME			2000

#define PLANT_STATE_IDLE			40000
#define PLANT_STATE_LOOKINGTOP		41000
#define PLANT_STATE_LOOKINGBOT		42000
#define PLANT_STATE_BITE			43000
#define GREEN_PIPE					44000

#pragma endregion

#pragma region Brick
#define BRICK_DEFLECT_SPEED			0.2f
#define BRICK_WIDTH					16
#define BRICK_HEIGHT				16
#pragma endregion

#pragma region MISC

#define MUSHROOM_STATE_INSIDE		10021
#define MUSHROOM_STATE_OUTSIDE		10022
#define REDLEAF_STATE_DROPPING		10041
#define REDLEAF_STATE_IDLE			10040
#define PLANT_BULLET				10070
#pragma endregion

#pragma region Koopa
#define KOOPA_NORMAL_WIDTH			26
#define KOOPA_NORMAL_HEIGHT			26
#define KOOPA_SHEILD_WIDTH			16
#define KOOPA_SHEILD_HEIGHT			14

#define KOOPA_WALKING_SPEED			0.05f
#define KOOPA_JUMP_DEFLECT_SPEED	0.2f
#define KOOPA_ROLLING_SPEED			0.1f

#define KOOPA_STATE_WALKING			30000
#define KOOPA_STATE_ROLLING			31000
#define KOOPA_STATE_INSIDE_SHELL	32000
#define KOOPA_STATE_ESCAPE_SHELL	33000
#define KOOPA_STATE_WING			34000
#define KOOPA_STATE_HOLDED			35000

#pragma endregion

#pragma region GAME_VFX
#define BRICK_BROKEN 9900
#define HARD_COLLISION 9901
#define COIN_DROP		9902
#pragma endregion