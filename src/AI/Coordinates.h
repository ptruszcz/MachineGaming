//
// Created by fajqa on 28.03.17.
//

#ifndef MACHINEGAMING_COORDINATES_H
#define MACHINEGAMING_COORDINATES_H


class Coordinates {
private:
    int x;
    int y;

public:
    Coordinates(int x, int y);

    int getX() const;

    int getY() const;
};


#endif //MACHINEGAMING_COORDINATES_H
