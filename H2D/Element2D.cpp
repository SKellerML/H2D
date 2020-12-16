#include "Element2D.h"
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>

#include "VertexPos2D.h"

ElementProgram Element2D::elementProgram;

Element2D::Element2D(void)
{
	GLuint mVBOID=0;
	GLuint mIBOID=0;
	GLuint mVAOID=0;
}


Element2D::~Element2D(void)
{
	GLuint mVBOID=0;
	GLuint mIBOID=0;
	GLuint mVAOID=0;
}

void Element2D::loadElementProgram()
{
	elementProgram.loadProgram();
	elementProgram.bind();
	elementProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,0.f));
	elementProgram.updateProjectionMatrix();
	elementProgram.setModelViewMatrix(glm::mat4());
	elementProgram.updateModelViewMatrix();
	elementProgram.setColor(1.f,1.f,1.f,1.f);
}


void Element2D::initElement(std::vector<b2Vec2>* vertices)
{
	
	if(mVAOID == 0)
	{
		GLuint ibo;
		
		m_vertices=*vertices;

		amountOfVertices = m_vertices.size();
		
		drawingType=GL_LINE_STRIP;

		//if(amountOfVertices==1)			drawingType=GL_POINTS;
		//else if(amountOfVertices==2)	drawingType=GL_LINES;
		//else drawingType=GL_TRIANGLE_FAN;

		printf("T: %i || %i \n",GL_LINE,drawingType);
		
		std::vector<GLuint> indices;
		for(int i=0; i < amountOfVertices; i++)
		{
			indices.push_back(GLuint(i));
		}

			


		/*
		VertexPos2D quadPos[ 4 ];
		 
		quadPos[ 0 ].x =    -1000.f; quadPos[ 0 ].y =    -1000.f;
		quadPos[ 1 ].x = 1000.f; quadPos[ 1 ].y =    -1000.f;
		quadPos[ 2 ].x = 1000.f; quadPos[ 2 ].y = 1000.f;
		quadPos[ 3 ].x =    -1000.f; quadPos[ 3 ].y = 1000.f; 

		//Create VBOs 
		 glGenBuffers( 1, &vbo ); 
		 glBindBuffer( GL_ARRAY_BUFFER, vbo ); 
		 glBufferData( GL_ARRAY_BUFFER, 4 * sizeof(VertexPos2D), quadPos, GL_STATIC_DRAW ); 
	
		*/
		 //Create VBOs 
		 glGenBuffers( 1, &mVBOID ); 
		 glBindBuffer( GL_ARRAY_BUFFER, mVBOID ); 
		 glBufferData( GL_ARRAY_BUFFER, amountOfVertices * sizeof(b2Vec2), &m_vertices[0], GL_DYNAMIC_DRAW ); 
	
		 glGenBuffers( 1, &ibo); 
		 glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo ); 
		 glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW );
		
		//VAO
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		//glEnableVertexAttribArray(0);
		elementProgram.enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,mVBOID);
		//VertexPointer
		//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
		
		elementProgram.setVertexPointer(sizeof(VertexPos2D),(GLvoid*)offsetof(VertexPos2D,x));//(GLvoid*)offsetof(VertexPos2D,pos));
		
		//mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		//mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);
	}
	
	if(glGetError() != GL_NO_ERROR)
	{
		printf("Error detected");
	}

}

bool Element2D::updateVertex(GLuint vertexID,b2Vec2 vertexData)
{
	if(vertexID >= m_vertices.size())
	{


		return false;
	}
	else
	{	
		m_vertices[vertexID]=vertexData;

		glBindBuffer( GL_ARRAY_BUFFER, mVBOID );
		glBufferSubData( GL_ARRAY_BUFFER ,vertexID * sizeof(b2Vec2),sizeof(b2Vec2),&vertexData);

	}
	return true;
}
// Lines
void ElementLines::initElement(std::vector<b2Vec2>* vertices, GLfloat width, Color4f color, GLushort pattern, GLfloat factor, bool singleLine)
{

		m_linewidth=width;
		m_pattern=pattern;
		m_factor=factor;
		m_color=color;

		GLuint ibo;
		
		m_vertices=*vertices;

		amountOfVertices = m_vertices.size();
		
		if(singleLine)	drawingType=GL_LINE_STRIP;
		else drawingType = GL_LINES;
		
		std::vector<GLuint> indices;
		for(int i=0; i < amountOfVertices; i++)
		{
			indices.push_back(GLuint(i));
		}

		 //Create VBOs 
		 glGenBuffers( 1, &mVBOID ); 
		 glBindBuffer( GL_ARRAY_BUFFER, mVBOID ); 
		 glBufferData( GL_ARRAY_BUFFER, amountOfVertices * sizeof(b2Vec2), &m_vertices[0], GL_DYNAMIC_DRAW ); 
		
		//VAO
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		elementProgram.enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,mVBOID);
		//VertexPointer
		elementProgram.setVertexPointer(sizeof(VertexPos2D),(GLvoid*)offsetof(VertexPos2D,x));//(GLvoid*)offsetof(VertexPos2D,pos));

		glBindVertexArray(NULL);

		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
		}

}
void ElementLines::render(b2Vec2 pos,GLfloat angle)
{
	elementProgram.bind();
	elementProgram.setProjectionMatrix(glm::ortho<GLfloat>(0.5f,1920.5f,1080.5f,0.5f,-1.f,1.f));
	elementProgram.updateProjectionMatrix();

	elementProgram.setModelViewMatrix(glm::translate<GLfloat>( glm::vec3(pos.x,pos.y,0.f)));
	elementProgram.leftMultModelView(glm::rotate<GLfloat>(angle,glm::vec3(0.f, 0.f, 1.f)));
	elementProgram.updateModelViewMatrix();
	if(amountOfVertices > 1)
	{
		elementProgram.bind();
		elementProgram.setColor(m_color);

		//glEnable(GL_LINE_STIPPLE);	// http://www.felixgers.de/teaching/jogl/stippledLines.html
		glEnable(GL_LINE_WIDTH);

		glLineWidth(m_linewidth);
		glLineStipple(m_factor,m_pattern);

		glBindVertexArray( mVAOID ); 
		glDrawArrays( drawingType, 0,amountOfVertices);
		glBindVertexArray(NULL);

	}

	if(glGetError() == GL_INVALID_VALUE)//GL_NO_ERROR)
	{
		printf("Error detected in Line rendering\n");
	}
}
// Polygon
void ElementPolygon::initElement(std::vector<b2Vec2>* vertices,Color4f color)
{

	m_vertices.clear();

		m_color=color;
		GLuint ibo;
		
		m_vertices=*vertices;

		amountOfVertices = m_vertices.size();
		
		drawingType=GL_TRIANGLE_FAN;
		
		
		/*
		std::vector<GLuint> indices;
		for(int i=0; i < amountOfVertices; i++)
		{
			indices.push_back(GLuint(i));
		}*/

		 //Create VBOs 
		 glGenBuffers( 1, &mVBOID ); 
		 glBindBuffer( GL_ARRAY_BUFFER, mVBOID ); 
		 glBufferData( GL_ARRAY_BUFFER, amountOfVertices * sizeof(b2Vec2), &m_vertices[0], GL_DYNAMIC_DRAW ); 
	
		 //glGenBuffers( 1, &ibo); 
		 //glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo ); 
		 //glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW );
		
		//VAO
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		elementProgram.enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,mVBOID);
		//VertexPointer
		elementProgram.setVertexPointer(sizeof(VertexPos2D),(GLvoid*)offsetof(VertexPos2D,x));//(GLvoid*)offsetof(VertexPos2D,pos));

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);

		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
		}
}

void ElementPolygon::render(b2Vec2 pos,GLfloat angle)
{

	elementProgram.bind();
	
	
	elementProgram.setModelViewMatrix(glm::translate<GLfloat>( glm::vec3(pos.x, pos.y, 0.f)));
	elementProgram.leftMultModelView(glm::rotate<GLfloat>(angle, glm::vec3(0.f, 0.f, 1.f)));
	elementProgram.updateModelViewMatrix();

	if(amountOfVertices > 1)
	{
		//elementProgram.bind();
		elementProgram.setColor(m_color);

		glBindVertexArray( mVAOID ); 
		//glDrawElements( drawingType, amountOfVertices, GL_UNSIGNED_INT, NULL );
		glDrawArrays(drawingType, 0, m_vertices.size());
		glBindVertexArray(NULL);
	}
	if (glGetError() != GL_NO_ERROR)
	{
		printf("Error detected in Line rendering\n");
	}
}