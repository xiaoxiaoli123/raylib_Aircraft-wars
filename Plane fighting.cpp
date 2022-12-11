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
enum Screen //设置窗口大小
{
    screenWidth = 480,
    screenHeight = 700
};

struct Player
{
    int x;
    int y;
    bool live;//是否存活
}player;//结构体别名

void gameInit()//游戏初始化
{
    player.x = screenWidth / 2 - 60;
    player.y = screenHeight - 120;
    player.live = true;
}

//角色移动，用键盘上、下、左、右键控制
void playerMove(int speed) //可以通过speed调节飞机速度
{
    if (IsKeyDown(KEY_UP))
    {
        player.y -= speed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        player.y += speed;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        player.x -= speed;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        player.x += speed;
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
        playerMove(5);

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
      
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(tbk);//卸载图片，放在while循环外
    UnloadTexture(tplayer);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}