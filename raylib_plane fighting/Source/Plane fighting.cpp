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
enum General //create the common constants
{
    screenWidth = 480,
    screenHeight = 700,
    BULLET_NUM = 15,//玩家子弹数量 the bullet number of player
    ENEMY_NUM = 10,//敌机数量 the maximum number of enemies on screen at the same time
    BIG,
    SMALL
};

struct Plane
{
    int x;
    int y;
    bool live;//是否存活 if the object live or not(player/ enemy)
    //int lifespawn;//解决子弹在屏幕上同时多个分布的问题 solve spawn many bullets on the screen at the same time
    int width; 
    int height;
    int hp;
    int type;//敌机类型 big/ small types of enemy (big/ small)
}player, bullet[BULLET_NUM], enemy[ENEMY_NUM];//类似于公共变量，括号后面不同的类可以直接用了  variables for different objectives 

//定大小敌机的血量 create the Hp for enemies)
void enemyHP(int i)
{
    if (GetRandomValue(1, 10) % 10 == 0) //0~9之间的随机数 random number between 0~9
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

void gameInit()//游戏初始化 initialization of the game
{
    player.x = screenWidth / 2 - 60;
    player.y = screenHeight - 120;
    player.live = true;

    //初始化子弹的状况 initialization of the bullet
    for (int i = 0; i < BULLET_NUM; i++)
    {
        //初始bullet开始的状态，如果是false的话没必要去画它 if bullet is dead, it's no need to draw it
        bullet[i].x = 0;
        bullet[i].y = 0;
        bullet[i].live = false;
        //bullet[i].lifespawn = 0;
    }

    //初始化敌机 initialization of the enemy
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].live = false;
        enemyHP(i);
    }
}

//创建子弹(因为后面玩家要一按键就创建一个子弹，playerMove里要引用这个函数，所以放在playerMove之前)create bullet (as it'll be called by the player, so it should be put before the player)
void createBullet()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        //如果子弹死了才能重新从飞机头部创建 the bullet can be created only after it dies, it should be created at the head of the player
        if (!bullet[i].live)
        {
            bullet[i].x = player.x + 50;
            bullet[i].y = player.y;
            bullet[i].live = true;
            break; //按一次键发射一次 press key once, shoot one bullet, so "break" should be used here
        }
    }
}

//让子弹移动 make the bullet move
void bulletMove()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (bullet[i].live) //子弹活着的时候才会动 bullet move only if it's alive
        {
            bullet[i].y -= 10;//只需要y轴的变化 moves only in the y axis
            if (bullet[i].y < 0) //如果子弹飞出屏幕，那么它就死了，这样才能创建出新的子弹 make bullet dead if it's out of the screen, then a new bullet can be created
            {
                bullet[i].live = false;
            }
        }
    }
}

//角色移动，用键盘上、下、左、右键控制 make the player move, use UP/DOWN/LEFT/RIGHT
void playerMove(int speed) //可以通过speed调节飞机速度 use "speed" to control the movement of player
{
    if (IsKeyDown(KEY_UP))
    {
        //处理边界，不让飞机飞到屏幕外去 deal with the borders, player can't go out of the screen
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

        static double t1 = 0, t2 = 0; // time delay between two bullets
        if (IsKeyDown(KEY_SPACE) && t2 - t1 > 0.05)
    {
                   
        createBullet();
        t1 = t2;
        // bullet life timer
       /* for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].live)
            {
                bullet[i].lifespawn++;
            }
        }*/
    }
    t2 = GetTime();
}

//产生敌机 create enemy
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

//敌机的移动(和bullet移动是一样的) make enemy move (same as bullet)
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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");//已经都帮我们写好了，直接修改上面的数值，获得所需窗口 already set by templete, just modified the data above
    gameInit();//玩家初始化不能放在while循环中，否则永远回到初始的位置，就移动不了了 it can't be in the loop, or it'll be in the initialized position forever, it can' move
    // 加载图片，注意要用texture load the pictures, use "texture" here
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
        //显示图片（因为一直要显示的，所以放在while循环里) show the pics (as they should show all the time, need to be put in the loop)
        DrawTexture(tbk, 0, 0, WHITE);
        DrawTexture(tplayer, player.x, player.y, WHITE);
        
        //绘制子弹，注意要判断为true时才绘制 draw bullet only when it's alive
        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].live)
            {
                DrawTexture(tbullet, bullet[i].x, bullet[i].y, WHITE); 
            }
        }

        //绘制敌机 draw enemy
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

        //static double t1, t2;//用定时器解决敌机不同时落下
        //if (t2 - t1 > 0.01)
        //{
        //    createEnemy();
        //    t1 = t2;
        //    
        //}
        //t2 = GetTime();
        createEnemy();
        enemyMove(1);
        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
      
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(tbk);//卸载图片，放在while循环外 unload the pics, they should be put outside the loop
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