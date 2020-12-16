#include "FontProgram2D.h"
#include "Engine.h"

#include <glm\gtc\type_ptr.hpp>
#include "VertexPos2D.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

FontProgram2D::FontProgram2D(void)
{
	mVertexPos2DLocation=0;
	mTexCoordLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mTextColorLocation=0;
	mTextureUnitLocation=0;
}


FontProgram2D::~FontProgram2D(void)
{
	mVertexPos2DLocation=0;
	mTexCoordLocation=0;
	mProjectionMatrixLocation=0;
	mModelViewMatrixLocation=0;	
	mTextColorLocation=0;
	//mTextureUnitLocation=0;
}

bool FontProgram2D::loadProgram()
{
	mProgramID = glCreateProgram();

	GLuint vertexShader,fragmentShader;

	vertexShader = loadShaderFromFile("FontProgram2D.glvs",GL_VERTEX_SHADER);

	glAttachShader(mProgramID,vertexShader);

	fragmentShader = loadShaderFromFile("FontProgram2D.glfs",GL_FRAGMENT_SHADER);

	glAttachShader(mProgramID,fragmentShader);

	if(vertexShader == 0 || fragmentShader == 0)
	{
		mProgramID = 0;
		return false;
	}

	glLinkProgram(mProgramID);

	GLint programSuccess = GL_FALSE;
	glGetProgramiv(mProgramID,GL_LINK_STATUS,&programSuccess);
	if( programSuccess != GL_TRUE )
    {
		printf( "Could not link program %d\n", mProgramID );
        mProgramID = 0;
        return false;
    }

	mProjectionMatrixLocation=glGetUniformLocation(mProgramID,"ProjectionMatrix");
	if(mProjectionMatrixLocation == -1)
	{
		printf("ProjectionMatrix is not a valid uniform\n");
	}
	mModelViewMatrixLocation=glGetUniformLocation(mProgramID,"ModelViewMatrix");
	if(mModelViewMatrixLocation == -1)
	{
		printf("ModelViewMatrix is not a valid uniform\n");
	}
	mVertexPos2DLocation = glGetAttribLocation(mProgramID,"VertexPos2D");
	if(mVertexPos2DLocation == -1)
	{
		printf("VertexPos2D is not a valid uniform\n");
	}
	mTexCoordLocation = glGetAttribLocation(mProgramID,"TextureCoord");
	if(mTexCoordLocation == -1)
	{
		printf("TextureCoord is not a valid uniform\n");
	}
	mTextColorLocation = glGetUniformLocation(mProgramID,"TextColor");
	if(mTextColorLocation == -1)
	{
		printf("TextColor is not a valid uniform\n");
	}
	mTextureUnitLocation = glGetUniformLocation(mProgramID,"TextureUnit");
	if(mTextureUnitLocation == -1)
	{
		printf("TextureUnit is not a valid uniform\n");
	}

	return true;
}

void FontProgram2D::setProjectionMatrix(glm::mat4 matrix)
{
	ProjectionMatrix = matrix;
}

void FontProgram2D::setModelViewMatrix(glm::mat4 matrix)
{
	ModelViewMatrix = matrix;
}

void FontProgram2D::setTextColor(GLfloat r,GLfloat g,GLfloat b,GLfloat a)
{
	glUniform4f(mTextColorLocation,r,g,b,a);
}

void FontProgram2D::setTextColor(Color4f col)
{
	glUniform4f(mTextColorLocation,col.r,col.g,col.b,col.a);
}

void FontProgram2D::updateProjectionMatrix()
{
	glUniformMatrix4fv(mProjectionMatrixLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
}

void FontProgram2D::updateModelViewMatrix()
{
	glUniformMatrix4fv(mModelViewMatrixLocation,1,GL_FALSE,glm::value_ptr(ModelViewMatrix));
}

void FontProgram2D::leftMultModelView(glm::mat4 matrix)
{
	ModelViewMatrix=ModelViewMatrix*matrix;
}

void FontProgram2D::setTextureUnit( GLuint unit )
{
	glUniform1i( mTextureUnitLocation, unit );
}

void FontProgram2D::enableDataPointers()
{
	glEnableVertexAttribArray(mTexCoordLocation);
	glEnableVertexAttribArray(mVertexPos2DLocation);

	//glEnableVertexAttribArray(0);
}

void FontProgram2D::setVertexPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mVertexPos2DLocation,2,GL_FLOAT,GL_FALSE,stride,data);
	//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride,data);
}

void FontProgram2D::setTexCoordPointer(GLsizei stride,const GLvoid* data)
{
	glVertexAttribPointer(mTexCoordLocation,2,GL_FLOAT,GL_FALSE,stride,data);

}


GLuint FontProgram2D::initVAO(GLuint textureWidth,GLuint textureHeight,Rect* clip)
{
		GLuint fVAO=0;
		GLuint vbo;
		GLuint ibo;

			GLfloat texLeft=clip->x/((float) textureWidth);
			GLfloat texRight=(clip->x+clip->w)/((float)textureWidth);
			GLfloat texTop=(clip->y+clip->h)/((float)textureHeight);
			GLfloat texBottom=clip->y/((float)textureHeight);
		

		TexturedVertexPos2D quadPos[ 4 ];
		quadPos[ 0 ].pos.x = 0.f; quadPos[ 0 ].pos.y = 0.f; 
		quadPos[ 1 ].pos.x = clip->w; quadPos[ 1 ].pos.y = 0.f; 
		quadPos[ 2 ].pos.x = clip->w; quadPos[ 2 ].pos.y = clip->h; 
		quadPos[ 3 ].pos.x = 0.f; quadPos[ 3 ].pos.y = clip->h;
		
		quadPos[ 0 ].texCoord.s = texLeft; quadPos[ 0 ].texCoord.t =   texTop; 
		quadPos[ 1 ].texCoord.s =texRight; quadPos[ 1 ].texCoord.t =   texTop; 
		quadPos[ 2 ].texCoord.s =texRight; quadPos[ 2 ].texCoord.t =texBottom; 
		quadPos[ 3 ].texCoord.s = texLeft; quadPos[ 3 ].texCoord.t =texBottom;

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
		glGenVertexArrays(1,&fVAO);
		glBindVertexArray(fVAO);
		//Pointers
		enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);
		
		return fVAO;
}

void FontProgram2D::drawVAO(GLuint textureID,GLuint fVAO,GLfloat x, GLfloat y)
{


		setModelViewMatrix(glm::mat4());
		leftMultModelView(glm::translate<GLfloat>(glm::vec3(x,y,0.f)));
		//leftMultModelView(glm::scale<GLfloat>(1.f,1.f,1.f));
		
		updateModelViewMatrix();
		
		glBindTexture(GL_TEXTURE_2D,textureID);
		glBindVertexArray( fVAO ); 
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		glBindVertexArray(NULL);
	
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected in font drawing");
		}
}

