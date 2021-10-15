#pragma once
#include <string>
#include <unordered_map>

class ShaderSnippetLib
{
private:
	static std::unordered_map<std::string, std::string> s_ShaderSnippets;
public:
	ShaderSnippetLib() = delete;
	static void AddSnippetFromPath(const std::string& filepath);
	static void AddSnippet(const std::string& identifier, const std::string& snippet);
	static std::string GetSnippet(const std::string& identifier);
};