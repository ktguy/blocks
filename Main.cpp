#include "DxLib.h"

#define FIELD_WIDTH 14
#define FIELD_HEIGHT 14

enum {
	CONTROLE,
	PLAY1,
	PLAY2,
	MAX_PLAY
};

int player[MAX_PLAY*2];
int turn = 1;
int px = 1, py = 1;
int mino_change = 0;

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,-1,0,1 };
int naname_x[4] = { 1, 1, -1, -1 };
int naname_y[4] = { 1, -1, -1, 1 };


int FIELD[FIELD_HEIGHT][FIELD_WIDTH]
	= {
		{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
		{ 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}

	};

int FIELD_CAN_PUT[2][FIELD_HEIGHT][FIELD_WIDTH] //1絶対一つは置く場所,0おいても置かなくてもいい、-1絶対置けない
	= {
		{ //青
			{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
		},
		{ //赤
			{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
			{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
		}
	};

enum {
	MINO_TYPE_1,
	MINO_TYPE_2,
	MINO_TYPE_3I,
	MINO_TYPE_3L,
	MINO_TYPE_T,
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_I,
	MINO_TYPE_5L,
	MINO_TYPE_5T,
	MINO_TYPE_5W,
	MINO_TYPE_5X,
	MINO_TYPE_MAX
};
enum {
	MINO_ANGLE_0,
	MINO_ANGLE_90,
	MINO_ANGLE_180,
	MINO_ANGLE_270,
	MINO_ANGLE_MAX,
};

#define MINO_WIDTH 4
#define MINO_HEIGHT 4
char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] = {	
	//MINO_TYPE_1,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},	
	//MINO_TYPE_2,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_3I,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_3L,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_T,
		{
		//MINO_ANGLE_0,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},

		//MINO_ANGLE_90,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_O,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_S,
		{
		//MINO_ANGLE_0,
		{
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_Z,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_J,
		{
		//MINO_ANGLE_0,
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_L,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_I,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_5L,
		{
		//MINO_ANGLE_0,
		{
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_5T,
		{
		//MINO_ANGLE_0,
		{
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_5W,
		{
		//MINO_ANGLE_0,
		{
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
		},
	},
	//MINO_TYPE_5X,
		{
		//MINO_ANGLE_0,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_90,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_180,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
		//MINO_ANGLE_270,
		{
			{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 },
		},
	},
};


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	//画面設定
	{
		SetWindowText("Blocks duo mini");	// ウィンドウのタイトルを設定する
		ChangeWindowMode(TRUE);
		SetGraphMode(FIELD_WIDTH * 32 + 32*6, FIELD_HEIGHT * 32, 16);
	}

	//初期化
	{
		DxLib_Init();
		SetDrawScreen(DX_SCREEN_BACK);
	}

	//画像読み込み
	{
		LoadDivGraph("picture/player1.png", MAX_PLAY*2, MAX_PLAY, 2, 32, 32, player);

	}

	int angle = 0;//MINO_ANGLE_MAX
	while (!ProcessMessage()) {
		ClearDrawScreen();

		//キー操作
		{
			WaitKey();
			int kx = px, ky = py;
			if (CheckHitKey(KEY_INPUT_LEFT)) kx--;
			if (CheckHitKey(KEY_INPUT_RIGHT)) kx++;
			if (CheckHitKey(KEY_INPUT_UP)) ky--;
			if (CheckHitKey(KEY_INPUT_DOWN)) ky++;

			if (CheckHitKey(KEY_INPUT_B)) {
				mino_change = (mino_change + 1) % MINO_TYPE_MAX;
			}
			if (CheckHitKey(KEY_INPUT_V)) {
				angle--;
				if (angle < 0) angle = MINO_ANGLE_MAX - 1;
			}
			if (CheckHitKey(KEY_INPUT_N)) {
				angle++;
				if (angle >= MINO_ANGLE_MAX)  angle = 0;
			}

			//はみ出し判定
			{
				bool area_flag = true;
				for (int y = ky; y < ky + MINO_HEIGHT; y++) {
					for (int x = kx; x < kx + MINO_WIDTH; x++) {
						if (minoShapes[mino_change][angle][y - ky][x - kx] == 1 && FIELD[y][x] == -1) {
							area_flag = false;
						}
					}
				}
				if (area_flag) {
					px = kx, py = ky;
				}
			}


			if (CheckHitKey(KEY_INPUT_SPACE)) {				
				//置けるか置けないかのチェック1（何もない場所におく）
				bool put_flag = true;
				for (int y = py; y < py + MINO_HEIGHT; y++) {
					for (int x = px; x < px + MINO_WIDTH; x++) {
						if (minoShapes[mino_change][angle][y - py][x - px]) {
							if (FIELD[y][x] != 0) put_flag = false;
						}
					}
				}
				if (!put_flag) continue;

				//置けるか置けないかのチェック2 (斜めに触れてるか、隣接してないか)
				//FIELD_CAN_PUT配列は …(1：絶対一つは置く場所, 0：おいても置かなくてもいい、-1：絶対置けない)
				bool flag1 = false; //ななめスタート判定
				bool flag2 = true;  //隣接判定
				for (int y = py; y < py + MINO_HEIGHT; y++) {
					for (int x = px; x < px + MINO_WIDTH; x++) {
						if (minoShapes[mino_change][angle][y - py][x - px]) {
							if(FIELD_CAN_PUT[turn-1][y][x]==1) {
								flag1 = true;
								continue;
							}
							if(FIELD_CAN_PUT[turn-1][y][x] == -1) flag2 = false;
						}
					}
				}
				
				//もしおけるなら
				if (flag1 && flag2) {
					for (int y = py; y < py + MINO_HEIGHT; y++) {
						for (int x = px; x < px + MINO_WIDTH; x++) {
							if (minoShapes[mino_change][angle][y - py][x - px]) {
								for (int d = 0; d < 4; d++) {
									if(FIELD_CAN_PUT[turn - 1][y + naname_y[d]][x + naname_x[d]]==0){
										FIELD_CAN_PUT[turn - 1][y + naname_y[d]][x + naname_x[d]] = 1;
									}
								}
								for (int d = 0; d < 4; d++) {
									FIELD_CAN_PUT[turn - 1][y + dy[d]][x + dx[d]] = -1;
								}
								FIELD_CAN_PUT[turn - 1][y][x] = -1;
							}
						}
					}
				}
				else {
					continue;
				}

				//ブロック配置
				for (int y = py; y < py + MINO_HEIGHT; y++) {
					for (int x = px; x < px + MINO_WIDTH; x++) {
						if (minoShapes[mino_change][angle][y - py][x - px]) {
							FIELD[y][x] = turn;
						}
					}
				}
				turn = turn % (MAX_PLAY - 1);
				turn++;
			}
		}



		//画面表示
		{
			//全体表示
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				for (int x = 0; x < FIELD_WIDTH; x++) {
					if (FIELD[y][x] == -1) {
						DrawGraph(x * 32, y * 32, player[MAX_PLAY], FALSE);
					}
					if (FIELD[y][x] == 1) {
						DrawGraph(x * 32, y * 32, player[1], FALSE);
					}
					else if(FIELD[y][x] == 2) {
						DrawGraph(x * 32, y * 32, player[2], FALSE);
					}
				}
			}
			//キー操作部分の表示
			for (int y = py; y < py + MINO_HEIGHT; y++) {
				for (int x = px; x < px + MINO_WIDTH; x++) {
					if (minoShapes[mino_change][angle][y - py][x - px]) {
						DrawGraph(x * 32, y * 32, player[0], FALSE);
					}
				}
			}
		}
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}