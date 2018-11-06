#include <iostream>

#include "gltools/Window"

int main(int argc, char **argv) {
    GLTools::Window window("Hello world");
    return window.run();
}