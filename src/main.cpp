#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "swatch.h"

using namespace std;

// Program variables
bool hideUI = false;
bool moveMode = true;
float swatchDimensions = 200;
float brushRadius = 25;
Color pickedColor = WHITE;  // Starting color picker color

void ChangeBool();
void DrawBrush();
void ColorPicker();
void SelectionButtons();
void BrushSize();



int main(void) {
    InitWindow(0, 0, "BlendIn");

    // Sets window to borderless fullscreen
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);
    SetWindowState(FLAG_WINDOW_UNDECORATED); // Removes title bar

    SetTargetFPS(60);

    HideCursor();

    Swatch swatch(GetScreenWidth() / 2 - swatchDimensions / 2, GetScreenHeight() / 2 - swatchDimensions / 2, swatchDimensions, swatchDimensions, 5);
    cout << swatch.x << ", " << swatch.y << ", " << swatch.width << ", " << swatch.height << ", " << endl;
    
    

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

// ART
//------------------------------------------------------------------------------------------------------------------------------------------------------------
        if(moveMode) {
            swatch.Update();
        }
        swatch.Draw();

// UI
//------------------------------------------------------------------------------------------------------------------------------------------------------------
        DrawBrush();
        ColorPicker();
        SelectionButtons();
        BrushSize();
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void ChangeBool(bool & boolean) {
    if(boolean) {
        boolean = false;
    } else {
        boolean = true;
    }
}

void DrawBrush() {
    if(!hideUI) {
        DrawRing(GetMousePosition(), brushRadius - 1, brushRadius, 0, 360, brushRadius, WHITE);
    }
}

void ColorPicker() {
    if(!hideUI) {
        GuiColorPicker((Rectangle){ 20, 20, 300, 300 }, "", &pickedColor);
        DrawRectangle(20, 340, 50, 50, pickedColor);
    }
}

void SelectionButtons() {
    // Num keybinds
    if(IsKeyPressed(KEY_ONE)) {
        ChangeBool(hideUI);
    }
    if(IsKeyPressed(KEY_TWO)) {
        ChangeBool(moveMode);
    }

    // Interaction Buttons
    if(hideUI) {
        if(GuiButton((Rectangle){20, 20, 100, 30}, "Show UI (1)")){
            ChangeBool(hideUI);
        }
    } else {
        if(GuiButton((Rectangle){350, 20, 100, 30}, "Hide UI (1)")){
            ChangeBool(hideUI);
        }


        // Move Mode interactions and UI
        if(GuiButton((Rectangle){350, 70, 100, 30}, "Move Mode (2)")) {
            ChangeBool(moveMode);
        }

        if(moveMode) {
            DrawText("Move mode: Unlocked", GetScreenWidth() / 3, 20, 30, GREEN);
        } else {
            DrawText("Move mode: Locked", GetScreenWidth() / 3, 20, 30, RED);
        }
    }
}

void BrushSize() {
    if(!hideUI) {
        GuiSlider((Rectangle){20, 410, 200, 20}, "", "", &brushRadius, 1, swatchDimensions / 2);
        DrawText(TextFormat("%.0f", brushRadius), 230, 410, 20, GRAY);
    }
}

