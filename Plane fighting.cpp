/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
enum General //设置窗口大小
{
    screenWidth = 480,
    screenHeight = 700,
    BULLET_NUM = 15,//玩家子弹的数量
    ENEMY_NUM = 10,//敌机数量
    BIG,
    SMALL
};

struct Plane
{
    int x;
    int y;
    bool live;//是否存活
    //int lifespawn;//解决子弹在屏幕上同时多个分布的问题
    int width; 
    int height;
    int hp;
    int type;//敌机类型 big/ small
}player, bullet[BULLET_NUM], enemy[ENEMY_NUM];//player结构体别名, 子弹直接放在这里

//定大小敌机的血量
void enemyHP(int i)
{
    if (GetRandomValue(1, 10) % 10 == 0) //0~9之间的随机数
    {
        enemy[i].type = BIG;
        enemy[i].hp = 3;
        enemy[i].width = 69;
        enemy[i].height = 99;
    }
    else
    {
        enemy[i].type = SMALL;
        enemy[i].hp = 1;
        enemy[i].width = 57;
        enemy[i].height = 43;
    }
}

void gameInit()//游戏初始化
{
    player.x = screenWidth / 2 - 60;
    player.y = screenHeight - 120;
    player.live = true;

    //初始化子弹的状况
    for (int i = 0; i < BULLET_NUM; i++)
    {
        //初始bullet开始的状态，如果是false的话没必要去画它
        bullet[i].x = 0;
        bullet[i].y = 0;
        bullet[i].live = false;
        //bullet[i].lifespawn = 0;
    }

    //初始化敌机
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].live = false;
        enemyHP(i);
    }
}

//创建子弹(因为后面玩家要一按键就创建一个子弹，playerMove里要引用这个函数，所以放在playerMove之前)
void createBullet()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        //如果子弹死了才能重新从飞机头部创建
        if (!bullet[i].live)
        {
            bullet[i].x = player.x + 50;
            bullet[i].y = player.y;
            bullet[i].live = true;
            break; //按一次键发射一次
        }
    }
}

//让子弹移动
void bulletMove()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (bullet[i].live) //子弹活着的时候才会动
        {
            bullet[i].y -= 10;//只需要y轴的变化
            if (bullet[i].y < 0) //如果子弹飞出屏幕，那么它就死了，这样才能创建出新的子弹
            {
                bullet[i].live = false;
            }
        }
    }
}

//角色移动，用键盘上、下、左、右键控制
void playerMove(int speed) //可以通过speed调节飞机速度
{
    if (IsKeyDown(KEY_UP))
    {
        //处理边界，不让飞机飞到屏幕外去
        if (player.y > 0)
        {
            player.y -= speed;
        }
    }
    if (IsKeyDown(KEY_DOWN))
    {
        if (player.y < (screenHeight - 120))
        {
            player.y += speed;
        }
    }
    if (IsKeyDown(KEY_LEFT))
    {
        if (player.x > -30)
        {
            player.x -= speed;
        }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        if (player.x < (screenWidth - 80))
        {
            player.x += speed; 
        }
    }

    if (IsKeyDown(KEY_SPACE))
    {
        createBullet();
        
        // bullet life timer
       /* for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].live)
            {
                bullet[i].lifespawn++;
            }
        }*/
    }
}

//产生敌机
void createEnemy()
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (!enemy[i].live)
        {
            enemy[i].live = true;
            enemy[i].x = GetRandomValue(0, (screenWidth - 70));
            enemy[i].y = 0;
            break;
        }
    }
}

//敌机的移动(和bullet移动是一样的)
void enemyMove(int speed)
{
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        if (enemy[i].live)
        {
            enemy[i].y += speed;
            if (enemy[i].y > screenHeight)
            {
                enemy[i].live = false;
            }
        }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");//已经都帮我们写好了，直接修改上面的数值，获得所需窗口
    gameInit();//玩家初始化不能放在while循环中，否则永远回到初始的位置，就移动不了了
    // 加载图片，注意要用texture
    Texture tbk = LoadTexture("background.png");//背景
    Texture tplayer = LoadTexture("me1.png");//玩家
    Texture tbullet = LoadTexture("bullet1.png");//子弹   
    Texture tenemy1 = LoadTexture("enemy1.png");//小敌机
    Texture tenemy2 = LoadTexture("enemy2.png");//大敌机

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //显示图片（因为一直要显示的，所以放在while循环里）
        DrawTexture(tbk, 0, 0, WHITE);
        DrawTexture(tplayer, player.x, player.y, WHITE);
        
        //绘制子弹，注意要判断为true时才绘制
        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].live)
            {
                DrawTexture(tbullet, bullet[i].x, bullet[i].y, WHITE); 
            }
        }

        //绘制敌机
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (enemy[i].live)
            {
                if (enemy[i].type == BIG)
                {
                    DrawTexture(tenemy1, enemy[i].x, enemy[i].y, WHITE);
                }
                else
                {
                    DrawTexture(tenemy2, enemy[i].x, enemy[i].y, WHITE);
                }
            }
        }
        playerMove(5);
        bulletMove();
        createEnemy();
        enemyMove(1);
        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
      
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(tbk);//卸载图片，放在while循环外
    UnloadTexture(tplayer);
    UnloadTexture(tbullet);
    UnloadTexture(tenemy1);
    UnloadTexture(tenemy2);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}