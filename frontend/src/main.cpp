#include "webui.hpp"
#include <string>

int main() {
    webui::window win;
    
    // Show the window with initial HTML content
    win.show(R"(
        <html>
        <head>
            <script src="webui.js"></script>
            <title>Cosmic Architect</title>
        </head>
        <body>
            <h1>Cosmic Architect</h1>
            <p>Welcome to the universe simulator!</p>
        </body>
        </html>
    )");

    // Wait for the window
    webui::wait();
    return 0;
} 