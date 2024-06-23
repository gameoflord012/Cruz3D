#include <stdio.h>
#include "Mesh.h"

namespace cruz
{
	void Mesh::AddMesh(const aiMesh& mesh)
	{
		for (unsigned int i = 0; i < mesh.mNumVertices; i++)
		{
			m_vbuf.Push(mesh.mVertices[i]);
			m_vbuf.Push(mesh.HasVertexColors(0) ? mesh.mColors[0][i] : aiColor4D(0, 1, 0, 1));
			m_vbuf.Push(mesh.HasTextureCoords(0) ? mesh.mTextureCoords[0][i] : aiVector3D(0, 0, 0));
		}

		for (size_t i = 0; i < mesh.mNumFaces; i++)
		{
			m_ibuf.Push(mesh.mFaces[i]);
		}
	}

	const VertexBuffer& Mesh::GetVBuf() const
	{
		return m_vbuf;
	}

	const IndexBuffer& Mesh::GetIBuf() const
	{
		return m_ibuf;
	}
    
	unsigned int Mesh::NumberOfIndicies() const
    {
        return m_ibuf.count();
    }
    } // namespace cruz
