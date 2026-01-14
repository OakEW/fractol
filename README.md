*This project has been created as part of the 42 curriculum by <login1>[ywang2]*

# fractol

## Description
### Objectives

Learn to use the school’s graphical library, the MiniLibX. This library was developed
internally and includes basic necessary tools to open a window, create images and deal
with keyboard and mouse events

### Goal

This will be an opportunity for you to become familiar with the MiniLibX library, dis-
cover or use the mathematical concept of **complex numbers**, explore computer graphics
**optimization**, and practice **event handling**.

## Instructions

### Compile
Run `make` for fractol

### Rules

You must use the MiniLibX library. Either the version available on the school
machines, or installing it using its sources.
- You have to turn in a Makefile which will compile your source files. It must not
relink.
- Global variables are forbidden.

### Rendering

- Your program must offer the `Julia` set and the `Mandelbrot` set.
- The mouse wheel allows zooming in and out almost infinitely (within the computer’s
limits). This is the very principle of fractals.
- You must be able to create different **Julia** sets by passing **different parameters** to
the program.

  ```
  Beautiful Julia Set Values:
  c = -0.83 0.23
  c = -0.70176 -0.3842
  c = 0.355 +0.355
  ```
- A parameter is passed on the command line to define what type of fractal will be
displayed in a window.
  - You can handle more parameters to use them as rendering options.
  - If no parameter is provided, or if the parameter is invalid, the program displays
a list of available parameters and exits properly.
- You must use at least a few colors to reveal the depth of each fractal. Experiment-
ing with psychedelic effects is encouraged.

### Graphic management

- Your program has to display the image in a window.
- Window management must remain smooth (e.g., switching to another window,
minimizing, etc.).
- Pressing `ESC` must close the window and quit the program in a clean way.
- `Clicking on the cross` on the window’s frame must close the window and quit the
program in a clean way.
- The use of the images of the MiniLibX library is mandatory.

### Bonus part

You will get some extra points with the following features:
- One more different fractal (more than a hundred different types of fractals are
referenced online).
- The zoom follows the actual mouse position.
- In addition to zooming, allow moving the view using the arrow keys.
- Make the color range shift. 

  - Offer three set :  `mandelbrot` `julia` `multibrot4`
  - Zoom follows mouse position
  - `arrow keys` Allow view moving
  - Color auto shifts
  - `S` stop / restart color shifting
  - `A` & `D` shift colors
  - `W` switch between Color / B&W
  - `I` `K` `O` `L` change the shape for julia set
  - `Mouse center click` center image to mouse position

## Resources

Regarding **AI** : AI is used to assist understanding the math and choosing fractol formula (for example: the calculation of fractols, the escape condition and why pix need to be mapped to |1| * scale), as well as fine tunning some of the formula as such smoother color grident (using sin to get smooth waves).

>[**fract-ol: creating graphically beautiful fractals**](https://medium.com/@leogaudin/fract-ol-creating-graphically-beautiful-fractals-6664b6b045b5) *by Léo Gaudin*

>[**MiniLibX - GuideBook**](https://42-cursus.gitbook.io/guide/minilibx) *by Laura & Simon*

>[**Libs/MiniLibX**](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html) *42 Doc*