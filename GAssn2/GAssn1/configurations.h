#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

const int FINISH = 5000;

const int LION_DEFAULT = 100;
const float LION_SPEED = 2.5f;
const float LION_JUMP_SPEED = 7.2f;
const float LION_JUMP_GRAVITY = -0.2f;
const int LION_CAMERA = 150;
const int LION_CAMERA_MIN = 100;
const int LION_FLASH_TIME = 100;

const int GAME_START = 0;
const int GAME_ING = 1;
const int GAME_OVER = 2;
const int GAME_CLEAR = 3;

const int LIFE_DEFAULT = 3;

const int CAMERA_DEFAULT = 0;

const int JAR_GEN_MIN = 700;
const int JAR_GEN_MAX = FINISH - 100;

const int JAR_HEIGHT = 30;
const int JAR_DIST_MIN_0 = 400;
const int JAR_DIST_MAX_0 = 700;
const int JAR_DIST_MIN_1 = 350;
const int JAR_DIST_MAX_1 = 650;
const int JAR_DIST_MIN_2 = 300;
const int JAR_DIST_MAX_2 = 600;
const int JAR_DIST_MIN_3 = 250;
const int JAR_DIST_MAX_3 = 550;

const int RING_TOP = 180;
const int RING_BOTTOM = 50;
const int RING_GEN_MIN = 1000;
const int RING_GEN_MAX = FINISH + 1000;

const int RING_DIST_MIN_0 = 320;
const int RING_DIST_MAX_0 = 640;
const int RING_DIST_MIN_1 = 280;
const int RING_DIST_MAX_1 = 600;
const int RING_DIST_MIN_2 = 240;
const int RING_DIST_MAX_2 = 560;
const int RING_DIST_MIN_3 = 200;
const int RING_DIST_MAX_3 = 520;

const int RING_REMOVE = -100;
const int RING_REGEN = RING_GEN_MAX + RING_REMOVE;

const float RING_SPEED = 1.0f;
