#include <GL/glut.h>  // Include GLUT library for OpenGL
#include <stdlib.h>
#include <math.h>

// Global variables for rotation and translation
static GLfloat spin = 0.0; // Rotation angle
static float tx = 10.0;    // Translation along X-axis , Move tx units along the x-axis.
static float ty = 10.0;     // Translation along Y-axis

// Function to display the rectangle
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glPushMatrix();               // Save current transformation state

    glColor3f(1.0, 1.0, 1.0);      // Set rectangle color to white
    glTranslatef(tx, ty, 0);       // his function moves (translates) objects in the x, y, and z directions.
    glRectf(-25.0, -25.0, 25.0, 25.0); // Draw rectangle centered at origin

    glPopMatrix(); // Restore transformation state
    glFlush();     // Render the scene
}

// Function to rotate the rectangle to the left
void spinDisplay_left(void)
{
    spin = 5;               // Set rotation angle
    glutPostRedisplay();    // Request redisplay (re-render the scene) - will call display() when change occurred
    glRotatef(spin, 0.0, 0.0, 1.0); // Apply rotation about Z-axis
}

// Function to rotate the rectangle to the right
void spinDisplay_right(void)
{
    spin = -5;              // Set negative rotation angle
    glutPostRedisplay();    // Request redisplay
    glRotatef(spin, 0.0, 0.0, 1.0); // Apply rotation about Z-axis
}

// Function to initialize OpenGL settings
void init(void)
{
    glClearColor(1.0, 0.0, 0.0, 0.0); // Set background color to red
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0); // Set orthographic projection
}

// Keyboard callback function to handle key presses
void my_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'l': // Press 'l' to rotate left
        spinDisplay_left();
        break;
    case 'r': // Press 'r' to rotate right
        spinDisplay_right();
        break;
    case 's': // Press 's' to stop rotation
        glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}

// Special keyboard callback function (handles arrow keys)
void spe_key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:  // Left arrow key moves rectangle left
        tx -= 5;
        glutPostRedisplay(); // Request redisplay
        break;
    case GLUT_KEY_RIGHT: // Right arrow key moves rectangle right
        tx += 5;
        glutPostRedisplay(); // Request redisplay
        break;
    case GLUT_KEY_UP:    // Move up
        ty += 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:  // Move down
        ty -= 5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

// Mouse callback function to handle mouse button presses
void my_mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) // Left mouse button rotates left
            glutIdleFunc(spinDisplay_left);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) // Right mouse button rotates right
            glutIdleFunc(spinDisplay_right);
        break;
    default:
        break;
    }
}

// Main function to set up the OpenGL environment and start the event loop
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Set display mode
    glutInitWindowSize(800, 800);                   // Set window size
    glutInitWindowPosition(100, 100);               // Set window position
    glutCreateWindow("Mahmud");                       // Create window with title
    init();                                         // Initialize OpenGL settings

    glutDisplayFunc(display);                       // Register display callback
    glutKeyboardFunc(my_keyboard);                  // Register keyboard callback
    glutSpecialFunc(spe_key);                       // Register special key callback

    glutMouseFunc(my_mouse);                        // Register mouse callback
    glutMainLoop();                                 // Enter the event-processing loop
    return 0;
}


/*
Let's go through each function in the code in detail to understand how it works:

### 1. **`display()`**

```cpp
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glPushMatrix();               // Save current transformation state

    glColor3f(1.0, 1.0, 1.0);      // Set rectangle color to white
    glTranslatef(tx, ty, 0);       // Move rectangle by tx (x-axis) and ty (y-axis)
    glRectf(-25.0, -25.0, 25.0, 25.0); // Draw rectangle centered at origin

    glPopMatrix(); // Restore transformation state
    glFlush();     // Render the scene
}
```

- **Purpose:** This function is responsible for rendering the scene (drawing the rectangle in this case) on the screen.
- **`glClear(GL_COLOR_BUFFER_BIT);`** clears the window (or frame buffer) by removing previous drawing, so we start with a clean slate.
- **`glPushMatrix();`** saves the current transformation matrix so that it can be restored later (useful for resetting transformations).
- **`glColor3f(1.0, 1.0, 1.0);`** sets the color of the shape to white (RGB values between 0 and 1).
- **`glTranslatef(tx, ty, 0);`** applies a translation (movement) to the object in the X and Y directions based on the `tx` and `ty` variables.
- **`glRectf(-25.0, -25.0, 25.0, 25.0);`** draws a rectangle centered at the origin `(0, 0)` with width 50 and height 50 (from -25 to +25 on both axes).
- **`glPopMatrix();`** restores the previous transformation matrix saved by `glPushMatrix()`. This ensures that any transformation applied to the rectangle doesn’t affect other objects.
- **`glFlush();`** forces OpenGL to execute all commands, ensuring that the drawing operations are performed immediately.

### 2. **`spinDisplay_left()`**

```cpp
void spinDisplay_left(void)
{
    spin = 5;               // Set rotation angle
    glutPostRedisplay();    // Request redisplay (re-render the scene)
    glRotatef(spin, 0.0, 0.0, 1.0); // Apply rotation about Z-axis
}
```

- **Purpose:** This function is responsible for rotating the rectangle in the counter-clockwise direction (left).
- **`spin = 5;`** sets the rotation angle to 5 degrees.
- **`glutPostRedisplay();`** tells GLUT to trigger the `display()` function again, causing the window to be redrawn. This is necessary to update the screen with the new transformation (rotation).
- **`glRotatef(spin, 0.0, 0.0, 1.0);`** applies a 5-degree rotation about the Z-axis (rotation in 2D). The Z-axis is perpendicular to the screen in 2D space.

### 3. **`spinDisplay_right()`**

```cpp
void spinDisplay_right(void)
{
    spin = -5;              // Set negative rotation angle
    glutPostRedisplay();    // Request redisplay
    glRotatef(spin, 0.0, 0.0, 1.0); // Apply rotation about Z-axis
}
```

- **Purpose:** This function is responsible for rotating the rectangle in the clockwise direction (right).
- **`spin = -5;`** sets the rotation angle to -5 degrees (negative value for clockwise rotation).
- **`glutPostRedisplay();`** requests the window to be redrawn to reflect the new rotation.
- **`glRotatef(spin, 0.0, 0.0, 1.0);`** applies the negative rotation about the Z-axis.

### 4. **`init()`**

```cpp
void init(void)
{
    glClearColor(1.0, 0.0, 0.0, 0.0); // Set background color to red
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0); // Set orthographic projection
}
```

- **Purpose:** This function initializes the OpenGL settings before the program starts rendering anything.
- **`glClearColor(1.0, 0.0, 0.0, 0.0);`** sets the background color of the window to red (RGB values: red=1.0, green=0.0, blue=0.0).
- **`glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);`** sets up an orthographic projection. It defines the coordinates of the scene. The values `-50.0 to 50.0` specify the visible range along the X and Y axes, and `-1.0 to 1.0` specify the depth range (since it’s a 2D scene, the Z-range isn't used).

### 5. **`my_keyboard()`**

```cpp
void my_keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'l': // Press 'l' to rotate left
        spinDisplay_left();
        break;
    case 'r': // Press 'r' to rotate right
        spinDisplay_right();
        break;
    case 's': // Press 's' to stop rotation
        glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}
```

- **Purpose:** This function handles regular keyboard inputs. It listens for key presses and performs actions based on the key.
- **`key`:** The character of the key that was pressed.
- **`x`, `y`:** The mouse position when the key is pressed (although not used here).
- **`switch` statement:**
  - **Case `'l'`:** When the 'l' key is pressed, the rectangle rotates to the left by calling `spinDisplay_left()`.
  - **Case `'r'`:** When the 'r' key is pressed, the rectangle rotates to the right by calling `spinDisplay_right()`.
  - **Case `'s'`:** When the 's' key is pressed, it stops any ongoing rotation by calling `glutIdleFunc(NULL)`, which disables any idle function (in this case, the automatic rotation).

### 6. **`spe_key()`**

```cpp
void spe_key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:  // Left arrow key moves rectangle left
        tx -= 5;
        glutPostRedisplay(); // Request redisplay
        break;
    case GLUT_KEY_RIGHT: // Right arrow key moves rectangle right
        tx += 5;
        glutPostRedisplay(); // Request redisplay
        break;
    case GLUT_KEY_UP:    // Move up
        ty += 5;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:  // Move down
        ty -= 5;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}
```

- **Purpose:** This function handles special keyboard inputs (such as the arrow keys).
- **`key`:** The special key that was pressed (e.g., arrow keys).
- **`x`, `y`:** The mouse position when the key is pressed (although not used here).
- **`switch` statement:**
  - **Case `GLUT_KEY_LEFT`:** Moves the rectangle 5 units to the left by decreasing `tx` (translation on the X-axis).
  - **Case `GLUT_KEY_RIGHT`:** Moves the rectangle 5 units to the right by increasing `tx`.
  - **Case `GLUT_KEY_UP`:** Moves the rectangle 5 units up by increasing `ty` (translation on the Y-axis).
  - **Case `GLUT_KEY_DOWN`:** Moves the rectangle 5 units down by decreasing `ty`.
- After each movement, **`glutPostRedisplay();`** requests a window redraw.

### 7. **`my_mouse()`**

```cpp
void my_mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) // Left mouse button rotates left
            glutIdleFunc(spinDisplay_left);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) // Right mouse button rotates right
            glutIdleFunc(spinDisplay_right);
        break;
    default:
        break;
    }
}
```

- **Purpose:** This function handles mouse input. It listens for mouse button presses and performs actions based on the button pressed.
- **`button`:** The mouse button pressed (left or right).
- **`state`:** The state of the button (whether it was pressed or released).
- **`x`, `y`:** The mouse position when the button was pressed (although not used here).
- **`switch` statement:**
  - **Case `GLUT_LEFT_BUTTON`:** If the left mouse button is pressed, it triggers continuous rotation to the left by calling `glutIdleFunc(spinDisplay_left)`.
  - **Case `GLUT_RIGHT_BUTTON`:** If the right mouse button is pressed, it triggers continuous rotation to the right by calling `glutIdleFunc(spinDisplay_right)`.

### 8. **`main()`**

```cpp
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Set display mode
    glutInitWindowSize(800, 800);                   // Set window size
    glutInitWindowPosition(100, 100);               // Set window position
    glutCreateWindow("Mahmud");                       // Create window with title
    init();                                         // Initialize OpenGL settings

    glutDisplayFunc(display);                       // Register display callback
    glutKeyboardFunc(my_keyboard);                  // Register keyboard callback
    glutSpecialFunc(spe_key);                       // Register special key callback

    glutMouseFunc(my_mouse);                        // Register mouse callback
    glutMainLoop();                                 // Enter the event-processing loop
    return 0;
}
```

- **Purpose:** This function initializes GLUT, sets up the OpenGL window, and enters the event-processing loop.
- **`glutInit(&argc, argv);`** initializes GLUT.
- **`glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);`** sets the display mode for the window (single buffer and RGB color model).
- **`glutInitWindowSize(800, 800);`** sets the window size to 800x800 pixels.
- **`glutInitWindowPosition(100, 100);`** sets the window position to (100, 100) on the screen.
- **`glutCreateWindow("Mahmud");`** creates the window with the title "Mahmud".
- **`init();`** calls the `init()` function to set up OpenGL parameters.
- **`glutDisplayFunc(display);`** registers the display callback function.
- **`glutKeyboardFunc(my_keyboard);`** registers the regular keyboard callback function.
- **`glutSpecialFunc(spe_key);`** registers the special keyboard callback (for arrow keys).
- **`glutMouseFunc(my_mouse);`** registers the mouse callback function.
- **`glutMainLoop();`** enters the main GLUT event processing loop.

*/
