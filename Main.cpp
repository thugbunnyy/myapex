#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include "Utils.cpp"
#include "Offsets.cpp"
#include "Level.cpp"
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Sense.cpp"
#include "NoRecoil.cpp"
#include "Aimbot.cpp"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"

int main(int argc, char *argv[])
{
    // Check if root privileges are available
    if (getuid())
    {
        std::cout << "MUST RUN AS ROOT!\n";
        return -1;
    }

    // Check if the game process is running
    if (mem::GetPID() == 0)
    {
        std::cout << "GAME NOT FOUND. EXITING!\n";
        return -1;
    }

    // Create objects needed for the main loop
    ConfigLoader configLoader;
    Level level;
    LocalPlayer localPlayer;
    X11Utils x11Utils;
    std::vector<Player> players(60);
    Sense sense(&configLoader, &level, &localPlayer, &players, &x11Utils);
    NoRecoil noRecoil(&configLoader, &level, &localPlayer, &players, &x11Utils);
    Aimbot aimbot(&configLoader, &level, &localPlayer, &players, &x11Utils);

    std::cout << "MYAPEX STARTING MAIN LOOP\n";

    int counter = 0;
    while (1)
    {
        try
        {
            // Reload the config file if there have been any updates
            if (counter % 200 == 0)
                configLoader.reloadFile();

            // Resolve pointers
            localPlayer.markForPointerResolution();
            for (auto& player : players)
            {
                player.markForPointerResolution();
            }

            // Run features
            if (configLoader.isAimbotOn())
                aimbot.update();

            if (configLoader.isNorecoilOn())
                noRecoil.update();

            if (configLoader.isSenseOn())
                sense.update();

            // All ran fine
            if (counter % 1000 == 0)
                std::cout << "UPDATE[" << counter << "] OK. \n";

            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        catch (...)
        {
            std::cout << "UPDATE[" << counter << "] ERROR (LOADING SCREEN?). SLEEPING FOR 10 SECONDS\n";
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

        counter++;
        if (counter > 1000)
            counter = 0;
    }
}

