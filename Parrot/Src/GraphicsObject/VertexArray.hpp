#pragma once
#include "VertexBuffer.hpp"

namespace Parrot
{
	namespace GraphicsObject
	{
		enum class VertexAttribute
		{
			FLOAT, FLOAT2, FLOAT3, FLOAT4, INT
		};

		class VertexArray
		{
		private:
			uint32_t m_ID = 0;
		public:
			uint32_t GetID() const { return m_ID; }
		private:
			void CreateBuffer();
			void AddElement(uint32_t element, VertexAttribute type, uint64_t offset, uint32_t stride);

			constexpr uint32_t GetStride()
			{
				return 0;
			}
			template<class Arg, class... FArgs>
			constexpr uint32_t GetStride(Arg arg, FArgs... fArgs)
			{
				uint32_t offset = 0;
				switch (arg)
				{
				case VertexAttribute::FLOAT:
					offset = 4;
					break;
				case VertexAttribute::FLOAT2:
					offset = 8;
					break;
				case VertexAttribute::FLOAT3:
					offset = 12;
					break;
				case VertexAttribute::FLOAT4:
					offset = 16;
					break;
				case VertexAttribute::INT:
					offset = 4;
					break;
				default:
					break;
				}
				return GetStride(fArgs...) + offset;
			}

			void RecursiveAddElement(uint32_t element, uint64_t offset, uint32_t stride) { }
			template<class Arg, class... FArgs>
			void RecursiveAddElement(uint32_t element, uint64_t offset, uint32_t stride, Arg arg, FArgs... fArgs)
			{
				AddElement(element, arg, offset, stride);
				RecursiveAddElement(element + 1, offset + GetStride(arg), stride, fArgs...);
			}
		public:
			template<class Arg, class... FArgs>
			VertexArray(const VertexBuffer& vb, Arg arg, FArgs... fArgs)
			{
				CreateBuffer();
				vb.Bind();
				Bind();
				RecursiveAddElement(0, 0, GetStride(arg, fArgs...), arg, fArgs...);
			}

			~VertexArray();

			void Bind() const;
			void Unbind() const;
		};
	}
}