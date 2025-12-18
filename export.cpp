/*
 * LeetCode Solution Exporter
 * Extracts the Solution class from a file for easy copying to LeetCode
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

// ANSI color codes
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Function to check if file exists
bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

// Helper: determine directory range for problem ID
string getDirectoryForProblemId(int problemId) {
    int rangeStart = (problemId / 100) * 100;
    int rangeEnd = rangeStart + 99;
    return to_string(rangeStart) + "-" + to_string(rangeEnd);
}

// Helper: search for file in directory structure or root
string findProblemFile(const string& filename) {
    // First check if file exists in current directory
    if (fileExists(filename)) {
        return filename;
    }
    
    // Extract problem ID from filename (e.g., "160.cpp" -> 160, "160-1.cpp" -> 160)
    size_t dotPos = filename.find('.');
    if (dotPos == string::npos) return "";
    
    string baseName = filename.substr(0, dotPos);
    size_t dashPos = baseName.find('-');
    string problemNumStr = (dashPos != string::npos) ? baseName.substr(0, dashPos) : baseName;
    
    // Try to parse problem ID
    int problemId;
    try {
        problemId = stoi(problemNumStr);
    } catch (...) {
        return "";
    }
    
    // Try directory for problem ID range
    string directory = getDirectoryForProblemId(problemId);
    string fullPath = directory + "/" + filename;
    if (fileExists(fullPath)) {
        return fullPath;
    }
    
    return "";
}

// Function to copy text to clipboard (macOS)
bool copyToClipboard(const string& text) {
    FILE* pipe = popen("pbcopy", "w");
    if (!pipe) {
        return false;
    }
    
    fwrite(text.c_str(), sizeof(char), text.length(), pipe);
    int result = pclose(pipe);
    
    return (result == 0);
}

// Function to create directory if it doesn't exist
bool createDirectory(const string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return true; // Directory already exists
    }
    
    // Try to create directory
    string command = "mkdir -p \"" + path + "\"";
    return (system(command.c_str()) == 0);
}

// Function to save solution to file
bool saveToFile(const vector<string>& solutionLines, const string& outputPath) {
    // Extract directory path and create it if needed
    size_t lastSlash = outputPath.find_last_of('/');
    if (lastSlash != string::npos) {
        string dirPath = outputPath.substr(0, lastSlash);
        if (!createDirectory(dirPath)) {
            return false;
        }
    }
    
    ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        return false;
    }
    
    for (const string& line : solutionLines) {
        outFile << line << endl;
    }
    
    outFile.close();
    return true;
}

// Function to extract and format the Solution class
bool exportSolution(const string& filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << RED << "Error: Could not open file " << filepath << RESET << endl;
        return false;
    }
    
    vector<string> solutionLines;
    string line;
    bool inSolutionClass = false;
    int braceCount = 0;
    bool foundClass = false;
    
    while (getline(file, line)) {
        // Look for the start of the Solution class
        if (!inSolutionClass && line.find("class Solution") != string::npos) {
            inSolutionClass = true;
            foundClass = true;
            solutionLines.push_back(line);
            
            // Count braces in this line
            for (char c : line) {
                if (c == '{') braceCount++;
                else if (c == '}') braceCount--;
            }
            continue;
        }
        
        // If we're inside the Solution class, keep collecting lines
        if (inSolutionClass) {
            solutionLines.push_back(line);
            
            // Count braces
            for (char c : line) {
                if (c == '{') braceCount++;
                else if (c == '}') braceCount--;
            }
            
            // When braces balance back to 0, we've reached the end of the class
            if (braceCount == 0) {
                break;
            }
        }
    }
    
    file.close();
    
    if (!foundClass) {
        cerr << RED << "Error: No Solution class found in " << filepath << RESET << endl;
        return false;
    }
    
    // Build the solution text
    string solutionText;
    for (const string& line : solutionLines) {
        solutionText += line + "\n";
    }
    
    // Print header
    cout << BLUE << "═══════════════════════════════════════════════════════════════" << RESET << endl;
    cout << GREEN << "Solution exported from: " << RESET << filepath << endl;
    cout << BLUE << "═══════════════════════════════════════════════════════════════" << RESET << endl;
    cout << endl;
    
    // Print the solution class
    cout << solutionText;
    
    cout << BLUE << "═══════════════════════════════════════════════════════════════" << RESET << endl;
    
    // Determine output file path (e.g., 100-199/solutions/121-1.txt)
    string outputPath;
    size_t lastSlash = filepath.find_last_of('/');
    if (lastSlash != string::npos) {
        // File is in a subdirectory (e.g., "100-199/121-1.cpp")
        string directory = filepath.substr(0, lastSlash);
        string filename = filepath.substr(lastSlash + 1);
        
        // Change .cpp to .txt
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != string::npos) {
            filename = filename.substr(0, dotPos) + ".txt";
        }
        
        outputPath = directory + "/solutions/" + filename;
    } else {
        // File is in current directory
        string filename = filepath;
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != string::npos) {
            filename = filename.substr(0, dotPos) + ".txt";
        }
        outputPath = "solutions/" + filename;
    }
    
    // Try to copy to clipboard
    bool copiedToClipboard = copyToClipboard(solutionText);
    
    // Always save to file as well
    bool savedToFile = saveToFile(solutionLines, outputPath);
    
    if (copiedToClipboard) {
        cout << GREEN << "✓ Copied to clipboard!" << RESET << endl;
        if (savedToFile) {
            cout << GREEN << "✓ Saved to " << outputPath << RESET << endl;
        }
    } else {
        // Clipboard failed
        if (savedToFile) {
            cout << YELLOW << "⚠ Clipboard copy failed" << RESET << endl;
            cout << GREEN << "✓ Saved to " << outputPath << " (Ctrl+A, Ctrl+C to copy)" << RESET << endl;
        } else {
            cout << YELLOW << "⚠ Could not copy to clipboard or save to file" << RESET << endl;
            cout << GREEN << "✓ Ready to copy from above!" << RESET << endl;
        }
    }
    
    cout << BLUE << "═══════════════════════════════════════════════════════════════" << RESET << endl;
    
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <problem_number>[.cpp]" << endl;
        cerr << "Examples:" << endl;
        cerr << "  " << argv[0] << " 121" << endl;
        cerr << "  " << argv[0] << " 121-1" << endl;
        cerr << "  " << argv[0] << " 121.cpp" << endl;
        return 1;
    }
    
    string input = argv[1];
    string filename;
    
    // If input doesn't end with .cpp, add it
    if (input.find(".cpp") == string::npos) {
        filename = input + ".cpp";
    } else {
        filename = input;
    }
    
    // Find the file
    string filepath = findProblemFile(filename);
    
    if (filepath.empty()) {
        cerr << RED << "Error: Could not find file " << filename << RESET << endl;
        cerr << "Searched in:" << endl;
        cerr << "  - Current directory" << endl;
        
        // Extract problem ID to show which directory was searched
        size_t dotPos = filename.find('.');
        if (dotPos != string::npos) {
            string baseName = filename.substr(0, dotPos);
            size_t dashPos = baseName.find('-');
            string problemNumStr = (dashPos != string::npos) ? baseName.substr(0, dashPos) : baseName;
            
            try {
                int problemId = stoi(problemNumStr);
                string directory = getDirectoryForProblemId(problemId);
                cerr << "  - " << directory << "/" << endl;
            } catch (...) {}
        }
        
        return 1;
    }
    
    // Export the solution
    if (!exportSolution(filepath)) {
        return 1;
    }
    
    return 0;
}
