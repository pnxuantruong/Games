#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include "Grid.h"
#include "Input.h"
#include "Direction.h"
#include "Subject.h"
#include <list>

class Snake :
    public GameObject, public Subject
{
public:
    Snake(Grid* grid, float snakeSpeed, SDL_Point position = { 0, 0 }, Color::Enum headColor = Color::Enum::YELLOW, Color::Enum bodyColor = Color::Enum::GREEN);
    ~Snake() {};

    virtual void Update();
    virtual void Render(SDL_Renderer* renderer);
    
    bool IsOpposite(Direction d1, Direction d2);

    void ChangeDirection(Direction);

    void Move();

    bool CanMove();

    SDL_Point GetHeadPosition();

    void Reload();

    // return list positions of cells on snake including head, head will be front
    std::list<SDL_Point> ToList();

protected:
    Grid* grid;

    //setting properties
    float speed, percent; // percent += speed, percent >= 1.0 then snake move
    int length;
    bool canMove; 
    Color::Enum headColor;
    Color::Enum bodyColor;

    SDL_Point head;

private: 

    // contraint maxX, maxY;
    SDL_Point constraint;

    std::list<SDL_Point> body;

    // direction properties
    Direction currentDirection;

    
};

#endif // !SNAKE_H

