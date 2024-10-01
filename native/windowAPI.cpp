#include <napi.h>
#include <X11/Xlib.h>
#include <iostream>
#include <string>

// Global variables for the X11 display and window
Display* display;
Window window;

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
    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Optionally handle expose events to redraw window contents
        }
        if (event.type == KeyPress) {
            break; // Exit on key press
        }
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
    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(
        display,
        RootWindow(display, screen),
        10, 10, 800, 600, 1,
        BlackPixel(display, screen), 
        WhitePixel(display, screen)
    );
    
    std::cout << "Window created successfully" << std::endl;

    // Set window properties
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

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
