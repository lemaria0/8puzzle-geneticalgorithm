#include <GL/gl.h>
#include "renderer.h"
#include <vector>
#include <cstdlib>

static const float NUM_SCALE = 0.8f;

// -------------------- NÚMEROS --------------------

void drawOne(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawTwo(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glEnd();
}

void drawThree(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawFour(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.1f);

    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);

    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.2f);
    glEnd();
}

void drawFive(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawSix(float x, float y)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x, y);
    glVertex2f(x, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glEnd();
}

void drawSeven(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);

    glVertex2f(x + 0.1f, y);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

void drawEight(float x, float y)
{
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x, y - 0.1f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.1f);
    glVertex2f(x + 0.1f, y - 0.2f);
    glVertex2f(x, y - 0.2f);
    glEnd();
}

// -------------------- DRAW NUMBER --------------------

void drawNumber(float x, float y, int value, float scale)
{
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    switch (value)
    {
    case 1:
        drawOne(0, 0);
        break;
    case 2:
        drawTwo(0, 0);
        break;
    case 3:
        drawThree(0, 0);
        break;
    case 4:
        drawFour(0, 0);
        break;
    case 5:
        drawFive(0, 0);
        break;
    case 6:
        drawSix(0, 0);
        break;
    case 7:
        drawSeven(0, 0);
        break;
    case 8:
        drawEight(0, 0);
        break;
    }

    glPopMatrix();
}

// -------------------- TILE --------------------

void drawRoundedTile(float x, float y, float size)
{
    float r = 0.02f;

    glBegin(GL_POLYGON);
    glVertex2f(x + r, y);
    glVertex2f(x + size - r, y);
    glVertex2f(x + size, y - r);
    glVertex2f(x + size, y - size + r);
    glVertex2f(x + size - r, y - size);
    glVertex2f(x + r, y - size);
    glVertex2f(x, y - size + r);
    glVertex2f(x, y - r);
    glEnd();
}

// -------------------- RENDER --------------------

void renderState(const PuzzleState &state)
{
    glClearColor(0.6f, 0.45f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(6.0f);

    float boardSize = 1.6f;
    float spacing = 0.02f;
    float tileSize = (boardSize - 2 * spacing) / 3.0f;

    float startX = -boardSize / 2.0f;
    float startY = boardSize / 2.0f;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int value = state.board[i][j];

            float x = startX + j * (tileSize + spacing);
            float y = startY - i * (tileSize + spacing);

            if (value != 0)
            {
                glColor3f(0.9f, 0.9f, 0.9f);
                drawRoundedTile(x, y, tileSize);

                glColor3f(0.7f, 0.7f, 0.7f);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x, y);
                glVertex2f(x + tileSize, y);
                glVertex2f(x + tileSize, y - tileSize);
                glVertex2f(x, y - tileSize);
                glEnd();

                float centerX = x + tileSize * 0.35f;
                float centerY = y - tileSize * 0.25f;

                glColor3f(0.2f, 0.2f, 0.2f);
                drawNumber(centerX, centerY, value, tileSize * 2.5f);
            }
        }
    }

    glFlush();
}