from Coordinates import Coordinates

COLOR_WHITE = (255, 255, 255)
COLOR_BLACK = (0, 0, 0)
COLOR_GREEN = (0, 255, 0)
COLOR_RED = (255, 0, 0)

WINDOW_SIZE_X = 600
WINDOW_SIZE_Y = 600
POINTS_FOR_BEING_ALIVE = False
DEFAULT_SPEED = 1
DEFAULT_TRACKED_ASTEROIDS = 5
CENTER_POINT = Coordinates(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2)
SPEED_AFTER_BOUNCE = 0.7

ASTEROIDS_MAX_VELOCITY = 1
ASTEROIDS_POINTS_PER_HIT = 1000
ASTEROIDS_PER_SPAWN = 1
ASTEROIDS_SPAWN_INTERVAL = 1000
ASTEROIDS_MAX_ON_SCREEN = 5
ASTEROIDS_BOUNCE = True
DIFFICULTY_INCREASE_INTERVAL = 60000
SPAWN_INTERVAL_DECREASE = 20
SPAWN_MARGIN = 100

MISSILE_RELOAD_TIME = 1000
MISSILE_BOUNCE = False

MAIN_BOOSTER_POWER = 0.09
SIDE_BOOSTER_POWER = 3  # in degrees
FIRE_POWER = 7
SLOW_DOWN_RATE = 0.01
MAX_SPEED = 7
SPACESHIP_BOUNCE = True
