#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <ranges>

using ull = unsigned long long;
using ll = long long;

std::ifstream file;



void cleanup()
{
    if (file.is_open())
    {
        file.close();
        std::cout << "File closed successfully.\n";
    }
}

int main(const int argc, const char *const argv[])
{
    // Ensure the correct number of arguments
    if (argc != 2)
    {
        std::cerr << "Error: You should specify the relative path to the input file when running the script." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Register cleanup function
    std::atexit(cleanup);

    const char *filePath = argv[1];

    file.open(filePath);
    if (!file)
    {
        std::cerr << "Error: The file '" << filePath << "' does not exist or cannot be opened." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (file.bad())
    {
        std::cerr << "Error: Failed to read the file." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    file.seekg(0, std::ios::end);
    ull maxLines = static_cast<ull>(file.tellg() / 4);
    file.seekg(0, std::ios::beg);
    std::cout << maxLines << std::endl;

    // Save the original stream buffer of std::cin
    std::streambuf *originalCinBuffer = std::cin.rdbuf();
    // Redirect std::cin to read from the file
    std::cin.rdbuf(file.rdbuf());
    std::vector<ll> pointsA, pointsB;

    pointsA.reserve(maxLines);
    pointsB.reserve(maxLines);

    ll a, b;
    while (std::cin >> a >> b)
    {
        pointsA.emplace_back(a);
        pointsB.emplace_back(b);
    }
    // Restore the original stream buffer of std::cin
    std::cin.rdbuf(originalCinBuffer);

    // do the calculations
    std::sort(pointsA.begin(), pointsA.end());
    std::sort(pointsB.begin(), pointsB.end());

    const auto zipped = std::ranges::views::zip(pointsA, pointsB);

    ull sum = std::transform_reduce(
        zipped.begin(),
        zipped.end(),
        0ull,
        std::plus<>{}, // Reduction (sum the differences)
        [](auto pair)
        { return std::abs(pair.first - pair.second); } // Transformation (calculate the absolute difference)
    );
    std::cout << "Sum of differences: " << sum << '\n';

    return 0;
}
