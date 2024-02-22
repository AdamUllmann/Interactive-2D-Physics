#include "raylib.h"

struct Ball {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float radius;
};

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "physics 2D");
    Ball ball;
    ball.position = { 50.0f, 50.0f };
    ball.velocity = { 100.0f, 0.0f };
    ball.acceleration = { 0.0f, -500.0f };
    ball.radius = 20.0f;
    bool isDragging = false;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointCircle(GetMousePosition(), ball.position, ball.radius)) {
                isDragging = true;
            }
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (isDragging) {
                ball.velocity.x = (GetMouseX() - ball.position.x) / deltaTime;
                ball.velocity.y = -((GetMouseY() - ball.position.y) / deltaTime);

                isDragging = false;
            }
        }
        if (isDragging) {
            ball.position.x = GetMouseX();
            ball.position.y = GetMouseY();
        }
        if (!isDragging) {
            ball.velocity.x += ball.acceleration.x * deltaTime;
            ball.velocity.y += ball.acceleration.y * deltaTime;
            ball.position.x += ball.velocity.x * deltaTime;
            ball.position.y -= ball.velocity.y * deltaTime;
            if (ball.position.y >= screenHeight - ball.radius) {
                ball.position.y = screenHeight - ball.radius;
                ball.velocity.y *= -1.0f;
                ball.velocity.y -= 100;
            }
            if (ball.position.x >= screenWidth - ball.radius) {
                ball.position.x = screenWidth - ball.radius;
                ball.velocity.x *= -1.0f;
                ball.velocity.x += 100;
            }
            if (ball.position.x <= ball.radius) {
                ball.position.x = ball.radius;
                ball.velocity.x *= -1.0f;
                ball.velocity.x -= 100;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(ball.position, ball.radius, BLUE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
