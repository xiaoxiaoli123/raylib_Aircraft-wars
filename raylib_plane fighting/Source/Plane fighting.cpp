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
    BULLET_NUM = 15,//����ӵ����� the bullet number of player
    ENEMY_NUM = 10,//�л����� the maximum number of enemies on screen at the same time
    BIG,
    SMALL
};

struct Plane
{
    int x;
    int y;
    bool live;//�Ƿ��� if the object live or not(player/ enemy)
    //int lifespawn;//����ӵ�����Ļ��ͬʱ����ֲ������� solve spawn many bullets on the screen at the same time
    int width; 
    int height;
    int hp;
    int type;//�л����� big/ small types of enemy (big/ small)
}player, bullet[BULLET_NUM], enemy[ENEMY_NUM];//�����ڹ������������ź��治ͬ�������ֱ������  variables for different objectives 

//����С�л���Ѫ�� create the Hp for enemies)
void enemyHP(int i)
{
    if (GetRandomValue(1, 10) % 10 == 0) //0~9֮�������� random number between 0~9
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

void gameInit()//��Ϸ��ʼ�� initialization of the game
{
    player.x = screenWidth / 2 - 60;
    player.y = screenHeight - 120;
    player.live = true;

    //��ʼ���ӵ���״�� initialization of the bullet
    for (int i = 0; i < BULLET_NUM; i++)
    {
        //��ʼbullet��ʼ��״̬�������false�Ļ�û��Ҫȥ���� if bullet is dead, it's no need to draw it
        bullet[i].x = 0;
        bullet[i].y = 0;
        bullet[i].live = false;
        //bullet[i].lifespawn = 0;
    }

    //��ʼ���л� initialization of the enemy
    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].live = false;
        enemyHP(i);
    }
}

//�����ӵ�(��Ϊ�������Ҫһ�����ʹ���һ���ӵ���playerMove��Ҫ����������������Է���playerMove֮ǰ)create bullet (as it'll be called by the player, so it should be put before the player)
void createBullet()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        //����ӵ����˲������´ӷɻ�ͷ������ the bullet can be created only after it dies, it should be created at the head of the player
        if (!bullet[i].live)
        {
            bullet[i].x = player.x + 50;
            bullet[i].y = player.y;
            bullet[i].live = true;
            break; //��һ�μ�����һ�� press key once, shoot one bullet, so "break" should be used here
        }
    }
}

//���ӵ��ƶ� make the bullet move
void bulletMove()
{
    for (int i = 0; i < BULLET_NUM; i++)
    {
        if (bullet[i].live) //�ӵ����ŵ�ʱ��Żᶯ bullet move only if it's alive
        {
            bullet[i].y -= 10;//ֻ��Ҫy��ı仯 moves only in the y axis
            if (bullet[i].y < 0) //����ӵ��ɳ���Ļ����ô�������ˣ��������ܴ������µ��ӵ� make bullet dead if it's out of the screen, then a new bullet can be created
            {
                bullet[i].live = false;
            }
        }
    }
}

//��ɫ�ƶ����ü����ϡ��¡����Ҽ����� make the player move, use UP/DOWN/LEFT/RIGHT
void playerMove(int speed) //����ͨ��speed���ڷɻ��ٶ� use "speed" to control the movement of player
{
    if (IsKeyDown(KEY_UP))
    {
        //����߽磬���÷ɻ��ɵ���Ļ��ȥ deal with the borders, player can't go out of the screen
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

//�����л� create enemy
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

//�л����ƶ�(��bullet�ƶ���һ����) make enemy move (same as bullet)
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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");//�Ѿ���������д���ˣ�ֱ���޸��������ֵ��������贰�� already set by templete, just modified the data above
    gameInit();//��ҳ�ʼ�����ܷ���whileѭ���У�������Զ�ص���ʼ��λ�ã����ƶ������� it can't be in the loop, or it'll be in the initialized position forever, it can' move
    // ����ͼƬ��ע��Ҫ��texture load the pictures, use "texture" here
    Texture tbk = LoadTexture("background.png");//����
    Texture tplayer = LoadTexture("me1.png");//���
    Texture tbullet = LoadTexture("bullet1.png");//�ӵ�   
    Texture tenemy1 = LoadTexture("enemy1.png");//С�л�
    Texture tenemy2 = LoadTexture("enemy2.png");//��л�

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
        //��ʾͼƬ����ΪһֱҪ��ʾ�ģ����Է���whileѭ����) show the pics (as they should show all the time, need to be put in the loop)
        DrawTexture(tbk, 0, 0, WHITE);
        DrawTexture(tplayer, player.x, player.y, WHITE);
        
        //�����ӵ���ע��Ҫ�ж�Ϊtrueʱ�Ż��� draw bullet only when it's alive
        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bullet[i].live)
            {
                DrawTexture(tbullet, bullet[i].x, bullet[i].y, WHITE); 
            }
        }

        //���Ƶл� draw enemy
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

        //static double t1, t2;//�ö�ʱ������л���ͬʱ����
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
    UnloadTexture(tbk);//ж��ͼƬ������whileѭ���� unload the pics, they should be put outside the loop
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