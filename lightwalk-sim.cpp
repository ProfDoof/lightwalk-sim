//============================================================================
// Name        : lightwalk-sim.cpp
// Author      : Brent Neal Reeves
// Version     :
// Copyright   : (c) 2017 all rights reserved
// Description : simulate lightwalk effects
// ToDo        : load all effects and choose via command line option
//             :   but effect files have conflicting symbols (#DEFINE DURATION)
//             :
//============================================================================
// mac os x
// g++ -std=c++11 -stdlib=libc++ -o go -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -framework Cocoa lightwalk-sim.cpp
//
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "cxxopts.hpp"
#include "lib/constants.h"
#include "lib/sim.h"
#include "lib/node.cpp"
using namespace std;

#define radian2degree(a) (a * 57.295779513082)
#define degree2radian(a) (a * 0.017453292519)

// top left corner of window is 0,0
const int PIXEL_HEIGHT = 3, PIXEL_WIDTH = 2, PIXEL_SPACING_X = 3, PIXEL_SPACING_Y = 8;
const int WINDOW_REED_START = 10 + (PIXEL_COUNT * (PIXEL_HEIGHT + PIXEL_SPACING_Y));
const int WINDOW_HEIGHT = WINDOW_REED_START + 30;
const int NODEWIDTH = 30 + ((PIXEL_WIDTH + PIXEL_SPACING_X) * 10);
//const int NODE_COUNT = 13; // change this in constants.h
const int WINDOW_WIDTH = NODE_COUNT * NODEWIDTH;

// ----------------------------------------------------------------------------------------------------------
// choose an effect here by uncommenting something
// a wee bit subtle... need to include these files up here before other things have seen the compiler.
// and sometimes only include one at a time due to #defines.
// ----------------------------------------------------------------------------------------------------------

//#include "lib/WaveUp.cpp"
//WaveUp e = WaveUp(0, 0, 255, 0, 255, 1);

//#include "lib/WaveDown.cpp"
//WaveDown e = WaveDown(0, 0, 255, 0, 0, 10);

//needs more sim-time so we can watch node zero wink back out
//#include "lib/WaveSide.cpp"
//WaveSide e = WaveSide(0, 0, 255, 0, 0, 0, 10); // r,g,b,  direction (0 is right), velocity

//#include "lib/Breathe.cpp"
//Breathe e = Breathe(0, 0, 0, 255, 0, 0);

//#include "lib/Starfield.cpp"
//Starfield e = Starfield(0, 0, 0, 0, 255, 1, 1); // id, time,  r,g,b, density, speed 0 is slow, 10 is fast

// #include "lib/AcidRain.cpp"
// #include "lib/WaveSide.cpp"
// #include "lib/RainbowRain.cpp"
// #include "lib/SplishSplash.cpp"
// #include "lib/Bubbles.cpp"
//#include "lib/Magneto.cpp"
#include "lib/Power.cpp"
// #include "lib/WhackAMole.cpp"
// #include "lib/Shimmer.cpp"
// #include "lib/TugOfWar.cpp"
// #include "lib/Rainbow.cpp"

// =============================================================================================
// main
// =============================================================================================
int main(int argc, char *argv[])
{

    int someTime = 5;
    int speed = 3;
    bool wait = false;
    bool dump = false;
    bool pizza = false;
    bool verbose = false;
    int rgb_r = 0;
    int rgb_g = 250;
    int rgb_b = 0;

    try
    {
      //        cout << " before options... verbose " << verbose << endl;

        cxxopts::Options options(argv[0], " - command line options");
        options.add_options()("help", "Print help")
        ("r","red", cxxopts::value<int>(rgb_r))
        ("g","green", cxxopts::value<int>(rgb_g))
        ("b","blue", cxxopts::value<int>(rgb_b))
        ("t,time", "time in seconds", cxxopts::value<int>()->default_value("4"), "N")
        ("v,verbose", "be talkative", cxxopts::value<bool>(verbose))
        ("w,wait", "whether to wait at the end", cxxopts::value<bool>(wait))
        ("s,speed", "speed 1 - 10; 10 is fast", cxxopts::value<int>(speed))
        ("d,dump", "whether to show text array at end", cxxopts::value<bool>(dump));

        options.parse(argc, argv);

        if (options.count("help"))
        {
            cout << options.help({"", "Group"}) << endl;
            exit(0);
        }
        if (options.count("time"))
        {
            someTime = options["time"].as<int>();
        }

        if (wait)
            if (verbose)
                cout << "will wait for you to close window." << endl;

        if (dump)
            if (verbose)
                cout << "will print ascii represenation of reeds at the end" << endl;
        
    }
    catch (const cxxopts::OptionException &e)
    {
        cout << "Apologies - error parsing options: " << e.what() << endl;
        exit(1);
    }

    if (verbose)
        cout << "Time " << someTime << " seconds. " << NODE_COUNT << " nodes. " 
        << (pizza ? "Angled" : "Straight") << " reeds. " 
        << " speed: " << speed
        << " rgb: " << rgb_r << "," << rgb_g << "," << rgb_b
        << endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL_INIT not happy: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    window = SDL_CreateWindow(
        "lightwalk simulator", //
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
        // or SDL_WINDOW_ALWAYS_ON_TOP, SDL_WINDOW_ALLOW_HIGHDPI
        );

    if (window == NULL)
    {
        cout << "SDL window not happy." << SDL_GetError() << endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // =============================================================================================
    // setup the reed pixels via SDL's rectangles
    // =============================================================================================
    SDL_Rect rect[NODE_COUNT][REED_COUNT][PIXEL_COUNT];
    for (int n = 0; n < NODE_COUNT; n++)
    {
        for (int x = 0; x < REED_COUNT; x++)
        {
            //cout << "n " << n << " reed " << x << " ";
            //n 0 reed 0 x 0 angle -0.261799 l 1221 startX 37 endX 1216 deltaX 1179   startY 417 endY 733 deltaY 316

            double l = (PIXEL_COUNT * (PIXEL_HEIGHT + PIXEL_SPACING_Y));
            double degrees = 75.0 + (random(1, 5) * 5.0);
            // cout << "degrees " << degrees << endl;
            double angle = degree2radian(degrees);

            int startX = 10 + (n * NODEWIDTH) + (x * (PIXEL_WIDTH + PIXEL_SPACING_X));
            int endX = startX + (l * cos(angle));
            double deltaX = endX - startX;

            int startY = WINDOW_REED_START;
            int endY = startY - (l * sin(angle));
            double deltaY = startY - endY;

            for (int y = 0; y < PIXEL_COUNT; y++)
            {
                rect[n][x][y].h = PIXEL_HEIGHT;
                rect[n][x][y].w = PIXEL_WIDTH;

                if (pizza)
                {
                    double pcnt = y / (1.0 * PIXEL_COUNT);
                    rect[n][x][y].x = startX + (deltaX * pcnt);
                    rect[n][x][y].y = startY - (deltaY * pcnt);
                }
                else
                {
                    rect[n][x][y].x = 10 + (n * NODEWIDTH) + (x * (PIXEL_WIDTH + PIXEL_SPACING_X));
                    rect[n][x][y].y = WINDOW_REED_START - (y * (PIXEL_HEIGHT + PIXEL_SPACING_Y));
                }
            }
        }
    }

    // =====================================================================================================
    // vague rectangles below reeds to help visually group them
    // =====================================================================================================   
    SDL_Rect buttonOn[NODE_COUNT];
    for (int n = 0; n < NODE_COUNT; n++)
    {
        buttonOn[n].h = 20;
        buttonOn[n].w = NODEWIDTH - 50;
        buttonOn[n].x = 5 + (n * NODEWIDTH);
        buttonOn[n].y = WINDOW_REED_START + 10;
    }

    SDL_SetRenderDrawColor(renderer, 0x03, 0x03, 0x03, 0xFF);
    SDL_RenderClear(renderer);
    SDL_Delay(100);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point endIt = (std::chrono::steady_clock::now() +
                                                   std::chrono::seconds(someTime));
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endIt - start).count() << "ms.\n";
    // =====================================================================================================
    // GOOD STUFF
    // =====================================================================================================
    Node *nodes[NODE_COUNT];
    int lengths[REED_COUNT] = {22, 27, 22, 27, 37, 27, 32, 32, 27, 27};

    for (int ee = 0; ee < NODE_COUNT; ee++)
    {
        // Bubbles *e = new Bubbles(ee, 0, 200, 0,200);
        // WaveSide *e = new WaveSide(ee, 0, rgb_r, rgb_g, rgb_b, 0, 1);
        // Shimmer *e = new Shimmer(ee, 0, rgb_r, rgb_g, rgb_b);
        // AcidRain *e = new AcidRain(ee, 0, rgb_r, rgb_g, rgb_b, speed);
        // RainbowRain *e = new RainbowRain(ee, 0);
        // Rainbow *e = new Rainbow(ee,0);
        // SplishSplash e = new SplishSplash(0, rgb_r, rgb_g, rgb_b, ee * 30, speed);

        // Magneto *e = new Magneto(ee, 0, rgb_r, rgb_g, rgb_b, speed);
<<<<<<< HEAD
=======
        Power *e = new Power(ee, 0, rgb_r, rgb_g, rgb_b, speed);
>>>>>>> 1783b956e5ff593dcf875b435d319e93873afe0c
        // WhackAMole *e = new WhackAMole(ee, 0, rgb_r, rgb_g, rgb_b, speed);

        TugOfWar *e = new TugOfWar(ee, 0);

        nodes[ee] = new Node(ee, (ee * 10), e, 0, lengths);
        // nodes[ee] = new Node(ee, (ee * 10), e, 37, lengths);
    }

    bool quit = false;
    SDL_Event event;
    long clickTime = 24;
    bool firstCard = true;
    long steps = 0;

    while ((now < endIt) && (!quit))
    {
        steps++;
        uint32_t newColor = 0;

        long daTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
        for (int n = 0; n < NODE_COUNT; n++)
        {
            // cout << "node: " << n << endl;
            nodes[n]->effect()->update(daTime); // effect will then call _update()
        }

        int likelyNode;
        int likelyX;
        if (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    likelyNode = (event.button.x / NODEWIDTH);
                    likelyX = nodes[likelyNode]->effect()->xOffset() - 2;
                    for (int n = 0; n < NODE_COUNT; n++)
                    {
                        // nodes[likelyNode]->movementOn(daTime, likelyX, likelyNode);
                        nodes[n]->effect()->movementOn(daTime, likelyX, likelyNode);
                    }
                    // cout << "step: " << steps << " moveOn mouse x: " << event.button.x << " node: " << likelyNode << " x: " << likelyX << endl;
                    break;

                case SDL_BUTTON_RIGHT:
                    likelyNode = (event.button.x / NODEWIDTH);
                    likelyX = nodes[likelyNode]->effect()->xOffset() - 2;
                    // cout << "step: " << steps << " moveOff " << event.button.x << " node: " << likelyNode << " x: " << likelyX << endl;
                    for (int n = 0; n < NODE_COUNT; n++)
                    {
                        likelyNode = (event.button.x / NODEWIDTH);
                        nodes[n]->effect()->movementOff(likelyX, likelyNode);
                    }
                    break;

                default:
                    // SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
                    break;
                }
            }
        }

        for (int n = 0; n < NODE_COUNT; n++)
        {
            for (int x = 0; x < REED_COUNT; x++)
            {
                for (int y = 0; y < nodes[n]->reedLengthAt(x); y++)
                {
                    if (nodes[n]->effect()->cares(x, y))
                    {
                        newColor = (uint32_t)nodes[n]->effect()->colorFor(x, y);
                    }
                    else
                    {
                        newColor = (uint32_t)0;
                    }
                    Uint8 colorR = (Uint8)(newColor >> 16);
                    Uint8 colorG = (Uint8)(newColor >> 8);
                    Uint8 colorB = (Uint8)(newColor);

                    SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, 0xFF);
                    SDL_RenderFillRect(renderer, &rect[n][x][y]);
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 66, 0, 0xFF);
            SDL_RenderFillRect(renderer, &buttonOn[n]);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1);

        now = std::chrono::steady_clock::now();
    }

    // cout << std::flush;
    SDL_Delay(1000); // Pause execution for a wee bit, in milliseconds

    if (dump)
    {
        for (int n = 0; n < NODE_COUNT; n++)
        {
            cout << "Node: " << setw(2) << n << " ";
            for (int r = 0; r < REED_COUNT; r++)
            {
                cout << nodes[n]->reedLengthAt(r) << " ";
            }
            cout << endl;
        }

        for (int y = PIXEL_COUNT; y > 0; y--)
        {
            cout << endl
                 << setw(2) << y << ": ";
            for (int x = 0; x < REED_COUNT; x++)
            {
                if (nodes[0]->reedLengthAt(x) >= y)
                {
                    if (nodes[0]->effect()->cares(x, y))
                        cout << "O ";
                    else
                        cout << "- ";
                }
                else
                {
                    cout << "  ";
                }
            }
        }
        cout << endl;
        //    cout << endl << e.positions() << endl;
    }

    if (verbose)
        cout << "And... we're done." << endl;

    if (wait)
    {
        cout << "Waiting for you to close window." << std::flush << endl;
        SDL_Event event;
        bool running = true;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                    break;
                }
            }
        }
    }

    if (verbose)
        cout << "Deleting Nodes" << endl;
    for (int ee = 0; ee < NODE_COUNT; ee++)
    {
        delete nodes[ee]->effect();
        delete nodes[ee];
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
