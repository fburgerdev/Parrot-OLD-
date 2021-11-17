#pragma once
#include <string>
#include "Math/Vector.hpp"

namespace Parrot
{
	namespace Utils
	{
		static void GetKey(const std::string& line, std::string& key)
		{
			size_t i = 0;
			while (line[i] == '\t' || line[i] == ' ')
				i++;
			key = line.substr(i, line.find_first_of(':') - i);
		}
		
		static void GetArg(const std::string& line, std::string& arg)
		{
			size_t quotation = line.find_first_of('\"') + 1;
			arg = line.substr(quotation, line.find_first_of('\"', quotation) - quotation);
		}

		static bool GetArgWIdentifier(const std::string& line, const std::string& identifier, std::string& arg)
		{
			size_t i = line.find(identifier);
			if (i == line.npos)
				return false;
			size_t quotation = line.find_first_of('\"', i) + 1;
			arg = line.substr(quotation, line.find_first_of('\"', quotation) - quotation);
			return true;
		}

		static float ArgToFloat(const std::string& arg)
		{
			return std::stof(arg);
		}
		static Math::Vec2u ArgToVec2u(const std::string& arg)
		{
			Math::Vec2u out;
			size_t comma = arg.find_first_of(',');
			out.x = (uint32_t)std::stoul(arg.substr(0, comma));
			out.y = (uint32_t)std::stoul(arg.substr(comma + 1, arg.length() - comma));
			return out;
		}

		static Math::Vec2f ArgToVec2f(const std::string& arg)
		{
			Math::Vec2f out;
			size_t comma = arg.find_first_of(',');
			out.x = std::stof(arg.substr(0, comma));
			out.y = std::stof(arg.substr(comma + 1, arg.length() - comma));
			return out;
		}

		static Math::Vec3f ArgToVec3f(const std::string& arg)
		{
			Math::Vec3f out;
			size_t comma1 = arg.find_first_of(',');
			size_t comma2 = arg.find_last_of(',');
			out.x = std::stof(arg.substr(0, comma1));
			out.y = std::stof(arg.substr(comma1 + 1, comma2 - comma1));
			out.z = std::stof(arg.substr(comma2 + 1, arg.length() - comma2));
			return out;
		}
	}
}