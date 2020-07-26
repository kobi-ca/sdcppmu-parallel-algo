
#include <cstdlib>   // for EXIT_FAILURE
#include <execution> // for the execution policy
#include <filesystem>// filesystem library
#include <iostream>
#include <numeric>// for transform_reduce()
#include <vector>

int main(int argc, char *argv[]) {
    // root directory is passed as command line argument:
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <path> \n";
        return EXIT_FAILURE;
    }
    const std::filesystem::path root{argv[1]};

    // init list of all file paths in passed file tree:
    std::vector<std::filesystem::path> paths;
    try {
        std::filesystem::recursive_directory_iterator dirpos{root};
        (void) std::copy(begin(dirpos), end(dirpos),
                         std::back_inserter(paths));
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // accumulate size of all regular files:
    const auto sz = std::transform_reduce(
            std::execution::par,                // parallel execution
            paths.cbegin(), paths.cend(),       // range
            std::uintmax_t{0},                  // initial value
            std::plus<>(),                      // accumulate ...
            [](const std::filesystem::path &p) {//  file size if regular file
                return is_regular_file(p) ? file_size(p)
                                          : std::uintmax_t{0};
            });
    std::clog << "size of all " << paths.size()
              << " regular files: " << sz << '\n';
}
