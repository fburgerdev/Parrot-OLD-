#pragma once
#include <vector>

namespace Parrot
{
	struct VertexBufferElement
	{
		enum class DType : int32_t
		{
			Float = 0x1406, Uint32 = 0x1405, Int32 = 0x1404, UByte = 0x1401
		};
		
		DType dType;
		uint32_t count;

		uint32_t GetStride() const
		{
			switch (dType)
			{
			case DType::Float:
			case DType::Uint32:
			case DType::Int32:
				return 4 * count;
			case DType::UByte:
				return count;
			default:
				return 0;
			}
		}
	};

	class VertexBufferLayout
	{
	public:
		template<typename T>
		void Push(uint32_t count);
		template<> void Push<float>(uint32_t count) { elements.push_back({ VertexBufferElement::DType::Float, count }); stride += count * 4; }
		template<> void Push<int32_t>(uint32_t count) { elements.push_back({ VertexBufferElement::DType::Int32, count }); stride += count * 4; }
		template<> void Push<uint32_t>(uint32_t count) { elements.push_back({ VertexBufferElement::DType::Uint32, count }); stride += count * 4; }
		template<> void Push<uint8_t>(uint32_t count) { elements.push_back({ VertexBufferElement::DType::UByte, count }); stride += count; }

		const std::vector<VertexBufferElement> GetElements() const { return elements; }
		unsigned int  GetStride() const { return stride; }
	private:
		std::vector<VertexBufferElement> elements;
		unsigned int stride = 0;
	};
}