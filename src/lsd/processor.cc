#include "lsd/processor.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "lsd/file.h"

lsd::File& lsd::Processor::ProcessFile(lsd::File& file) {
  std::string text = lsd::RemoveSingleLineComments(
                     lsd::RemoveMultiLineComments(
                     lsd::ReadText(file.path)));
  for (const auto& incl:lsd::ParseIncludes(text)) {
    auto incl_filename = lsd::GetFileName(incl);
    auto incl_file = std::make_unique<lsd::File>(incl_filename);
    ProcessFile(*incl_file);
    file.files.push_back(std::move(incl_file));
  }
  return file;
}

void lsd::Processor::PrintFile(const lsd::File& f, std::string indent) {
  std::cout << indent << f.path << std::endl;
  for (const auto& ff:f.files) {
    PrintFile(*ff, indent + tab_);
  }
 }

std::string lsd::ReadText(const std::string& filename) {
  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

std::vector<std::string> lsd::ReadLines(const std::string& filename) {
  std::ifstream file(filename);
  std::string str;
  std::vector<std::string> lines;
  while (std::getline(file, str)) {
    lines.push_back(str);
  }
  return lines;
}

std::vector<std::string> lsd::ParseIncludes(const std::string& s) {
   std::smatch match;
   std::regex regex("#\\s*include\\s*([\"<]{1}[\\w\\s/.]+[\">]{1})");
   auto iter = s.begin();
   std::vector<std::string> out;
   while (std::regex_search(iter, s.end(), match, regex)) {
     out.push_back(match[1]);
     iter = match[0].second;
   }
   return out;
}

std::string lsd::RemoveMultiLineComments(const std::string& s) {
  std::regex re("/\\*[\\s\\S]*?\\*/");
  return std::regex_replace(s, re, "");
}

std::string lsd::RemoveSingleLineComments(const std::string& s) {
  std::regex re("//.*");
  return std::regex_replace(s, re, "");
}

std::string lsd::GetFileName(const std::string& include) {
  return include.substr(1, include.size() - 2);
}
