// src/index.ts
const WindowAPI = require('../native/build/Release/windowAPI.node');

// Function to create an application using the C++ windowAPI addon
function createApp(...params: any) {
    const title = params[0].title || 'Untitled Application';
    const width = params[0].width || 800;
    const height = params[0].height || 600;

    WindowAPI.logEnvInfo();

    // Create the window
    const window = WindowAPI.createWindow(null);

    // Resize the window after it's created
    window.setWindowSize(width, height);
    
    // Set the windows title
    window.setWindowTitle(title);

    // Run the event loop to keep the window active
    window.eventLoop();

}

createApp({
    title: "Cross Platform Application X11 Example Window",
    width: 1024,
    height:768
});
