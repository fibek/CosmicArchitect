#include "webui.hpp"
#include <string>

int main() {
    webui::window win;
    
    // Set the base directory for UI files
    win.set_root_folder("../ui");
    
    // Show the UI starting with index.html
    win.show("index.html");
    
    // Wait for the window
    webui::wait();
    return 0;
} 