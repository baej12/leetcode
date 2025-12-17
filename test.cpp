/*
 * LeetCode Solution Tester
 * Compiles and tests C++ solution files against example test cases
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sys/stat.h>

using namespace std;

// ANSI color codes
const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";

// Function to check if file exists
bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

// Function to execute a command and capture output
string executeCommand(const string& command) {
    string result = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Error: Could not execute command" << endl;
        return "";
    }
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
    int exitCode = pclose(pipe);
    if (exitCode != 0) {
        return ""; // Command failed
    }
    
    return result;
}

// Function to parse example test cases from file
vector<string> parseExampleTestCases(const string& filename) {
    vector<string> testCases;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << RED << "✗ Error: Could not open file " << filename << RESET << endl;
        return testCases;
    }
    
    string line;
    bool inExampleSection = false;
    
    while (getline(file, line)) {
        // Look for "Example Test Cases:" section
        if (line.find("Example Test Cases:") != string::npos) {
            inExampleSection = true;
            continue;
        }
        
        // Stop at end of comment block
        if (inExampleSection && line.find("*/") != string::npos) {
            break;
        }
        
        // Extract test case lines
        if (inExampleSection) {
            // Remove comment markers and whitespace
            size_t pos = line.find("* ");
            if (pos != string::npos) {
                string testCase = line.substr(pos + 2);
                // Trim whitespace
                size_t start = testCase.find_first_not_of(" \t");
                if (start != string::npos) {
                    testCase = testCase.substr(start);
                    size_t end = testCase.find_last_not_of(" \t\r\n");
                    if (end != string::npos) {
                        testCase = testCase.substr(0, end + 1);
                    }
                    if (!testCase.empty()) {
                        testCases.push_back(testCase);
                    }
                }
            }
        }
    }
    
    file.close();
    return testCases;
}

// Function to extract expected outputs from problem description
vector<pair<vector<string>, string>> parseExamplesFromDescription(const string& filename) {
    vector<pair<vector<string>, string>> examples;
    ifstream file(filename);
    
    if (!file.is_open()) {
        return examples;
    }
    
    string line;
    bool inDescription = false;
    vector<string> currentInput;
    string currentOutput;
    bool expectingInput = false;
    bool expectingOutput = false;
    
    while (getline(file, line)) {
        if (line.find("Description:") != string::npos) {
            inDescription = true;
            continue;
        }
        
        if (inDescription && line.find("Example Test Cases:") != string::npos) {
            break;
        }
        
        if (inDescription) {
            // Look for "Input:" and "Output:" patterns
            if (line.find("Input:") != string::npos) {
                // Save previous example if exists
                if (!currentInput.empty() && !currentOutput.empty()) {
                    examples.push_back({currentInput, currentOutput});
                }
                currentInput.clear();
                currentOutput.clear();
                expectingInput = true;
                expectingOutput = false;
                
                // Extract input from same line
                size_t inputPos = line.find("Input:");
                if (inputPos != string::npos) {
                    size_t start = line.find_first_not_of(" \t", inputPos + 6);
                    if (start != string::npos) {
                        string inputLine = line.substr(start);
                        // Parse comma-separated inputs
                        size_t pos = 0;
                        while ((pos = inputLine.find(" = ")) != string::npos) {
                            size_t valueStart = pos + 3;
                            size_t valueEnd = inputLine.find(",", valueStart);
                            if (valueEnd == string::npos) {
                                valueEnd = inputLine.length();
                            }
                            string value = inputLine.substr(valueStart, valueEnd - valueStart);
                            // Trim
                            size_t trimStart = value.find_first_not_of(" \t");
                            size_t trimEnd = value.find_last_not_of(" \t,");
                            if (trimStart != string::npos && trimEnd != string::npos) {
                                value = value.substr(trimStart, trimEnd - trimStart + 1);
                                currentInput.push_back(value);
                            }
                            inputLine = inputLine.substr(valueEnd);
                        }
                    }
                }
            } else if (line.find("Output:") != string::npos) {
                expectingInput = false;
                expectingOutput = true;
                
                // Extract output from same line
                size_t outputPos = line.find("Output:");
                if (outputPos != string::npos) {
                    size_t start = line.find_first_not_of(" \t", outputPos + 7);
                    if (start != string::npos) {
                        currentOutput = line.substr(start);
                        // Trim
                        size_t trimEnd = currentOutput.find_last_not_of(" \t\r\n");
                        if (trimEnd != string::npos) {
                            currentOutput = currentOutput.substr(0, trimEnd + 1);
                        }
                    }
                }
            }
        }
    }
    
    // Add last example
    if (!currentInput.empty() && !currentOutput.empty()) {
        examples.push_back({currentInput, currentOutput});
    }
    
    file.close();
    return examples;
}

// Function to compile the solution
bool compileSolution(const string& sourceFile, const string& outputFile) {
    cout << BLUE << "Compiling " << sourceFile << "..." << RESET << endl;
    
    string compileCmd = "g++ -std=c++17 -O2 -o " + outputFile + " " + sourceFile + " 2>&1";
    string compileOutput = executeCommand(compileCmd);
    
    if (!fileExists(outputFile)) {
        cerr << RED << "✗ Compilation failed:" << RESET << endl;
        cerr << compileOutput << endl;
        return false;
    }
    
    if (!compileOutput.empty()) {
        cout << YELLOW << "⚠ Compilation warnings:" << RESET << endl;
        cout << compileOutput << endl;
    }
    
    cout << GREEN << "✓ Compilation successful" << RESET << endl;
    return true;
}

// Function to run tests with input
string runTestWithInput(const string& executable, const vector<string>& inputs) {
    string inputStr = "";
    for (const auto& input : inputs) {
        inputStr += input + "\n";
    }
    
    string command = "echo '" + inputStr + "' | ./" + executable + " 2>&1";
    return executeCommand(command);
}

// Function to trim whitespace
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <solution-file.cpp>" << endl;
        cerr << "Example: " << argv[0] << " 42.cpp" << endl;
        return 1;
    }
    
    string sourceFile = argv[1];
    
    // Check if source file exists
    if (!fileExists(sourceFile)) {
        cerr << RED << "✗ Error: File '" << sourceFile << "' not found" << RESET << endl;
        return 1;
    }
    
    // Generate executable name
    string executableName = "test_" + sourceFile.substr(0, sourceFile.find_last_of('.'));
    
    // Compile the solution
    if (!compileSolution(sourceFile, executableName)) {
        return 1;
    }
    
    cout << endl;
    
    // Parse test cases
    vector<string> testCases = parseExampleTestCases(sourceFile);
    
    if (testCases.empty()) {
        cout << YELLOW << "⚠ No example test cases found in file" << RESET << endl;
        cout << "You can add test cases in the 'Example Test Cases:' section" << endl;
        cout << endl;
        cout << "Note: Make sure to implement your solution and update main()" << endl;
        cout << "to read inputs and produce outputs as expected by LeetCode." << endl;
    } else {
        cout << BLUE << "Found " << testCases.size() << " test input line(s)" << RESET << endl;
        cout << endl;
        
        // Run the program with all test inputs
        cout << "Running tests..." << endl;
        cout << "========================================" << endl;
        
        string output = runTestWithInput(executableName, testCases);
        
        if (output.empty()) {
            cout << RED << "✗ Program produced no output or crashed" << RESET << endl;
        } else {
            cout << "Output:" << endl;
            cout << output << endl;
            cout << "========================================" << endl;
            cout << GREEN << "✓ Program executed successfully" << RESET << endl;
            cout << endl;
            cout << "Please verify the output matches the expected results from" << endl;
            cout << "the problem description." << endl;
        }
    }
    
    // Cleanup
    string cleanupCmd = "rm -f " + executableName;
    system(cleanupCmd.c_str());
    
    return 0;
}
