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
enum Screen //���ô��ڴ�С
{
    screenWidth = 480,
    screenHeight = 700
};

struct Player
{
    int x;
    int y;
    bool live;//�Ƿ���
}player;//�ṹ�����

void gameInit()//��Ϸ��ʼ��
{
    player.x = screenWidth / 2 - 60;
    player.y = screenHeight - 120;
    player.live = true;
}

//��ɫ�ƶ����ü����ϡ��¡����Ҽ�����
void playerMove(int speed) //����ͨ��speed���ڷɻ��ٶ�
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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");//�Ѿ���������д���ˣ�ֱ���޸��������ֵ��������贰��
    gameInit();//��ҳ�ʼ�����ܷ���whileѭ���У�������Զ�ص���ʼ��λ�ã����ƶ�������
    // ����ͼƬ��ע��Ҫ��texture
    Texture tbk = LoadTexture("background.png");//����
    Texture tplayer = LoadTexture("me1.png");//���
    
    
    

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
        //��ʾͼƬ����ΪһֱҪ��ʾ�ģ����Է���whileѭ���
        DrawTexture(tbk, 0, 0, WHITE);
        DrawTexture(tplayer, player.x, player.y, WHITE);
        playerMove(5);

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
      
        //----------------------------------------------------------------------------------
    }
    UnloadTexture(tbk);//ж��ͼƬ������whileѭ����
    UnloadTexture(tplayer);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}