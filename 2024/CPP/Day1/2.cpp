#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <ranges>
#include <chrono>

using ull = unsigned long long;
using ll = long long;

std::ifstream file;

// custom hash to ensure safety of unordered map against collisions ( I use this technique especially in codeforces rounds where someone may hack my solution)
struct custom_hash
{
    static ull splitmix64(ull x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(ull x) const
    {
        static const ull FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

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

    std::vector<ll> pointsA;
    std::unordered_map<ll, int, custom_hash> repetitions;

    pointsA.reserve(maxLines);

    ll a, b;
    while (std::cin >> a >> b)
    {
        pointsA.emplace_back(a);
        ++repetitions[b];
    }
    // Restore the original stream buffer of std::cin
    std::cin.rdbuf(originalCinBuffer);

    // ull sum = 0ull;
    // const ull s = pointsA.size();
    // for (size_t i = 0; i < s; ++i)
    // {
    //     sum += pointsA[i] * repetitions[pointsA[i]];
    // }

    ull sum = std::transform_reduce(
        pointsA.begin(),
        pointsA.end(),
        0ull,
        std::plus<>(),
        [&repetitions](const ll &point)
        { return point * repetitions[point]; });

    std::cout << "Sum of differences: " << sum << '\n';

    return 0;
}
