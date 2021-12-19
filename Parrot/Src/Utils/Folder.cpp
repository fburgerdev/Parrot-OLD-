#include "Ptpch.hpp"
#include "Folder.hpp"
#include "Debug/Debugstream.hpp"

namespace Parrot
{
	namespace Utils
	{
		Folder::Folder(const Utils::Directory& dir)
			: m_Dir(dir), m_ValidDir(std::filesystem::exists(dir.Str()))
		{
			if (m_ValidDir)
				m_RecursiveIt = recursiveIt(dir.Str());
			else
				DebugOut << UnknownDirWarning << "Dir: " << dir << Debugstream::EndMsg;
		}
		Folder::Folder(Utils::Directory&& dir)
			: m_Dir(std::move(dir)), m_ValidDir(std::filesystem::exists(m_Dir.Str()))
		{
			if (m_ValidDir)
				m_RecursiveIt = recursiveIt(m_Dir.Str());
			else
				DebugOut << UnknownDirWarning << "Dir: " << m_Dir << Debugstream::EndMsg;
		}
		Folder::RecursiveIterator::RecursiveIterator(recursiveIt it)
			: m_It(it) 
		{

		}
		void Folder::RecursiveIterator::operator++()
		{
			m_It++;
		}
		bool Folder::RecursiveIterator::operator!=(const RecursiveIterator& other)
		{
			return m_It != other.m_It;
		}
		Utils::Filepath Folder::RecursiveIterator::operator*()
		{
			return Utils::Filepath(m_It.operator*().path().string());
		}
	
		Folder::RecursiveIterator Folder::begin() const
		{
			if (m_ValidDir)
				return RecursiveIterator(std::filesystem::begin(m_RecursiveIt));
			else
				return end();
		}
		Folder::RecursiveIterator Folder::end() const
		{
			return RecursiveIterator(std::filesystem::end(m_RecursiveIt));
		}

		const Utils::Directory& Folder::GetDir() const
		{
			return m_Dir;
		}
	}
}