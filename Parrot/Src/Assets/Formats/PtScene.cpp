#include "Ptpch.hpp"
#include "PtScene.hpp"

namespace Parrot
{
	PtScene::PtScene(const Utils::Filepath& filepath)
		: m_Filepath(filepath)
	{

	}

	const Utils::Filepath& PtScene::GetFilepath() const
	{
		return m_Filepath;
	}
	const PtScene::Data& PtScene::GetData() const
	{
		return m_Data;
	}
}