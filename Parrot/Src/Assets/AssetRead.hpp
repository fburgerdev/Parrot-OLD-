#pragma once
#include "Math/Vector.hpp"

#include <string>

namespace Parrot
{
	namespace Asset
	{
		void AssetSyntaxAssert(bool success, const std::string& msg);
		void ToLower(std::string& line);

		bool GetKey(const std::string& line, std::string& key);

		bool GetArg(const std::string& line, std::string& arg);
		bool GetArgWIdentifier(const std::string& line, const std::string& identifier, std::string& arg);

		float ArgToFloat(const std::string& arg);
		bool ArgToVec2u(const std::string& arg, Math::Vec2u& vec);
		bool ArgToVec2f(const std::string& arg, Math::Vec2f& vec);
		bool ArgToVec3f(const std::string& arg, Math::Vec3f& vec);
		bool ArgToVec3u8(const std::string& arg, Math::Vec3u8& vec);
	}
}