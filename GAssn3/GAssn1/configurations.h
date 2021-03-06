#pragma once

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

const int LION_DEFAULT = 0;
const float LION_SPEED = 2.5f;
const float LION_JUMP_SPEED = 8.f;
const float LION_JUMP_GRAVITY = -0.2f;
const int LION_CAMERA = 100;
const int LION_CAMERA_MIN = LION_CAMERA;
const int LION_FLASH_TIME = 100;

const int GAME_START = 0;
const int GAME_ING = 1;
const int GAME_OVER = 2;
const int GAME_CLEAR = 3;

const int LIFE_DEFAULT = 3;

const int CAMERA_DEFAULT = 0;

const int JAR_GEN_MIN = 700;
const int JAR_GEN_MAX = 5000 - 100;

const int JAR_HEIGHT = 30;
const int JAR_DIST_MIN = 400;
const int JAR_DIST_MAX = 700;

const int RING_TOP = 190;
const int RING_BOTTOM = 50;
const int RING_GEN_MIN = 1000;
const int RING_GEN_MAX = 5000 + 1000;

const int RING_DIST_MIN = 320;
const int RING_DIST_MAX = 640;

const int RING_REMOVE = -100;
const int RING_REGEN = RING_GEN_MAX + RING_REMOVE;

const int RING_HEIGHT = 140;
const int RING_RADIUS = 100;//100;

const float RING_SPEED = 1.0f;

const int VIEW_FIRST = 2;
const int VIEW_THIRD = 3;
const int VIEW_TOP_MAP = 4;
const int VIEW_RIGHT_MAP = 5;
const int VIEW_TOP = 6;
const int VIEW_RIGHT = 7;
