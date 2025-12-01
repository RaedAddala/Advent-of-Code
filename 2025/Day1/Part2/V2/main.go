package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Usage: %s <filename>\n", os.Args[0])
		os.Exit(1)
	}

	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatalf("Error opening file: %v", err)
	}
	defer file.Close()

	var total int64 = 50
	totalZeros := 0
	lineNum := 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lineNum++
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue //skip empty lines
		}

		if len(line) < 2 {
			log.Fatalf("Line %d: too short, expected format like R10 or L5", lineNum)
		}

		dirByte := line[0]
		dir := dirByte
		if dirByte >= 'a' && dirByte <= 'z' {
			dir = dirByte - 'a' + 'A'
		}
		numStr := line[1:]

		num := 0
		for _, c := range []byte(numStr) {
			if c < '0' || c > '9' {
				log.Fatalf("Line %d: invalid number '%s'", lineNum, numStr)
			}
			num = num*10 + int(c-'0')
		}

		switch dir {
		case 'R':
			total += int64(num)
		case 'L':
			total -= int64(num)
		default:
			log.Fatalf("Line %d: invalid direction '%c', must be R or L", lineNum, dir)
		}

		total = ((total % 100) + 100) % 100
		if total == 0 {
			totalZeros++
		}
	}

	if err := scanner.Err(); err != nil {
		log.Fatalf("Error reading file: %v", err)
	}

	fmt.Printf("Number of Zeros: %d\n", totalZeros)
}
