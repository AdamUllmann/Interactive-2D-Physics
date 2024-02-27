#include "raylib.h"
#include <stdlib.h>

struct Ball {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float radius;
    Color color;
};

#define NUM_BALLS 1000

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "physics 2D");
    Ball balls[NUM_BALLS];
    for (int i = 0; i < NUM_BALLS; i++) {
        balls[i].position = { (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) };
        balls[i].velocity = { (float)GetRandomValue(-200, 200), (float)GetRandomValue(-200, 200) };
        balls[i].acceleration = { 0.0f, -500.0f };
        balls[i].radius = (float)GetRandomValue(10, 30);
        balls[i].color = { unsigned char(GetRandomValue(0, 255)), unsigned char(GetRandomValue(0, 255)), unsigned char(GetRandomValue(0, 255)), 255 };
    }
    bool isDragging = false;
    int draggedBallIndex = -1;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < NUM_BALLS; i++) {
                if (CheckCollisionPointCircle(GetMousePosition(), balls[i].position, balls[i].radius)) {
                    isDragging = true;
                    draggedBallIndex = i;
                    break;
                }
            }
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (isDragging) {
                balls[draggedBallIndex].velocity.x = (GetMouseX() - balls[draggedBallIndex].position.x) / deltaTime;
                balls[draggedBallIndex].velocity.y = -((GetMouseY() - balls[draggedBallIndex].position.y) / deltaTime);
                isDragging = false;
            }
        }
        if (isDragging) {
            balls[draggedBallIndex].position.x = GetMouseX();
            balls[draggedBallIndex].position.y = GetMouseY();
        }
        for (int i = 0; i < NUM_BALLS; i++) {
            balls[i].velocity.x += balls[i].acceleration.x * deltaTime;
            balls[i].velocity.y += balls[i].acceleration.y * deltaTime;
            balls[i].position.x += balls[i].velocity.x * deltaTime;
            balls[i].position.y -= balls[i].velocity.y * deltaTime;
            if (balls[i].position.y >= screenHeight - balls[i].radius) {
                balls[i].position.y = screenHeight - balls[i].radius;
                balls[i].velocity.y *= -1.0f;
                balls[i].velocity.y -= 100;
            }
            if (balls[i].position.x >= screenWidth - balls[i].radius) {
                balls[i].position.x = screenWidth - balls[i].radius;
                balls[i].velocity.x *= -1.0f;
                balls[i].velocity.x += 100;
            }
            if (balls[i].position.x <= balls[i].radius) {
                balls[i].position.x = balls[i].radius;
                balls[i].velocity.x *= -1.0f;
                balls[i].velocity.x -= 100;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < NUM_BALLS; i++) {
            DrawCircleV(balls[i].position, balls[i].radius, balls[i].color);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
