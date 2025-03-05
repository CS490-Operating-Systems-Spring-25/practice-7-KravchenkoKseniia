#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

int main() {
    std::ofstream file("task2.1/test.txt");
    if (!file) {
        std::cout << "Error: Unable to open file.\n";
        return 1;
    }

    for (int i = 0; i < 1000; ++i) {
        file << "Line " << i << std::endl;
        file.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    file.close();
    return 0;
}
