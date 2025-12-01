package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Printf("Usage: %s <filename>\n", os.Args[0])
		os.Exit(1)
	}

	filename := os.Args[1]
	total := 50
	totalZeros := 0

	file, err := os.Open(filename)
	if err != nil {
		log.Fatalf("Error opening file: %v", err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	lineNum := 0
	for scanner.Scan() {
		lineNum++
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue // skip empty lines
		}

		if len(line) < 2 {
			log.Fatalf("Line %d: too short, expected R/L followed by number", lineNum)
		}

		dir := strings.ToUpper(line[:1])
		numStr := line[1:]

		num, err := strconv.Atoi(numStr)
		if err != nil {
			log.Fatalf("Line %d: invalid number '%s'", lineNum, numStr)
		}

		switch dir {
		case "R":
			total += num
		case "L":
			total -= num
		default:
			log.Fatalf("Line %d: invalid direction '%s', must be R or L", lineNum, dir)
		}
		total = ((total % 100) + 100) % 100
		if total == 0 {
			totalZeros += 1
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatalf("Error reading file: %v", err)
	}

	fmt.Printf("Number of Zeros: %d\n", totalZeros)

}
