This README exists to log some of the answers I have submitted to leetcode.

## Setup Tool

This repository includes a `get` utility to automatically fetch LeetCode problems and create template files.

### Building the Tool

```bash
make
```

This will compile `get.cpp` into an executable named `get`.

### Usage

**Option 1: Using the shell script (recommended)**
```bash
./fetch.sh <problem-number-or-slug>
```

**Option 2: Direct executable**
```bash
./get <problem-number-or-slug>
```

**Examples:**
```bash
# Using problem number
./fetch.sh 1                    # Creates 1.cpp (Two Sum)
./fetch.sh 53                   # Creates 53.cpp (Maximum Subarray)

# Using problem slug
./fetch.sh two-sum              # Creates 1.cpp
./fetch.sh trapping-rain-water  # Creates 42.cpp
```

**Note:** You can use either:
- **Problem number** (e.g., `1`, `53`, `42`) - the number shown on LeetCode
- **Problem slug** (the URL-friendly name from the URL, e.g., `two-sum`, `maximum-subarray`)

Find these in the LeetCode URL: https://leetcode.com/problems/**[slug]**/

### What It Does

1. Fetches problem information from LeetCode (title, difficulty, URL)
2. Creates a new `.cpp` file with:
   - Problem metadata in comments
   - Common C++ includes
   - Solution class template
   - Main function with test case section

### Requirements

- C++17 compiler (g++ or clang++)
- `curl` (for API requests)
- Internet connection 
