# SimplePaintCpp
# Paint App

This project is a simple paint application built using C++ and SDL2. The application allows you to draw various shapes and lines on a canvas, switch between different pen colors and sizes, and save or load your artwork.

## Features

- Draw with different pen sizes and colors.
- Draw shapes: circles, rectangles, triangles, lines, polygons (quad, pentagon, hexagon).
- Erase using an eraser tool.
- Save and load your drawings.
- Clear the canvas.

## Requirements

- SDL2 library

## Installation

1. Install SDL2 library:
   - On Debian-based systems: `sudo apt-get install libsdl2-dev`
   - On Fedora: `sudo dnf install SDL2-devel`
   - On macOS using Homebrew: `brew install sdl2`
   - For Windows, download the development libraries from the [SDL2 website](https://www.libsdl.org/download-2.0.php).

2. Clone the repository:
   ```bash
   git clone https://github.com/your-username/paint-app.git
   cd paint-app
   ```

3. Compile the program:
   ```bash
   makefile
   ```

## Usage

Run the application:
```bash
./paint_app
```

### Controls

- **Mouse Left Click:** Draw with the selected tool.
- **Keyboard Shortcuts:**
  - **E:** Switch to eraser.
  - **P:** Switch to pen.
  - **Q:** Clear the canvas.
  - **A:** Draw a circle at the mouse position.
  - **R:** Draw a rectangle at the mouse position.
  - **T:** Draw a triangle at the mouse position.
  - **L:** Draw a line from the starting point to the ending point.
  - **G:** Draw a polygon (provide 3 or more points).
  - **F:** Draw a quadrilateral (provide 4 points).
  - **H:** Draw a pentagon (provide 5 points).
  - **J:** Draw a hexagon (provide 6 points).
  - **S:** Save the canvas to `image.bmp`.
  - **O:** Load the canvas from `image.bmp`.
  - **Z:** Change pen color to red.
  - **X:** Change pen color to blue.
  - **V:** Change pen color to green.
  - **B:** Change pen color to black.
  - **N:** Change pen color to brown.
  - **M:** Change pen color to purple.
  - **1-9:** Change pen size (1 sets size to 10, 2 to 20, etc.).

## Code Overview

### Classes

- `Pen`: Represents a pen for drawing with a specific color and size.
- `Circle`, `Rectangle`, `Triangle`, `Line`: Classes to draw respective shapes.
- `Polygon`, `Quad`, `Pentagon`, `Hexagon`: Classes to draw polygons with varying number of sides.

### Functions

- `saveImage`: Saves the current canvas to a BMP file.
- `loadImage`: Loads a BMP file into the canvas.

### Main Loop

- Handles SDL events for drawing, changing tools, and saving/loading images.
- Renders the updated canvas using SDL textures.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgements

- [SDL2](https://www.libsdl.org) for providing the graphics library used in this project.
