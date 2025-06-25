#include "../include/raylib.h"
#include "../include/raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FRAMERATE 60

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct {
    float movspeed;
    float rotspeed;

} Player;

void UpdatePlayer(Player *player, Vector2 *pos, Vector2 *dir, Vector2 *plane, float dt) {
    if (IsKeyDown(KEY_W)) {
        if (worldMap[(int)(pos->x + dir->x * player->movspeed * dt)][(int)pos->y] == 0)
            pos->x += dir->x * player->movspeed * dt;
        if (worldMap[(int)pos->x][(int)(pos->y + dir->y * player->movspeed * dt)] == 0)
            pos->y += dir->y * player->movspeed * dt;
    }

    if (IsKeyDown(KEY_S)) {
        if (worldMap[(int)(pos->x - dir->x * player->movspeed * dt)][(int)pos->y] == 0)
            pos->x -= dir->x * player->movspeed * dt;
        if (worldMap[(int)pos->x][(int)(pos->y - dir->y * player->movspeed * dt)] == 0)
            pos->y -= dir->y * player->movspeed * dt;
    }

    if (IsKeyDown(KEY_D)) {
        float oldDirX = dir->x;
        dir->x = dir->x * cos(-player->rotspeed * dt) - dir->y * sin(-player->rotspeed * dt);
        dir->y = oldDirX * sin(-player->rotspeed * dt) + dir->y * cos(-player->rotspeed * dt);

        float oldPlaneX = plane->x;
        plane->x = plane->x * cos(-player->rotspeed * dt) - plane->y * sin(-player->rotspeed * dt);
        plane->y = oldPlaneX * sin(-player->rotspeed * dt) + plane->y * cos(-player->rotspeed * dt);
    }

    if (IsKeyDown(KEY_A)) {
        float oldDirX = dir->x;
        dir->x = dir->x * cos(player->rotspeed * dt) - dir->y * sin(player->rotspeed * dt);
        dir->y = oldDirX * sin(player->rotspeed * dt) + dir->y * cos(player->rotspeed * dt);

        float oldPlaneX = plane->x;
        plane->x = plane->x * cos(player->rotspeed * dt) - plane->y * sin(player->rotspeed * dt);
        plane->y = oldPlaneX * sin(player->rotspeed * dt) + plane->y * cos(player->rotspeed * dt);
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raycaster");
    SetTargetFPS(TARGET_FRAMERATE);

    Vector2 pos = {22.0f, 12.0f};
    Vector2 dir = {-1, 0};
    Vector2 plane = {0, 0.66f};

    Vector2 camera = {0, 0};
    Vector2 rayDir = {0, 0};

    Vector2 map = {0, 0};
    Vector2 sideDist = {0, 0};
    Vector2 deltaDist = {0, 0};

    float time = 0.0f;
    float oldTime = 0.0f;

    Player player = {5.0f, 3.0f};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        UpdatePlayer(&player, &pos, &dir, &plane, dt);
        BeginDrawing();

        ClearBackground(BLACK);
        // calculating rays
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            camera.x = 2 * x / (float)SCREEN_WIDTH - 1;
            rayDir.x = dir.x + plane.x * camera.x;
            rayDir.y = dir.y + plane.y * camera.x;

            map.x = (int)pos.x;
            map.y = (int)pos.y;

            deltaDist.x = (rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x);
            deltaDist.y = (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y);

            float perpWallDist;
            Vector2 step = {0, 0};
            int hit = 0;
            int side;

            if (rayDir.x < 0) {
                step.x = -1;
                sideDist.x = (pos.x - map.x) * deltaDist.x;
            } else {
                step.x = 1;
                sideDist.x = (map.x + 1.0 - pos.x) * deltaDist.x;
            }

            if (rayDir.y < 0) {
                step.y = -1;
                sideDist.y = (pos.y - map.y) * deltaDist.y;
            } else {
                step.y = 1;
                sideDist.y = (map.y + 1.0 - pos.y) * deltaDist.y;
            }

            // dda algorithm
            // increment ray with 1 square every time until a wall is hit
            while (hit == 0) {
                if (sideDist.x < sideDist.y) {
                    sideDist.x += deltaDist.x;
                    map.x += step.x;
                    side = 0;
                } else {
                    sideDist.y += deltaDist.y;
                    map.y += step.y;
                    side = 1;
                }
                // hit a wall
                if (worldMap[(int)map.x][(int)map.y] > 0) hit = 1;
            }

            if (side == 0) {
                perpWallDist = (sideDist.x - deltaDist.x);
            } else {
                perpWallDist = (sideDist.y - deltaDist.y);
            }
            // height of wall on screen
            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
            // lowest and highest pixel to fill
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) {
                drawStart = 0;
            }
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) {
                drawEnd = SCREEN_HEIGHT - 1;
            }

            Color color;
            switch (worldMap[(int)map.x][(int)map.y]) {
                case 1:
                    color = RED;
                    break;
                case 2:
                    color = GREEN;
                    break;
                case 3:
                    color = BLUE;
                    break;
                case 4:
                    color = RAYWHITE;
                    break;
                default:
                    color = YELLOW;
                    break;
            }
            if (side == 1) {
                color.r = color.r / 2;
                color.g = color.g / 2;
                color.b = color.b / 2;
            }
            DrawLine(x, drawStart, x, drawEnd, color);
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
