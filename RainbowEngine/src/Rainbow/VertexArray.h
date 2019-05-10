#pragma once

#include "VertexBuffer.h"

namespace Rainbow {

	//juste pour �viter des pb d'inclusion
	class VertexBufferLayout;

	class VertexArray {

	private:

		unsigned int m_RendererID;

	public:
		//Constructeur du vertex Array
		VertexArray();

		//Destructeur du vertex array
		~VertexArray();

		//Ajout du Vertex Buffer (les donn�es) et le layout � notre VertexArray
		void AddBuffer( const VertexBuffer& vb, const VertexBufferLayout& layout);

		//Pour lier notre VertexArray au renderer
		void Bind() const;

		//d�lier notre VertexArray au renderer
		void UnBind() const;
	};
}