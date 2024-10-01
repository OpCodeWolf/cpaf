#include <napi.h>
#include <X11/Xlib.h>

#include <iostream>
#include <string>

// TODO convert to a class object

struct Button {
    int x, y;               // Position
    int width, height;      // Size
    bool isPressed;         // Button state
    std::string label;      // Button label

    int bgColor;            // Background color
    int bgHoverColor;       // Background hover color
    int bgActiveColor;      // Background active color

    int textColor;          // Text color
    int textHoverColor;     // Text hover color
    int textActiveColor;    // Text active color

    int borderColor;        // Border color
    int borderWidth;        // Border width
    int borderRadius;       // Border radius

    int padding;            // Padding
    int margin;             // Margin

    // int fontSize;        // Font size
    // int fontWeight;      // Font weight
    // int fontFamily;      // Font family
};

void DrawButton(Display* display, Window window, Button& button) {
    // GC gc = DefaultGC(display, DefaultScreen(display));

    // Set the button background color
    XSetForeground(
        display,
        DefaultGC(display, DefaultScreen(display)),
        button.isPressed ? button.bgActiveColor : button.bgColor
    );
   
    // Draw the rectangle for the button
    XFillRectangle(
        display,
        window,
        DefaultGC(display, DefaultScreen(display)),
        button.x, button.y, button.width, button.height
    );
    
    // Text Color
    XSetForeground(
        display,
        DefaultGC(display, DefaultScreen(display)),
        button.isPressed ? button.textActiveColor : button.textColor
    );

    // Draw the button label - You can use XDrawString for simplicity, or implement more sophisticated text rendering
    XDrawString(
        display,
        window, DefaultGC(display, DefaultScreen(display)),
        button.x + 10, button.y + button.height / 2,
        button.label.c_str(),
        button.label.size()
    );
}

void HandleMouseEvent(XEvent& event, Button& button, Display* display, Window window) {
    if (event.type == ButtonPress) {
        if (event.xbutton.x >= button.x && event.xbutton.x <= button.x + button.width &&
            event.xbutton.y >= button.y && event.xbutton.y <= button.y + button.height) {
            button.isPressed = true; // Button pressed
            std::cout << "Button " << button.label << " down!" << std::endl;
            DrawButton(display, window, button);
        }
    } else if (event.type == ButtonRelease) {
        if (button.isPressed) {
            // Button released; handle button click here
            std::cout << "Button " << button.label << " up!" << std::endl;
            button.isPressed = false; // Reset button state
            DrawButton(display, window, button);
        }
    }
}
