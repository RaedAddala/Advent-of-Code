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
	crossings := 0

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
			continue
		}

		if len(line) < 2 {
			log.Fatalf("Line %d: too short", lineNum)
		}

		dir := strings.ToUpper(line[:1])
		numStr := line[1:]
		num, err := strconv.Atoi(numStr)
		if err != nil {
			log.Fatalf("Line %d: invalid number '%s'", lineNum, numStr)
		}

		delta := num
		if dir == "L" {
			delta = -num
		} else if dir != "R" {
			log.Fatalf("Line %d: invalid direction '%s'", lineNum, dir)
		}

		oldTotal := total

		total += delta
		total = ((total % 100) + 100) % 100

		crossings += countCrossings(oldTotal, delta)
	}

	if err := scanner.Err(); err != nil {
		log.Fatalf("Error reading file: %v", err)
	}

	fmt.Printf("Number of times passed through 0: %d\n", crossings)
}

func countCrossings(oldPos, delta int) int {
	if delta == 0 {
		return 0 // no movement
	}

	count := 0
	step := 1
	if delta < 0 {
		step = -1
	}

	pos := oldPos
	for i := 0; i < abs(delta); i++ {
		pos += step
		if ((pos%100)+100)%100 == 0 {
			count++
		}
	}

	return count
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
