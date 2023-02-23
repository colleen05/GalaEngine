#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <map>

#include <Demos.hpp>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

struct DemoProfile {
    std::string name;
    std::string description;
};

std::vector<std::pair<std::string, DemoProfile>>::iterator
find_by_name(
    std::vector<std::pair<std::string, DemoProfile>> &vec,
    const std::string &name
) {
    for(auto i = 0; i < vec.size(); i++) {
        if(vec[i].first == name)
            return vec.begin() + i;
    }

    return vec.end();
}

int main(int argc, char **argv) {
    GalaEngine::Game *game = nullptr;

    bool skipmenu = false;

    InitWindow(720, 540, "GalaEngine Demos");
    SetTargetFPS(60);

    GuiLoadStyle("./resources/guistyles/dark.rgs");

    Texture tex_banner = LoadTexture("./resources/spr_banner.png");

    std::vector<std::pair<std::string, DemoProfile>> profiles = {
        {"drawing", 
            DemoProfile {
                "Surface Drawing",
                "Drawing to surfaces with\nGalaEngine::Surface::Draw*() functions."
            }
        },
        {"assets", 
            DemoProfile {
                "Asset Management",
                "Simple asset management via\nGalaEngine::AssetManager class."
            }
        },
        {"scene",
            DemoProfile {
                "Scene",
                "A simple scene with a few layers and entities."
            }
        },
        {"tiles",
            DemoProfile {
                "Tiles",
                "Demonstrates tileset and tilemap features."
            }
        },
        {"radio",
            DemoProfile {
                "Sound Management",
                "Demonstrates use of GalaEngine::SoundManager\nclass with a music player interface."
            }
        },
        {"input",
            DemoProfile {
                "Input & Binding",
                "Demonstrates use of GalaEngine::InputManager\nfor detecting and binding input, with GUI."
            }
        },
        {"window",
            DemoProfile {
                "Window",
                "Demonstrates management of window via\nGalaEngine::Window functions."
            }
        }
    };

    std::string currentProfile = "drawing";

    if(argc == 2) {
        if(find_by_name(profiles, std::string(argv[1])) != profiles.end()) {
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

        const std::string versionText = "GalaEngine v" GALAENGINE_VERSION_STRING;
        const int versionTextWidth = MeasureTextEx(GuiGetFont(), versionText.c_str(), 16, 0.0f).x;
        DrawTextEx(GuiGetFont(), versionText.c_str(), {696.0f - versionTextWidth - 8.0f, 72.0f}, 16, 0.0f, C_WHITE);
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
            (*find_by_name(profiles, currentProfile)).second.description.c_str(),
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
            }else if(currentProfile == "scene") {
                game = new Demo_Scene();
            }else if(currentProfile == "tiles") {
                game = new Demo_Tiles();
            }else if(currentProfile == "assets") {
                game = new Demo_Assets();
            }else if(currentProfile == "radio") {
                game = new Demo_Radio();
            }else if(currentProfile == "input") {
                game = new Demo_Input();
            }else if(currentProfile == "window") {
                game = new Demo_Window();
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
