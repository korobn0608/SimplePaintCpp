#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <cmath>
#include <cstring>

const int WIDTH = 800, HEIGHT = 600;

class Pen
{
public:
    Pen(Uint32 color, int size) : color(color), size(size) {}

    void draw(Uint32* pixels, int x, int y)
    {
        int halfSize = size / 2;
        for (int i = -halfSize; i <= halfSize; i++)
        {
            for (int j = -halfSize; j <= halfSize; j++)
            {
                int pixelX = x + j;
                int pixelY = y + i;
                if (pixelX >= 0 && pixelX < WIDTH && pixelY >= 0 && pixelY < HEIGHT)
                {
                    pixels[pixelY * WIDTH + pixelX] = color;
                }
            }
        }
    }

    void setColor(Uint32 newColor) { color = newColor; }
    Uint32 getColor() const { return color; }
    int getSize() const { return size; }

private:
    Uint32 color;
    int size;
};

class Circle
{
public:
    Circle(int x, int y, int radius, Uint32 color) : x(x), y(y), radius(radius), color(color) {}

    void draw(Uint32* pixels, int width)
    {
        int centerX = x;
        int centerY = y;

        for (int i = -radius; i <= radius; i++)
        {
            for (int j = -radius; j <= radius; j++)
            {
                int distance = i * i + j * j;
                if (distance <= radius * radius)
                {
                    int pixelX = centerX + j;
                    int pixelY = centerY + i;
                    if (pixelX >= 0 && pixelX < width && pixelY >= 0 && pixelY < HEIGHT)
                    {
                        pixels[pixelY * width + pixelX] = color;
                    }
                }
            }
        }
    }

private:
    int x;
    int y;
    int radius;
    Uint32 color;
};

class Rectangle
{
public:
    Rectangle(int x, int y, int width, int length, Uint32 color) : x(x), y(y), width(width), length(length), color(color) {}

    void draw(Uint32* pixels, int screenWidth)
    {
        int startX = x - width / 2;
        int startY = y - length / 2;

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < length; j++)
            {
                int pixelX = startX + i;
                int pixelY = startY + j;
                if (pixelX >= 0 && pixelX < screenWidth && pixelY >= 0 && pixelY < HEIGHT)
                {
                    pixels[pixelY * screenWidth + pixelX] = color;
                }
            }
        }
    }

private:
    int x;
    int y;
    int width;
    int length;
    Uint32 color;
};

class Triangle
{
public:
    Triangle(int x, int y, int size, Uint32 color) : x(x), y(y), size(size), color(color) {}

    void draw(Uint32* pixels, int screenWidth)
    {
        int halfSize = size / 2;
        for (int i = 0; i < size; ++i)
        {
            for (int j = -i; j <= i; ++j)
            {
                int pixelX = x + j;
                int pixelY = y + (size - i);
                if (pixelX >= 0 && pixelX < screenWidth && pixelY >= 0 && pixelY < HEIGHT)
                {
                    pixels[pixelY * screenWidth + pixelX] = color;
                }
            }
        }
    }

private:
    int x;
    int y;
    int size;
    Uint32 color;
};

class Line
{
public:
    Line(int x1, int y1, int x2, int y2, Uint32 color) : x1(x1), y1(y1), x2(x2), y2(y2), color(color) {}

    void draw(Uint32* pixels, int screenWidth)
    {
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;

        while (true)
        {
            if (x1 >= 0 && x1 < screenWidth && y1 >= 0 && y1 < HEIGHT)
            {
                pixels[y1 * screenWidth + x1] = color;
            }

            if (x1 == x2 && y1 == y2)
                break;

            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }

private:
    int x1, y1, x2, y2;
    Uint32 color;
};

class Polygon
{
public:
    Polygon(const std::vector<std::pair<int, int>>& points, Uint32 color) : points(points), color(color) {}

    virtual void draw(Uint32* pixels, int screenWidth)
    {
        for (size_t i = 0; i < points.size(); ++i)
        {
            int x1 = points[i].first;
            int y1 = points[i].second;
            int x2 = points[(i + 1) % points.size()].first;
            int y2 = points[(i + 1) % points.size()].second;

            Line line(x1, y1, x2, y2, color);
            line.draw(pixels, screenWidth);
        }
    }

protected:
    std::vector<std::pair<int, int>> points;
    Uint32 color;
};

class Quad : public Polygon
{
public:
    Quad(const std::pair<int, int>& p1, const std::pair<int, int>& p2, const std::pair<int, int>& p3, const std::pair<int, int>& p4, Uint32 color)
        : Polygon({p1, p2, p3, p4}, color) {}
};

class Pentagon : public Polygon
{
public:
    Pentagon(const std::pair<int, int>& p1, const std::pair<int, int>& p2, const std::pair<int, int>& p3, const std::pair<int, int>& p4, const std::pair<int, int>& p5, Uint32 color)
        : Polygon({p1, p2, p3, p4, p5}, color) {}
};

class Hexagon : public Polygon
{
public:
    Hexagon(const std::pair<int, int>& p1, const std::pair<int, int>& p2, const std::pair<int, int>& p3, const std::pair<int, int>& p4, const std::pair<int, int>& p5, const std::pair<int, int>& p6, Uint32 color)
        : Polygon({p1, p2, p3, p4, p5, p6}, color) {}
};

void saveImage(const char* filename, Uint32* pixels)
{
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, WIDTH, HEIGHT, 32, WIDTH * sizeof(Uint32),
                                                    0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (surface)
    {
        if (SDL_SaveBMP(surface, filename) != 0)
        {
            std::cout << "Failed to save image: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(surface);
    }
    else
    {
        std::cout << "Failed to create surface for saving image: " << SDL_GetError() << std::endl;
    }
}

void loadImage(const char* filename, Uint32* pixels)
{
    SDL_Surface* surface = SDL_LoadBMP(filename);
    if (surface)
    {
        memcpy(pixels, surface->pixels, WIDTH * HEIGHT * sizeof(Uint32));
        SDL_FreeSurface(surface);
    }
    else
    {
        std::cout << "Failed to load image: " << SDL_GetError() << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Paint App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (NULL == renderer)
    {
        std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Uint32 pixels[WIDTH * HEIGHT];
    std::fill_n(pixels, WIDTH * HEIGHT, 0xFFFFFFFF); // Fill the array with white color

    std::unique_ptr<Pen> pen = std::make_unique<Pen>(0x000000, 10); // Default black pen with size 10
    Pen eraser(0xFFFFFFFF, 20); // White pen (eraser) with size 20
    bool drawCircle = false;
    bool drawRectangle = false;
    bool drawTriangle = false;
    bool drawLine = false;
    bool drawPolygon = false;
    bool drawQuad = false;
    bool drawPentagon = false;
    bool drawHexagon = false;
    bool mouseDown = false;
    Pen* currentPen = pen.get();
    int startX, startY, endX, endY;
    std::vector<std::pair<int, int>> polygonPoints;

    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
    if (NULL == texture)
    {
        std::cout << "Could not create texture: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_e)
                {
                    currentPen = &eraser; // Switch to eraser
                }
                else if (event.key.keysym.sym == SDLK_p)
                {
                    currentPen = pen.get(); // Switch back to pen
                }
                else if (event.key.keysym.sym == SDLK_q)
                {
                    std::fill_n(pixels, WIDTH * HEIGHT, 0xFFFFFFFF); // Clear the screen with white color
                }
                else if (event.key.keysym.sym == SDLK_a)
                {
                    drawCircle = true;
                }
                else if (event.key.keysym.sym == SDLK_r)
                {
                    drawRectangle = true;
                }
                else if (event.key.keysym.sym == SDLK_t)
                {
                    drawTriangle = true;
                }
                else if (event.key.keysym.sym == SDLK_l)
                {
                    drawLine = true;
                }
                else if (event.key.keysym.sym == SDLK_g)
                {
                    drawPolygon = true;
                }
                else if (event.key.keysym.sym == SDLK_f)
                {
                    drawQuad = true;
                }
                else if (event.key.keysym.sym == SDLK_h)
                {
                    drawPentagon = true;
                }
                else if (event.key.keysym.sym == SDLK_j)
                {
                    drawHexagon = true;
                }
                else if (event.key.keysym.sym == SDLK_s)
                {
                    saveImage("image.bmp", pixels);
                }
                else if (event.key.keysym.sym == SDLK_o)
                {
                    loadImage("image.bmp", pixels);
                }
                else if (event.key.keysym.sym == SDLK_z)
                {
                    pen->setColor(0xFF0000); // Red color
                }
                else if (event.key.keysym.sym == SDLK_x)
                {
                    pen->setColor(0x0000FF); // Blue color
                }
                else if (event.key.keysym.sym == SDLK_v)
                {
                    pen->setColor(0x00FF00); // Green color
                }
                else if (event.key.keysym.sym == SDLK_b)
                {
                    pen->setColor(0x000000); // Black color
                }
                else if (event.key.keysym.sym == SDLK_n)
                {
                    pen->setColor(0x8B4513); // Brown color
                }
                else if (event.key.keysym.sym == SDLK_m)
                {
                    pen->setColor(0x800080); // Purple color
                }
                else if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_9)
                {
                    int num = event.key.keysym.sym - SDLK_1 + 1; // Calculate the corresponding pen size based on the key pressed
                    int penSize = num * 10; // Set the pen size accordingly
                    pen = std::make_unique<Pen>(currentPen->getColor(), penSize); // Create a new Pen object with the updated size and current color
                    currentPen = pen.get(); // Update current pen
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseDown = true;
                    startX = event.button.x;
                    startY = event.button.y;

                    if (drawCircle)
                    {
                        Circle circle(startX, startY, currentPen->getSize(), currentPen->getColor()); // Circle radius based on pen size
                        circle.draw(pixels, WIDTH);
                        drawCircle = false;
                    }
                    if (drawRectangle)
                    {
                        int rectLength = (currentPen->getSize()) * 3;
                        int rectWidth = 2 * rectLength;
                        Rectangle rectangle(startX, startY, rectWidth, rectLength, currentPen->getColor());
                        rectangle.draw(pixels, WIDTH);
                        drawRectangle = false;
                    }
                    if (drawTriangle)
                    {
                        Triangle triangle(startX, startY, currentPen->getSize(), currentPen->getColor());
                        triangle.draw(pixels, WIDTH);
                        drawTriangle = false;
                    }
                    if (drawPolygon)
                    {
                        polygonPoints.push_back({startX, startY});
                        if (polygonPoints.size() >= 3)
                        {
                            Polygon polygon(polygonPoints, currentPen->getColor());
                            polygon.draw(pixels, WIDTH);
                            polygonPoints.clear();
                            drawPolygon = false;
                        }
                    }
                    if (drawQuad)
                    {
                        polygonPoints.push_back({startX, startY});
                        if (polygonPoints.size() == 4)
                        {
                            Quad quad(polygonPoints[0], polygonPoints[1], polygonPoints[2], polygonPoints[3], currentPen->getColor());
                            quad.draw(pixels, WIDTH);
                            polygonPoints.clear();
                            drawQuad = false;
                        }
                    }
                    if (drawPentagon)
                    {
                        polygonPoints.push_back({startX, startY});
                        if (polygonPoints.size() == 5)
                        {
                            Pentagon pentagon(polygonPoints[0], polygonPoints[1], polygonPoints[2], polygonPoints[3], polygonPoints[4], currentPen->getColor());
                            pentagon.draw(pixels, WIDTH);
                            polygonPoints.clear();
                            drawPentagon = false;
                        }
                    }
                    if (drawHexagon)
                    {
                        polygonPoints.push_back({startX, startY});
                        if (polygonPoints.size() == 6)
                        {
                            Hexagon hexagon(polygonPoints[0], polygonPoints[1], polygonPoints[2], polygonPoints[3], polygonPoints[4], polygonPoints[5], currentPen->getColor());
                            hexagon.draw(pixels, WIDTH);
                            polygonPoints.clear();
                            drawHexagon = false;
                        }
                    }
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseDown = false;
                    endX = event.button.x;
                    endY = event.button.y;
                    if (drawLine)
                    {
                        Line line(startX, startY, endX, endY, currentPen->getColor());
                        line.draw(pixels, WIDTH);
                        drawLine = false;
                    }
                }
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                if (mouseDown && !drawLine)
                {
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    currentPen->draw(pixels, mouseX, mouseY);
                }
            }
        }

        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
