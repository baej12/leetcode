#!/bin/bash
# Build script for LeetCode helper tools
# Works in Git Bash without requiring make

set -e

CXX="g++"
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

build_all() {
    echo "Building all tools..."
    build_export
    build_get
    build_test
    echo "✓ All tools built successfully"
}

build_export() {
    echo "Compiling export..."
    $CXX $CXXFLAGS -o export.exe export.cpp
    echo "✓ export.exe built"
}

build_get() {
    echo "Compiling get..."
    $CXX $CXXFLAGS -o get.exe get.cpp
    echo "✓ get.exe built"
}

build_test() {
    echo "Compiling test..."
    $CXX $CXXFLAGS -o test.exe test.cpp
    echo "✓ test.exe built"
}

clean() {
    echo "Cleaning build artifacts..."
    rm -f export.exe get.exe test.exe
    echo "✓ Clean complete"
}

# Parse command
case "${1:-all}" in
    all)
        build_all
        ;;
    export)
        build_export
        ;;
    get)
        build_get
        ;;
    test)
        build_test
        ;;
    clean)
        clean
        ;;
    rebuild)
        clean
        build_all
        ;;
    *)
        echo "Usage: $0 [all|export|get|test|clean|rebuild]"
        exit 1
        ;;
esac
