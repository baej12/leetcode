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

// Helper function to check if file contains a data structure definition
bool containsDataStructure(const string& filename, const string& structName) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    
    string line;
    while (getline(file, line)) {
        if (line.find("struct " + structName) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Helper function to generate ListNode builder code
string generateListNodeBuilder() {
    return R"(
// Build linked list from array
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* buildList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

void printList(ListNode* head) {
    cout << "[";
    bool first = true;
    while (head != nullptr) {
        if (!first) cout << ",";
        cout << head->val;
        first = false;
        head = head->next;
    }
    cout << "]";
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}
)";
}

// Helper function to generate TreeNode builder code
string generateTreeNodeBuilder() {
    return R"(
// Build binary tree from level-order array with nulls
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* buildTree(const vector<string>& values) {
    if (values.empty() || values[0] == "null") return nullptr;
    
    TreeNode* root = new TreeNode(stoi(values[0]));
    queue<TreeNode*> q;
    q.push(root);
    
    size_t i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* node = q.front();
        q.pop();
        
        // Left child
        if (i < values.size() && values[i] != "null") {
            node->left = new TreeNode(stoi(values[i]));
            q.push(node->left);
        }
        i++;
        
        // Right child
        if (i < values.size() && values[i] != "null") {
            node->right = new TreeNode(stoi(values[i]));
            q.push(node->right);
        }
        i++;
    }
    
    return root;
}

void printTree(TreeNode* root) {
    if (!root) {
        cout << "[]";
        return;
    }
    
    cout << "[";
    queue<TreeNode*> q;
    q.push(root);
    bool first = true;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (!first) cout << ",";
        if (node) {
            cout << node->val;
            q.push(node->left);
            q.push(node->right);
        } else {
            cout << "null";
        }
        first = false;
    }
    cout << "]";
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
)";
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
    
    while (getline(file, line)) {
        // Check if we're in the description section
        if (line.find("Description:") != string::npos) {
            inDescription = true;
            continue;
        }
        
        // Stop at Example Test Cases section
        if (inDescription && line.find("Example Test Cases:") != string::npos) {
            break;
        }
        
        if (inDescription && line.find(" * ") != string::npos) {
            string content = line.substr(line.find(" * ") + 3);
            
            // Look for "Example N:" to start a new example
            if (content.find("Example") != string::npos && content.find(":") != string::npos) {
                // Save previous example if exists
                if (!currentInput.empty() && !currentOutput.empty()) {
                    examples.push_back({currentInput, currentOutput});
                    currentInput.clear();
                    currentOutput.clear();
                }
                continue;
            }
            
            // Parse "Input: var = value" lines
            if (content.find("Input:") != string::npos) {
                size_t pos = content.find("Input:");
                string inputLine = content.substr(pos + 6);
                
                // Extract values (handle multiple inputs)
                size_t eqPos;
                while ((eqPos = inputLine.find(" = ")) != string::npos) {
                    size_t valueStart = eqPos + 3;
                    
                    // Find the end of this value
                    // If value starts with '[', find matching ']'
                    // Otherwise, find next comma or end of string
                    size_t endPos;
                    string value;
                    
                    // Trim leading space
                    while (valueStart < inputLine.length() && isspace(inputLine[valueStart])) {
                        valueStart++;
                    }
                    
                    if (valueStart < inputLine.length() && inputLine[valueStart] == '[') {
                        // Array value - find closing bracket
                        size_t bracketEnd = inputLine.find(']', valueStart);
                        if (bracketEnd != string::npos) {
                            endPos = bracketEnd + 1;
                            value = inputLine.substr(valueStart, endPos - valueStart);
                        } else {
                            value = inputLine.substr(valueStart);
                            endPos = inputLine.length();
                        }
                    } else {
                        // Regular value - find next comma or end
                        size_t commaPos = inputLine.find(",", valueStart);
                        if (commaPos != string::npos) {
                            endPos = commaPos;
                            value = inputLine.substr(valueStart, endPos - valueStart);
                        } else {
                            value = inputLine.substr(valueStart);
                            endPos = inputLine.length();
                        }
                    }
                    
                    // Trim whitespace from value
                    size_t start = value.find_first_not_of(" \t");
                    size_t end = value.find_last_not_of(" \t");
                    if (start != string::npos && end != string::npos) {
                        value = value.substr(start, end - start + 1);
                        if (!value.empty()) {
                            currentInput.push_back(value);
                        }
                    }
                    
                    // Move past this value
                    if (endPos < inputLine.length() && inputLine[endPos] == ',') {
                        inputLine = inputLine.substr(endPos + 1);
                    } else {
                        break;
                    }
                }
            }
            
            // Parse "Output: value" lines
            if (content.find("Output:") != string::npos) {
                size_t pos = content.find("Output:");
                currentOutput = content.substr(pos + 7);
                // Trim whitespace
                size_t start = currentOutput.find_first_not_of(" \t");
                size_t end = currentOutput.find_last_not_of(" \t\r\n");
                if (start != string::npos && end != string::npos) {
                    currentOutput = currentOutput.substr(start, end - start + 1);
                }
            }
        }
    }
    
    // Add last example if not already added
    if (!currentInput.empty() && !currentOutput.empty()) {
        examples.push_back({currentInput, currentOutput});
    }
    
    file.close();
    return examples;
}

// Function to create test wrapper for data structure problems
string createDataStructureWrapper(const string& sourceFile, bool hasListNode, bool hasTreeNode) {
    string wrapperFile = "test_wrapper_" + sourceFile;
    ofstream out(wrapperFile);
    
    if (!out.is_open()) {
        return "";
    }
    
    // Write includes
    out << "#include <iostream>" << endl;
    out << "#include <vector>" << endl;
    out << "#include <string>" << endl;
    out << "#include <sstream>" << endl;
    out << "#include <queue>" << endl;
    out << "using namespace std;" << endl;
    out << endl;
    
    // Add appropriate builder code
    if (hasListNode) {
        out << generateListNodeBuilder() << endl;
    }
    if (hasTreeNode) {
        out << generateTreeNodeBuilder() << endl;
    }
    
    // Include the original solution file
    out << "// Include solution" << endl;
    out << "#include \"" << sourceFile << "\"" << endl;
    out << endl;
    
    // Note: The main() function would need to be customized per problem
    // For now, we'll just include basic structure
    out << "// Note: main() needs to be implemented based on problem requirements" << endl;
    out << "int main() {" << endl;
    out << "    // TODO: Parse input and call solution" << endl;
    out << "    return 0;" << endl;
    out << "}" << endl;
    
    out.close();
    return wrapperFile;
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
        cerr << "Usage: " << argv[0] << " <problem_number>[.cpp]" << endl;
        cerr << "Examples:" << endl;
        cerr << "  " << argv[0] << " 121" << endl;
        cerr << "  " << argv[0] << " 121-1" << endl;
        cerr << "  " << argv[0] << " 121.cpp" << endl;
        return 1;
    }
    
    string input = argv[1];
    string sourceFile;
    
    // If input doesn't end with .cpp, add it
    if (input.find(".cpp") == string::npos) {
        sourceFile = input + ".cpp";
    } else {
        sourceFile = input;
    }
    
    // Try to find the file in directory structure or root
    string actualFile = findProblemFile(sourceFile);
    if (actualFile.empty()) {
        cerr << RED << "✗ Error: File '" << sourceFile << "' not found" << RESET << endl;
        return 1;
    }
    
    // Generate executable name
    string executableName = "test_" + sourceFile.substr(0, sourceFile.find_last_of('.'));
    
    // Compile the solution
    if (!compileSolution(actualFile, executableName)) {
        return 1;
    }
    
    cout << endl;
    
    // Check for custom data structures and inform user
    bool hasListNode = containsDataStructure(actualFile, "ListNode");
    bool hasTreeNode = containsDataStructure(actualFile, "TreeNode");
    
    if (hasListNode || hasTreeNode) {
        cout << BLUE << "ℹ This problem uses custom data structures (";
        if (hasListNode) cout << "ListNode";
        if (hasListNode && hasTreeNode) cout << ", ";
        if (hasTreeNode) cout << "TreeNode";
        cout << ")" << RESET << endl;
        cout << "The generated file includes parsing and construction code." << endl;
        cout << "Make sure to implement the solution and update output formatting." << endl;
        cout << endl;
    }
    
    // Parse examples with expected outputs from description
    auto examples = parseExamplesFromDescription(actualFile);
    
    if (examples.empty()) {
        cout << YELLOW << "⚠ No examples with expected outputs found in description" << RESET << endl;
        cout << "Running with test cases only..." << endl;
        cout << endl;
        
        // Fallback to running test cases without validation
        vector<string> testCases = parseExampleTestCases(actualFile);
        if (!testCases.empty()) {
            cout << BLUE << "Found " << testCases.size() << " test input line(s)" << RESET << endl;
            string output = runTestWithInput(executableName, testCases);
            cout << "Output:" << endl;
            cout << output << endl;
        } else {
            cout << "No test cases found." << endl;
        }
    } else {
        cout << BLUE << "Found " << examples.size() << " example(s) with expected outputs" << RESET << endl;
        cout << endl;
        
        int passed = 0;
        int failed = 0;
        
        for (size_t i = 0; i < examples.size(); i++) {
            cout << "Example " << (i + 1) << ":" << endl;
            cout << "  Input: ";
            for (size_t j = 0; j < examples[i].first.size(); j++) {
                if (j > 0) cout << ", ";
                cout << examples[i].first[j];
            }
            cout << endl;
            cout << "  Expected: " << examples[i].second << endl;
            
            string output = runTestWithInput(executableName, examples[i].first);
            output = trim(output);
            
            cout << "  Got:      " << output << endl;
            
            if (output == examples[i].second) {
                cout << GREEN << "  ✓ PASSED" << RESET << endl;
                passed++;
            } else {
                cout << RED << "  ✗ FAILED" << RESET << endl;
                failed++;
            }
            cout << endl;
        }
        
        // Summary
        cout << "========================================" << endl;
        cout << "Summary: ";
        if (failed == 0) {
            cout << GREEN << "All " << passed << " test(s) passed! ✓" << RESET << endl;
        } else {
            cout << passed << " passed, " << RED << failed << " failed" << RESET << endl;
        }
    }
    
    // Cleanup
    string cleanupCmd = "rm -f " + executableName;
    system(cleanupCmd.c_str());
    
    return 0;
}
