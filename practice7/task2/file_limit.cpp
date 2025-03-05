#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <sys/resource.h>
#include <unistd.h>
#include <cstdlib>
#include <fstream>

int main() {
    const int batchSize = 1000;
    const int totalFiles = 100000;
    std::vector<std::ofstream> fileStreams;
    fileStreams.reserve(batchSize);

    struct rlimit lim;
    if (getrlimit(RLIMIT_NOFILE, &lim) == 0) {
        std::cout << "Current file descriptor limit: " << lim.rlim_cur << " (max: " << lim.rlim_max << ")\n";
        if (lim.rlim_cur < 65535) {
            lim.rlim_cur = 65535;
            lim.rlim_max = 65535;
            if (setrlimit(RLIMIT_NOFILE, &lim) == 0) {
                std::cout << "Successfully increased file descriptor limit to " << 65535 << "\n";
            } else {
                std::cerr << "Failed to set new file descriptor limit.\n";
            }
        }
    } else {
        std::cerr << "Failed to retrieve file descriptor limit.\n";
    }
    
    for (int i = 0; i < totalFiles; i++) {
        std::string fileName = "file_" + std::to_string(i) + ".txt";
        fileStreams.emplace_back(fileName);
        
        if (!fileStreams.back()) {
            std::cerr << "Error opening file: " << fileName << ". Reached system limit?\n";
            break;
        }

        fileStreams.back() << "This is file " << i << "\n";
        fileStreams.back().flush();
        
        if (i % batchSize == 0 && i > 0) {
            std::cout << "Opened " << i << " files. Sleeping for 1 second...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::cout << "Attempted to open " << fileStreams.size() << " files.\n";
    std::this_thread::sleep_for(std::chrono::seconds(90));
    return 0;
}
