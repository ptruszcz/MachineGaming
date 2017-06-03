"""
File created by: Piotr Truszczynski
"""

import math


class Coordinates:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def calculate_distance(self, other):
        return math.sqrt((other.x - self.x) ** 2 +
                         (other.y - self.y) ** 2)
