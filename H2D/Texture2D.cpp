#include "Texture2D.h"
#include "VertexPos2D.h"
#include "Engine.h"

#include <IL\il.h>
#include <IL\ilu.h>

#include <gtx\transform.hpp>

TexturedPolygon2D* Texture2D::mTexturePolygonProgram2D = NULL;

void Texture2D::setTexturedPolygonProgram2D(TexturedPolygon2D* program)
{
	mTexturePolygonProgram2D = program;
}

Texture2D::Texture2D(void)
{
	mVAOID = 0;
	mTextureID=0;

	mPixels32 = NULL;
	mPixels8  = NULL;

	mTextureWidth= 0;
	mTextureHeight= 0;

	mImgWidth= 0;
	mImgHeight= 0;

	mPixelFormat= 0;

	mVBOID= 0;
	mIBOID= 0;
	mVAOID= 0;
}


Texture2D::~Texture2D(void)
{
	glDeleteTextures(1,&mTextureID);

	delete[] mPixels8;
	delete[] mPixels32;

	mVAOID = 0;
	mTextureID=0;

	mPixels32 = NULL;
	mPixels8  = NULL;

	mTextureWidth= 0;
	mTextureHeight= 0;

	mImgWidth= 0;
	mImgHeight= 0;

	mPixelFormat= 0;

	mVBOID= 0;
	mIBOID= 0;
	mVAOID= 0;
}

bool Texture2D::loadTextureFromFile32(std::string path)
{
	bool textureloaded=false;

	ILuint imgID = 0;
	ilGenImages(1,&imgID);
	ilBindImage(imgID);
	
	ILboolean success = ilLoadImage((const wchar_t*)path.c_str());
	if(success==IL_TRUE)
	{
				
		success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
        if( success == IL_TRUE )
        {
			GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

			GLuint texWidth = powerOfTwo(imgWidth);
			GLuint texHeight = powerOfTwo(imgHeight);
		
			if(imgWidth != texWidth || imgHeight != texHeight)
			{
				iluImageParameter(ILU_PLACEMENT,ILU_UPPER_LEFT);
				iluEnlargeCanvas((int)texWidth,(int)texHeight,1);
			}
			textureloaded = loadTextureFromPixels32( (GLuint*)ilGetData(), imgWidth, imgHeight, texWidth, texHeight );
		}
			
			ilDeleteImages( 1, &imgID );
			mPixelFormat = GL_RGBA;
	}

	if(!textureloaded)
	{
		printf( "Unable to load %s\n", path.c_str() );
	}
	return textureloaded;
	
}

bool Texture2D::loadPixelsFromFile32(std::string path)
{
	bool pixelsloaded=false;

	ILuint imgID = 0;
	ilGenImages(1,&imgID);
	ilBindImage(imgID);
	
	ILboolean success = ilLoadImage((const wchar_t*)path.c_str());
	if(success==IL_TRUE)
	{
		success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
        if( success == IL_TRUE )
        {
			mImgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			mImgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

			mTextureWidth = powerOfTwo(mImgWidth);
			mTextureHeight = powerOfTwo(mImgHeight);
		
			if(mImgWidth != mTextureWidth || mImgHeight != mTextureHeight)
			{
				iluImageParameter(ILU_PLACEMENT,ILU_UPPER_LEFT);
				iluEnlargeCanvas((int)mTextureWidth,(int)mTextureHeight,1);
			}

			GLuint size = mTextureWidth*mTextureHeight;
			mPixels32=new GLuint[size];

			memcpy(mPixels32,ilGetData(),size*4);

			pixelsloaded = true;
		}
			
			ilDeleteImages( 1, &imgID );
			mPixelFormat = GL_RGBA;
	}

	if(!pixelsloaded)
	{
		printf( "Unable to load %s\n", path.c_str() );
	}
	return pixelsloaded;
}

bool Texture2D::loadPixelsFromFile8(std::string path)
{
	bool pixelsloaded=false;

	ILuint imgID = 0;
	ilGenImages(1,&imgID);
	ilBindImage(imgID);
	
	ILboolean success = ilLoadImage((const wchar_t*)path.c_str());
	if(success==IL_TRUE)
	{
		success = ilConvertImage( IL_LUMINANCE, IL_UNSIGNED_BYTE );
        if( success == IL_TRUE )
        {
			mImgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			mImgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

			mTextureWidth = powerOfTwo(mImgWidth);
			mTextureHeight = powerOfTwo(mImgHeight);
		
			if(mImgWidth != mTextureWidth || mImgHeight != mTextureHeight)
			{
				iluImageParameter(ILU_PLACEMENT,ILU_UPPER_LEFT);
				iluEnlargeCanvas((int)mTextureWidth,(int)mTextureHeight,1);
			}

			GLuint size = mTextureWidth*mTextureHeight;
			mPixels8=new GLubyte[size];

			memcpy(mPixels8,ilGetData(),size);

			pixelsloaded = true;
		}
			
			ilDeleteImages( 1, &imgID );
			mPixelFormat = GL_RED;
	}

	if(!pixelsloaded)
	{
		printf( "Unable to load %s\n", path.c_str() );
	}
	return pixelsloaded;
}
	
bool Texture2D::loadTextureFromPixels32()
{
	if(mTextureID==0 && mPixels32 != NULL)
	{
		glGenTextures(1,&mTextureID);
		glBindTexture(GL_TEXTURE_2D,mTextureID);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mTextureWidth,mTextureHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,mPixels32);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

		glBindTexture(GL_TEXTURE_2D,NULL);

		delete[] mPixels32;
		mPixels32 = NULL;

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error loading texture from pixels! \n");
			return false;
		}
		Rect c(0.f,0.f,(GLfloat)mImgWidth,(GLfloat)mImgHeight);
		initVAO(&c);

		mPixelFormat = GL_RGBA;
		return true;
	}
	return false;
}

bool Texture2D::loadTextureFromPixels8()
{
	if(mTextureID==0 && mPixels8 != NULL)
	{
		glGenTextures(1,&mTextureID);
		glBindTexture(GL_TEXTURE_2D,mTextureID);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RED,mTextureWidth,mTextureHeight,0,GL_RED,GL_UNSIGNED_BYTE,mPixels8);
	glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
		
		glBindTexture(GL_TEXTURE_2D,NULL);

		//delete[] mPixels8;
		mPixels8 = NULL;

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error loading texture from pixels! \n");
			return false;
		}
		Rect c(0.f,0.f,(GLfloat)mImgWidth,(GLfloat)mImgHeight);
		initVAO(&c);

		mPixelFormat = GL_RED;
		return true;
	}
	return false;
}

bool Texture2D::loadTextureFromPixels32( GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight )
{
	if(mTextureID == 0)
	{
		mImgWidth=imgWidth;
		mImgHeight=imgHeight;
		mTextureWidth=texWidth;
		mTextureHeight=texHeight;

		glGenTextures(1,&mTextureID);
		glBindTexture(GL_TEXTURE_2D,mTextureID);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mTextureWidth,mTextureHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

		glBindTexture(GL_TEXTURE_2D,NULL);

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error loading texture! \n");
			return false;
		}
		Rect c(0.f,0.f,(GLfloat)mImgWidth,(GLfloat)mImgHeight);
		initVAO(&c);
		mPixelFormat = GL_RGBA;
		return true;
	}
	return false;
}

bool Texture2D::loadScreenshotFromPixels32( GLuint* pixels, GLuint imgWidth, GLuint imgHeight, GLuint texWidth, GLuint texHeight )
{
	if(mTextureID == 0)
	{
		/*
		mImgWidth=imgWidth;
		mImgHeight=imgHeight;
		mTextureWidth=texWidth;
		mTextureHeight=texHeight;
		*/

		glGenTextures(1,&mTextureID);
		glBindTexture(GL_TEXTURE_2D,mTextureID);
		
		//glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mTextureWidth,mTextureHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1920,1080,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
		glGenerateMipmapEXT(GL_TEXTURE_2D);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

		glBindTexture(GL_TEXTURE_2D,NULL);

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error loading texture! \n");
			return false;
		}
		
		// INIT VAO START
		/*
		
		Rect c = {0.f,0.f,(GLfloat)mImgWidth,(GLfloat)mImgHeight};

			texLeft=clip->x/mImgWidth;
			texRight=(clip->x+clip->w)/mImgWidth;
			texTop=clip->y/mImgHeight;
			texBottom=(clip->y+clip->h)/mImgHeight;

			GLfloat posRight = clip->w;
			GLfloat posBottom = clip->h;
			*/
		GLuint vbo;
		GLuint ibo;

		GLfloat texLeft = 1.f;
		GLfloat texRight = 0.f;
		GLfloat texTop = 0.f;
		GLfloat texBottom = 1.f;


		GLfloat posLeft = Engine::screenWidth();
		GLfloat posRight = 0.f;
		GLfloat posTop = Engine::screenHeight();
		GLfloat posBottom = 0.f;

		TexturedVertexPos2D quadPos[ 4 ];
		quadPos[ 0 ].pos.x = posLeft;  quadPos[ 0 ].pos.y = posTop; 
		quadPos[ 1 ].pos.x = posRight; quadPos[ 1 ].pos.y = posTop; 
		quadPos[ 2 ].pos.x = posRight; quadPos[ 2 ].pos.y = posBottom; 
		quadPos[ 3 ].pos.x = posLeft;  quadPos[ 3 ].pos.y = posBottom;
		
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
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		//glEnableVertexAttribArray(0);
		mTexturePolygonProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
		
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		
		//mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		//mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);

		// INIT VAO END

		mPixelFormat = GL_RGBA;
		return true;
	}
	return false;
}

void Texture2D::createScreenTexture(int w,int h)
{
	glGenTextures(1,&mTextureID);
	glBindTexture(GL_TEXTURE_2D,mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error loading texture! \n");
		}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR); /* no mipmaps (see below) */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  /* no repeat (see below) */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D,NULL);

	// VAO

		GLuint vbo;
		GLuint ibo;

		GLfloat texLeft = 1.f;
		GLfloat texRight = 0.f;
		GLfloat texTop = 0.f;
		GLfloat texBottom = 1.f;


		GLfloat posLeft = Engine::screenWidth();
		GLfloat posRight = 0.f;
		GLfloat posTop = Engine::screenHeight();
		GLfloat posBottom = 0.f;

		TexturedVertexPos2D quadPos[ 4 ];
		quadPos[ 0 ].pos.x = posLeft;  quadPos[ 0 ].pos.y = posTop; 
		quadPos[ 1 ].pos.x = posRight; quadPos[ 1 ].pos.y = posTop; 
		quadPos[ 2 ].pos.x = posRight; quadPos[ 2 ].pos.y = posBottom; 
		quadPos[ 3 ].pos.x = posLeft;  quadPos[ 3 ].pos.y = posBottom;
		
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
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		//glEnableVertexAttribArray(0);
		mTexturePolygonProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
		
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		
		// WARNING || SCREEN TEXTURE HAS mImgHeight and mImgWidth as vbo and ibo id's || WARNING
		mImgHeight = vbo;
		mImgWidth = ibo;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);

}

void Texture2D::changeScreenTextureSize()
{
	// WARNING || SCREEN TEXTURE HAS mImgHeight and mImgWidth as vbo and ibo id's || WARNING
	glDeleteVertexArrays(1,&mVAOID);
	glDeleteBuffers(1,&mImgHeight);
	glDeleteBuffers(1,&mImgWidth);


		GLuint vbo;
		GLuint ibo;

		GLfloat texLeft = 1.f;
		GLfloat texRight = 0.f;
		GLfloat texTop = 0.f;
		GLfloat texBottom = 1.f;


		GLfloat posLeft = Engine::screenWidth();
		GLfloat posRight = 0.f;
		GLfloat posTop = Engine::screenHeight();
		GLfloat posBottom = 0.f;

		TexturedVertexPos2D quadPos[ 4 ];
		quadPos[ 0 ].pos.x = posLeft;  quadPos[ 0 ].pos.y = posTop; 
		quadPos[ 1 ].pos.x = posRight; quadPos[ 1 ].pos.y = posTop; 
		quadPos[ 2 ].pos.x = posRight; quadPos[ 2 ].pos.y = posBottom; 
		quadPos[ 3 ].pos.x = posLeft;  quadPos[ 3 ].pos.y = posBottom;
		
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
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		//glEnableVertexAttribArray(0);
		mTexturePolygonProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
		
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		
		//mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		//mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);
}


void Texture2D::createPixels32(GLuint imgWidth,GLuint imgHeight)
{
	if(imgWidth > 0 && imgHeight > 0)
	{
		GLuint size = imgWidth * imgHeight;
		mPixels32= new GLuint[size];
		memset(mPixels32,0,size*4);

		mImgWidth=imgWidth;
		mImgHeight=imgHeight;
		mTextureWidth=imgWidth;
		mTextureHeight=imgHeight;

		mPixelFormat = GL_RGBA;
	}
}

void Texture2D::createPixels8(GLuint imgWidth,GLuint imgHeight)
{
	if(imgWidth > 0 && imgHeight > 0)
	{
		GLuint size = imgWidth * imgHeight;
		mPixels8= new GLubyte[size];
		memset(mPixels8,0,size);

		mImgWidth=imgWidth;
		mImgHeight=imgHeight;
		mTextureWidth=imgWidth;
		mTextureHeight=imgHeight;

		mPixelFormat = GL_RED;
	}
}

void Texture2D::copyPixels32(GLuint* pixels, GLuint imgWidth,GLuint imgHeight)
{
	if(imgWidth > 0 && imgHeight > 0)
	{
		GLuint size = imgWidth * imgHeight;
		mPixels32= new GLuint[size];
		memcpy(mPixels32,pixels,size*4);

		mImgWidth=imgWidth;
		mImgHeight=imgHeight;
		mTextureWidth=imgWidth;
		mTextureHeight=imgHeight;

		mPixelFormat = GL_RGBA;
	}
}

void Texture2D::copyPixels8(GLubyte* pixels, GLuint imgWidth,GLuint imgHeight)
{
	if(imgWidth > 0 && imgHeight > 0)
	{
		GLuint size = imgWidth * imgHeight;
		mPixels8= new GLubyte[size];
		memcpy(mPixels8,pixels,size);

		mImgWidth=imgWidth;
		mImgHeight=imgHeight;
		mTextureWidth=imgWidth;
		mTextureHeight=imgHeight;

		mPixelFormat = GL_RED;
	}
}

void Texture2D::padPixels32()
{
	if(mPixels32 != NULL)
	{
		GLuint oTextureWidth = mTextureWidth;
		GLuint oTextureHeight = mTextureHeight;

		mTextureWidth=powerOfTwo(mImgWidth);
		mTextureHeight=powerOfTwo(mImgHeight);

		if(mTextureWidth != mImgWidth && mTextureHeight != mImgWidth)
		{
			GLuint size = mTextureWidth * mTextureHeight;
			GLuint* pixels = new GLuint[size];

			for(unsigned int i = 0;i<mImgHeight;++i)
			{
				memcpy( &pixels[ i * mTextureWidth ], &mPixels32[ i * oTextureWidth ], mImgWidth * 4 );
			}

			delete[] mPixels32;
			mPixels32 = pixels;
		}

	}
}

void Texture2D::padPixels8()
{
	if(mPixels8 != NULL)
	{
		GLuint oTextureWidth = mTextureWidth;
		GLuint oTextureHeight = mTextureHeight;

		mTextureWidth=powerOfTwo(mImgWidth);
		mTextureHeight=powerOfTwo(mImgHeight);

		if(mTextureWidth != mImgWidth && mTextureHeight != mImgWidth)
		{
			GLuint size = mTextureWidth * mTextureHeight;
			GLubyte* pixels = new GLubyte[size];

			for(unsigned int i = 0;i<mImgHeight;++i)
			{
				memcpy( &pixels[ i * mTextureWidth ], &mPixels8[ i * oTextureWidth ], mImgWidth);
			}

			delete[] mPixels8;
			mPixels8 = pixels;
		}

	}
}

GLubyte* Texture2D::padPixels8(GLubyte* pixels)
{
	if(mPixels8 != NULL)
	{
		GLuint oTextureWidth = mTextureWidth;
		GLuint oTextureHeight = mTextureHeight;

		mTextureWidth=powerOfTwo(mImgWidth);
		mTextureHeight=powerOfTwo(mImgHeight);

		if(mTextureWidth != mImgWidth && mTextureHeight != mImgWidth)
		{
			GLuint size = mTextureWidth * mTextureHeight;
			GLubyte* pixels2 = new GLubyte[size];

			for(unsigned int i = 0;i<mImgHeight;++i)
			{
				memcpy( &pixels2[ i * mTextureWidth ], &pixels[ i * oTextureWidth ], mImgWidth);
			}

			return pixels2;
		}

	}
	return NULL;
}

void Texture2D::blitPixels32(GLuint x, GLuint y, Texture2D& destination)
{
	if(mPixels32 != NULL && destination.mPixels32 != 0)
	{
		GLuint* dPixels = destination.mPixels32;
		GLuint* sPixels = mPixels32;

		for(unsigned int i = 0; i < mImgHeight; ++i )
        {
            memcpy( &dPixels[ ( i + y ) * destination.mTextureWidth + x ], &sPixels[ i * mTextureWidth ], mImgWidth * 4 );
        }

	}

}

void Texture2D::blitPixels8(GLuint x, GLuint y, Texture2D& destination)
{
	if(mPixels8 != NULL && destination.mPixels8 != 0)
	{
		GLubyte* dPixels = destination.mPixels8;
		GLubyte* sPixels = mPixels8;

		for(unsigned int i = 0; i < mImgHeight; ++i )
        {
            memcpy( &dPixels[ ( i + y ) * destination.mTextureWidth + x ], &sPixels[ i * mTextureWidth ], mImgWidth );
        }

	}

}

void Texture2D::render(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,GLfloat rPointX,GLfloat rPointY)
{
	if(mTextureID != 0)
	{
		mTexturePolygonProgram2D->bind();

		
		mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(x,y,0.f));
		
		mTexturePolygonProgram2D->leftMultModelView(glm::rotate<GLfloat>(rz,0.f,0.f,1.f));		
		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(rPointX,rPointY,0.f));
		mTexturePolygonProgram2D->leftMultModelView(glm::scale<GLfloat>(sx,sy,1.f));
		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
		mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
		
		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));		
		
		
		

		mTexturePolygonProgram2D->updateModelViewMatrix();

		//Usually it is scale * rotation * translation. However, if you want to rotate an object around a certain point, then it is scale * point_translation * rotation * object_translation.

		glBindTexture(GL_TEXTURE_2D,mTextureID);

		glBindVertexArray( mVAOID );
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		glBindVertexArray(NULL);
	
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected: Rendering Texture\n");

			if(glGetError() == GL_INVALID_OPERATION)
			{
			printf("Error detected: Framebuffer Operation\n");
			}
		}
	}
	else
	{
		printf("No texture loaded");
	}
}

void Texture2D::render(GLfloat x, GLfloat y, Color4f color, GLfloat sx, GLfloat sy, GLfloat rz, GLfloat rPointX, GLfloat rPointY)
{
	if (mTextureID != 0)
	{
		mTexturePolygonProgram2D->bind();


		mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(x, y, 0.f));

		mTexturePolygonProgram2D->leftMultModelView(glm::rotate<GLfloat>(rz, 0.f, 0.f, 1.f));
		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(rPointX,rPointY,0.f));
		mTexturePolygonProgram2D->leftMultModelView(glm::scale<GLfloat>(sx, sy, 1.f));
		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
		mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX, -rPointY, 0.f));

		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));		




		mTexturePolygonProgram2D->updateModelViewMatrix();
		mTexturePolygonProgram2D->setTextureColor(color.r, color.g, color.b, color.a);
		//Usually it is scale * rotation * translation. However, if you want to rotate an object around a certain point, then it is scale * point_translation * rotation * object_translation.

		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glBindVertexArray(mVAOID);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(NULL);

		if (glGetError() != GL_NO_ERROR)
		{
			printf("Error detected: Rendering Texture\n");

			if (glGetError() == GL_INVALID_OPERATION)
			{
				printf("Error detected: Framebuffer Operation\n");
			}
		}
		mTexturePolygonProgram2D->setTextureColor(1.f,1.f,1.f,1.f);
	}
	else
	{
		printf("No texture loaded");
	}
}

void Texture2D::renderVAO(GLuint fVAO,GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,GLfloat rPointX,GLfloat rPointY)
{
	if(mTextureID != 0)
	{
		mTexturePolygonProgram2D->bind();

		if(rPointX != 0.f || rPointY != 0.f)
		{
			//mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(+rPointX,+rPointY,0.f));
			//mTexturePolygonProgram2D->leftMultModelView(glm::rotate<GLfloat>(rz,0.f,0.f,1.f));			
			//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));

			//mTexturePolygonProgram2D->leftMultModelView(glm::scale<GLfloat>(sx,sy,1.f));
			//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(x, y, 0.f));
			mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(x, y, 0.f));
			mTexturePolygonProgram2D->leftMultModelView(glm::scale<GLfloat>(sx, sy, 1.f));
			mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX, -rPointY, 0.f));
			mTexturePolygonProgram2D->leftMultModelView(glm::rotate<GLfloat>(rz, 0.f, 0.f, 1.f));
			mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(+rPointX, +rPointY, 0.f));
		}
		else
		{
			//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(-rPointX,-rPointY,0.f));
			mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(x,y,0.f));
			mTexturePolygonProgram2D->leftMultModelView(glm::scale<GLfloat>(sx,sy,1.f));

			mTexturePolygonProgram2D->leftMultModelView(glm::rotate<GLfloat>(rz,0.f,0.f,1.f));

		}

		//mTexturePolygonProgram2D->leftMultModelView(glm::translate<GLfloat>(x,y,0.f));
		

		mTexturePolygonProgram2D->updateModelViewMatrix();


		glBindTexture(GL_TEXTURE_2D,mTextureID);

		glBindVertexArray( fVAO ); 
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		//glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		glBindVertexArray(NULL);
	
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
		}
	}
	else
	{
		printf("No texture loaded");
	}
}

void Texture2D::renderFast(b2Vec2 pos)
{


	mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(pos.x, pos.y,0.f));



		mTexturePolygonProgram2D->updateModelViewMatrix();


		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glBindVertexArray(mVAOID);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(NULL);

		if (glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
		}
}

GLuint Texture2D::getTextureID()
{
	return mTextureID;
}

GLuint Texture2D::powerOfTwo(GLuint num)
{
	    if( num != 0 )
    {
        num--;
        num |= (num >> 1); //Or first 2 bits
        num |= (num >> 2); //Or next 2 bits
        num |= (num >> 4); //Or next 4 bits
        num |= (num >> 8); //Or next 8 bits
        num |= (num >> 16); //Or next 16 bits
        num++;
    }
    return num;
}

void Texture2D::initVAO(Rect* clip)
{
	if(mTextureID != 0 && mVAOID == 0)
	{
		GLuint vbo;
		GLuint ibo;

		GLfloat texLeft = 0.f;
		GLfloat texRight = (float)mImgWidth/(float)mTextureWidth;
		GLfloat texTop = (float)mImgHeight/(float)mTextureHeight;
		GLfloat texBottom = 0.f;

		GLfloat posLeft = -1.f*(float)mImgWidth/2.f;
		GLfloat posRight = (float)mImgWidth/2.f;
		GLfloat posTop = -1.f*(float)mImgHeight/2.f;
		GLfloat posBottom = (float)mImgHeight/2.f;

		//printf("Object: Img: %f, r: %f, t: %f, b %f \n",posLeft,posRight,posTop,posBottom);
		
		if(clip != NULL)
		{
			texLeft=clip->x/((float)mTextureWidth);
			texRight=(clip->x+clip->w)/((float)mTextureWidth);
			texTop=(clip->y+clip->h)/((float)mTextureHeight);
			texBottom=clip->y/((float)mTextureHeight);

			GLfloat posLeft = -1.f*(float)mImgWidth/2.f;
			GLfloat posRight = (float)mImgWidth/2.f;
			GLfloat posTop = -1.f*(float)mImgHeight/2.f;
			GLfloat posBottom = (float)mImgHeight/2.f;
		}
		
		TexturedVertexPos2D quadPos[ 4 ];
		 
		quadPos[ 0 ].pos.x =  posLeft; quadPos[ 0 ].pos.y = posBottom;
		quadPos[ 1 ].pos.x = posRight; quadPos[ 1 ].pos.y = posBottom;
		quadPos[ 2 ].pos.x = posRight; quadPos[ 2 ].pos.y =    posTop;
		quadPos[ 3 ].pos.x =  posLeft; quadPos[ 3 ].pos.y =    posTop; 
/*		 
		quadPos[ 0 ].pos.x = posLeft; quadPos[ 0 ].pos.y = posBottom;
		quadPos[ 1 ].pos.x = posRight; quadPos[ 1 ].pos.y = posBottom;
		quadPos[ 2 ].pos.x = posRight; quadPos[ 2 ].pos.y = posTop;
		quadPos[ 3 ].pos.x = posLeft; quadPos[ 3 ].pos.y = posTop; 
*/
		quadPos[ 0 ].texCoord.s = texLeft; quadPos[ 0 ].texCoord.t =texBottom;
		quadPos[ 1 ].texCoord.s =texRight; quadPos[ 1 ].texCoord.t =texBottom; 		
		quadPos[ 2 ].texCoord.s =texRight; quadPos[ 2 ].texCoord.t =   texTop;		
		quadPos[ 3 ].texCoord.s = texLeft; quadPos[ 3 ].texCoord.t =   texTop; 
		
		/*
		quadPos[ 0 ].pos.x = -mTextureWidth/2.f; quadPos[ 0 ].pos.y = -mTextureHeight/2.f;
		quadPos[ 1 ].pos.x = mTextureWidth/2.f; quadPos[ 1 ].pos.y = -mTextureHeight/2.f;
		quadPos[ 2 ].pos.x = mTextureWidth/2.f; quadPos[ 2 ].pos.y = mTextureHeight/2.f;
		quadPos[ 3 ].pos.x = -mTextureWidth/2.f; quadPos[ 3 ].pos.y = mTextureHeight/2.f; 

		quadPos[ 3 ].texCoord.s = texLeft; quadPos[ 3 ].texCoord.t =texTop;
		quadPos[ 2 ].texCoord.s =texRight; quadPos[ 2 ].texCoord.t =texTop; 		
		quadPos[ 1 ].texCoord.s =texRight; quadPos[ 1 ].texCoord.t =   texBottom;		
		quadPos[ 0 ].texCoord.s = texLeft; quadPos[ 0 ].texCoord.t =   texBottom;
		*/
		

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
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		//Pointers
		//glEnableVertexAttribArray(0);
		mTexturePolygonProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		//glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,NULL);
		
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		
		//mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		//mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);

	}
}

GLuint Texture2D::initVAOf(Rect* clip,bool invert)
{

		GLuint fVAO=0;
		GLuint vbo;
		GLuint ibo;
		/*
		GLfloat texLeft = 0.f;
		GLfloat texRight = (float)mImgWidth/(float)mTextureWidth;
		GLfloat texTop = 0.f;
		GLfloat texBottom = (float)mImgHeight/(float)mTextureHeight;
		*/
		GLfloat texLeft = 0.f;
		GLfloat texRight = (float)mImgWidth/(float)mTextureWidth;
		GLfloat texTop = (float)mImgHeight/(float)mTextureHeight;
		GLfloat texBottom = 0.f;


		GLfloat posLeft = -1.f*(float)mImgWidth/2.f;
		GLfloat posRight = (float)mImgWidth/2.f;
		GLfloat posTop = -1.f*(float)mImgHeight/2.f;
		GLfloat posBottom = (float)mImgHeight/2.f;
		

		if(clip != NULL)
		{
		/*	
		texLeft=clip->x/((float)mTextureWidth);
		texRight=(clip->x+clip->w)/((float)mTextureWidth);
		texTop=clip->y/((float)mTextureHeight);
		texBottom=(clip->y+clip->h)/((float)mTextureHeight);
		*/	
		texLeft=(1.f+clip->x)/((float)mTextureWidth);
		texRight=(clip->x+clip->w - 1.f)/((float)mTextureWidth);
		texTop=(1.f+clip->y+clip->h)/((float)mTextureHeight);
		texBottom=(clip->y - 1.f)/((float)mTextureHeight);
		
		posLeft = -1.f*(float)clip->w/2.f;
		posRight = (float)clip->w/2.f;
		posTop = -1.f*(float)clip->h/2.f;
		posBottom = (float)clip->h/2.f;
		}
		if(invert)
		{
			std::swap(texTop,texBottom);
		}


		//printf("Object: Sprite: l: %f, r: %f, t: %f, b %f \n",posLeft,posRight,posTop,posBottom);

		TexturedVertexPos2D quadPos[ 4 ];
		
		quadPos[ 0 ].pos.x =  posLeft; quadPos[ 0 ].pos.y = posBottom;
		quadPos[ 1 ].pos.x = posRight; quadPos[ 1 ].pos.y = posBottom;
		quadPos[ 2 ].pos.x = posRight; quadPos[ 2 ].pos.y =    posTop;
		quadPos[ 3 ].pos.x =  posLeft; quadPos[ 3 ].pos.y =    posTop; 

		quadPos[ 0 ].texCoord.s = texLeft; quadPos[ 0 ].texCoord.t =texBottom;
		quadPos[ 1 ].texCoord.s =texRight; quadPos[ 1 ].texCoord.t =texBottom; 		
		quadPos[ 2 ].texCoord.s =texRight; quadPos[ 2 ].texCoord.t =   texTop;		
		quadPos[ 3 ].texCoord.s = texLeft; quadPos[ 3 ].texCoord.t =   texTop; 

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
		mTexturePolygonProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);
				
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
			return 0;
		}

	return fVAO;
}

GLuint* Texture2D::getPixelData32()
{
	return mPixels32;
}
GLubyte* Texture2D::getPixelData8()
{
	return mPixels8;
}

GLuint Texture2D::getPixel32(GLuint x, GLuint y)
{
	return mPixels32[mTextureWidth*y + x];
}
GLubyte Texture2D::getPixel8(GLuint x, GLuint y)
{
	return mPixels8[mTextureWidth*y + x];
}

void Texture2D::setPixel32(GLuint x, GLuint y, GLuint pixel)
{
	mPixels32[mTextureWidth*y + x]=pixel;
}
void Texture2D::setPixel8(GLuint x, GLuint y, GLubyte pixel)
{
	mPixels8[mTextureWidth*y + x]=pixel;
}

//Get | Set

GLuint Texture2D::getImgHeight()
{
	return mImgHeight;
}

GLuint Texture2D::getImgWidth()
{
	return mImgWidth;
}
		/*
		//Texture coordinates
		GLfloat texTop = 0.f;
		GLfloat texBottom = 1.f;
		GLfloat texLeft = 0.f;
		GLfloat texRight = 1.f;

		GLfloat quadWidth =  (GLfloat)mTextureWidth;
		GLfloat quadHeight = (GLfloat)mTextureHeight;

		//Clip is copied
      
		if( clip != NULL )
		{
				//Texture coordinates
				texLeft = clip->x / mTextureWidth;
				texRight = ( clip->x + clip->w ) / mTextureWidth;
				texTop = clip->y / mTextureHeight;
				texBottom = ( clip->y + clip->h ) / mTextureHeight;

				//Vertex coordinates
				quadWidth = texRight - texLeft;
				quadHeight = texTop-texBottom;
		}
	

		TexturedVertexPos2D pos[4];
	
		
		//Positions
		pos[0].vertex.x = 0.0f;
		pos[0].vertex.y = 0.0f;
	
		pos[1].vertex.x = quadWidth;
		pos[1].vertex.y = 0.0f;
	
		pos[2].vertex.x = quadWidth;
		pos[2].vertex.y = quadHeight;
	
		pos[3].vertex.x = 0.0f;
		pos[3].vertex.y = quadHeight;
		
		//Texture Coordinates
		pos[ 0 ].texCoord.s =  texLeft; pos[ 0 ].texCoord.t =    texTop;
		pos[ 1 ].texCoord.s = texRight; pos[ 1 ].texCoord.t =    texTop;
		pos[ 2 ].texCoord.s = texRight; pos[ 2 ].texCoord.t = texBottom;
		pos[ 3 ].texCoord.s =  texLeft; pos[ 3 ].texCoord.t = texBottom;


		GLuint indices[4];	
	
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 3;

		glGenBuffers(1,&vbo);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glBufferData(GL_ARRAY_BUFFER,4*sizeof(TexturedVertexPos2D),&pos,GL_STATIC_DRAW);

		glGenBuffers(1,&mIBOID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,4*sizeof(GLuint),indices,GL_STATIC_DRAW);
		
		//Generate Vertex Array Object
		
		GLuint mVAOID;
		glGenVertexArrays(1,&mVAOID);
		glBindVertexArray(mVAOID);
		


		glBindBuffer(GL_ARRAY_BUFFER,vbo);

		mTexturePolygonProgram2D->enableDataPointers();

		//mTexturePolygonProgram2D->setVertexPointer(0,NULL);
				
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,vertex));
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mIBOID);
			
		glBindVertexArray(NULL);
		*/