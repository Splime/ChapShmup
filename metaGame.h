/**
 * MetaGame: The actual game, with all the persistent info (inventory, upgrades, etc.)
 */

 #pragma once
 #include "chap_header.h"

 struct GameTime
 {
    int hour;
    int minute;
    float seconds;

    int day;
    int month;
    int year;
 };

 class MetaGame
 {
 public:
    MetaGame();
    ~MetaGame();

 private:
    GameTime theTime;



 };


