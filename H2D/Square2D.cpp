#include "Square2D.h"
#include "VertexPos2D.h"
#include <gtx\transform.hpp>
#include "Engine.h"

BorderPolygon2D *Square2D::mBorderProgram2D = NULL;

void Square2D::setBorderPolygon2D(BorderPolygon2D *polygonProgram)
{
	mBorderProgram2D=polygonProgram;
}

void Square2D::unsetBorderPolygon2D()
{
	delete[] mBorderProgram2D;
	mBorderProgram2D=NULL;
}

Square2D::Square2D(void)
{
}


Square2D::~Square2D(void)
{
}

GLuint Square2D::initVAO(Rect* clip,GLfloat thickness)
{
		GLuint vaoID;
		GLuint vbo;
		GLuint ibo;

		VertexPos2D quadPos[ 4 ];
		quadPos[0].x = -clip->w / 2.f; quadPos[0].y = -clip->h / 2.f;
		quadPos[1].x = clip->w / 2.f; quadPos[1].y = -clip->h / 2.f;
		quadPos[2].x = clip->w / 2.f; quadPos[2].y = clip->h / 2.f;
		quadPos[3].x = -clip->w / 2.f; quadPos[3].y = clip->h / 2.f;
		

		GLuint indices[ 4 ];
		indices[ 0 ] = 0; indices[ 1 ] = 1; indices[ 2 ] = 2; indices[ 3 ] = 3;

		 //Create VBOs 
		 glGenBuffers( 1, &vbo ); 
		 glBindBuffer( GL_ARRAY_BUFFER, vbo ); 
		 glBufferData( GL_ARRAY_BUFFER, 4 * sizeof(TexturedVertexPos2D), quadPos, GL_STATIC_DRAW ); 
	
		 glGenBuffers( 1, &ibo); 
		 glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo ); 
		 glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW );
		
		//VAO
		glGenVertexArrays(1,&vaoID);
		glBindVertexArray(vaoID);
		//Pointers
		//glEnableVertexAttribArray(0);
		mBorderProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
		
		mBorderProgram2D->setVertexPointer();
		
		//mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		//mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);

		return vaoID;
}

void Square2D::render(GLuint vaoID,GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,Color4f *color)
{
		mBorderProgram2D->bind();

		mBorderProgram2D->setModelViewMatrix(glm::translate<GLfloat>(x,y,0.f));
		//mBorderProgram2D->leftMultModelView(glm::scale<GLfloat>(sx,sy,1.f));
		//mBorderProgram2D->leftMultModelView(glm::rotate<GLfloat>(rz,0.f,0.f,1.f));

		mBorderProgram2D->updateModelViewMatrix();

		mBorderProgram2D->setColor(color->r,color->g,color->b,color->a);
		//mBorderProgram2D->setColor(0,0,0,1);
		//glm::vec4 x = glm::vec4(-.5,-.5,-.5,-.5);

		//glm::mat4(glm::vec4(-.5,-.5,-.5,-.5),glm::vec4(-.5,-.5,-.5,-.5),glm::vec4(-.5,-.5,-.5,-.5),glm::vec4(-.5,-.5,-.5,-.5));

		glBindVertexArray( vaoID ); 
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		
		/* Border Test 1
			glBindVertexArray( vaoID+1 ); 
			glLineWidth(20.f);
			glDrawElements(GL_LINE_LOOP,4,GL_UNSIGNED_INT,NULL);
		*/
		glBindVertexArray(NULL);
	
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
		}
}