#include <napi.h>
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "controls/button.cpp"

// #include "./controls/label.h"
// #include "./controls/textbox.h"
// #include "./controls/checkbox.h"
// #include "./controls/radiobutton.h"
// #include "./controls/combobox.h"
// #include "./controls/listbox.h"
// #include "./controls/treeview.h"
// #include "./controls/progressbar.h"
// #include "./controls/slider.h"
// #include "./controls/spinner.h"
// #include "./controls/scrollbar.h"
// #include "./controls/tabcontrol.h"
// #include "./controls/datagrid.h"
// #include "./controls/calendar.h"
// #include "./controls/menu.h"
// #include "./controls/statusbar.h"
// #include "./controls/toolstrip.h"
// #include "./controls/panel.h"
// #include "./controls/progressbar.h"
// #include "./controls/progressbar.h"

// Global variables for the X11 display and window
Display* display;
Window window;
Pixmap pixmap; // Pixmap to serve as our drawable area
int screen;

// NAPI Callback Signature:
// static Napi::Function Napi::Function::New(
//     Napi::Env env,
//     Callable cb,
//     const char* utf8name = nullptr,
//     void* data = nullptr
// );


// Example of logging something from env
void LogEnvironmentInfo(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Output some information about the environment.
    // (Though `env` itself is not directly printable, we can get certain properties)
    
    if (env.IsExceptionPending()) {
        Napi::Error error = env.GetAndClearPendingException();
        std::cout << "Error occurred: " << error.Message() << std::endl;
    } else {
        std::cout << "INFO: Environment is OK, no pending exceptions." << std::endl;
    }
}

// Method to set window title
void SetWindowTitle(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    // Check if argument is a string
    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return;
    }

    // Get the title string from the first argument
    std::string title = info[0].As<Napi::String>().Utf8Value();

    // Set the window title using X11 function
    XStoreName(display, window, title.c_str());
    XFlush(display);  // Ensure the change is applied
}

// Method to set window size
void SetWindowSize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Check if we received 2 arguments (width and height)
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
        Napi::TypeError::New(env, "Expected two arguments: width and height").ThrowAsJavaScriptException();
        return;
    }

    // Get width and height from arguments
    int width = info[0].As<Napi::Number>().Int32Value();
    int height = info[1].As<Napi::Number>().Int32Value();

    // Resize the window using X11 function
    XResizeWindow(display, window, width, height);
    XFlush(display);  // Ensure the change is applied
}

// Method to handle X11 events
void EventLoop(const Napi::CallbackInfo& info) {

    // Define the button instance
    Button myButton;

    // Initialize the button properties
    myButton.x = 50;            // X position of the button
    myButton.y = 50;            // Y position of the button
    myButton.width = 100;       // Width of the button
    myButton.height = 40;       // Height of the button
    myButton.isPressed = false; // Initial state (not pressed)
    myButton.label = "Click Me"; // Button label
    myButton.bgColor = 0x444444;
    myButton.bgActiveColor = 0x777777;
    myButton.textColor = 0xffffff;
    myButton.textActiveColor = 0xffffff;
    myButton.borderColor = 0x000000;
    myButton.borderWidth = 2;
    myButton.borderRadius = 5;
    // myButton.font = "Arial";
    // myButton.fontSize = 14;
    // myButton.fontWeight = "bold";
    // myButton.fontColor = 0xffffff;
    // myButton.fontAlign = "center";
    // myButton.fontBaseline = "middle";
    // myButton.fontVariant = "normal";



    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == Expose) {

            DrawButton(display, window, myButton);

            // // Handle expose events (redraw the window)
            // XSetForeground(display, DefaultGC(display, DefaultScreen(display)), 0x000000); // Black color
            // XFillRectangle(display, window, DefaultGC(display, DefaultScreen(display)), 20, 20, 200, 100);

            // // Draw something (e.g., a red rectangle)
            // XSetForeground(display, DefaultGC(display, DefaultScreen(display)), 0xff0000); // Red color
            // XFillRectangle(display, window, DefaultGC(display, DefaultScreen(display)), 80, 80, 200, 100);

            XFlush(display);  // Ensure the changes are applied

        }
        if (event.type == KeyPress) {
            break; // Exit on key press
        }

        HandleMouseEvent(event, myButton, display, window);
    }
}

// Function to create the X11 window and return an object
Napi::Object CreateWindow(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Object windowObj = Napi::Object::New(env);

    // Open the display
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        Napi::Error::New(env, "Unable to open X display").ThrowAsJavaScriptException();
        return windowObj;
    }

    // Create a simple window
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        10, 10, 800, 600, 1,
        BlackPixel(display, screen), 
        WhitePixel(display, screen)
    );
    
    // std::cout << "Window created successfully" << std::endl;

    // Set window properties
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask);
    XMapWindow(display, window);

    // --------------------------------------

    XFlush(display);

    // // Cleanup
    // XFreeGC(display, gc);

    // Attach export functions to the window object
    windowObj.Set("setWindowTitle", Napi::Function::New(env, SetWindowTitle));
    windowObj.Set("setWindowTitle", Napi::Function::New(env, SetWindowTitle));
    windowObj.Set("setWindowSize", Napi::Function::New(env, SetWindowSize));
    windowObj.Set("eventLoop", Napi::Function::New(env, EventLoop));

    
    return windowObj;
}

// Initializer function to export methods to Node.js
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("logEnvInfo", Napi::Function::New(env, LogEnvironmentInfo));
    exports.Set("createWindow", Napi::Function::New(env, CreateWindow));
    return exports;
}

// Register and initialize the module
NODE_API_MODULE(window, Init)
