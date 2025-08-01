#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring> // for std::memcpy

namespace fs = std::filesystem;

// Detect architecture from ELF header
std::string getArchitecture(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "[ERROR] Cannot open file: " << filepath << "\n";
        return "unknown";
    }

    unsigned char header[64] = {};
    file.read(reinterpret_cast<char*>(header), sizeof(header));

    if (file.gcount() < 20) {
        std::cerr << "[WARNING] File too short: " << filepath << "\n";
        return "unknown";
    }

    if (header[0] != 0x7f || header[1] != 'E' || header[2] != 'L' || header[3] != 'F') {
        std::cerr << "[WARNING] Invalid ELF magic in: " << filepath << "\n";
        return "unknown";
    }

    // EI_DATA tells us endian-ness: 1 = little, 2 = big
    uint8_t ei_data = header[5];
    uint16_t e_machine = 0;

    if (ei_data == 1) {
        // little endian
        e_machine = static_cast<uint16_t>(header[18]) | (static_cast<uint16_t>(header[19]) << 8);
    } else if (ei_data == 2) {
        // big endian
        e_machine = static_cast<uint16_t>(header[19]) | (static_cast<uint16_t>(header[18]) << 8);
    } else {
        std::cerr << "[WARNING] Unknown endianness in: " << filepath << "\n";
        return "unknown";
    }

    switch (e_machine) {
        case 0x28: return "armeabi-v7a";
        case 0xB7: return "arm64-v8a";
        case 0x03: return "x86";
        case 0x3E: return "x86-64";
        case 0x08: return "mips";
        default:
            std::cerr << "[WARNING] Unknown e_machine (0x"
                      << std::hex << e_machine << std::dec
                      << ") in: " << filepath << "\n";
            return "unknown";
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./arch_detector <folder_path>\n";
        return 1;
    }

    fs::path folderPath(argv[1]);
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Invalid directory.\n";
        return 1;
    }

    int libCount = 0;
    std::vector<std::pair<std::string, std::string>> results;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_regular_file()) continue;

        std::string filename = entry.path().filename().string();
        if (entry.path().extension() != ".so") continue;

        std::string arch = getArchitecture(entry.path().string());
        if (arch == "unknown") continue;

        libCount++;
        results.emplace_back(filename, arch);
    }

    std::cout << "\nTotal number of libraries: " << libCount << "\n\n";
    std::cout << std::left << std::setw(35) << "File" << "ArchType\n";
    std::cout << std::setw(35) << "====" << "========\n";

    for (const auto& [file, arch] : results) {
        std::cout << std::left << std::setw(35) << file << arch << "\n";
    }

    return 0;
}
