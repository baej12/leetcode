#!/usr/bin/env python3
"""
Helper script to generate appropriate main() function based on LeetCode function signature
"""

import re
import sys


def parse_function_signature(code_snippet):
    """
    Parse the function signature from code snippet
    Returns: (return_type, function_name, parameters)
    """
    # Look for function definition pattern
    pattern = r"(\w+(?:\s*<[^>]+>)?)\s+(\w+)\s*\(([^)]*)\)"
    match = re.search(pattern, code_snippet)

    if not match:
        return None, None, []

    return_type = match.group(1).strip()
    function_name = match.group(2).strip()
    params_str = match.group(3).strip()

    # Parse parameters
    parameters = []
    if params_str:
        # Split by comma, but be careful with templates
        param_list = []
        current = ""
        depth = 0
        for char in params_str:
            if char == "<":
                depth += 1
            elif char == ">":
                depth -= 1
            elif char == "," and depth == 0:
                param_list.append(current.strip())
                current = ""
                continue
            current += char
        if current.strip():
            param_list.append(current.strip())

        for param in param_list:
            # Extract type and name
            parts = param.rsplit(None, 1)
            if len(parts) == 2:
                param_type = parts[0].strip()
                param_name = parts[1].strip()
                # Remove & or * from name if present
                param_name = param_name.lstrip("&*")
                parameters.append((param_type, param_name))

    return return_type, function_name, parameters


def get_cpp_type_category(cpp_type):
    """Categorize C++ types for parsing logic"""
    cpp_type = cpp_type.replace("&", "").replace("*", "").strip()

    if "vector<int>" in cpp_type or cpp_type == "vector<int>":
        return "vector_int"
    elif "vector<vector<int>>" in cpp_type:
        return "vector_vector_int"
    elif "vector<string>" in cpp_type:
        return "vector_string"
    elif cpp_type == "string":
        return "string"
    elif cpp_type == "int":
        return "int"
    elif cpp_type == "double" or cpp_type == "float":
        return "float"
    elif cpp_type == "bool":
        return "bool"
    elif cpp_type == "char":
        return "char"
    elif "ListNode" in cpp_type:
        return "listnode"
    elif "TreeNode" in cpp_type:
        return "treenode"
    else:
        return "unknown"


def generate_parser_code(param_type, param_name, is_first=True):
    """Generate parsing code for a parameter"""
    category = get_cpp_type_category(param_type)

    code = []

    if category == "vector_int":
        if is_first:
            code.append("    // Parse vector<int>")
        code.append(f"    vector<int> {param_name};")
        code.append("    getline(cin, line);")
        code.append("    {")
        code.append("        size_t start = line.find('[');")
        code.append("        size_t end = line.find(']');")
        code.append("        if (start != string::npos && end != string::npos) {")
        code.append(
            "            string content = line.substr(start + 1, end - start - 1);"
        )
        code.append("            if (!content.empty()) {")
        code.append("                stringstream ss(content);")
        code.append("                string num;")
        code.append("                while (getline(ss, num, ',')) {")
        code.append(f"                    {param_name}.push_back(stoi(num));")
        code.append("                }")
        code.append("            }")
        code.append("        }")
        code.append("    }")

    elif category == "vector_vector_int":
        if is_first:
            code.append("    // Parse vector<vector<int>>")
        code.append(f"    vector<vector<int>> {param_name};")
        code.append("    getline(cin, line);")
        code.append("    // TODO: Implement 2D array parsing")

    elif category == "string":
        if is_first:
            code.append("    // Parse string")
        code.append(f"    string {param_name};")
        code.append("    getline(cin, line);")
        code.append("    // Remove quotes if present")
        code.append(
            "    if (!line.empty() && line.front() == '\"' && line.back() == '\"') {"
        )
        code.append(f"        {param_name} = line.substr(1, line.length() - 2);")
        code.append("    } else {")
        code.append(f"        {param_name} = line;")
        code.append("    }")

    elif category == "int":
        if is_first:
            code.append("    // Parse int")
        code.append(f"    int {param_name};")
        code.append("    getline(cin, line);")
        code.append(f"    {param_name} = stoi(line);")

    elif category == "bool":
        if is_first:
            code.append("    // Parse bool")
        code.append(f"    bool {param_name};")
        code.append("    getline(cin, line);")
        code.append(f'    {param_name} = (line == "true" || line == "1");')

    elif category == "char":
        if is_first:
            code.append("    // Parse char")
        code.append(f"    char {param_name};")
        code.append("    getline(cin, line);")
        code.append("    if (!line.empty()) {")
        code.append(
            f"        {param_name} = (line.front() == '\"' && line.length() >= 3) ? line[1] : line[0];"
        )
        code.append("    }")

    else:
        code.append(f"    // TODO: Parse {param_type} {param_name}")
        code.append("    getline(cin, line);")

    return code


def generate_output_code(return_type, function_name, param_names):
    """Generate output code based on return type"""
    category = get_cpp_type_category(return_type)
    func_call = f"sol.{function_name}({', '.join(param_names)})"

    code = []
    code.append("    // Call solution and output result")

    if category == "vector_int":
        code.append(f"    vector<int> result = {func_call};")
        code.append('    cout << "[";')
        code.append("    for (size_t i = 0; i < result.size(); i++) {")
        code.append('        if (i > 0) cout << ",";')
        code.append("        cout << result[i];")
        code.append("    }")
        code.append('    cout << "]" << endl;')

    elif category == "vector_string":
        code.append(f"    vector<string> result = {func_call};")
        code.append('    cout << "[";')
        code.append("    for (size_t i = 0; i < result.size(); i++) {")
        code.append('        if (i > 0) cout << ",";')
        code.append('        cout << "\\"" << result[i] << "\\"";')
        code.append("    }")
        code.append('    cout << "]" << endl;')

    elif category == "string":
        code.append(f'    cout << "\\"" << {func_call} << "\\"" << endl;')

    elif category == "char":
        code.append(f'    cout << "\\"" << {func_call} << "\\"" << endl;')

    elif category == "bool":
        code.append(f'    cout << ({func_call} ? "true" : "false") << endl;')

    elif category == "int" or category == "float":
        code.append(f"    cout << {func_call} << endl;")

    elif return_type == "void":
        code.append(f"    {func_call};")
        code.append('    cout << "null" << endl;')

    else:
        code.append(f"    auto result = {func_call};")
        code.append("    // TODO: Format output based on return type")
        code.append("    cout << result << endl;")

    return code


def generate_main_function(code_snippet):
    """Generate complete main function based on code snippet"""
    return_type, function_name, parameters = parse_function_signature(code_snippet)

    if not function_name:
        # Return generic template
        return """int main() {
    Solution sol;
    
    // Read input
    string line;
    getline(cin, line);
    
    // Parse input (modify based on problem requirements)
    vector<int> nums;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string content = line.substr(start + 1, end - start - 1);
        stringstream ss(content);
        string num;
        while (getline(ss, num, ',')) {
            nums.push_back(stoi(num));
        }
    }
    
    // Call solution and output result
    // TODO: Modify based on function signature
    // cout << sol.functionName(args) << endl;
    
    return 0;
}"""

    # Generate the main function
    lines = []
    lines.append("int main() {")
    lines.append("    Solution sol;")
    lines.append("    string line;")
    lines.append("")

    # Generate parsing code for each parameter
    param_names = []
    for i, (param_type, param_name) in enumerate(parameters):
        parser_lines = generate_parser_code(param_type, param_name, i == 0)
        lines.extend(parser_lines)
        if i < len(parameters) - 1:
            lines.append("")
        param_names.append(param_name)

    lines.append("")

    # Generate output code
    output_lines = generate_output_code(return_type, function_name, param_names)
    lines.extend(output_lines)

    lines.append("    ")
    lines.append("    return 0;")
    lines.append("}")

    return "\n".join(lines)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 generate_main.py '<code_snippet>'")
        sys.exit(1)

    code_snippet = sys.argv[1]
    main_function = generate_main_function(code_snippet)
    print(main_function)
