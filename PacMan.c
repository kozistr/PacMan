#include "PacMan.h"

/***************************
- Player's Info
-> xPos  : Current x Position
-> yPos  : Currnet y Position
-> OxPos : Old x Position
-> OyPos : Old y Position
-> stime : Remain Super Time
****************************/
typedef struct _Player {
	int xPos, yPos;
	int OxPos, OyPos;
	int super;
	clock_t stime;
} Player;

/************************************
- Enmey's Info
-> xPos    : Current x Position
-> yPos    : Currnet y Position
-> OxPos   : Old x Position
-> OyPos   : Old y Position
-> nDirect : which way enemy goes on
-> stright : Is on stright?
*************************************/
typedef struct _Enemy {
	int xPos, yPos;
	int OxPos, OyPos;
	int nDirect, stright;
} Enemy;

/***********************************************************
- Map's Info
-> nStage  : Total 3 stage ( 1, 2 , 3)
-> nEnemy  : How many enmeys are there? ( Depends on level )
-> nSocre  : Total Score
-> nReplay : Replay this Stage ?
-> pPos    : Player Structure
-> ePos    : Enemy Structure
*************************************************************/
typedef struct _MapInfo {
	int eFlag;
	int nStage;
	int nEnemy;
	int nScore;
	int nReplay;
	Player pPos;
	Enemy ePos;
} MapInfo;

FMOD_SYSTEM *g_System;
FMOD_SOUND *g_Sound[6];
FMOD_CHANNEL *g_Channel[6];

Enemy *E;
MapInfo map;

/*******************************
- StateScreen
: Print Current Player's Stated
- level
- score
********************************/
void StateScreen() {
	SetColor(14, 0);
	gotoxy(52, 0); printf("Stage %d", map.nStage + 1);
	gotoxy(52, 1); printf("score : %d", map.nScore);
}

void InitScreen() {
	SetColor(9, 0);
	Putxy(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━┓");
	Putxy(0, 1, "┃■■■■■■■■■■■■■■■■■■■■■■┃");
	Putxy(0, 2, "┃■                                        ■┃");
	Putxy(0, 3, "┃■                                        ■┃");
	Putxy(0, 4, "┃■       ◎  ■■■■■          ◎       ■┃");

	SetColor(14, 0);
	Putxy(0, 5, "┃■      ♥  ■■            ♥            ■┃");
	Putxy(0, 6, "┃■         ■   ┏━━━━━━━━┓      ■┃");
	Putxy(0, 7, "┃■    ■■■    ┃★ Pac Man    ★┃      ■┃");
	Putxy(0, 8, "┃■              ┗━━━━━┳━━┛      ■┃");
	Putxy(0, 9, "┃■     ◎             /)/)  ┃ ☆     ■■■┃");
	Putxy(0, 10, "┃■              ★(*'')/                  ■┃");

	SetColor(9, 0);
	Putxy(0, 11, "┃■                          ◎   ♥       ■┃");
	Putxy(0, 12, "┃■               ◎                       ■┃");
	Putxy(0, 13, "┃■    ■■■■                            ■┃");
	Putxy(0, 14, "┃■          ■             ●◆◆◆       ■┃");

	SetColor(14, 0);
	Putxy(0, 15, "┃■      ♥◎■                    ◆      ■┃");
	Putxy(0, 16, "┃■          ■  Press Space Key !! ◆◆◆ ■┃");
	Putxy(0, 17, "┃■          ■                            ■┃");
	Putxy(0, 18, "┃■        ■■■■       ◎  ♥ ■■■■■■┃");

	SetColor(9, 0);
	Putxy(0, 19, "┃■                           ■           ■┃");
	Putxy(0, 20, "┃■                        ■     ◎  ♥   ■┃");
	Putxy(0, 21, "┃■                     ■                 ■┃");
	Putxy(0, 22, "┃■■■■■■■■■■■■■■■■■■■■■■┃");
	Putxy(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━━┛");
}
void ClearStage(int stage) {
	SetColor(14, 0);
	Putxy(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━┓");
	Putxy(0, 1, "┃                                            ┃");
	Putxy(0, 2, "┃                                            ┃");
	Putxy(0, 3, "┃                                            ┃");
	Putxy(0, 4, "┃                                            ┃");
	Putxy(0, 5, "┃                                            ┃");
	Putxy(0, 6, "┃                       *.   .*              ┃");
	Putxy(0, 7, "┃                    *.┏┓┏┓.*대          ┃");
	Putxy(0, 8, "┃                    ┏┻┫┣┻┓단          ┃");
	Putxy(0, 9, "┃                    ┃━┫┣━┃해          ┃");
	Putxy(0, 10, "┃                    ┃━┫┣━┃요~         ┃");
	Putxy(0, 11, "┃                    ┗━┛┗━┛            ┃");
	Putxy(0, 12, "┃                                            ┃");
	Putxy(0, 13, "┃                                            ┃");
	gotoxy(0, 14); printf("┃                   Stage %d Clear ~!         ┃", stage + 1);
	gotoxy(0, 15); printf("┃                  Total Score %d          ┃", map.nScore);
	Putxy(0, 16, "┃                                            ┃");
	Putxy(0, 17, "┃                                            ┃");
	Putxy(0, 18, "┃                                            ┃");
	Putxy(0, 19, "┃                                            ┃");
	Putxy(0, 20, "┃                                            ┃");
	Putxy(0, 21, "┃                                            ┃");
	Putxy(0, 22, "┃  - Press Any key to exit...                ┃");
	Putxy(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━━┛");

	for (;;) {
		if (_kbhit()) {
			Sleep(1000); 
			FMOD_Channel_Stop(g_Channel[0]); 
			exit(1); 
		}
	}
}
void FailureScreen() {
	SetColor(14, 0);
	Putxy(0, 0, "┏━━━━━━━━━━━━━━━━━━━━━━┓");
	Putxy(0, 1, "┃                                            ┃");
	Putxy(0, 2, "┃                                            ┃");
	Putxy(0, 3, "┃                                            ┃");
	Putxy(0, 4, "┃                                            ┃");
	Putxy(0, 5, "┃                                            ┃");
	Putxy(0, 6, "┃                                            ┃");
	Putxy(0, 7, "┃                 *┭┮  ┭┮*               ┃");
	Putxy(0, 8, "┃              *.  ㅣㅣ▽ㅣㅣ   .*           ┃");
	Putxy(0, 9, "┃          ┏ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┓          ┃");
	Putxy(0, 10, "┃          ┃     미션 실패      ┃          ┃");
	Putxy(0, 11, "┃          ┗ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┛          ┃");
	Putxy(0, 12, "┃                                            ┃");
	Putxy(0, 13, "┃                                            ┃");
	Putxy(0, 14, "┃           (*⌒⌒*)                         ┃");
	Putxy(0, 15, "┃         ┏O━━━O━━━━━━━━━━┓   ┃");
	Putxy(0, 16, "┃         ┃계속하시겠습니까? <y/n>     ┃   ┃");
	Putxy(0, 17, "┃         ┗━━━━━━━━━━━━━━┛   ┃");
	Putxy(0, 18, "┃                                            ┃");
	Putxy(0, 19, "┃                                            ┃");
	Putxy(0, 20, "┃                                            ┃");
	Putxy(0, 21, "┃                                            ┃");
	Putxy(0, 22, "┃                                            ┃");
	Putxy(0, 23, "┗━━━━━━━━━━━━━━━━━━━━━━┛");
up:
	switch (_getch()) {
	case 'Y':
	case 'y':
		map.nReplay = 1; break;
	case 'N':
	case 'n':
		Sleep(555); exit(1); break;
	default: goto up; break;
	}
}

/********************************
- UpdateScreen
: Map[stage][i][j]
-> 0 : Food
-> 1 : Map Block
-> 2 : Map Goal
-> 3 : Player
     - super on  -> 1 : lightblue
	 - super off -> 0 : gray
-> 4 : Enmey
-> 5 : Super Fruit
-> 6 : Empty Block
*********************************/
void UpdateScreen(int stage) {
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			switch (Map[stage][i][j]) {
			case 0:
				Putxy(j * 2, i, ".");
				break;
			case 1:
				SetColor(14, 0); Putxy(j * 2, i, "■");
				break;
			case 2:
				SetColor(6, 0); Putxy(j * 2, i, "◎");
				break;
			case 3:
				if (map.pPos.super == 1) SetColor(9, 0);
				else                     SetColor(8, 0);
				Putxy(j * 2, i, "★");
				break;
			case 4:
				SetColor(9, 0); Putxy(j * 2, i, "◆");
				break;
			case 5:
				SetColor(12, 0); Putxy(j * 2, i, "♥");
				break;
			case 6: 
				Putxy(j * 2, i, " "); 
				break;
			default: break;
			}
		}
	}
}

/********************************
- IsClearStage
: If Player ate all of super fruits,
  Clear the stage
*********************************/
BOOL IsClearStage(int stage) {
	for (int i = 1; i < COL - 1; i++) {
		for (int j = 1; j < ROW - 1; j++) {
			/* Are there any super fruits on Map */
			if (Map[stage][i][j] == 5) return FALSE;
		}
	}
	return TRUE;
}

BOOL eColli(int i) {
	if (Map[map.nStage][E[i].xPos][E[i].yPos] == 1)	return TRUE;
	return FALSE;
}
void GoOneBlock(int i) {
	if (E[i].stright == 1) {
		int a = 0;
		if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] == 1)
			++a;
		if (Map[map.nStage][E[i].yPos - 1][E[i].xPos] == 1)
			++a;
		if (Map[map.nStage][E[i].yPos][E[i].xPos + 1] == 1)
			++a;
		if (Map[map.nStage][E[i].yPos][E[i].xPos - 1] == 1)
			++a;

		if (a != 2) { E[i].stright = 0; }
		else {
			E[i].OxPos = E[i].xPos; E[i].OyPos = E[i].yPos;

			if (E[i].nDirect == 1) { E[i].yPos += 1; E[i].nDirect = 1; }
			else if (E[i].nDirect == 2) { E[i].yPos -= 1; E[i].nDirect = 2; }
			else if (E[i].nDirect == 3) { E[i].xPos += 1; E[i].nDirect = 3; }
			else { E[i].xPos -= 1; E[i].nDirect = 4; }

			if (!eColli(i)) {
				Map[map.nStage][E[i].OyPos][E[i].OxPos] = 6;
				Map[map.nStage][E[i].yPos][E[i].xPos] = 4;
			}
			else {
				E[i].xPos = E[i].OxPos; E[i].yPos = E[i].OyPos;
				Map[map.nStage][E[i].OyPos][E[i].OxPos] = 6;
				Map[map.nStage][E[i].yPos][E[i].xPos] = 4;
			}
		}
	}

	if (E[i].stright == 0) {
		srand((unsigned)GetTickCount()); Sleep(10);
		int c = 0;
		if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] == 1)
			++c;
		if (Map[map.nStage][E[i].yPos - 1][E[i].xPos] == 1)
			++c;
		if (Map[map.nStage][E[i].yPos][E[i].xPos + 1] == 1)
			++c;
		if (Map[map.nStage][E[i].yPos][E[i].xPos - 1] == 1)
			++c;

		E[i].OxPos = E[i].xPos; E[i].OyPos = E[i].yPos;

		if (c == 2) {
			if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos - 1][E[i].xPos] != 1) {
				if (rand() % 2 == 0) { E[i].yPos += 1; E[i].nDirect = 1; }
				else { E[i].yPos -= 1; E[i].nDirect = 2; }
			}
			if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos + 1] != 1) {
				if (rand() % 2 == 0) { E[i].yPos += 1; E[i].nDirect = 1; }
				else { E[i].xPos += 1; E[i].nDirect = 3; }
			}
			if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos - 1] != 1) {
				if (rand() % 2 == 0) { E[i].yPos += 1; E[i].nDirect = 1; }
				else { E[i].xPos -= 1; E[i].nDirect = 4; }
			}
			if (Map[map.nStage][E[i].yPos - 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos + 1] != 1) {
				if (rand() % 2 == 0) { E[i].yPos -= 1; E[i].nDirect = 2; }
				else { E[i].xPos += 1; E[i].nDirect = 3; }
			}
			if (Map[map.nStage][E[i].yPos - 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos - 1] != 1) {
				if (rand() % 2 == 0) { E[i].yPos -= 1; E[i].nDirect = 2; }
				else { E[i].xPos -= 1; E[i].nDirect = 4; }
			}
			if (Map[map.nStage][E[i].yPos][E[i].xPos + 1] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos - 1] != 1) {
				if (rand() % 2 == 0) { E[i].xPos += 1; E[i].nDirect = 3; }
				else { E[i].xPos -= 1; E[i].nDirect = 4; }
			}
		}
		else if (c == 1) {
			if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos - 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos + 1] != 1) {
				int rr = rand() % 3;
				if (rr == 0) { E[i].yPos += 1; E[i].nDirect = 1; }
				else if (rr == 1) { E[i].yPos -= 1; E[i].nDirect = 2; }
				else { E[i].xPos += 1; E[i].nDirect = 3; }
			}
			if (Map[map.nStage][E[i].yPos + 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos - 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos - 1] != 1) {
				int rrr = rand() % 3;
				if (rrr == 0) { E[i].yPos += 1; E[i].nDirect = 1; }
				else if (rrr == 1) { E[i].yPos -= 1; E[i].nDirect = 2; }
				else { E[i].xPos -= 1; E[i].nDirect = 4; }
			}
			if (Map[map.nStage][E[i].yPos - 1][E[i].xPos] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos + 1] != 1 && Map[map.nStage][E[i].yPos][E[i].xPos - 1] != 1) {
				int rrrr = rand() % 3;
				if (rrrr == 0) { E[i].yPos -= 1; E[i].nDirect = 2; }
				else if (rrrr == 1) { E[i].xPos += 1; E[i].nDirect = 3; }
				else { E[i].xPos -= 1; E[i].nDirect = 4; }
			}
		}
		else if (c == 0) {
			int r = rand() % 4;
			if (r == 0) { E[i].yPos += 1; E[i].nDirect = 1; }
			else if (r == 1) { E[i].yPos -= 1; E[i].nDirect = 2; }
			else if (r == 2) { E[i].xPos += 1; E[i].nDirect = 3; }
			else { E[i].xPos -= 1; E[i].nDirect = 4; }
		}
		++E[i].stright;
		if (!eColli(i)) {
			Map[map.nStage][E[i].OyPos][E[i].OxPos] = 6;
			Map[map.nStage][E[i].yPos][E[i].xPos] = 4;
		}
		else {
			E[i].xPos = E[i].OxPos; E[i].yPos = E[i].OyPos;
			Map[map.nStage][E[i].OyPos][E[i].OxPos] = 6;
			Map[map.nStage][E[i].yPos][E[i].xPos] = 4;
		}
	}
}

/********************************
- EnmeyDraw
: If Player ate all of super fruits,
Clear the stage
*********************************/
void EnemyDraw(MapInfo m) {
	/* If enemy nerver generates before, ... */
	if (map.eFlag == 0) {
		int blank[COL*ROW][2] = { 0, }, c = 0;

		for (int i = 5; i < COL - 1; i++) {
			for (int j = 5; j < ROW - 1; j++) {
				/* Get Cord where enemy can be spwaned */
				if (Map[m.nStage][i][j] == 0) {
					/* Save Cord */
					blank[c][0] = i;
					blank[c][1] = j;
					++c;
				}
			}
		}

		for (int z = 0; z < m.nEnemy; z++) {
			srand((unsigned)GetTickCount()); Sleep(11);
			int r = rand() % c;

			E[z].xPos = blank[r][1];
			E[z].yPos = blank[r][0];

			/* Enemy */
			Map[m.nStage][E[z].yPos][E[z].xPos] = 4;
		}

		++map.eFlag;
		//UpdateScreen(map.nStage);
	}
	//	for (int i = 0; i < map.nEnemy; i++)
	//		GoOneBlock(i);
	UpdateScreen(map.nStage);
}

/***********************************************
- IsCollision
: Controlling Collision to any blocks
-> Super Power Remain Time : 3 sec
   - can eat enemy while super power mode is on
-> Food Score        : 1
-> Super Fruit Score : 50
-> Enemy Score       : 100
************************************************/
void IsCollision(int yPos, int xPos, int stage) {
	/* Empty now Position*/
	Map[stage][map.pPos.OyPos][map.pPos.OxPos] = 6;

	/* If Super Power is on */
	if (map.pPos.super == 1) {
		/* But Super power Remanin time is over 3 sec */
		if (GetTickCount() - map.pPos.stime > 3000) {
			/* Initializing super power and super time */
			map.pPos.super = 0;
			map.pPos.stime = 0;
		}
	}

	/* If Current Position is ... */
	switch (Map[stage][yPos][xPos]) {
	case 0: /* food */
		map.nScore += 1; // +1 score
		Map[stage][yPos][xPos] = 6; // Be Empty
		break;
	case 1: /* Map Block -> Collision */
		/* Back to Old Position */
		map.pPos.xPos = map.pPos.OxPos;
		map.pPos.yPos = map.pPos.OyPos;
		break;
	case 2: /* Map Goal */
		/* If Clear Stage is Ture */
		if (IsClearStage(map.nStage)) {
			/* Stop Map BGM */
			FMOD_Channel_Stop(g_Channel[5]);
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[3], 0, &g_Channel[3]);
			
			/* Clear the Screen */
			system("cls");

			/* Print Success Screen */
			ClearStage(map.nStage);
		}
		break;
	case 4: /* Enemy */
		/* If Player has super power */
		if (map.pPos.super > 0) {
			map.nScore += 100; // +100 score
			map.nEnemy -= 1; // Terminate 1 enemy
		}
		else { /* If not */
			/* Stop Map BGM */
			FMOD_Channel_Stop(g_Channel[5]);
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[1], 0, &g_Channel[1]);

			/* Clear the Stage*/
			system("cls");

			/* Print Failure Screen */
			FailureScreen();
		}
		break;
	case 5: /* Super Fruit */
		/* Play eat Sound */
		FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[4], 0, &g_Channel[4]);

		Map[stage][yPos][xPos] = 6; // Empty Current Block
		map.nScore += 50; // +50 score
		++map.pPos.super; // ON Super Power

		/* If already on super mode , keep going */
		if (map.pPos.super >= 1) map.pPos.super = 1;

		map.pPos.stime = GetTickCount(); // Start Super Power Mode
		break;
	default: break;
	}

	/* Make Current Position to Player Block */
	Map[stage][map.pPos.yPos][map.pPos.xPos] = 3;
}

/***************************************************************
- Initialzing
: Initializing all of settings depands on stage and Music System
- Map Info
-> eFlag      : 0
   - Temp Enemy init value for generating
-> nScore     : 0
   - Player's Score
-> nReplay    : 0
   - Check Replay  ( 1 : on, 0 : off )
-> pPos.xPos  : 1
   - Current x Pos
-> pPos.yPos  : 1
   - Currnet y Pos
-> nStage     : stage - 1
   - Choose Stage what u want
-> pPos.OxPos : pPos.xPos
   - Old x Position
-> pPos.OxPos : pPos.yPos
   - Old y Position
-> nEnemy     : 2*stage + 5
   - Total Enemy's Count

- BGM
-> g_Sound[0] -> intro
-> g_Sound[1] -> dead
-> g_Sound[2] -> stage
-> g_Sound[3] -> success
-> g_Sound[4] -> eat
-> g_Sound[5] -> collision // Main Game BGM

- Screen Setting
-> Remove Curson on console
-> Set Title      : The New 'Pac Man'
-> Resize Console : 32x66
****************************************************************/
void Initializing(int stage) {
	/* Initializing Map Info */
	map.eFlag = 0;
	map.nScore = 0;
	map.nReplay = 0;
	map.pPos.xPos = 1;
	map.pPos.yPos = 1;
	map.nStage = stage - 1;
	map.pPos.OxPos = map.pPos.xPos;
	map.pPos.OyPos = map.pPos.yPos;
	map.nEnemy = (map.nStage + 1) * 2 + 3;
	
	Map[stage][map.pPos.yPos][map.pPos.xPos] = 3;

	/* Allocate Memory just Enemy count */
	E = (Enemy *)malloc(sizeof(Enemy)*map.nEnemy); 

	/* Initializing Sound System */
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);

	/* Loop Sound */
	FMOD_System_CreateSound(g_System, "intro.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[0]);
	FMOD_System_CreateSound(g_System, "collision.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &g_Sound[5]);

	/* One time effect Sound */
	FMOD_System_CreateSound(g_System, "dead.wav", FMOD_DEFAULT, 0, &g_Sound[1]);
	FMOD_System_CreateSound(g_System, "stage.wav", FMOD_DEFAULT, 0, &g_Sound[2]);
	FMOD_System_CreateSound(g_System, "success.wav", FMOD_DEFAULT, 0, &g_Sound[3]);
	FMOD_System_CreateSound(g_System, "eat.wav", FMOD_DEFAULT, 0, &g_Sound[4]);

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };

	/* Set Cursor Invisible on Screen */
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	/* Set Title */
	system("title The New 'Pac Man'");

	/* Set Console Size */
	system("mode con:lines=32 cols=66");
}

/********************************
- Release
: Release all of settings
*********************************/
void Release() {
	/* Release all of musics */
	for (int i = 0; i < 5; i++)
		FMOD_Sound_Release(g_Sound[i]);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);

	/* free 'Enemy's */
	free(E);
}

void main(int argc, char *argv[]) {
start:
	/* Initializing */
	Initializing(0);

	/* Intro Screen */
	InitScreen();

	/* Play Intro Music */
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[0], 0, &g_Channel[0]);

	for (;;) {
		/* If any key is input */
		if (_kbhit()) {
			/* Clear the Screen */
			system("cls");

			/* Stop Intro Music */
			FMOD_Channel_Stop(g_Channel[0]);
			
			/* Play Game Music */
			FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[5], 0, &g_Channel[5]);
			break;
		}
	}

	for (;;) {
		/* Print Player's Info */
		StateScreen();
		
		/* If Replay is ... */
		if (map.nReplay == 1) {
			/* Init */
			map.nReplay = 0;

			/* goto start of the game */
			goto start;
		}

		if (_kbhit()) {
			Map[map.nStage][1][24] = 2;

			/* Backup Current Positions */
			map.pPos.OxPos = map.pPos.xPos;
			map.pPos.OyPos = map.pPos.yPos;

			/* Player's Move */
			switch (_getch()) {
			case UP: map.pPos.yPos -= 1; break;
			case DOWN: map.pPos.yPos += 1; break;
			case LEFT: map.pPos.xPos -= 1; break;
			case RIGHT: map.pPos.xPos += 1; break;
			case SPACE: /* Stop Main Game BGM */
				FMOD_Channel_Stop(g_Channel[5]); break;
			default: break;
			}

			/* Checking Player's Coliision */
			IsCollision(map.pPos.yPos, map.pPos.xPos, map.nStage);
		}

		for (;;) {
			if (_kbhit()) break;
			EnemyDraw(map);
		}

		/* Update Screen */
		UpdateScreen(map.nStage);
	}

	/* Release All Settings */
	Release();
}