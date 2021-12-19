#include "Ptpch.hpp"
#include "AssetRead.hpp"

#include "Core/Core.hpp"
#include "Debug/Debugstream.hpp"

namespace Parrot
{
	namespace Asset
	{
		void AssetSyntaxAssert(bool success, const std::string& msg)
		{
			if (!success)
			{
				DebugOut << AssetSyntaxWarning << msg << Debugstream::EndMsg;
			}
		}
		void ToLower(std::string& line)
		{
			for (size_t i = 0; i < line.length(); ++i)
				if (line[i] >= 65 && line[i] <= 90)
					line[i] += 32;
		}

		bool GetKey(const std::string& line, std::string& key)
		{
			size_t i = 0;
			while (line[i] == '\t' || line[i] == ' ')
				i++;
			size_t end = line.find_first_of(':');
			if (PT_FUNC_GUARDS_ENABLED && end == line.npos)
				return false;
			key = line.substr(i, end - i);
			ToLower(key);
			return true;
		}

		bool GetArg(const std::string& line, std::string& arg)
		{
			size_t start = line.find_first_of('\"') + 1;
			size_t end = line.find_first_of('\"', start);
			if (PT_FUNC_GUARDS_ENABLED && (start == line.npos || end == line.npos))
				return false;
			arg = line.substr(start, end - start);
			//ToLower(arg);
			return true;
		}
		bool GetArgWIdentifier(const std::string& line, const std::string& identifier, std::string& arg)
		{
			size_t pos = line.find(identifier);
			if (pos == line.npos)
				return false;
			size_t start = line.find_first_of('\"', pos) + 1;
			size_t end = line.find_first_of('\"', start);
			if (PT_FUNC_GUARDS_ENABLED && (start == line.npos || end == line.npos))
				return false;
			arg = line.substr(start, end - start);
			//ToLower(arg);
			return true;
		}
		float ArgToFloat(const std::string& arg)
		{
			return std::stof(arg);
		}
		bool ArgToVec2u(const std::string& arg, Math::Vec2u& vec)
		{
			size_t comma = arg.find_first_of(',');
			if (PT_FUNC_GUARDS_ENABLED && comma == arg.npos)
				return false;
			vec.x = (uint32_t)std::stoul(arg.substr(0, comma));
			vec.y = (uint32_t)std::stoul(arg.substr(comma + 1, arg.length() - comma));
			return true;
		}
		bool ArgToVec2f(const std::string& arg, Math::Vec2f& vec)
		{
			Math::Vec2f out;
			size_t comma = arg.find_first_of(',');
			if (PT_FUNC_GUARDS_ENABLED && comma == arg.npos)
				return false;
			vec.x = std::stof(arg.substr(0, comma));
			vec.y = std::stof(arg.substr(comma + 1, arg.length() - comma));
			return true;
		}
		bool ArgToVec3f(const std::string& arg, Math::Vec3f& vec)
		{
			Math::Vec3f out;
			size_t comma1 = arg.find_first_of(',');
			size_t comma2 = arg.find_last_of(',');
			if (PT_FUNC_GUARDS_ENABLED && (comma1 == arg.npos || comma2 == arg.npos))
				return false;
			vec.x = std::stof(arg.substr(0, comma1));
			vec.y = std::stof(arg.substr(comma1 + 1, comma2 - comma1));
			vec.z = std::stof(arg.substr(comma2 + 1, arg.length() - comma2));
			return true;
		}
		bool ArgToVec3u8(const std::string& arg, Math::Vec3u8& vec)
		{
			Math::Vec3u8 out;
			size_t comma1 = arg.find_first_of(',');
			size_t comma2 = arg.find_last_of(',');
			if (PT_FUNC_GUARDS_ENABLED && (comma1 == arg.npos || comma2 == arg.npos))
				return false;
			vec.x = (uint8_t)std::stoul(arg.substr(0, comma1));
			vec.y = (uint8_t)std::stoul(arg.substr(comma1 + 1, comma2 - comma1));
			vec.z = (uint8_t)std::stoul(arg.substr(comma2 + 1, arg.length() - comma2));
			return true;
		}
	}
}