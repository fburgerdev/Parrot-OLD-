#include "ShaderSnippetLib.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, std::string> ShaderSnippetLib::s_ShaderSnippets;

void ShaderSnippetLib::AddSnippetFromPath(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::stringstream ss;
	ss << stream.rdbuf();
	
	size_t substrStart = filepath.find_last_of('/') + 1;
	std::string identifier = filepath.substr(substrStart, filepath.find('.') - substrStart);
	AddSnippet(identifier, ss.str());
}

void ShaderSnippetLib::AddSnippet(const std::string& identifier, const std::string& snippet)
{
	if (s_ShaderSnippets.find(identifier) == s_ShaderSnippets.end())
		s_ShaderSnippets[identifier] = snippet;
}

std::string ShaderSnippetLib::GetSnippet(const std::string& identifier)
{
	if (s_ShaderSnippets.find(identifier) != s_ShaderSnippets.end())
		return s_ShaderSnippets[identifier];
	std::cout << "[WARNING] Could not find shader snippet \"" << identifier << "\"!\n";
	return "";
}