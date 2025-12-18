#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <regex>

using namespace std;

// Function to execute shell command and capture output
string executeCommand(const string& command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        cerr << "Error: Failed to execute command" << endl;
        return "";
    }
    
    char buffer[256];
    string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

// Function to parse JSON field (simple extraction)
string extractJsonField(const string& json, const string& field) {
    string pattern = "\"" + field + "\":\"";
    size_t pos = json.find(pattern);
    if (pos == string::npos) return "";
    
    pos += pattern.length();
    size_t endPos = json.find("\"", pos);
    if (endPos == string::npos) return "";
    
    return json.substr(pos, endPos - pos);
}

// Function to unescape HTML entities
string unescapeHtml(const string& str) {
    string result = str;
    size_t pos = 0;
    
    // Replace entities (do &amp; last since other entities contain &)
    while ((pos = result.find("&nbsp;", pos)) != string::npos) {
        result.replace(pos, 6, " ");
    }
    pos = 0;
    while ((pos = result.find("&#39;", pos)) != string::npos) {
        result.replace(pos, 5, "'");
    }
    pos = 0;
    while ((pos = result.find("&quot;", pos)) != string::npos) {
        result.replace(pos, 6, "\"");
    }
    pos = 0;
    while ((pos = result.find("&lt;", pos)) != string::npos) {
        result.replace(pos, 4, "<");
    }
    pos = 0;
    while ((pos = result.find("&gt;", pos)) != string::npos) {
        result.replace(pos, 4, ">");
    }
    pos = 0;
    while ((pos = result.find("&le;", pos)) != string::npos) {
        result.replace(pos, 4, "≤");
    }
    pos = 0;
    while ((pos = result.find("&ge;", pos)) != string::npos) {
        result.replace(pos, 4, "≥");
    }
    pos = 0;
    while ((pos = result.find("&hellip;", pos)) != string::npos) {
        result.replace(pos, 8, "...");
    }
    pos = 0;
    while ((pos = result.find("&minus;", pos)) != string::npos) {
        result.replace(pos, 7, "-");
    }
    pos = 0;
    while ((pos = result.find("&times;", pos)) != string::npos) {
        result.replace(pos, 7, "×");
    }
    pos = 0;
    while ((pos = result.find("&amp;", pos)) != string::npos) {
        result.replace(pos, 5, "&");
    }
    return result;
}

// Function to strip HTML tags and format as plain text
string stripHtmlTags(const string& html) {
    string result = "";
    bool inTag = false;
    bool inCode = false;
    
    for (size_t i = 0; i < html.length(); i++) {
        if (html[i] == '<') {
            // Check if it's a code tag
            if (i + 5 < html.length() && html.substr(i, 6) == "<code>") {
                inCode = true;
                i += 5;
                continue;
            } else if (i + 6 < html.length() && html.substr(i, 7) == "</code>") {
                inCode = false;
                i += 6;
                continue;
            } else if (i + 3 < html.length() && html.substr(i, 4) == "<br>") {
                result += '\n';
                i += 3;
                continue;
            } else if (i + 2 < html.length() && html.substr(i, 3) == "<p>") {
                if (!result.empty() && result.back() != '\n') result += "\n\n";
                i += 2;
                continue;
            } else if (i + 3 < html.length() && html.substr(i, 4) == "</p>") {
                if (!result.empty() && result.back() != '\n') result += '\n';
                i += 3;
                continue;
            }
            inTag = true;
        } else if (html[i] == '>') {
            inTag = false;
        } else if (!inTag) {
            result += html[i];
        }
    }
    
    return unescapeHtml(result);
}

// Function to check if string is a number
bool isNumber(const string& str) {
    return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}

// Function to fetch problem slug from problem ID
string fetchProblemSlug(const string& problemId) {
    string curlCmd = "curl -s 'https://leetcode.com/api/problems/all/' 2>/dev/null";
    string response = executeCommand(curlCmd);
    
    if (response.empty()) {
        return "";
    }
    
    // Search for the problem with this frontend_question_id in the JSON response
    // Format: {"stat":{"frontend_question_id":53,...,"question__title_slug":"maximum-subarray",...}
    
    // The number is followed by a comma in the JSON, with a space after the colon
    string searchPattern = "\"frontend_question_id\": " + problemId + ",";
    
    size_t pos = response.find(searchPattern);
    
    if (pos == string::npos) {
        return "";
    }
    
    // Search backwards to find the beginning of this stat object
    size_t statStart = response.rfind("\"stat\":", pos);
    if (statStart == string::npos) {
        return "";
    }
    
    // Find the title slug - it appears BEFORE frontend_question_id in the JSON
    // Search between statStart and pos
    size_t slugPos = response.find("\"question__title_slug\": \"", statStart);
    if (slugPos == string::npos || slugPos > pos) {
        return "";
    }
    
    slugPos += 25; // Length of "question__title_slug": \"
    
    size_t endPos = response.find("\"", slugPos);
    if (endPos == string::npos) {
        return "";
    }
    
    return response.substr(slugPos, endPos - slugPos);
}

// Function to extract content field (handles content with newlines)
string extractContent(const string& json, const string& field) {
    string pattern = "\"" + field + "\":\"";
    size_t pos = json.find(pattern);
    if (pos == string::npos) return "";
    
    pos += pattern.length();
    string result = "";
    
    // Parse until we find the closing quote that's not escaped
    for (size_t i = pos; i < json.length(); i++) {
        if (json[i] == '\\' && i + 1 < json.length()) {
            // Handle escape sequences
            char next = json[i + 1];
            if (next == 'n') {
                result += '\n';
                i++;
            } else if (next == 't') {
                result += '\t';
                i++;
            } else if (next == '"') {
                result += '"';
                i++;
            } else if (next == '\\') {
                result += '\\';
                i++;
            } else {
                result += json[i];
            }
        } else if (json[i] == '"') {
            break;
        } else {
            result += json[i];
        }
    }
    
    return result;
}

// Function to extract data structure definitions from code snippet
string extractDataStructures(const string& cppCode) {
    string result = "";
    size_t pos = 0;
    
    // Look for struct or class definitions (typically commented out in LeetCode snippets)
    // They appear in comments like: * struct TreeNode { ... }; or * struct ListNode { ... };
    
    // Find all comment blocks with struct definitions
    while ((pos = cppCode.find("struct ", pos)) != string::npos) {
        // Check if this is in a comment (preceded by * or /*)
        size_t lineStart = cppCode.rfind('\n', pos);
        if (lineStart == string::npos) lineStart = 0;
        
        string linePrefix = cppCode.substr(lineStart, pos - lineStart);
        bool inComment = (linePrefix.find("*") != string::npos || linePrefix.find("//") != string::npos);
        
        if (inComment) {
            // Extract the struct definition
            size_t structStart = pos;
            size_t structEnd = cppCode.find("};", pos);
            
            if (structEnd != string::npos) {
                structEnd += 2; // Include the closing };
                string structDef = cppCode.substr(structStart, structEnd - structStart);
                
                // Clean up the comment markers and fix indentation
                string cleaned = "";
                istringstream stream(structDef);
                string line;
                while (getline(stream, line)) {
                    // Remove leading * and whitespace from comment lines
                    size_t contentStart = line.find_first_not_of(" \t*");
                    if (contentStart != string::npos) {
                        string content = line.substr(contentStart);
                        // Add proper indentation for struct members
                        if (content.find("struct ") != 0 && content.find("};") != 0) {
                            cleaned += "    " + content + "\n";
                        } else {
                            cleaned += content + "\n";
                        }
                    }
                }
                
                result += cleaned + "\n";
                pos = structEnd;
            } else {
                pos++;
            }
        } else {
            pos++;
        }
    }
    
    return result;
}

// Function to extract C++ code snippet from codeSnippets
string extractCppCodeSnippet(const string& json) {
    // Find the C++ code snippet in the codeSnippets array
    size_t pos = 0;
    while ((pos = json.find("\"langSlug\":\"cpp\"", pos)) != string::npos) {
        // Found C++ snippet, now extract the code
        size_t codeStart = json.find("\"code\":\"", pos);
        if (codeStart != string::npos) {
            codeStart += 8; // Length of "code":"
            string code = "";
            
            // Parse until closing quote (handle escapes)
            for (size_t i = codeStart; i < json.length(); i++) {
                if (json[i] == '\\' && i + 1 < json.length()) {
                    char next = json[i + 1];
                    if (next == 'n') {
                        code += '\n';
                        i++;
                    } else if (next == 't') {
                        code += '\t';
                        i++;
                    } else if (next == '"') {
                        code += '"';
                        i++;
                    } else if (next == '\\') {
                        code += '\\';
                        i++;
                    } else {
                        code += json[i];
                    }
                } else if (json[i] == '"') {
                    return code;
                } else {
                    code += json[i];
                }
            }
        }
        pos++;
    }
    return "";
}

// Function to fetch problem info from LeetCode
bool fetchProblemInfo(const string& problemIdentifier, string& title, string& difficulty, 
                      string& titleSlug, string& questionId, string& content, string& exampleTestcases,
                      string& cppCode) {
    // If input is a number, fetch the slug first
    string slug = problemIdentifier;
    
    if (isNumber(problemIdentifier)) {
        cout << "Looking up problem #" << problemIdentifier << "..." << endl;
        slug = fetchProblemSlug(problemIdentifier);
        if (slug.empty()) {
            cerr << "Could not find problem with ID " << problemIdentifier << endl;
            return false;
        }
        cout << "Found: " << slug << endl;
    }
    
    // Use curl to fetch problem data from LeetCode GraphQL API
    // Include content, exampleTestcases, and codeSnippets in the query
    string curlCmd = "curl -s 'https://leetcode.com/graphql' "
                     "-H 'Content-Type: application/json' "
                     "--data-raw '{\"query\":\"query questionContent($titleSlug: String!) "
                     "{ question(titleSlug: $titleSlug) { questionId title titleSlug difficulty content exampleTestcases "
                     "codeSnippets { lang langSlug code } }}\","
                     "\"variables\":{\"titleSlug\":\"" + slug + "\"}}' 2>/dev/null";
    
    string response = executeCommand(curlCmd);
    
    if (response.empty()) {
        return false;
    }
    
    // Extract fields
    title = extractJsonField(response, "title");
    difficulty = extractJsonField(response, "difficulty");
    titleSlug = extractJsonField(response, "titleSlug");
    questionId = extractJsonField(response, "questionId");
    content = extractContent(response, "content");
    exampleTestcases = extractContent(response, "exampleTestcases");
    cppCode = extractCppCodeSnippet(response);
    
    if (!title.empty()) {
        title = unescapeHtml(title);
        return true;
    }
    
    return false;
}

// Helper function to generate main() for ListNode problems
string generateListNodeMain() {
    return R"(int main() {
    Solution sol;
    
    // Read input - linked list format: [1,2,3,4,5]
    string line;
    getline(cin, line);
    
    // Parse array
    vector<int> values;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        if (!content.empty()) {
            stringstream ss(content);
            string num;
            while (getline(ss, num, ',')) {
                values.push_back(stoi(num));
            }
        }
    }
    
    // Build linked list
    ListNode* head = nullptr;
    if (!values.empty()) {
        head = new ListNode(values[0]);
        ListNode* current = head;
        for (size_t i = 1; i < values.size(); i++) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }
    }
    
    // Call solution
    // TODO: Modify based on function signature
    // ListNode* result = sol.functionName(head);
    
    // Output result
    // TODO: Print result in correct format
    
    // Cleanup
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
})";
}

// Helper function to generate main() for TreeNode problems
string generateTreeNodeMain() {
    return R"(int main() {
    Solution sol;
    
    // Read input - tree format: [3,9,20,null,null,15,7]
    string line;
    getline(cin, line);
    
    // Parse array with null support
    vector<string> values;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        if (!content.empty()) {
            stringstream ss(content);
            string val;
            while (getline(ss, val, ',')) {
                // Trim whitespace
                size_t s = val.find_first_not_of(" \t");
                size_t e = val.find_last_not_of(" \t");
                if (s != string::npos && e != string::npos) {
                    values.push_back(val.substr(s, e - s + 1));
                }
            }
        }
    }
    
    // Build tree (level-order)
    TreeNode* root = nullptr;
    if (!values.empty() && values[0] != "null") {
        root = new TreeNode(stoi(values[0]));
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
    }
    
    // Call solution
    // TODO: Modify based on function signature
    // int result = sol.functionName(root);
    // cout << result << endl;
    
    return 0;
})";
}

// Function to create problem template file
void createProblemFile(const string& problemNum, const string& title, 
                       const string& difficulty, const string& titleSlug,
                       const string& content, const string& exampleTestcases,
                       const string& cppCode) {
    string filename = problemNum + ".cpp";
    
    // Check if file already exists, if so append -1, -2, etc.
    ifstream checkFile(filename);
    if (checkFile.good()) {
        checkFile.close();
        int suffix = 1;
        while (true) {
            filename = problemNum + "-" + to_string(suffix) + ".cpp";
            ifstream checkFile2(filename);
            if (!checkFile2.good()) {
                break;
            }
            checkFile2.close();
            suffix++;
        }
        cout << "Note: " << problemNum << ".cpp already exists, creating " << filename << " instead." << endl;
    }
    
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not create file " << filename << endl;
        return;
    }
    
    file << "/*" << endl;
    file << " * LeetCode Problem #" << problemNum << endl;
    file << " * Title: " << title << endl;
    file << " * Difficulty: " << difficulty << endl;
    file << " * https://leetcode.com/problems/" << titleSlug << "/" << endl;
    file << " *" << endl;
    
    // Add description if available
    if (!content.empty()) {
        string description = stripHtmlTags(content);
        file << " * Description:" << endl;
        file << " * " << endl;
        
        // Write description with proper comment formatting
        istringstream descStream(description);
        string line;
        while (getline(descStream, line)) {
            // Skip empty lines at the start
            if (line.empty()) continue;
            file << " * " << line << endl;
        }
        file << " *" << endl;
    }
    
    // Add example test cases if available
    if (!exampleTestcases.empty()) {
        file << " * Example Test Cases:" << endl;
        istringstream testStream(exampleTestcases);
        string line;
        while (getline(testStream, line)) {
            file << " * " << line << endl;
        }
        file << " *" << endl;
    }
    
    file << " */" << endl;
    file << endl;
    file << "#include <iostream>" << endl;
    file << "#include <vector>" << endl;
    file << "#include <string>" << endl;
    file << "#include <sstream>" << endl;
    file << "#include <unordered_map>" << endl;
    file << "#include <unordered_set>" << endl;
    file << "#include <algorithm>" << endl;
    file << "#include <queue>" << endl;
    file << "#include <stack>" << endl;
    file << endl;
    file << "using namespace std;" << endl;
    file << endl;
    
    // Extract and write data structure definitions if present
    string dataStructures = extractDataStructures(cppCode);
    if (!dataStructures.empty()) {
        file << "// Data structure definition(s)" << endl;
        file << dataStructures;
    }
    
    // Write the Solution class with the actual function signature if available
    if (!cppCode.empty()) {
        file << cppCode << endl;
    } else {
        file << "class Solution {" << endl;
        file << "public:" << endl;
        file << "    // TODO: Implement solution" << endl;
        file << "    " << endl;
        file << "};" << endl;
    }
    file << endl;
    
    // Determine which data structures are present (reuse extracted dataStructures)
    bool hasListNode = (dataStructures.find("struct ListNode") != string::npos);
    bool hasTreeNode = (dataStructures.find("struct TreeNode") != string::npos);
    
    // Generate appropriate main() based on data structures
    if (hasListNode) {
        file << generateListNodeMain() << endl;
    } else if (hasTreeNode) {
        file << generateTreeNodeMain() << endl;
    } else {
        // Default main() for array/integer problems
        file << "int main() {" << endl;
        file << "    Solution sol;" << endl;
        file << "    " << endl;
        file << "    // Read input" << endl;
        file << "    string line;" << endl;
        file << "    getline(cin, line);" << endl;
        file << "    " << endl;
        file << "    // Parse input (modify based on problem requirements)" << endl;
        file << "    vector<int> nums;" << endl;
        file << "    size_t start = line.find('[');" << endl;
        file << "    size_t end = line.find(']');" << endl;
        file << "    if (start != string::npos && end != string::npos) {" << endl;
        file << "        string content = line.substr(start + 1, end - start - 1);" << endl;
        file << "        stringstream ss(content);" << endl;
        file << "        string num;" << endl;
        file << "        while (getline(ss, num, ',')) {" << endl;
        file << "            nums.push_back(stoi(num));" << endl;
        file << "        }" << endl;
        file << "    }" << endl;
        file << "    " << endl;
        file << "    // Call solution and output result" << endl;
        file << "    // TODO: Modify based on function signature" << endl;
        file << "    // cout << sol.functionName(args) << endl;" << endl;
        file << "    " << endl;
        file << "    return 0;" << endl;
        file << "}" << endl;
    }
    
    file.close();
    cout << "\n✓ Successfully created " << filename << endl;
    cout << "  Problem #" << problemNum << ": " << title << endl;
    cout << "  Difficulty: " << difficulty << endl;
    cout << "  URL: https://leetcode.com/problems/" << titleSlug << "/" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <problem-number-or-slug>" << endl;
        cerr << "Examples:" << endl;
        cerr << "  " << argv[0] << " 1" << endl;
        cerr << "  " << argv[0] << " 53" << endl;
        cerr << "  " << argv[0] << " two-sum" << endl;
        return 1;
    }
    
    string problemIdentifier = argv[1];
    
    cout << "Fetching LeetCode problem info for: " << problemIdentifier << endl;
    
    string title, difficulty, titleSlug, questionId, content, exampleTestcases, cppCode;
    
    if (fetchProblemInfo(problemIdentifier, title, difficulty, titleSlug, questionId, content, exampleTestcases, cppCode)) {
        // Use questionId for filename if available, otherwise use identifier
        string problemNum = questionId.empty() ? problemIdentifier : questionId;
        
        createProblemFile(problemNum, title, difficulty, titleSlug, content, exampleTestcases, cppCode);
    } else {
        cerr << "\n✗ Failed to fetch problem information." << endl;
        cerr << "  Make sure you have curl installed and internet connection." << endl;
        cerr << "  Verify the problem number/slug is correct." << endl;
        return 1;
    }
    
    return 0;
}
