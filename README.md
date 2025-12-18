This README exists to log some of the answers I have submitted to leetcode.

## Tools

This repository includes three utilities:
- **`get`** - Fetches LeetCode problems and creates template files
- **`test`** - Compiles and tests your solutions
- **`export`** - Exports your solution in a clean, copy-pastable format for LeetCode

### Building the Tools

```bash
make          # Builds all utilities
make get      # Builds only the get utility
make test     # Builds only the test utility
make export   # Builds only the export utility
```

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

The `get` utility:
1. Fetches problem information from LeetCode (title, difficulty, URL, description, examples)
2. Creates a new `.cpp` file with:
   - Problem metadata and full description in comments
   - Example test cases from the problem
   - Common C++ includes
   - Solution class template
   - Main function with test case section

### File Naming

If a file already exists (e.g., `42.cpp`), the tool automatically creates an incremented version (`42-1.cpp`, `42-2.cpp`, etc.) to avoid overwriting your work.

## Testing Tool

### Usage

```bash
./test <solution-file.cpp>
```

**Example:**
```bash
./test 1.cpp
./test 42-1.cpp
```

### What It Does

The `test` utility:
1. Compiles your solution with optimizations (`-O2`)
2. Extracts test inputs from the "Example Test Cases" section
3. Runs your program with those inputs
4. Displays the output for verification

### Notes

- Your solution's `main()` function should read from standard input and write to standard output
- The tool shows compilation warnings/errors if any
- The executable is automatically cleaned up after testing
- You should verify the output matches the expected results from the problem description

## Export Tool

### Usage

```bash
./export <problem-number>
```

**Examples:**
```bash
./export 121        # Exports 121.cpp
./export 121-1      # Exports 121-1.cpp
./export 121.cpp    # Also works with .cpp extension
```

### What It Does

The `export` utility:
1. Locates your solution file in the appropriate directory
2. Extracts only the `Solution` class from your file
3. Displays it in a clean, formatted output
4. **Automatically copies to your clipboard** (macOS)
5. **Saves to `<directory>/solutions/<problem>.txt`** (e.g., `100-199/solutions/121-1.txt`)

This removes all the test code, includes, and comments, leaving just the solution that LeetCode expects. After running, you can paste directly into LeetCode (⌘+V) or open the .txt file for easy Ctrl+A, Ctrl+C copying!

### Requirements

- C++17 compiler (g++ or clang++)
- `curl` (for API requests - get tool only)
- Internet connection (for get tool only) 
