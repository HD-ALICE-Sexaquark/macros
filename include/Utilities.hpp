#ifndef SM_UTILS_HXX
#define SM_UTILS_HXX

#include <sstream>
#include <string>
#include <string_view>

#include <TString.h>
#include <TSystem.h>

namespace SexaquarkMacros::Utils {

// Expands a path with wildcards into a list of matching file paths.
// This function uses the system's `ls` command to expand the wildcards.
// It is therefore not portable to non-Unix-like systems (e.g., Windows).
//
// Input:
// `path` -- The path containing wildcards (e.g., "/path/to/files/*.root").
// Output:
// A vector of strings, where each string is a path to a file matching the pattern.
static std::vector<std::string> ExpandWildcards(std::string_view path) {

    // prepare output
    std::vector<std::string> expanded_paths;

    // Using `ls -1` to list files, one per line.
    // `2>/dev/null` suppresses errors if no files match.
    TString command{TString::Format("ls -1 %s 2>/dev/null", std::string(path).c_str())};

    // gSystem is the global pointer to TSystem in ROOT
    TString file_list_str{gSystem->GetFromPipe(command)};

    if (file_list_str.IsNull() || file_list_str.Length() == 0) return expanded_paths;

    std::stringstream ss(file_list_str.Data());
    std::string line;
    while (std::getline(ss, line, '\n')) {
        if (!line.empty()) expanded_paths.push_back(line);
    }

    return expanded_paths;
}

}  // namespace SexaquarkMacros::Utils

#endif  // SM_UTILS_HXX
