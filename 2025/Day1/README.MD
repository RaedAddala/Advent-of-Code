# Advent of Code 2025 – Day 1: Secret Entrance

[Official Problem](https://adventofcode.com/2025/day/1)

## Solution

### Part 1

Algorithm:

- Each non-empty input line is a move: _R_ or _L_ (case-insensitive).
- Start accumulator total = $50$.
- Parse first char as direction (must be _R_ or _L_), remaining substring as a positive integer.
- Apply: _R_ adds, _L_ subtracts.
- After every operation wrap into $0..99$: ((total % 100) + 100) % 100.
- Count how many times the wrapped value equals 0.
- Output that zero count.

Complexity: $O(N)$ time, $O(1)$ space.

Implementation notes:

- V1 uses ``strconv`` and higher-level string helpers.
- V2 performs manual byte-wise parsing and in-place uppercasing to reduce allocations and slightly improve speed.
- Both validate format early and exit on malformed input.

Edge cases:

- Empty lines skipped.
- Large intermediate positives/negatives safely wrapped.
- Any non-digit in the numeric portion triggers a fatal error.

Example:
Input:
R10
L20
R60
Processing: 50->60->40->0 (zero counted once). Output: Number of Zeros: 1

### Part 2

## Folder Structure

```plaintext
.
├── Part1
│   ├── V1          # First working solution
│   │   └── main.go
│   └── V2          # Optimized version
│       └── main.go
├── Part2
├── input.txt 
├── test.txt
└── README.md
```

## How to Run

```bash
# From the project root

# Part 1 – Version 1
cd Part1/V1
go build -ldflags="-s -w" -o day1_v1 main.go
./day1_v1 ../../input.txt

# Part 1 – Version 2
cd Part1/V2
go build -ldflags="-s -w" -o day1_v2 main.go
./day1_v2 ../../input.txt

# Test with the example
./day1_v2 ../../test.txt
```

## What is hyperfine?

**hyperfine** is the modern, statistically-robust benchmarking tool. It automatically:

- Runs your program hundreds of times
- Does warm-up runs (so disk/cache effects don’t skew results)
- Removes outliers
- Shows mean ± standard deviation, min/max range

## How to Benchmark

### Build the Release Binary

Go does not have separate "debug" and "production" build modes. The default binary contains extra information useful for debugging and profiling.

For the fastest and smallest binary, we strip everything that is not needed at runtime:

```bash
# From the project root
cd Part1/V2
go build -ldflags="-s -w -buildid=" -trimpath -o day1_v2 main.go
```

**What these flags do:**

- `-s` → remove symbol table  
- `-w` → remove DWARF debug information  
- `-buildid=` → omit the build identifier  
- `-trimpath` → remove local paths from the binary (cleaner + slightly smaller)

**Result:**

- Significantly smaller binary  
- Faster program startup  
- No change to actual runtime performance  
- Loss of readable stack traces and debugging symbols (expected and desired for release)

### Benchmark using ``Hyperfine``

1. Quick command:

    ```bash
    hyperfine --shell=none --warmup 10 --min-runs 200 "./day1_v2 ../../input.txt"
    ```

2. Precise (removes the “less than 5 ms” warning + more stable):

    ```bash
    hyperfine -N -w 10 -r 1000 "./day1_v2 ../../input.txt"
    # -N = --shell=none     faster + no shell overhead warning
    # -w = --warmup
    # -r = --runs
    ```

3. Most Precise Benchmark:

    ```bash
    sudo nice -n -10 hyperfine -N -w 20 -r 2000 "./day1_v1 ../../input.txt"
    ```

## Benchmark Results for Part 1

| Version | Time (hyperfine)              | Command Used                              |
|---------|-------------------------------|-------------------------------------------|
| V1      | Time (mean ± σ):       1.4 ms ±   0.2 ms    [User: 1.0 ms, System: 0.4 ms] | `sudo nice -n -10 hyperfine -N -w 20 -r 2000 "./day1_v1 ../../input.txt"`|
| V2      | Time (mean ± σ):       1.3 ms ±   0.2 ms    [User: 1.0 ms, System: 0.3 ms] | `sudo nice -n -10 hyperfine -N -w 20 -r 2000 "./day1_v2 ../../input.txt"` |

## Benchmark Results for Part 2

| Version | Time (hyperfine)              | Command Used                              |
|---------|-------------------------------|-------------------------------------------|
| V1      | Time (mean ± σ):       1.4 ms ±   0.2 ms    [User: 1.0 ms, System: 0.4 ms] | `sudo nice -n -10 hyperfine -N -w 20 -r 2000 "./day1_v1 ../../input.txt"`|
| V2      | Time (mean ± σ):       1.3 ms ±   0.2 ms    [User: 1.0 ms, System: 0.3 ms] | `sudo nice -n -10 hyperfine -N -w 20 -r 2000 "./day1_v2 ../../input.txt"` |
