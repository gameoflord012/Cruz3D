#pragma once

#include "Cruz3D\Graphic.h"
#include "assimp\mesh.h"

namespace cruz
{
	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const aiMesh&);

		void AddMesh(const aiMesh&);
		const VertexBuffer& GetVBuf() const;
		const IndexBuffer& GetIBuf() const;
		unsigned int NumberOfIndicies() const;
	private:
		VertexBuffer m_vbuf;
		IndexBuffer m_ibuf;
	};
}