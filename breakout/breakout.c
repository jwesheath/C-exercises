// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initial ball velocity
    double xVelocity = drand48();
    double yVelocity = .5;
    
    // wait for click before starting
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        //paddle movement
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event);
                setLocation(paddle, x - 30, HEIGHT - 50);                
            }
        } 
        
        // ball movement
        move(ball, xVelocity, yVelocity);
        if (getX(ball) <= 0) xVelocity = -xVelocity;   
        else if (getX(ball) + RADIUS*2 >= WIDTH) xVelocity = -xVelocity;
        if (getY(ball) <= 0) yVelocity = -yVelocity; 

        // lose a life at bottom of screen        
        else if (getY(ball) + RADIUS*2 >= HEIGHT) 
        {
            lives -= 1;
            if (lives > 0) setLocation(ball, WIDTH/2 - RADIUS, HEIGHT/2);
            waitForClick();
        }
        
        // handling collisions
        GObject collider = detectCollision(window, ball);
        if (collider != NULL)
        {
            if (strcmp(getType(collider), "GRect") == 0)
            {
                yVelocity = -yVelocity;

                // remove bricks on collision                
                if (collider != paddle)
                {
                    removeGWindow(window, collider);
                    bricks -= 1;
                    points += 1;
                
                    // update the scoreboard after each collision
                    updateScoreboard(window, label, points);
                }
                
            }
        }        
        
        // check for win or loss and display appropriate message
        if (bricks == 0)
        { 
            label = newGLabel("You Win!");
            setFont(label, "SansSerif-36");
            setColor(label, "BLACK");
            add(window, label);
            setLocation(label, (getWidth(window) - getWidth(label))/2,
                        (getHeight(window) - getHeight(label))/2 + 50);
        }
        else if (lives == 0)
        { 
            label = newGLabel("You Lose!");
            setFont(label, "SansSerif-36");
            setColor(label, "BLACK");
            add(window, label);
            setLocation(label, (getWidth(window) - getWidth(label))/2,
                        (getHeight(window) - getHeight(label))/2 + 50);
        }

        pause(1);

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // set size of spaces between bricks and walls and between two bricks
    int sideGap = 3;
    int brickGap = 5;
    
    // set initial x and y coordinates for drawing the bricks
    int brickXStart = sideGap;
    int brickYStart = 50;
    
    // make each row of bricks a different color
    string colors[ROWS] = {"RED","ORANGE","YELLOW","GREEN","BLUE"};
    
    // draw bricks according to number of ROWS and COLS
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            GRect brick = newGRect(brickXStart + brickGap/2, brickYStart,
                                   (WIDTH - sideGap*2)/COLS - brickGap, 10);
            setColor(brick, colors[r]);
            setFilled(brick, true);
            add(window, brick);
            brickXStart += (WIDTH - sideGap*2)/COLS;
        }
        brickYStart += 15;
        brickXStart = sideGap;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2 - RADIUS, HEIGHT/2, RADIUS*2, RADIUS*2);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.  Returns paddle.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH - WIDTH/2 - 30, HEIGHT - 50, 60, 10);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // initialize scoreboard at 0
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    setColor(label, "LIGHT_GRAY");
    add(window, label);
    setLocation(label, (getWidth(window) - getWidth(label)) / 2,
                (getHeight(window) - getHeight(label)) / 2);

    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label with points
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // if no collision
    return NULL;
}
