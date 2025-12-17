#!/bin/bash
# LeetCode Problem Fetcher
# Usage: ./fetch.sh <problem-slug>

if [ $# -eq 0 ]; then
    echo "Usage: $0 <problem-slug>"
    echo ""
    echo "Examples:"
    echo "  $0 two-sum"
    echo "  $0 trapping-rain-water"
    echo ""
    echo "Find the problem slug in the LeetCode URL:"
    echo "  https://leetcode.com/problems/[slug]/"
    exit 1
fi

# Check if get executable exists
if [ ! -f "./get" ]; then
    echo "Building get utility..."
    make
    if [ $? -ne 0 ]; then
        echo "Error: Failed to build get utility"
        exit 1
    fi
fi

# Run the get utility
./get "$1"
