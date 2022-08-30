#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>

#include <Demo_Drawing.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

struct DemoProfile {
    std::string name;
    std::string description;
};

int main(int argc, char **argv) {
    GalaEngine::Game *game = nullptr;

    bool skipmenu = false;

    InitWindow(720, 540, "GalaEngine Demos");
    SetTargetFPS(60);

    GuiLoadStyle("./res/guistyles/dark.rgs");

    Texture tex_banner = LoadTexture("./res/tex/spr_banner.png");

    std::map<std::string, DemoProfile> profiles = {
        {"drawing", 
            DemoProfile {
                "Surface Drawing",
                "Drawing to surfaces with\nGalaEngine::Surface::Draw*() functions."
            }
        },
        {"layers",
            DemoProfile {
                "Scene Layers",
                "Demonstrates scene layers and effects."}
        },
        {"entities", 
            DemoProfile {
                "Entities",
                "Demonstrates entity logic."
            }
        },
        {"pixelcam",
            DemoProfile {
                "Pixelated Graphics",
                "Demonstrates pixelated graphics achieved with\nwindow surface scaling."
            }
        }
    };

    std::string currentProfile = "drawing";

    if(argc == 2) {
        if(profiles.find(std::string(argv[1])) != profiles.end()) {
            currentProfile = std::string(argv[1]);
            skipmenu = true;
        }
    }

    int btn_launch = false;

    while(!WindowShouldClose()) {
        // Logic
        if(IsKeyPressed(KEY_ONE)) {
            game = new Demo_Drawing();
        }

        // Drawing
        BeginDrawing();
        ClearBackground(C_BLACK);

        DrawTextEx(GuiGetFont(), "GalaEngine v" GALAENGINE_VERSION_STRING, {564.0f, 72.0f}, 16, 0.0f, C_WHITE);
        DrawTexture(tex_banner, 32, 16, C_WHITE);

        // Panel
        GuiPanel(Rectangle {
            32.0f, 96.0f,
            720.0f - 64.0f, 416.0f
        }, "Select a demo");

        // Buttons
        int i = 0;
        for(auto &p : profiles) {
            Rectangle btnRec = {
                64.0f, 176.0f + 40.0f * i,
                256.0f, 32.0f
            };

            if(currentProfile == p.first) {
                DrawRectangleRec(Rectangle {
                    btnRec.x - 31.0f,
                    btnRec.y - 4.0f,
                    btnRec.width + 64.0f,
                    btnRec.height + 8.0f
                }, C_GALARED);
            }

            bool btn_clicked = GuiButton(btnRec, p.second.name.c_str());

            if(btn_clicked) {
                currentProfile = p.first;
            }

            i++;
        }

        // Drawing description
        GuiPanel(Rectangle {
            720.0f - 368.0f, 136.0f,
            320.0f, 320.0f
        }, "Description");

        DrawTextEx(
            GuiGetFont(),
            profiles[currentProfile].description.c_str(),
            Vector2 {
                720.0f - 368.0f + 8.0f,
                168.0f
            },
            16.0f, 0.0f, C_WHITE
        );

        // Draw launch button
        btn_launch = GuiButton(Rectangle {
            480.0f, 466.0f,
            192.0f, 32.0f
        }, "Launch Demo");

        EndDrawing();

        // If demo is selected...
        if(btn_launch || skipmenu) {
            if(currentProfile == "drawing") {
                game = new Demo_Drawing();
            }
        }

        if(game != nullptr) {
            UnloadTexture(tex_banner);
            CloseWindow();
            game->Start();
        }
    }

    return 0;
}
