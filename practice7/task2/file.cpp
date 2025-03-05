
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

int main() {
    std::vector<std::ofstream> fileStreams;
    const int numFiles = 15;

    for (int i = 0; i < numFiles; i++) {
        std::string fileName = "file_" + std::to_string(i) + ".txt";
        fileStreams.emplace_back(fileName);
        
        if (!fileStreams.back()) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return 1;
        }

        fileStreams.back() << "This is file " << i << "\n";
        fileStreams.back().flush();

        std::cout << "Opened: " << fileName << std::endl;
    }

    std::cout << "Files are open" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(90));

    return 0;
}
