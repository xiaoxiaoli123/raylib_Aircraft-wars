#include "raylib.h"
#include "Constants.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

struct Game
{
    Player player;
    Enemy enemy[ENEMY_NUM];
    Bullet bullet[BULLET_NUM];

    Texture tbk;
    Texture tplayer;
    Texture tbullet;
    Texture tenemy1;
    Texture tenemy2;

    Music bkmusic;
    Sound blWav;
};

//create the Hp for enemies
void enemyType(Game* game, int i)
{
    if (GetRandomValue(0, 10) % 10 == 0) 
    {
        game->enemy[i].type = SMALL;
        game->enemy[i].hp = 1;
        game->enemy[i].width = 57;
        game->enemy[i].height = 43;
    }
    else
    {
        game->enemy[i].type = BIG;
        game->enemy[i].hp = 3;
        game->enemy[i].width = 69;
        game->enemy[i].height = 99;
    }
}

void gameInit(Game* game)
{
    game->tbk = LoadTexture("Asset/background.png");
    game->tplayer = LoadTexture("Asset/me1.png");
    game->tbullet = LoadTexture("Asset/bullet1.png");
    game->tenemy1 = LoadTexture("Asset/enemy1.png");
    game->tenemy2 = LoadTexture("Asset/enemy2.png");

    game->bkmusic = LoadMusicStream("Sound/game_music.ogg");
    game->blWav = LoadSound("Sound/bullet.wav");
    
    game->player.x = screenWidth / 2 - 60;
    game->player.y = screenHeight - 120;
    game->player.live = true;

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        game->enemy[i].live = false;
        enemyType(game, i);
    }

    for (int i = 0; i < BULLET_NUM; i++)
    {
        game->bullet[i].x = 0;
        game->bullet[i].y = 0;
        game->bullet[i].live= false;
    }

    PlayMusicStream(game->bkmusic);
    SetMusicVolume(game->bkmusic, 0.2f);
    SetSoundVolume(game->blWav, 0.5f);
}

void createBullet(Game* game)
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (!game->bullet[i].live)
        {
            game->bullet[i].x = game->player.x + 50;
            game->bullet[i].y = game->player.y;
            game->bullet[i].live = true;
            break; // press key once, shoot one bullet, so "break" should be used here
        }
    }
}

void bulletMove(Game* game)
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (game->bullet[i].live) 
        {
            game->bullet[i].y -= 10;
            if (game->bullet[i].y < 0) 
            {
                game->bullet[i].live = false;
            }
        }
    }
}

void playerMove(Game* game, int speed) 
{
    if (IsKeyDown(KEY_UP))
    {
        if (game->player.y > 0)
        {
            game->player.y -= speed;
        }
    }
    if (IsKeyDown(KEY_DOWN))
    {
        if (game->player.y < (screenHeight - 120))
        {
            game->player.y += speed;
        }
    }
    if (IsKeyDown(KEY_LEFT))
    {
        if (game->player.x > 0)
        {
            game->player.x -= speed;
        }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        if (game->player.x < (screenWidth - 80))
        {
            game->player.x += speed; 
        }
    }  

    static double t1 = 0, t2 = 0; // need time delay between two bullets
    if (IsKeyDown(KEY_SPACE) && t2 - t1 > 0.05)
    {            
        createBullet(game);
        t1 = t2;
    }
    t2 = GetTime();
}

void createEnemy(Game* game)
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (!game->enemy[i].live)
        {
            game->enemy[i].live = true;
            game->enemy[i].x = GetRandomValue(0, (screenWidth - 70));
            game->enemy[i].y = 0;
            enemyType(game, i); //need to create the hp for enemy, or it won't be created once is shoot by player
            break;
        }
    }
}

void enemyMove(Game* game, int speed)
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (game->enemy[i].live)
        {
            game->enemy[i].y += speed;
            if (game->enemy[i].y > screenHeight)
            {
                game->enemy[i].live = false;
            }
        }
    }
}

void collisionBullet(Game* game)
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (!game->enemy[i].live)
            continue;
        for (int k = 0; k < BULLET_NUM; k++)
        {
            if (!game->bullet[k].live)
                continue;
            if (game->bullet[k].x > game->enemy[i].x && game->bullet[k].x < game->enemy[i].x + game->enemy[i].width
                && game->bullet[k].y > game->enemy[i].y && game->bullet[k].y < game->enemy[i].y + game->enemy[i].height)
            {
                game->bullet[k].live = false;
                game->enemy[i].hp--;
            }
        }
        if (game->enemy[i].hp <= 0)
        {
            game->enemy[i].live = false;
        }
    }
}

void Drawing(Game *game)
{
    DrawTexture(game->tbk, 0, 0, WHITE);
    DrawTexture(game->tplayer, game->player.x, game->player.y, WHITE);

    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (game->bullet[i].live)
        {
            DrawTexture(game->tbullet, game->bullet[i].x, game->bullet[i].y, WHITE);
        }
    }

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (game->enemy[i].live)
        {
            if (game->enemy[i].type == BIG)
            {
                DrawTexture(game->tenemy1, game->enemy[i].x, game->enemy[i].y, WHITE);
            }
            else
            {
                DrawTexture(game->tenemy2, game->enemy[i].x, game->enemy[i].y, WHITE);
            }
        }
    }
}

int main(void)
{
    Game game = {};
    InitWindow(screenWidth, screenHeight, "aircraft wars");
    InitAudioDevice();

    gameInit(&game);

    SetTargetFPS(60);             

    while (!WindowShouldClose())    
    {
        UpdateMusicStream(game.bkmusic);   
   
        if (IsKeyPressed(KEY_SPACE)) 
            PlaySoundMulti(game.blWav);
        
        BeginDrawing();
       
        Drawing(&game);
       
        playerMove(&game, 5);
        bulletMove(&game);
 
        createEnemy(&game);       

        enemyMove(&game, 1);
        collisionBullet(&game);
        ClearBackground(RAYWHITE);

        EndDrawing();     
    }  
    
    UnloadTexture(game.tbk);
    UnloadTexture(game.tplayer);
    UnloadTexture(game.tbullet);
    UnloadTexture(game.tenemy1);
    UnloadTexture(game.tenemy2);

    StopSoundMulti();       
    UnloadMusicStream(game.bkmusic);  
    UnloadSound(game.blWav);
    CloseAudioDevice();       

    CloseWindow();       

    return 0;
}