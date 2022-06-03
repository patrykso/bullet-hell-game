#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h> 

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

typedef struct {
	float x, y, heartWidth, heartHeight;
	bool available;
	SDL_Surface* img;
	SDL_Rect hitbox;
} Heart;

typedef struct {
	int health, shotNumber, animationNumber;
	char direction;
	float x, y, speed, enemyWidth, enemyHeight, mX, mY;
	SDL_Surface* img, * anim1, * anim2, * anim3;
	SDL_Rect hitbox;
} Enemy;

typedef struct {
	float speed, angle, bulletWidth, bulletHeight, x, y, boomDelta, hX, hY, distanceToWall, xAngle, yAngle;
	int Hit;
	bool wall;
	SDL_Surface* img, * boom1, * boom2, * boom3;
	SDL_Rect hitbox;
} Bullet;

typedef struct {
	int shotNumber, health, score, scoreMultiplier, scoreMultiplierN;
	float x, y, speed, playerWidth, playerHeight, hX, hY;
	char grade;
	SDL_Surface* img, * anim1, * anim2, * anim3;
	SDL_Rect hitbox;
} Player;

typedef struct {
	int quit, rc, eBulletsCounter, czarny, czerwony, zielony, niebieski, t1, t2, frames, shootingTempTime, stage, shotsToCheck, shotsToCheckE, finalScore, frameTime;
	double worldTime, delta, fpsTimer, fps;
	SDL_Event event;
	SDL_Surface* screen, * charset, * floor, * gradeChange1, * gradeChange2;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect camera;
	char text[128], nickname[30], nicknamepart;
	float iFramesE, iFramesP, tempTime, animationCounter, bulletAngle = 0;
	int animationFrame, animationHelper;
	Uint32 frameStart;
} Game;

typedef struct {
	float counter;
} Timer;


void BulletHandler(Bullet* bullet, Game* gameManager, SDL_Rect* hitbox, int i);
void Enemy2ShootingHandler(Game* gameManager, Bullet* eBullets, Player* player);
void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y, Game* gameManager);
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void QuitGame(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void Initialize(Game* gameManager);
void EventHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void LoadImages(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void InitializeObjects(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void ArrowUpHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void ArrowDownHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void ArrowRightHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void ArrowLeftHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void GameLoop(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer);
void Rendering(Game* gameManager);
void CreateStage(Game* gameManager, Player* player, Enemy* enemy1, Heart* heart);
void DrawGUI(Game* gameManager, Player* player);
void PlayerShootingHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* pBullets, Timer* timer);
void MenuEventHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer);
bool PlayerHit(Game* gameManager, Player* player, Bullet* eBullets);
bool EnemyHit(Player* player, Bullet* pBullets, Enemy* enemy1);
void CheckWin(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void BulletHitPlayer(Game* gameManager, Player* player, Bullet* pBullets, Enemy* enemy1);
void GradeHandler(Game* gameManager, Player* player, Timer* timer);
void HeartHandler(Player* player, Heart* heart);
void Stage1Handler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer);
void MenuHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer);
void HighScoresHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void DrawMenu(Game* gameManager);
void GameOverHandler(Game* gameManager, Player* player);
void GameOverEventHandler(Game* gameManager);
void DrawGameOver(Game* gameManager);
void StageWonHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer);
void StageWonEventHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer);
void DrawStageWon(Game* gameManager, Player* player);
void PlayerBulletOverBoard(Game *gameManager, Player* player, Bullet* pBullets);
void PlayerAnimationHandler(Game* gameManager);
void InvincibilityForPlayer(Game* gameManager, Player* player, Bullet* eBullets);
void InitializeA(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer);
void SaveHighScoresHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart);
void DrawSaveHighScores(Game* gameManager, Player *player);
void SaveHighScoresEventHandler(Game* gameManager);
void CreateStage3(Game* gameManager, Player* player, Enemy* enemy1, Heart* heart);
void Stage3Handler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer);
void DrawEnemy(Game* gameManager, Enemy* enemy1, Player *player);
void EnemyAnimationHandler(Enemy* enemy1, Timer* timer);
void EnemyBulletOverBoard(Game* gameManager, Bullet* eBullets);
void DrawWarning(Game* gameManager, Timer* timer, int i);
void Stage2Handler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer);
void Enemy1ShootingHandler(Game* gameManager, Bullet* eBullets, Player* player);

#define SCREEN_WIDTH 640 //pixels
#define SCREEN_HEIGHT 480 //pixels
#define LEVEL_WIDTH 1920 //pixels
#define LEVEL_HEIGHT 1440 //pixels
#define EBULLETS_NUMBER 4000 //number of enemy bullets
#define PBULLETS_NUMBER 400 //number of player bullets
#define PSTARTING_X 0 //starting x for playera
#define PSTARTING_Y 0 //starting y for player
#define ESTARTING_X 0 //starting x for enemy
#define ESTARTING_Y 0 //starting y for enemy
#define MENU 0 //part of game menu
#define STAGE1 1 //part of game menu
#define STAGE2 2 //part of game menu
#define STAGE3 3 //part of game menu
#define HIGHSCORES 4 //part of game menu
#define STAGE_WON 5 //part of game menu
#define GAME_OVER 6 //part of game menu
#define SAVEHIGHSCORE 7 //part of game menu
#define PLAYER_SPEED_MULTIPLIER 500
#define PLAYER_BULLETS_MULTIPLIER 0.5
#define ENEMY_BULLETS_MULTIPLIER 0.6
#define ENEMY_MOVEMENT_MULTIPLIER 0.2
#define BOOM_ANIMATION_SPEED 0.2


#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {
	Game gameManager;
	Heart heart;
	Player player;
	Enemy enemy1, enemy2, enemy3;
	Bullet eBullets[EBULLETS_NUMBER];
	Bullet pBullets[PBULLETS_NUMBER];
	Timer timer[10];

	srand(time(NULL));

	LoadImages(&gameManager, &player, &enemy1, eBullets, pBullets, &heart);
	Initialize(&gameManager);
	InitializeA(&gameManager, &player, &enemy1, eBullets, pBullets, &heart, timer);

	gameManager.stage = MENU;
	while (!gameManager.quit) {
		GameLoop(&gameManager, &player, &enemy1, eBullets, pBullets, &heart, timer);
	};
	QuitGame(&gameManager, &player, &enemy1, eBullets, pBullets, &heart);
	return 0;
};

void GameLoop(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer) {
	gameManager->t2 = SDL_GetTicks();
	gameManager->frameStart = SDL_GetTicks();
	// w tym momencie t2-t1 to czas w milisekundach, jaki uplyna≥ od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	gameManager->delta = (gameManager->t2 - gameManager->t1) * 0.001;
	gameManager->t1 = gameManager->t2;
	gameManager->worldTime += gameManager->delta;
	gameManager->fpsTimer += gameManager->delta;
	if (gameManager->fpsTimer > 0.5) {
		gameManager->fps = gameManager->frames * 2;
		gameManager->frames = 0;
		gameManager->fpsTimer -= 0.5;
	};

	const int targetFPS = 30;
	const int delay = 1000 / targetFPS;

	if (gameManager->stage == MENU) {
		MenuHandler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
	}
	else if (gameManager->stage == STAGE1) {
		Stage1Handler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
	}
	else if (gameManager->stage == STAGE2) {
		Stage2Handler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
	}
	else if (gameManager->stage == STAGE3) {
		Stage3Handler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
	}
	else if (gameManager->stage == HIGHSCORES) {
		HighScoresHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
	}
	else if (gameManager->stage == SAVEHIGHSCORE) {
		SaveHighScoresHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
	}
	else if (gameManager->stage == STAGE_WON) {
		StageWonHandler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
	}
	else if (gameManager->stage == GAME_OVER) {
		GameOverHandler(gameManager, player);
	}
	
	for (int i = 0; i < 9; i++) {
		timer[i].counter += gameManager->delta;
	}
	
	gameManager->frameTime = SDL_GetTicks() - gameManager->frameStart;
	if (delay > gameManager->frameTime) {
		SDL_Delay(delay - gameManager->frameTime);
	}
	gameManager->frames++;
}

void InitializeA(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer) {
	gameManager->t1 = SDL_GetTicks();
	gameManager->frames = 0;
	gameManager->fpsTimer = 0;
	gameManager->fps = 0;
	gameManager->tempTime = 0;
	gameManager->iFramesE = 3;
	gameManager->iFramesP = 3;
	gameManager->bulletAngle = 0;
	gameManager->quit = 0;
	gameManager->rc = 0;
	gameManager->worldTime = 0;
	gameManager->shootingTempTime = -1;
	gameManager->animationHelper = 1;
	gameManager->animationFrame = 1;
	gameManager->animationCounter = 1;
	player->health = 10;
	player->shotNumber = 0;
	player->score = 0;
	player->scoreMultiplier = 1;
	player->grade = 'D';
	gameManager->camera = { 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	player->playerHeight = 90;
	player->playerWidth = 60;
	player->speed = gameManager->delta * PLAYER_SPEED_MULTIPLIER;
	enemy1->health = 10;
	enemy1->enemyWidth = 20;
	enemy1->enemyHeight = 40;
	heart->heartHeight = 40;
	heart->heartWidth = 40;
	heart->available = true;
	gameManager->eBulletsCounter = 0;
	gameManager->shotsToCheck = 0;
	player->x = SCREEN_WIDTH / 2;
	player->y = SCREEN_HEIGHT / 2;
	enemy1->x = 1000;
	enemy1->y = 700;
	enemy1->mX = 1000;
	enemy1->mY = 700;
	enemy1->direction = 'L';
	enemy1->animationNumber = 0;
	heart->x = (rand() % SCREEN_WIDTH) + (LEVEL_WIDTH - heart->heartWidth - SCREEN_WIDTH);
	heart->y = (rand() % SCREEN_HEIGHT) + (LEVEL_HEIGHT - heart->heartHeight - SCREEN_HEIGHT);
	heart->hitbox = { int(heart->x), int(heart->y), int(heart->heartWidth), int(heart->heartHeight) };
	enemy1->hitbox = { int(enemy1->x - enemy1->enemyWidth / 2), int(enemy1->y - enemy1->enemyHeight / 2), int(enemy1->enemyWidth), int(enemy1->enemyHeight) };
	player->hitbox = { int(player->x - player->playerWidth / 2), int(player->y - player->playerHeight / 2), int(player->playerWidth), int(player->playerHeight) };
	player->hX = SCREEN_WIDTH / 2;
	player->hY = SCREEN_HEIGHT / 2;
	for (int i = 0; i < EBULLETS_NUMBER; i++) {
		eBullets[i].angle = gameManager->worldTime * 2;
		eBullets[i].boomDelta = 0;
		eBullets[i].wall = false;
		eBullets[i].x = enemy1->x;
		eBullets[i].y = enemy1->y;
		eBullets[i].bulletWidth = 20;
		eBullets[i].bulletHeight = 24;
		eBullets[i].speed = player->speed * ENEMY_BULLETS_MULTIPLIER;
		eBullets[i].hitbox = { int(eBullets[i].x - eBullets[i].bulletWidth / 2), int(eBullets[i].y - eBullets[i].bulletHeight / 2), int(eBullets[i].bulletWidth), int(eBullets[i].bulletHeight) };
		eBullets[i].hX = eBullets[i].x;
		eBullets[i].hY = eBullets[i].y;
		eBullets[i].xAngle = cos(gameManager->bulletAngle);
		eBullets[i].yAngle = sin(gameManager->bulletAngle);
		gameManager->bulletAngle += 0.25;
	}
	for (int i = 0; i < PBULLETS_NUMBER; i++) {
		pBullets[i].angle = gameManager->worldTime * 2;
		pBullets[i].boomDelta = 0;
		pBullets[i].wall = false;
		pBullets[i].speed = player->speed * PLAYER_BULLETS_MULTIPLIER;
		pBullets[i].x = player->x;
		pBullets[i].y = player->y;
		pBullets[i].bulletWidth = 20;
		pBullets[i].bulletHeight = 24;
		pBullets[i].Hit = -1;
		pBullets[i].hitbox = { int(pBullets[i].x - pBullets[i].bulletWidth / 2), int(pBullets[i].y - pBullets[i].bulletHeight / 2), int(pBullets[i].bulletWidth), int(pBullets[i].bulletHeight) };
		pBullets[i].distanceToWall = LEVEL_WIDTH - (SCREEN_WIDTH / 2);
	}
	for (int i = 0; i < 9; i++) {
		timer[i].counter = 0;
	}
	gameManager->czarny = SDL_MapRGB(gameManager->screen->format, 0x00, 0x00, 0x00);
	gameManager->zielony = SDL_MapRGB(gameManager->screen->format, 0x00, 0xFF, 0x00);
	gameManager->czerwony = SDL_MapRGB(gameManager->screen->format, 0xFF, 0x00, 0x00);
	gameManager->niebieski = SDL_MapRGB(gameManager->screen->format, 0x11, 0x11, 0xCC);
}

void Initialize(Game* gameManager) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Quit();
		printf("SDL_Init error: %s\n", SDL_GetError());
		exit(1);
	}

	gameManager->rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gameManager->window, &gameManager->renderer);
	if (gameManager->rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		exit(1);
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(gameManager->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(gameManager->renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(gameManager->window, "Gra Bullet Hell - Projekt");

	gameManager->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	gameManager->scrtex = SDL_CreateTexture(gameManager->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);
}

void LoadImages(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	gameManager->charset = SDL_LoadBMP("./cs8x8.bmp");
	player->img = SDL_LoadBMP("./player.bmp");
	player->anim1 = SDL_LoadBMP("./wizardrun1.bmp");
	player->anim2 = SDL_LoadBMP("./wizardrun2.bmp");
	player->anim3 = SDL_LoadBMP("./wizardrun3.bmp");
	enemy1->img = SDL_LoadBMP("./enemy.bmp");
	enemy1->anim1 = SDL_LoadBMP("./witchrun1.bmp");
	enemy1->anim2 = SDL_LoadBMP("./witchrun2.bmp");
	enemy1->anim3 = SDL_LoadBMP("./witchrun3.bmp");
	gameManager->floor = SDL_LoadBMP("./floor.bmp");
	gameManager->gradeChange1 = SDL_LoadBMP("./warning1.bmp");
	gameManager->gradeChange2 = SDL_LoadBMP("./warning2.bmp");
	heart->img = SDL_LoadBMP("./heart.bmp");
	if (player->img == NULL || gameManager->charset == NULL || enemy1->img == NULL || gameManager->floor == NULL || heart->img == NULL || player->anim1 == NULL || player->anim2 == NULL
		|| player->anim3 == NULL || enemy1->anim1 == NULL || enemy1->anim2 == NULL || enemy1->anim3 == NULL
		|| gameManager->gradeChange1 == NULL || gameManager->gradeChange2 == NULL) {
		printf("Error loading image, error: %s\n", SDL_GetError());
		QuitGame(gameManager, player, enemy1, eBullets, pBullets, heart);
	};
	for (int i = 0; i < EBULLETS_NUMBER; i++) {
		eBullets[i].img = SDL_LoadBMP("./bullet2.bmp");
		eBullets[i].boom1 = SDL_LoadBMP("./boom1.bmp");
		eBullets[i].boom2 = SDL_LoadBMP("./boom2.bmp");
		eBullets[i].boom3 = SDL_LoadBMP("./boom3.bmp");
		if (eBullets[i].img == NULL || eBullets[i].boom1 == NULL || eBullets[i].boom2 == NULL || eBullets[i].boom3 == NULL) {
			printf("Error loading images, error: %s\n", SDL_GetError());
			QuitGame(gameManager, player, enemy1, eBullets, pBullets, heart);
		}
	}
	for (int i = 0; i < PBULLETS_NUMBER; i++) {
		pBullets[i].img = SDL_LoadBMP("./bullet1.bmp");
		pBullets[i].boom1 = SDL_LoadBMP("./boom1.bmp");
		pBullets[i].boom2 = SDL_LoadBMP("./boom2.bmp");
		pBullets[i].boom3 = SDL_LoadBMP("./boom3.bmp");
		if (pBullets[i].img == NULL || pBullets[i].boom1 == NULL || pBullets[i].boom2 == NULL || pBullets[i].boom3 == NULL) {
			printf("Error loading images, error: %s\n", SDL_GetError());
			QuitGame(gameManager, player, enemy1, eBullets, pBullets, heart);
		}
	}
	SDL_SetColorKey(gameManager->charset, true, 0x000000);
}

void EventHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	while (SDL_PollEvent(&gameManager->event)) {
		switch (gameManager->event.type) {
		case SDL_KEYDOWN:
			if (gameManager->event.key.keysym.sym == SDLK_ESCAPE) gameManager->quit = 1;
			else if (gameManager->event.key.keysym.sym == SDLK_UP) ArrowUpHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
			else if (gameManager->event.key.keysym.sym == SDLK_DOWN) ArrowDownHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
			else if (gameManager->event.key.keysym.sym == SDLK_RIGHT) ArrowRightHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
			else if (gameManager->event.key.keysym.sym == SDLK_LEFT) ArrowLeftHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
			else if (gameManager->event.key.keysym.sym == SDLK_n) {
				SDL_RenderClear(gameManager->renderer);
				gameManager->stage = MENU;
			}
			else if (gameManager->event.key.keysym.sym == SDLK_SPACE) {
				player->shotNumber++;
				DrawSurface(gameManager->screen, pBullets[player->shotNumber].img, pBullets[player->shotNumber].x, pBullets[player->shotNumber].y, gameManager);
			}
			player->hitbox.x = player->x - player->playerWidth / 2;
			player->hitbox.y = player->y - player->playerHeight / 2;
			player->hX = player->x;
			player->hY = player->y;
			//for (int i = player->shotNumber; i < PBULLETS_NUMBER; i++) {
			//	pBullets[i].hitbox.x = player->x;
			//	pBullets[i].hitbox.y = player->y;
			//}
			break;
		case SDL_KEYUP:
			//for (int i = player->shotNumber; i < PBULLETS_NUMBER; i++) {
			//	pBullets[i].hitbox.x = player->x;
			//	pBullets[i].hitbox.y = player->y;
			//	pBullets[i].hX = player->x;
			//	pBullets[i].hY = player->y;
			//	pBullets[i].x = player->x;
			//	pBullets[i].y = player->y;
			//}
			player->img = SDL_LoadBMP("./player.bmp");
			//printf("playerX: %f playerY: %f\n", player->x, player->y);
			//printf("bulletX: %i bulletY: %i\n", eBullets[0].hitbox.x, eBullets[0].hitbox.y);
			//printf("PbulletX: %f PbulletY: %f\n", pBullets[0].x, pBullets[0].y);
			//printf("bulletX: %f bulletY: %f\n", eBullets[5].x, eBullets[5].y);
			//printf("enemy1x: %f enemy1y: %f\n", enemy1->x, enemy1->y);
			//printf("enemy1HITBOXx: %f enemy1HITBOXy: %f\n", enemy1->hitbox.x, enemy1->hitbox.y);
			//printf("heartx: %f hearty: %f\n", heart->x, heart->y);
			//printf("heartHITx: %i heartHITy: %i\n", heart->hitbox.x, heart->hitbox.y);
			break;
		case SDL_QUIT:
			gameManager->quit = 1;
			break;
		};
	};
}

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y, Game* gameManager) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// rysowanie prostokπta o d≥ugoúci bokÛw l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void QuitGame(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	LoadImages(gameManager, player, enemy1, eBullets, pBullets, heart);
	SDL_FreeSurface(gameManager->charset);
	SDL_FreeSurface(gameManager->screen);
	SDL_FreeSurface(gameManager->floor);
	SDL_FreeSurface(gameManager->gradeChange1);
	SDL_FreeSurface(gameManager->gradeChange2);
	SDL_FreeSurface(player->img);
	SDL_FreeSurface(player->anim1);
	SDL_FreeSurface(player->anim2);
	SDL_FreeSurface(player->anim3);
	SDL_FreeSurface(enemy1->anim1);
	SDL_FreeSurface(enemy1->anim2);
	SDL_FreeSurface(enemy1->anim3);
	SDL_FreeSurface(enemy1->img);
	SDL_FreeSurface(heart->img);
	for (int i = 0; i < EBULLETS_NUMBER; i++) {
		SDL_FreeSurface(eBullets[i].img);
		SDL_FreeSurface(eBullets[i].boom1);
		SDL_FreeSurface(eBullets[i].boom2);
		SDL_FreeSurface(eBullets[i].boom3);
	}
	for (int i = 0; i < PBULLETS_NUMBER; i++) {
		SDL_FreeSurface(pBullets[i].img);
		SDL_FreeSurface(pBullets[i].boom1);
		SDL_FreeSurface(pBullets[i].boom2);
		SDL_FreeSurface(pBullets[i].boom3);
	}
	SDL_DestroyTexture(gameManager->scrtex);
	SDL_DestroyRenderer(gameManager->renderer);
	SDL_DestroyWindow(gameManager->window);
	SDL_Quit();
}

void Rendering(Game* gameManager) {
	SDL_UpdateTexture(gameManager->scrtex, NULL, gameManager->screen->pixels, gameManager->screen->pitch);
	SDL_RenderClear(gameManager->renderer);
	SDL_RenderCopy(gameManager->renderer, gameManager->scrtex, NULL, NULL);
	SDL_RenderPresent(gameManager->renderer);
}

void CreateStage(Game* gameManager, Player* player, Enemy* enemy1, Heart* heart) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	SDL_BlitSurface(gameManager->floor, &gameManager->camera, gameManager->screen, NULL);
	if (heart->available) DrawSurface(gameManager->screen, heart->img, heart->x, heart->y, gameManager);
	DrawSurface(gameManager->screen, enemy1->img, enemy1->x, enemy1->y, gameManager);
	DrawSurface(gameManager->screen, player->img, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gameManager);

}

void CreateStage3(Game* gameManager, Player* player, Enemy* enemy1, Heart* heart) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	SDL_BlitSurface(gameManager->floor, &gameManager->camera, gameManager->screen, NULL);
	if (heart->available) DrawSurface(gameManager->screen, heart->img, heart->x, heart->y, gameManager);
	DrawEnemy(gameManager, enemy1, player);
	DrawSurface(gameManager->screen, player->img, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, gameManager);

}

void EnemyAnimationHandler(Enemy *enemy1, Timer *timer) {
	if (timer[0].counter > 0.2) {
		enemy1->animationNumber += 1;
		timer[0].counter = 0;
	}
}

void DrawEnemy(Game* gameManager, Enemy* enemy1, Player *player) {
	if (enemy1->animationNumber % 3 == 0) {
		enemy1->img = enemy1->anim1;
	}
	else if (enemy1->animationNumber % 3 == 1) {
		enemy1->img = enemy1->anim2;
	}
	else if (enemy1->animationNumber % 3 == 2) {
		enemy1->img = enemy1->anim3;
	}
	
	if (enemy1->direction == 'R') {
		enemy1->x += player->speed * ENEMY_MOVEMENT_MULTIPLIER;
		enemy1->hitbox.x += player->speed * ENEMY_MOVEMENT_MULTIPLIER;
		enemy1->mX += player->speed * ENEMY_MOVEMENT_MULTIPLIER;
		if (enemy1->mX > 1200) enemy1->direction = 'L'; //uzaleznic to od czasu, a nie x i y, ograniczyc framerate i ogarnac spawn pociskow
	}
	else if (enemy1->direction == 'L') {
		enemy1->x -= player->speed * ENEMY_MOVEMENT_MULTIPLIER;
		enemy1->hitbox.x -= player->speed * ENEMY_MOVEMENT_MULTIPLIER;
		enemy1->mX -= player->speed * ENEMY_MOVEMENT_MULTIPLIER;
		if (enemy1->mX < 400) enemy1->direction = 'R';
	}
	DrawSurface(gameManager->screen, enemy1->img, enemy1->x, enemy1->y, gameManager);
}

void DrawGUI(Game* gameManager, Player* player) {
	DrawRectangle(gameManager->screen, 4, 440, SCREEN_WIDTH - 8, 36, gameManager->czarny, gameManager->czarny);
	if (player->health > 0) {
		if (player->health == 10) {
			DrawRectangle(gameManager->screen, 4, 440, SCREEN_WIDTH - 8, 36, gameManager->czerwony, gameManager->czerwony);
		}
		else
			DrawRectangle(gameManager->screen, 4, 440, SCREEN_WIDTH - (10 - player->health) * 64, 36, gameManager->czerwony, gameManager->czerwony);
	}
	sprintf(gameManager->text, "HP: %i/10, Score: %i, Grade: %c", player->health, player->score, player->grade);
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 455, gameManager->text, gameManager->charset);
	DrawRectangle(gameManager->screen, 4, 4, SCREEN_WIDTH - 8, 36, gameManager->czerwony, gameManager->niebieski);
	sprintf(gameManager->text, "Czas trwania poziomu = %.1lf s  %.0lf klatek / s", gameManager->worldTime, gameManager->fps);
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 10, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "Esc - wyjscie, Poruszanie graczem: \033\030\031\032, N - Nowa gra, Spacja - strzal");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 26, gameManager->text, gameManager->charset);
}

void DrawMenu(Game* gameManager) {
	sprintf(gameManager->text, "MENU - Wybierz na klawiaturze:");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 100, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "1 - Stage 1");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 120, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "2 - Stage 2");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 140, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "3 - Stage 3");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 160, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "4 - Highscores");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 180, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "ESC - wyjdz");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 200, gameManager->text, gameManager->charset);
}

void ArrowUpHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	if (player->y > 0) {
		player->y -= player->speed;
		gameManager->camera.y = player->y - (SCREEN_HEIGHT / 2);
		enemy1->y += player->speed;
		heart->y += player->speed;
		if (gameManager->animationFrame == 1) player->img = player->anim1;
		else if (gameManager->animationFrame == 2) player->img = player->anim2;
		else if (gameManager->animationFrame == 3) player->img = player->anim3;
		for (int i = 0; i < EBULLETS_NUMBER; i++) {
			eBullets[i].y += player->speed;
		}
		for (int i = 0; i < player->shotNumber; i++) {
			pBullets[i].y += player->speed;
			//pBullets[i].hitbox.y += player->speed;
		}
		for (int i = 0; i < PBULLETS_NUMBER; i++) { //aktualizacja koordynatow z ktorych ma byc wystrzelony nastepny pocisk NIEPRAWDA TO CHYBA?
			//pBullets[i].y += player->speed;
			pBullets[i].hitbox.y -= player->speed;
		}
	}
}

void ArrowDownHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	if (player->y < LEVEL_HEIGHT) {
		player->y += player->speed;
		gameManager->camera.y = player->y - (SCREEN_HEIGHT / 2);
		enemy1->y -= player->speed;
		heart->y -= player->speed;
		if (gameManager->animationFrame == 1) player->img = player->anim1;
		else if (gameManager->animationFrame == 2) player->img = player->anim2;
		else if (gameManager->animationFrame == 3) player->img = player->anim3;
		for (int i = 0; i < EBULLETS_NUMBER; i++) {
			eBullets[i].y -= player->speed;
		}
		for (int i = 0; i < player->shotNumber; i++) {
			pBullets[i].y -= player->speed;
			//pBullets[i].hitbox.y -= player->speed;
		}
		for (int i = 0; i < PBULLETS_NUMBER; i++) { //aktualizacja koordynatow z ktorych ma byc wystrzelony nastepny pocisk
			//pBullets[i].y -= player->speed;
			pBullets[i].hitbox.y += player->speed;
		}

	}
}

void ArrowRightHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	if (player->x < LEVEL_WIDTH) {
		player->x += player->speed;
		gameManager->camera.x = player->x - (SCREEN_WIDTH / 2);
		enemy1->x -= player->speed;
		heart->x -= player->speed;
		if (gameManager->animationFrame == 1) player->img = player->anim1;
		else if (gameManager->animationFrame == 2) player->img = player->anim2;
		else if (gameManager->animationFrame == 3) player->img = player->anim3;
		for (int i = 0; i < EBULLETS_NUMBER; i++) {
			eBullets[i].x -= player->speed;
		}
		for (int i = 0; i < player->shotNumber; i++) {
			pBullets[i].x -= player->speed;
			//pBullets[i].hitbox.x += player->speed;
			
		}
		for (int i = 0; i < PBULLETS_NUMBER; i++) { //aktualizacja koordynatow z ktorych ma byc wystrzelony nastepny pocisk
			//pBullets[i].x -= player->speed;
			pBullets[i].hitbox.x += player->speed;
			pBullets[i].distanceToWall -= player->speed;
		}

	}
}

void ArrowLeftHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	if (player->x > 0) {
		player->x -= player->speed;
		gameManager->camera.x = player->x - (SCREEN_WIDTH / 2);
		enemy1->x += player->speed;
		heart->x += player->speed;
		if (gameManager->animationFrame == 1) player->img = player->anim1;
		else if (gameManager->animationFrame == 2) player->img = player->anim2;
		else if (gameManager->animationFrame == 3) player->img = player->anim3;
		for (int i = 0; i < EBULLETS_NUMBER; i++) {
			eBullets[i].x += player->speed;
		}
		for (int i = 0; i < player->shotNumber; i++) {
			pBullets[i].x += player->speed;
			//pBullets[i].hitbox.x += player->speed;
			
		}
		for (int i = 0; i < PBULLETS_NUMBER; i++) { //aktualizacja koordynatow z ktorych ma byc wystrzelony nastepny pocisk
			//pBullets[i].x += player->speed;
			pBullets[i].hitbox.x -= player->speed;
			pBullets[i].distanceToWall += player->speed;
		}
	}
}

void PlayerShootingHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* pBullets, Timer* timer) {
	if (player->shotNumber > 0) {
		PlayerBulletOverBoard(gameManager, player, pBullets);
		for (int i = 0; i < player->shotNumber; i++) {
			if (!pBullets[i].wall) {
				DrawSurface(gameManager->screen, pBullets[i].img, pBullets[i].x, pBullets[i].y, gameManager);
				pBullets[i].x += pBullets[i].speed;
				pBullets[i].hitbox.x += pBullets[i].speed;
				pBullets[i].distanceToWall -= pBullets[i].speed;
			}
			else if (pBullets[i].wall == true) {
				if (pBullets[i].boomDelta > BOOM_ANIMATION_SPEED * 3);
				else if (pBullets[i].boomDelta > BOOM_ANIMATION_SPEED * 2) {
					DrawSurface(gameManager->screen, pBullets[i].boom3, pBullets[i].x, pBullets[i].y, gameManager);
				}
				else if (pBullets[i].boomDelta > BOOM_ANIMATION_SPEED) {
					DrawSurface(gameManager->screen, pBullets[i].boom2, pBullets[i].x, pBullets[i].y, gameManager);
				}
				else if (pBullets[i].boomDelta > 0) {
					DrawSurface(gameManager->screen, pBullets[i].boom1, pBullets[i].x, pBullets[i].y, gameManager);
				}
			}
		}
		if (gameManager->iFramesE > 1) {
			BulletHitPlayer(gameManager, player, pBullets, enemy1);
			if (EnemyHit(player, pBullets, enemy1)) {
				enemy1->health -= 1;
				gameManager->iFramesE = 0;
			}
		}
		else gameManager->iFramesE += gameManager->delta;
	}
}

void BulletHandler(Bullet* bullet, Game* gameManager, SDL_Rect* hitbox, int i) { //do usuniecia funkcja testowa
	bullet->x += bullet->speed * sin((gameManager->bulletAngle * M_PI) / 180.f) * 5.0f;
	hitbox->x += bullet->speed * sin((gameManager->bulletAngle * M_PI) / 180.f) * 5.0f;
	bullet->y += bullet->speed * cos(((gameManager->bulletAngle) * M_PI) / 180.f) * 5.0f;
	hitbox->y += bullet->speed * cos(((gameManager->bulletAngle) * M_PI) / 180.f) * 5.0f;
	DrawSurface(gameManager->screen, bullet->img, bullet->x, bullet->y, gameManager);
}

void Enemy1ShootingHandler(Game* gameManager, Bullet* eBullets, Player* player) {
	int tempTime = SDL_GetTicks();
	if (tempTime - gameManager->shootingTempTime > 25) {
		gameManager->eBulletsCounter++;
		gameManager->shootingTempTime = SDL_GetTicks();
	}

	EnemyBulletOverBoard(gameManager, eBullets);
	//for (int i = gameManager->eBulletsCounter; i < EBULLETS_NUMBER; i++) { //brak obslugi hitboxow
	//	eBullets[i].x += eBullets[i].speed * eBullets[i].xAngle;
	//	eBullets[i].y += eBullets[i].speed * eBullets[i].yAngle;
	//}
	for (int i = 0; i < gameManager->eBulletsCounter; i+=5) { //usunac hitboxy pociskow (rect) i osobna petla dla pociskow wystrzelonych i tych niewystrzelonych
		//angle wystrzelonych ma sie nie zmieniac (a sie zmienia)
		//angle niewystrzelonych ma sie zmieniac
		if (eBullets[i].wall == false) {
			//if (i % 2 == 1) {
			//eBullets[i].x += eBullets[i].speed; //* sin(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].y += eBullets[i].speed; //* cos(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			eBullets[i].x += eBullets[i].speed * eBullets[i].xAngle;
			eBullets[i].y += eBullets[i].speed * eBullets[i].yAngle;
			eBullets[i + 1].x += eBullets[i + 1].speed * eBullets[i + 1].xAngle;
			eBullets[i + 1].y += eBullets[i + 1].speed * eBullets[i + 1].yAngle;
			eBullets[i + 2].x += eBullets[i + 2].speed * eBullets[i + 2].xAngle;
			eBullets[i + 2].y += eBullets[i + 2].speed * eBullets[i + 2].yAngle;
			eBullets[i + 3].x += eBullets[i + 3].speed * eBullets[i + 3].xAngle;
			eBullets[i + 3].y += eBullets[i + 3].speed * eBullets[i + 3].yAngle;
			eBullets[i + 4].x += eBullets[i + 4].speed * eBullets[i + 4].xAngle;
			eBullets[i + 4].y += eBullets[i + 4].speed * eBullets[i + 4].yAngle;
			eBullets[i + 5].x += eBullets[i + 5].speed * eBullets[i + 5].xAngle;
			eBullets[i + 5].y += eBullets[i + 5].speed * eBullets[i + 5].yAngle;
			//eBullets[i].hitbox.x += eBullets[i].speed; //* sin(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].hitbox.y += eBullets[i].speed; //* cos(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].hY += eBullets[i].speed; //* cos(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].hX += eBullets[i].speed; //* sin(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			DrawSurface(gameManager->screen, eBullets[i + 1].img, eBullets[i + 1].x, eBullets[i + 1].y, gameManager);
			DrawSurface(gameManager->screen, eBullets[i + 2].img, eBullets[i + 2].x, eBullets[i + 2].y, gameManager);
			DrawSurface(gameManager->screen, eBullets[i + 3].img, eBullets[i + 3].x, eBullets[i + 3].y, gameManager);
			DrawSurface(gameManager->screen, eBullets[i + 4].img, eBullets[i + 4].x, eBullets[i + 4].y, gameManager);
			DrawSurface(gameManager->screen, eBullets[i + 5].img, eBullets[i + 5].x, eBullets[i + 5].y, gameManager);
			//gameManager->bulletAngle += 5;
			//}
		}
		else if (eBullets[i].wall == true) {
			if (eBullets[i].boomDelta > BOOM_ANIMATION_SPEED * 3);
			else if (eBullets[i].boomDelta > BOOM_ANIMATION_SPEED * 2) {
				DrawSurface(gameManager->screen, eBullets[i].boom3, eBullets[i].x, eBullets[i].y, gameManager);
			}
			else if (eBullets[i].boomDelta > BOOM_ANIMATION_SPEED) {
				DrawSurface(gameManager->screen, eBullets[i].boom2, eBullets[i].x, eBullets[i].y, gameManager);
			}
			else if (eBullets[i].boomDelta > 0) {
				DrawSurface(gameManager->screen, eBullets[i].boom1, eBullets[i].x, eBullets[i].y, gameManager);
			}
		}
	}
	InvincibilityForPlayer(gameManager, player, eBullets);
	//if (PlayerHit(gameManager, player, eBullets)) {
		//printf("PLAYER HAS BEEN HIT \n");
	//}
}

void Enemy2ShootingHandler(Game* gameManager, Bullet* eBullets, Player* player) {
	int tempTime = SDL_GetTicks();
	if (tempTime - gameManager->shootingTempTime > 25) {
		gameManager->eBulletsCounter++;
		gameManager->shootingTempTime = SDL_GetTicks();
	}

	EnemyBulletOverBoard(gameManager, eBullets);
	//for (int i = gameManager->eBulletsCounter; i < EBULLETS_NUMBER; i++) { //brak obslugi hitboxow
	//	eBullets[i].x += eBullets[i].speed * eBullets[i].xAngle;
	//	eBullets[i].y += eBullets[i].speed * eBullets[i].yAngle;
	//}
	for (int i = 0; i < gameManager->eBulletsCounter; i++) { //usunac hitboxy pociskow (rect) i osobna petla dla pociskow wystrzelonych i tych niewystrzelonych
		//angle wystrzelonych ma sie nie zmieniac (a sie zmienia)
		//angle niewystrzelonych ma sie zmieniac
		if (eBullets[i].wall == false) {
			//if (i % 2 == 1) {
			//eBullets[i].x += eBullets[i].speed; //* sin(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].y += eBullets[i].speed; //* cos(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			eBullets[i].x += eBullets[i].speed * eBullets[i].xAngle;
			eBullets[i].y += eBullets[i].speed * eBullets[i].yAngle;
			//eBullets[i].hitbox.x += eBullets[i].speed; //* sin(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].hitbox.y += eBullets[i].speed; //* cos(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].hY += eBullets[i].speed; //* cos(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			//eBullets[i].hX += eBullets[i].speed; //* sin(((gameManager->bulletAngle + 180 * i) * M_PI) / 180);
			DrawSurface(gameManager->screen, eBullets[i].img, eBullets[i].x, eBullets[i].y, gameManager);
			//gameManager->bulletAngle += 5;
			//}
		}
		else if (eBullets[i].wall == true) {
			if (eBullets[i].boomDelta > BOOM_ANIMATION_SPEED * 3);
			else if (eBullets[i].boomDelta > BOOM_ANIMATION_SPEED * 2) {
				DrawSurface(gameManager->screen, eBullets[i].boom3, eBullets[i].x, eBullets[i].y, gameManager);
			}
			else if (eBullets[i].boomDelta > BOOM_ANIMATION_SPEED) {
				DrawSurface(gameManager->screen, eBullets[i].boom2, eBullets[i].x, eBullets[i].y, gameManager);
			}
			else if (eBullets[i].boomDelta > 0) {
				DrawSurface(gameManager->screen, eBullets[i].boom1, eBullets[i].x, eBullets[i].y, gameManager);
			}
		}
	}
	InvincibilityForPlayer(gameManager, player, eBullets);
	//if (PlayerHit(gameManager, player, eBullets)) {
		//printf("PLAYER HAS BEEN HIT \n");
	//}
}

//bool PlayerHit(Game* gameManager, Player* player, Bullet* eBullets) {
//	for (int i = 0; i < gameManager->eBulletsCounter + 1; i++) {
//		if (SDL_HasIntersection(&eBullets[i].hitbox, &player->hitbox)) return true;
//	}
//	return false;
//}

bool PlayerHit(Game* gameManager, Player* player, Bullet* eBullets) {
	for (int i = 0; i < gameManager->eBulletsCounter + 1; i++) {
		if (eBullets[i].hX > player->hitbox.x && eBullets[i].hX < player->hitbox.x + player->hitbox.w) {
			if (eBullets[i].hY > player->hitbox.y && eBullets[i].hY < player->hitbox.y + player->hitbox.h) return true;
		}
	}
	return false;
}

bool EnemyHit(Player* player, Bullet* pBullets, Enemy* enemy1) {
	for (int i = 0; i < player->shotNumber + 1; i++) {
		if (SDL_HasIntersection(&pBullets[i].hitbox, &enemy1->hitbox)) {
			printf("enemy has been hit\n");
			return true;
		}
	}
	return false;
}

void MenuEventHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer) {
	while (SDL_PollEvent(&gameManager->event)) {
		switch (gameManager->event.type) {
		case SDL_KEYDOWN:
			if (gameManager->event.key.keysym.sym == SDLK_ESCAPE) gameManager->quit = 1;
			else if (gameManager->event.key.keysym.sym == SDLK_1) {
				InitializeA(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
				gameManager->worldTime = 0;
				gameManager->stage = STAGE1;
			}
			else if (gameManager->event.key.keysym.sym == SDLK_2) {
				InitializeA(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
				gameManager->worldTime = 0;
				gameManager->stage = STAGE2;
			}
			else if (gameManager->event.key.keysym.sym == SDLK_3) {
				InitializeA(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
				gameManager->worldTime = 0;
				gameManager->stage = STAGE3;
			}
			else if (gameManager->event.key.keysym.sym == SDLK_4) {
				gameManager->worldTime = 0;
				gameManager->stage = HIGHSCORES;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			gameManager->quit = 1;
			break;
		};
	};
}

void CheckWin(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	if (player->health <= 0) {
		SDL_RenderClear(gameManager->renderer);
		gameManager->stage = GAME_OVER;
	}
	else if (enemy1->health <= 0) {
		SDL_RenderClear(gameManager->renderer);
		gameManager->finalScore = player->score;
		gameManager->stage = STAGE_WON;
	}
}

void BulletHitPlayer(Game* gameManager, Player* player, Bullet* pBullets, Enemy* enemy1) { //obsluga trafiania przeicwnika
	for (int i = gameManager->shotsToCheck; i < player->shotNumber; i++) {
		if (pBullets[i].hitbox.x + pBullets[i].bulletWidth > enemy1->hitbox.x) {
			if (SDL_HasIntersection(&pBullets[i].hitbox, &enemy1->hitbox)) {
				pBullets[i].Hit = 1;
				player->score += 1 * player->scoreMultiplier;
				player->scoreMultiplier += 10;
				gameManager->shotsToCheck++;
				continue;
			}
			else
				pBullets[i].Hit = 0;
			player->scoreMultiplier = 1;
			gameManager->shotsToCheck++;
			continue;
		}
	}
}

void GradeHandler(Game *gameManager, Player* player, Timer *timer) {
	if (player->score > 400) {
		player->grade = 'A';
		timer[1].counter += gameManager->delta;
		timer[2].counter = 0;
		timer[3].counter = 0;
		timer[4].counter = 0;
		DrawWarning(gameManager, timer, 1);
	}
	else if (player->score > 250) {
		player->grade = 'B';
		timer[1].counter = 0;
		timer[2].counter += gameManager->delta;
		timer[3].counter = 0;
		timer[4].counter = 0;
		DrawWarning(gameManager, timer, 2);
	}
	else if (player->score > 100) {
		player->grade = 'C';
		timer[1].counter = 0;
		timer[2].counter = 0;
		timer[3].counter += gameManager->delta;
		timer[4].counter = 0;
		DrawWarning(gameManager, timer, 3);
	}
	else {
		player->grade = 'D';
		timer[1].counter = 0;
		timer[2].counter = 0;
		timer[3].counter = 0;
		timer[4].counter += gameManager->delta;
		DrawWarning(gameManager, timer, 4);
	}
}

void DrawWarning(Game *gameManager, Timer *timer, int i) {
	if (timer[i].counter > 1.5);
	else if (timer[i].counter > 1) DrawSurface(gameManager->screen, gameManager->gradeChange1, 430, 400, gameManager);
	else if (timer[i].counter > 0.5) DrawSurface(gameManager->screen, gameManager->gradeChange2, 430, 400, gameManager);
	else if (timer[i].counter > 0.0) DrawSurface(gameManager->screen, gameManager->gradeChange1, 430, 400, gameManager);
}

void HeartHandler(Player* player, Heart* heart) {
	if (heart->available) {
		if (SDL_HasIntersection(&heart->hitbox, &player->hitbox)) {
			if (player->health == 10) {
				player->score += 40;
				heart->available = false;
			}
			else if (player->health == 9) {
				player->score += 30;
				player->health += 1;
				heart->available = false;
			}
			else if (player->health < 9) {
				player->health += 2;
				player->score += 20;
				heart->available = false;
			}
		}
	}
}

void Stage1Handler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer) {
	CreateStage(gameManager, player, enemy1, heart);
	DrawGUI(gameManager, player);

	Enemy1ShootingHandler(gameManager, eBullets, player);
	//printf("pbullethitboxX %i, pbullethitboxY %i\t", pBullets[0].hitbox.x, pBullets[0].hitbox.y);
	//printf("distance to wall: %f \n", pBullets[0].distanceToWall);
	//printf("playerX: %f playerY: %f\n", player->x, player->y);
	////printf("PbulletX: %f PbulletY: %f\n", pBullets[0].x, pBullets[0].y);
	////printf("bulletX: %f bulletY: %f\n", eBullets[5].x, eBullets[5].y);
	//printf("enemy1x: %f enemy1y: %f\n", enemy1->x, enemy1->y);
	//printf("heartx: %f hearty: %f\n", heart->x, heart->y);
	PlayerShootingHandler(gameManager, player, enemy1, pBullets, timer);
	GradeHandler(gameManager, player, timer);
	HeartHandler(player, heart);
	CheckWin(gameManager, player, enemy1, eBullets, pBullets, heart);
	PlayerAnimationHandler(gameManager);

	Rendering(gameManager);
	EventHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
}

void Stage2Handler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer) {
	CreateStage(gameManager, player, enemy1, heart);
	DrawGUI(gameManager, player);

	Enemy2ShootingHandler(gameManager, eBullets, player);
	//printf("pbullethitboxX %i, pbullethitboxY %i\t", pBullets[0].hitbox.x, pBullets[0].hitbox.y);
	//printf("distance to wall: %f \n", pBullets[0].distanceToWall);
	//printf("playerX: %f playerY: %f\n", player->x, player->y);
	////printf("PbulletX: %f PbulletY: %f\n", pBullets[0].x, pBullets[0].y);
	////printf("bulletX: %f bulletY: %f\n", eBullets[5].x, eBullets[5].y);
	//printf("enemy1x: %f enemy1y: %f\n", enemy1->x, enemy1->y);
	//printf("heartx: %f hearty: %f\n", heart->x, heart->y);
	PlayerShootingHandler(gameManager, player, enemy1, pBullets, timer);
	GradeHandler(gameManager, player, timer);
	HeartHandler(player, heart);
	CheckWin(gameManager, player, enemy1, eBullets, pBullets, heart);
	PlayerAnimationHandler(gameManager);

	Rendering(gameManager);
	EventHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
}

void Stage3Handler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer* timer) {
	CreateStage3(gameManager, player, enemy1, heart);
	EnemyAnimationHandler(enemy1, timer);
	DrawGUI(gameManager, player);

	Enemy2ShootingHandler(gameManager, eBullets, player);
	PlayerShootingHandler(gameManager, player, enemy1, pBullets, timer);
	GradeHandler(gameManager, player, timer);
	HeartHandler(player, heart);
	CheckWin(gameManager, player, enemy1, eBullets, pBullets, heart);
	PlayerAnimationHandler(gameManager);

	Rendering(gameManager);
	EventHandler(gameManager, player, enemy1, eBullets, pBullets, heart);
}

void MenuHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	DrawMenu(gameManager);
	Rendering(gameManager);
	MenuEventHandler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
}

void HighScoresHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	//DrawHighScores(gameManager);
	Rendering(gameManager);
	//HighScoresEventHandler(gameManager);
}

void SaveHighScoresHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	DrawSaveHighScores(gameManager, player);
	Rendering(gameManager);
	SaveHighScoresEventHandler(gameManager);
}

void SaveHighScoresEventHandler(Game* gameManager) {
	while (SDL_PollEvent(&gameManager->event)) {
		switch (gameManager->event.type) {
		case SDL_KEYDOWN:
			if (gameManager->event.key.keysym.sym == SDLK_ESCAPE) gameManager->quit = 1;
			else if (gameManager->event.key.keysym.sym == SDLK_1) {
				gameManager->nicknamepart = '1';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_2) {
				gameManager->nicknamepart = '2';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_3) {
				gameManager->nicknamepart = '3';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_4) {
				gameManager->nicknamepart = '4';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_5) {
				gameManager->nicknamepart = '5';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_6) {
				gameManager->nicknamepart = '6';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_7) {
				gameManager->nicknamepart = '7';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_8) {
				gameManager->nicknamepart = '8';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_9) {
				gameManager->nicknamepart = '9';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_0) {
				gameManager->nicknamepart = '0';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_a) {
				gameManager->nicknamepart = 'a';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_b) {
				gameManager->nicknamepart = 'b';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_c) {
				gameManager->nicknamepart = 'c';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_d) {
				gameManager->nicknamepart = 'd';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_e) {
				gameManager->nicknamepart = 'e';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_f) {
				gameManager->nicknamepart = 'f';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_g) {
				gameManager->nicknamepart = 'g';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_h) {
				gameManager->nicknamepart = 'h';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_i) {
				gameManager->nicknamepart = 'i';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_j) {
				gameManager->nicknamepart = 'j';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_k) {
				gameManager->nicknamepart = 'k';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_l) {
				gameManager->nicknamepart = 'l';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_m) {
				gameManager->nicknamepart = 'm';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_n) {
				gameManager->nicknamepart = 'n';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_o) {
				gameManager->nicknamepart = 'o';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_p) {
				gameManager->nicknamepart = 'o';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_q) {
				gameManager->nicknamepart = 'q';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_r) {
				gameManager->nicknamepart = 'r';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_s) {
				gameManager->nicknamepart = 's';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_t) {
				gameManager->nicknamepart = 't';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_u) {
				gameManager->nicknamepart = 'u';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_v) {
				gameManager->nicknamepart = 'v';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_w) {
				gameManager->nicknamepart = 'w';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_x) {
				gameManager->nicknamepart = 'x';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_y) {
				gameManager->nicknamepart = 'y';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_z) {
				gameManager->nicknamepart = 'z';
			}
			else if (gameManager->event.key.keysym.sym == SDLK_RETURN) {
				gameManager->stage = HIGHSCORES;
			}
			break;
		case SDL_KEYUP:
			strncat(gameManager->nickname, &gameManager->nicknamepart, 1);
			break;
		case SDL_QUIT:
			gameManager->quit = 1;
			break;
		};
	};
}


void GameOverEventHandler(Game* gameManager) {
	while (SDL_PollEvent(&gameManager->event)) {
		switch (gameManager->event.type) {
		case SDL_KEYDOWN:
			if (gameManager->event.key.keysym.sym == SDLK_ESCAPE) gameManager->quit = 1;
			else if (gameManager->event.key.keysym.sym == SDLK_1) {
				gameManager->worldTime = 0;
				gameManager->stage = STAGE1; //trzeba zapisac wczesniej jaki to byl stage
			}
			else if (gameManager->event.key.keysym.sym == SDLK_2) {
				gameManager->worldTime = 0;
				gameManager->stage = MENU;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			gameManager->quit = 1;
			break;
		};
	};
}

void DrawGameOver(Game* gameManager) {
	sprintf(gameManager->text, "Game Over - przegrales/as");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 100, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "Wybierz na klawiaturze");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 120, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "1 - Sprobuj ponownie");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 140, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "2 - Wroc do menu");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 160, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "ESC - wyjdz");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 180, gameManager->text, gameManager->charset);
}

void DrawSaveHighScores(Game* gameManager, Player *player) {
	sprintf(gameManager->text, "Twoj wynik: %i", gameManager->finalScore); //edytowac
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 100, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "Wpisz na klawiaturze swoj nickname.");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 120, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "Twoj nickname: %s", gameManager->nickname); //edytowac
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 140, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "Wcisnij enter na klawiaturze, aby zapisac"); 
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 160, gameManager->text, gameManager->charset);
}

void StageWonHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	DrawStageWon(gameManager, player);
	Rendering(gameManager);
	StageWonEventHandler(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
}

void GameOverHandler(Game* gameManager, Player* player) {
	SDL_FillRect(gameManager->screen, NULL, gameManager->czarny);
	DrawGameOver(gameManager);
	Rendering(gameManager);
	GameOverEventHandler(gameManager);
}

void StageWonEventHandler(Game* gameManager, Player* player, Enemy* enemy1, Bullet* eBullets, Bullet* pBullets, Heart* heart, Timer *timer) {
	while (SDL_PollEvent(&gameManager->event)) {
		switch (gameManager->event.type) {
		case SDL_KEYDOWN:
			if (gameManager->event.key.keysym.sym == SDLK_ESCAPE) gameManager->quit = 1;
			else if (gameManager->event.key.keysym.sym == SDLK_1) {
				gameManager->worldTime = 0;
				InitializeA(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
				gameManager->stage = STAGE1; //next level dodac
			}
			else if (gameManager->event.key.keysym.sym == SDLK_2) {
				gameManager->worldTime = 0;
				InitializeA(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
				gameManager->stage = MENU;
			}
			else if (gameManager->event.key.keysym.sym == SDLK_3) {
				gameManager->worldTime = 0;
				InitializeA(gameManager, player, enemy1, eBullets, pBullets, heart, timer);
				gameManager->stage = SAVEHIGHSCORE;
			}
			break;
		case SDL_KEYUP:
			for (int i = 0; i < 30; i++) gameManager->nickname[i] = '\0';
			break;
		case SDL_QUIT:
			gameManager->quit = 1;
			break;
		};
	};
}

void DrawStageWon(Game* gameManager, Player* player) {
	sprintf(gameManager->text, "Gratulacje z okazji ukonczenia poziomu! Twoj score: %i Twoja ocena: %c", player->score, player->grade);
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 100, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "Wybierz na klawiaturze");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 120, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "1 - Przejdz do nastepnego poziomu");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 140, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "2 - Wroc do menu");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 160, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "3 - Zapisz wynik");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 180, gameManager->text, gameManager->charset);
	sprintf(gameManager->text, "ESC - wyjdz");
	DrawString(gameManager->screen, gameManager->screen->w / 2 - strlen(gameManager->text) * 8 / 2, 200, gameManager->text, gameManager->charset);
}

void PlayerBulletOverBoard(Game *gameManager, Player* player, Bullet* pBullets) {
	for (int i = 0; i <= player->shotNumber; i++) {
		if (pBullets[i].distanceToWall <= 0) pBullets[i].wall = true;
		if (pBullets[i].wall == true) pBullets[i].boomDelta += gameManager->delta;
	}
}

void EnemyBulletOverBoard(Game* gameManager, Bullet* eBullets) { //dodac naglowek funkcji na gore
	for (int i = 0; i < gameManager->eBulletsCounter; i++) {
		if (eBullets[i].hX > LEVEL_WIDTH) eBullets[i].wall = true;
		else if (eBullets[i].hX < 0) eBullets[i].wall = true;
		else if (eBullets[i].hY > LEVEL_HEIGHT) eBullets[i].wall = true;
		else if (eBullets[i].hY < 0) eBullets[i].wall = true;
		if (eBullets[i].wall == true) eBullets[i].boomDelta += gameManager->delta;
	}
}

void PlayerAnimationHandler(Game* gameManager) { //Player's moving animation
	gameManager->animationCounter += gameManager->delta;
	gameManager->frames++;
	if (gameManager->animationCounter > 0.2 && gameManager->animationHelper % 3 == 0) {
		gameManager->animationFrame = 1;
		gameManager->animationHelper++;
		gameManager->animationCounter = 0;
	}
	else if (gameManager->animationCounter > 0.2 && gameManager->animationHelper % 3 == 1) {
		gameManager->animationFrame = 2;
		gameManager->animationHelper++;
		gameManager->animationCounter = 0;
	}
	else if (gameManager->animationCounter > 0.2 && gameManager->animationHelper % 3 == 2) {
		gameManager->animationFrame = 3;
		gameManager->animationHelper++;
		gameManager->animationCounter = 0;
	}
}

void InvincibilityForPlayer(Game* gameManager, Player* player, Bullet* eBullets) { //InvincibilityFrames
	if (gameManager->iFramesP > 1) {
		if (PlayerHit(gameManager, player, eBullets)) {
			player->health -= 1;
			player->scoreMultiplier = 1;
			if (player->score < 10) {
				player->score = 0;
				gameManager->iFramesP = 0;
			}
			else
				player->score -= 10;
			gameManager->iFramesP = 0;
		}
	}
	else gameManager->iFramesP += gameManager->delta;
}