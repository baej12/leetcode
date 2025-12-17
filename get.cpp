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
    while ((pos = result.find("&#39;", pos)) != string::npos) {
        result.replace(pos, 5, "'");
    }
    pos = 0;
    while ((pos = result.find("&quot;", pos)) != string::npos) {
        result.replace(pos, 6, "\"");
    }
    pos = 0;
    while ((pos = result.find("&amp;", pos)) != string::npos) {
        result.replace(pos, 5, "&");
    }
    return result;
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

// Function to fetch problem info from LeetCode
bool fetchProblemInfo(const string& problemIdentifier, string& title, string& difficulty, string& titleSlug, string& questionId) {
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
    string curlCmd = "curl -s 'https://leetcode.com/graphql' "
                     "-H 'Content-Type: application/json' "
                     "--data-raw '{\"query\":\"query questionTitle($titleSlug: String!) "
                     "{ question(titleSlug: $titleSlug) { questionId title titleSlug difficulty }}\","
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
    
    if (!title.empty()) {
        title = unescapeHtml(title);
        return true;
    }
    
    return false;
}

// Function to create problem template file
void createProblemFile(const string& problemNum, const string& title, 
                       const string& difficulty, const string& titleSlug) {
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
    file << " */" << endl;
    file << endl;
    file << "#include <iostream>" << endl;
    file << "#include <vector>" << endl;
    file << "#include <string>" << endl;
    file << "#include <unordered_map>" << endl;
    file << "#include <unordered_set>" << endl;
    file << "#include <algorithm>" << endl;
    file << "#include <queue>" << endl;
    file << "#include <stack>" << endl;
    file << endl;
    file << "using namespace std;" << endl;
    file << endl;
    file << "class Solution {" << endl;
    file << "public:" << endl;
    file << "    // TODO: Implement solution" << endl;
    file << "    " << endl;
    file << "};" << endl;
    file << endl;
    file << "int main() {" << endl;
    file << "    Solution sol;" << endl;
    file << "    " << endl;
    file << "    // Test cases" << endl;
    file << "    " << endl;
    file << "    return 0;" << endl;
    file << "}" << endl;
    
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
    
    string title, difficulty, titleSlug, questionId;
    
    if (fetchProblemInfo(problemIdentifier, title, difficulty, titleSlug, questionId)) {
        // Use questionId for filename if available, otherwise use identifier
        string problemNum = questionId.empty() ? problemIdentifier : questionId;
        
        createProblemFile(problemNum, title, difficulty, titleSlug);
    } else {
        cerr << "\n✗ Failed to fetch problem information." << endl;
        cerr << "  Make sure you have curl installed and internet connection." << endl;
        cerr << "  Verify the problem number/slug is correct." << endl;
        return 1;
    }
    
    return 0;
}
