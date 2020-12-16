#include "Font2D.h"
#include "VertexPos2D.h"
#include "Engine.h"
#include <glm\gtx\transform.hpp>

#include <iostream>
//#include FT_BITMAP_H
//#include FT_GLYPH_H

FontProgram2D* Font2D::mFontProgram2D=NULL;
//FT_Library Font2D::mLibrary;

void Font2D::setFontProgram2D(FontProgram2D* program)
{
	mFontProgram2D = program;
}
/*
bool Font2D::initFreeType()
{
#ifndef __FREEGLUT_H__
	FT_Error error = FT_Init_FreeType(&mLibrary);
	if(error)
	{
		printf("FreeType error:%x",error);
		return false;
	}
#endif
	return true;
}
*/
Font2D::Font2D(void)
{
}


Font2D::~Font2D(void)
{
}

bool Font2D::loadBitmap( std::string path )
{
 //Loading flag
    bool success = true;

    //Background pixel
    const GLubyte BLACK_PIXEL = 0x00;

	//Image pixels loaded
    if( loadPixelsFromFile8( path ) )
    {
		//Get cell dimensions
		GLfloat cellW = mImgWidth / 16.f;
		GLfloat cellH = mImgHeight / 16.f;

		//Get letter top and bottom
		GLuint top = (GLuint)cellH;
		GLuint bottom = 0;
		GLuint aBottom = 0;

        //Current pixel coordinates
        int pX = 0;
        int pY = 0;

        //Base cell offsets
        int bX = 0;
        int bY = 0;

        //Begin parsing bitmap font
		GLuint currentChar = 0;
		Rect nextClip( 0.f, 0.f, cellW, cellH);

		//Go through cell rows
		for( unsigned int rows = 0; rows < 16; ++rows )
		{
		    //Go through each cell column in the row
			for( unsigned int cols = 0; cols < 16; ++cols )
			{
			    //Begin cell parsing

				//Set base offsets
				bX = (int)(cellW * cols);
				bY = (int)(cellH * rows);

				//Initialize clip
				nextClip.x = cellW * cols;
				nextClip.y = cellH * rows;

				nextClip.w = cellW;
				nextClip.h = cellH;

				//Find left side of character
				for( int pCol = 0; pCol < cellW; ++pCol )
				{
					for( int pRow = 0; pRow < cellH; ++pRow )
					{
					    //Set pixel offset
						pX = bX + pCol;
						pY = bY + pRow;

                        //Non-background pixel found
						if( getPixel8( pX, pY ) != BLACK_PIXEL )
						{
						    //Set sprite's x offset
							nextClip.x = (GLfloat)pX;

							//Break the loops
							pCol = (int)cellW;
							pRow = (int)cellH;
						}
					}
				}

				//Right side
				for( int pCol_w = cellW - 1; pCol_w >= 0; pCol_w-- )
				{
					for( int pRow_w = 0; pRow_w < cellH; pRow_w++ )
					{
					    //Set pixel offset
						pX = bX + pCol_w;
						pY = bY + pRow_w;

                        //Non-background pixel found
						if( getPixel8( pX, pY ) != BLACK_PIXEL )
						{
						    //Set sprite's width
							nextClip.w = ( pX - nextClip.x ) + 1;

							//Break the loops
							pCol_w = -1;
							pRow_w = cellH;
						}
					}
				}

				//Find Top
				for( int pRow = 0; pRow < cellH; ++pRow )
				{
					for( int pCol = 0; pCol < cellW; ++pCol )
					{
					    //Set pixel offset
						pX = bX + pCol;
						pY = bY + pRow;

						//Non-background pixel found
						if( getPixel8( pX, pY ) != BLACK_PIXEL )
						{
							//New Top Found
							if( pRow < top )
							{
								top = pRow;
							}

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Bottom
				for( int pRow_b = cellH - 1; pRow_b >= 0; --pRow_b )
				{
					for( int pCol_b = 0; pCol_b < cellW; ++pCol_b )
					{
					    //Set pixel offset
						pX = bX + pCol_b;
						pY = bY + pRow_b;

                        //Non-background pixel found
						if( getPixel8( pX, pY ) != BLACK_PIXEL )
						{
							//Set BaseLine
							if( currentChar == 'A' )
							{
								aBottom = pRow_b;
							}

							//New bottom Found
							if( pRow_b > bottom )
							{
								bottom = pRow_b;
							}

							//Break the loops
							pCol_b = cellW;
							pRow_b = -1;
						}
					}
				}
				//Go to the next character
				//letterVAO[rows*cols+cols]=addClipSprite( nextClip );
				//clipArray[rows*cols+cols]=nextClip;
				++currentChar;
				letterVAO[currentChar]=addClipSprite(nextClip,false);
				//printf("x: %i y: %i w: %i h: %i \n",nextClip.x,nextClip.y,nextClip.w,nextClip.h);
			}
		}

		//Set Top
		for( int t = 0; t < 256; ++t )
		{
			mClips[ t ].r.y += top;
			mClips[ t ].r.h -= top;
		}

        //Create texture from parsed pixels
        if( !loadTextureFromPixels8() )
        {
            printf( "Unable to create texture from bitmap font pixels!\n" );
            success = false;
        }

        //Set texture wrap
        glBindTexture( GL_TEXTURE_2D, getTextureID() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

        //Set spacing variables
		mSpace = cellW / 2;
		mNewLine = aBottom - top;
		mLineHeight = bottom - top;
    }
    else
    {
		printf( "Could not load bitmap font image: %s!\n", path.c_str() );
        success = false;
    }

    return success;
}

void Font2D::renderText( GLfloat x, GLfloat y, std::string text, int size)
{
	Engine::fontProgram.bind();

		//float s = 1.f/mLineHeight*size;
        //float s = size/mLineHeight*1.2;
		//float s=size;
		float s=size/mLineHeight;
		//Draw positions
        GLfloat dX = x;
        GLfloat dY = y;

	      glBindTexture(GL_TEXTURE_2D,mTextureID);
		
            //Go through string
            for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
				{
                    dX += mSpace*s/2;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
                    //Handle horizontal alignment
                    GLfloat targetX = x;

                    dY -= mNewLine*s;
                    //dX = targetX*s;// - dX;
					dX=x;
                }
                //Character
                else
                {
                    //Get ASCII
                    GLuint ascii = (unsigned char)text[ i ];

					drawFontSprite(text[i],dX,dY,s,s);
					//mFontProgram2D->drawVAO(mTextureID,text[i],dX,dY);
					dX += (mClips[ ascii ].r.w+5.f)*s;
                }
			}
}

void Font2D::renderText( GLfloat x, GLfloat y, std::string text, Rect *clip,int lines)
{
		//float s = 1.f/mLineHeight*size;

		Engine::fontProgram.bind();

		float size=clip->h/lines;//aviable Pixel per line

        float s = size/mLineHeight*1.2;

        GLfloat dX = x;
        GLfloat dY = y;



        glBindTexture(GL_TEXTURE_2D,mTextureID);
		
            //Go through string
            for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
				{
                    dX += mSpace*s/2;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
                    //Handle horizontal alignment
                    GLfloat targetX = x;

                    dY += mNewLine*s;
                    //dX = targetX*s;// - dX;
					dX=x;
				}
                //Character
                else
                {
                    //Get ASCII
                    GLuint ascii = (unsigned char)text[ i ];
					std::cout << "The Ascii Code: " << ascii << std::endl;
					std::cout << "The Length: " << mClips.size() << std::endl;
					drawFontSprite(text[i],dX,dY,s,s);
					//mFontProgram2D->drawVAO(mTextureID,text[i],dX,dY);
					dX += (mClips[ ascii ].r.w+5.f)*s;
                }
			}
}

void Font2D::setTextColor(float r,float g,float b,float a)
{
	Engine::fontProgram.bind();
	Engine::fontProgram.setTextColor(r,g,b,a);
}

void Font2D::setTextColor(Color4f col)
{
	Engine::fontProgram.bind();
	Engine::fontProgram.setTextColor(col);
}

void Font2D::drawFontSprite(GLuint fVAO,GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat rz,GLfloat rPointX,GLfloat rPointY)
{
	if(mTextureID!=0)
	{
		Engine::fontProgram.bind();

		Engine::fontProgram.setModelViewMatrix(glm::translate<GLfloat>(glm::vec3(x,y,0.f)));
		Engine::fontProgram.leftMultModelView(glm::scale<GLfloat>(glm::vec3(sx,sy,1.f)));
		Engine::fontProgram.leftMultModelView(glm::rotate<GLfloat>(rz, glm::vec3(0.f,0.f,1.f)));
		Engine::fontProgram.leftMultModelView(glm::translate<GLfloat>(glm::vec3(-rPointX,-rPointY,0.f)));

		Engine::fontProgram.updateModelViewMatrix();
		
		glBindTexture(GL_TEXTURE_2D,mTextureID);

		glBindVertexArray( mClips[fVAO].fVAO ); 
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
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

RectSize Font2D::getTextDimensions(std::string text)
{
	float s = 20/mLineHeight*1.2;

	RectSize size;
	//Länge des Strings berechnen
	GLfloat length=0.f;
	size.h=mLineHeight*s;
	size.w=0.f;
	        //Go through string
            for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
				{
					length+=mSpace*s/2;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
					if(length > size.w)
					{
						size.w=length;
					}
					size.h+=mLineHeight*s;
					length=0;
                }
                //Character
                else
                {
                    //Get ASCII
					//GLuint ascii = (unsigned char)text[ i ];
					length+=(mClips[ (unsigned char)text[ i ] ].r.w+5.f)*s;
                }
			}
		return size;
}

GLfloat Font2D::getSpace()
{
	return mSpace;
}

GLfloat Font2D::getLineHeight()
{
	return mLineHeight;
}

GLfloat Font2D::getNewLineHeight()
{
	return mNewLine;
}

GLfloat Font2D::getLetterWidth(unsigned char letter)
{
	GLuint ascii = letter;
	if (mClips.size() > ascii) {
		return (mClips[ascii].r.w + 5.f);
	}
	else {
		return (mClips[0].r.w + 5.f);
	}
}

/*
	Rendertext Backup

	void Font2D::renderText( GLfloat x, GLfloat y, std::string text, int size)
{
		//float s = 1.f/mLineHeight*size;
        float s = size/mLineHeight*1.2;
		//Draw positions
        GLfloat dX = x;
        GLfloat dY = y;

        glBindTexture(GL_TEXTURE_2D,mTextureID);
		
            //Go through string
            for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
                {
					//mFontProgram2D->leftMultModelView( glm::translate<GLfloat>( glm::mat4(), glm::vec3( mSpace, 0.f, 0.f ) ) );
					
					//mFontProgram2D->updateModelViewMatrix();

                    dX += mSpace;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
                    //Handle horizontal alignment
                    GLfloat targetX = x;

                    dY += mNewLine;
                    dX = targetX;// - dX;
                }
                //Character
                else
                {
                    //Get ASCII
                    GLuint ascii = (unsigned char)text[ i ];

					renderSprite(text[i],dX,dY,s,s);
					//mFontProgram2D->drawVAO(mTextureID,text[i],dX,dY);
					dX += mClips[ ascii ].r.w+5.f;
                }
			}
}
*/



/*
bool Font2D::loadFreeType(std::string path, GLuint pixelSize)
{
	FT_Error error = NULL;

	initFreeType();

	GLuint cellW = 0;
	GLuint cellH = 0;
	int maxBearing = 0;
	int minHang = 0;

	Texture2D bitmaps[256];
	FT_Glyph_Metrics metrics[256];

    //Load face
	FT_Face face = NULL;
	error = FT_New_Face(mLibrary,path.c_str(),0,&face);
	if(!error)
	{
		error = FT_Set_Pixel_Sizes(face,0,pixelSize);
		if(!error)
		{
			for(int i = 0; i < 256; ++i)
			{
				error = FT_Load_Char(face,i,FT_LOAD_RENDER);
				if(!error)
				{
					metrics[i] = face->glyph->metrics;
					//bitmaps[ i ].copyPixels8( face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows );
			
					letter[i]=loadGlyph((GLubyte*)face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows);
					
					if(metrics[i].horiBearingY/64 > maxBearing)
					{
						maxBearing = metrics[i].horiBearingY/64;
					}
					if(metrics[i].width/64 > cellW)
					{
						cellW = metrics[i].width/64;
					}
					int glyphHang = ( metrics[ i ].horiBearingY - metrics[ i ].height ) / 64;
                    if(glyphHang < minHang)
					{
						minHang = glyphHang;
					}
				}
				else
				{
					printf("Unable to load glyph. Freetype error: %x\n",error);
					error = NULL;
				}
			}
		 mSpace = cellW / 2; 
		 mNewLine = maxBearing; 
		 mLineHeight = cellH;
		 
		
		
	}
	else
	{
		printf("Unable to load load font face. FreeType error:%X\n", error );
		return false;
	}
	}
	FT_Done_Face(face);
#ifdef __FREEGLUT_H__
	FT_Done_FreeType(mLibrary);
#endif

	return error == NULL;
}

TextureVAO Font2D::loadGlyph(GLubyte* pixels, GLuint imgWidth,GLuint imgHeight)
{
	TextureVAO tf={0,0};

	if(imgWidth > 0 && imgHeight > 0)
	{
		GLuint textureID;

		GLuint textureWidth=powerOfTwo(mImgWidth);
		GLuint textureHeight=powerOfTwo(mImgHeight);

		GLubyte* pixelS=new GLubyte[textureWidth*textureHeight];
		pixelS = padPixels8(pixels);

		glGenTextures(1,&textureID);
		glBindTexture(GL_TEXTURE_2D,textureID);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RED,imgWidth,imgHeight,0,GL_RED,GL_UNSIGNED_BYTE,pixels);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

		glBindTexture(GL_TEXTURE_2D,NULL);

		GLenum error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error loading texture from pixels! \n");
		}
		else
		{
			Rect c = {0.f,0.f,(GLfloat)mImgWidth,(GLfloat)mImgHeight};

			tf.VAO=initVAOfont(&c);
			tf.textureID=textureID;

			mPixelFormat = GL_RED;
		}
		printf("IID: %d \n",textureID);
	}
	return tf;
}

void Font2D::renderText( GLfloat x, GLfloat y, std::string text, Rect* area, int align)
{

		mTexturePolygonProgram2D->setModelViewMatrix(glm::translate<GLfloat>(x,y,0.f));

		mTexturePolygonProgram2D->updateModelViewMatrix();


		glBindTexture(GL_TEXTURE_2D,letter[55].textureID);

		glBindVertexArray(letter[55].VAO); 
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
		glBindVertexArray(NULL);
	
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error detected");
		}

}

GLfloat Font2D::getLineHeight()
{
	return mLineHeight;
}

GLfloat Font2D::substringWidth(const char* substring)
{
	GLfloat subWidth = 0.f;

	for(int i = 0; i < substring[i] != '\0' && substring[i] != '\n'; i++)
	{
		//Space
		if(substring[i] == ' ')
		{
			subWidth+=mSpace;
		}
		//Character
		else
		{
			GLuint ascii = (unsigned char) substring[i];
			subWidth += mClips[ascii].r.w;
		}
	}

	return subWidth;
}

GLfloat Font2D::stringHeight(const char* thisString)
{
	GLfloat height = mLineHeight;

	for(int i = 0; thisString[i] != '\0';++i)
	{
		if(thisString[i] == '\n')
		{
			height += mLineHeight;
		}
	}

	return height;
}

int Font2D::addFontClipSprite(Rect newClip)
{
	RectVAO n;
	n.r = newClip;
	n.fVAO = mFontProgram2D->initVAO(mTextureWidth,mTextureHeight,&newClip);
	mClips.push_back(n);
	return mClips.size()-1;
}

GLuint Font2D::initVAOfont(Rect* clip)
{

		GLuint fVAO=0;
		GLuint vbo;
		GLuint ibo;


		GLfloat texLeft = 0.f;
		GLfloat texRight = 1.f;
		GLfloat texTop = 0.f;
		GLfloat texBottom = 1.f;
		/*
		if(clip != NULL)
		{
			texLeft=clip->x/mTextureWidth;
			texRight=(clip->x+clip->w)/mTextureWidth;
			texTop=clip->y/mTextureHeight;
			texBottom=(clip->y+clip->h)/mTextureHeight;
		}
		
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
		mTexturePolygonProgram2D->enableDataPointers();
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		//VertexPointer
		mTexturePolygonProgram2D->setVertexPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,pos));
		mTexturePolygonProgram2D->setTexCoordPointer(sizeof(TexturedVertexPos2D),(GLvoid*)offsetof(TexturedVertexPos2D,texCoord));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
		glBindVertexArray(NULL);

		printf("fVAO: %d \n",fVAO);
		return fVAO;
}
*/

/*f
void Font2D::renderText( GLfloat x, GLfloat y, std::string text, Rect* area, int align )
{
    //If there is a texture to render from
    if( getTextureID() != 0 )
    {
        //Draw positions
        GLfloat dX = x;
        GLfloat dY = y;

        //If the text needs to be aligned
        if( area != NULL )
        {
            //Correct empty alignment
            if( align == 0 )
            {
                align = LFONT_TEXT_ALIGN_LEFT | LFONT_TEXT_ALIGN_TOP;
            }

            //Handle horizontal alignment
            if( align & LFONT_TEXT_ALIGN_LEFT )
            {
                dX = area->x;
            }
            else if( align & LFONT_TEXT_ALIGN_CENTERED_H )
            {
                dX = area->x + ( area->w - substringWidth( text.c_str() ) ) / 2.f;
            }
            else if( align & LFONT_TEXT_ALIGN_RIGHT )
            {
                dX = area->x + ( area->w - substringWidth( text.c_str() ) );
            }

            //Handle vertical alignment
            if( align & LFONT_TEXT_ALIGN_TOP )
            {
                dY = area->y;
            }
            else if( align & LFONT_TEXT_ALIGN_CENTERED_V )
            {
                dY = area->y + ( area->h - stringHeight( text.c_str() ) ) / 2.f;
            }
            else if( align & LFONT_TEXT_ALIGN_BOTTOM )
            {
                dY = area->y + ( area->h - stringHeight( text.c_str() ) );
            }
        }

        //Move to draw position
		mFontProgram2D->leftMultModelView( glm::translate<GLfloat>( glm::mat4(), glm::vec3( dX, dY, 0.f ) ) );

        //Set texture
        glBindTexture( GL_TEXTURE_2D, getTextureID() );

        //Enable vertex and texture coordinate arrays
		mFontProgram2D->enableVertexPointer();
		mFontProgram2D->enableTexCoordPointer();

        //Bind vertex data
        glBindBuffer( GL_ARRAY_BUFFER, mVertexDataBuffer );

        //Set texture coordinate data
		mFontProgram2D->setTexCoordPointer( sizeof(LTexturedVertex2D), (GLvoid*)offsetof( LTexturedVertex2D, texCoord ) );

        //Set vertex data
		mFontProgram2D->setVertexPointer( sizeof(LTexturedVertex2D), (GLvoid*)offsetof( LTexturedVertex2D, position ) );

            //Go through string
            for( int i = 0; i < text.length(); ++i )
            {
                //Space
                if( text[ i ] == ' ' )
                {
					mFontProgram2D->leftMultModelView( glm::translate<GLfloat>( glm::mat4(), glm::vec3( mSpace, 0.f, 0.f ) ) );
					mFontProgram2D->updateModelView();

                    dX += mSpace;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
                    //Handle horizontal alignment
                    GLfloat targetX = x;
                    if( area != NULL )
                    {
                        if( align & LFONT_TEXT_ALIGN_LEFT )
                        {
                            targetX = area->x;
                        }
                        else if( align & LFONT_TEXT_ALIGN_CENTERED_H )
                        {
                            targetX = area->x + ( area->w - substringWidth( &text.c_str()[ i + 1 ] ) ) / 2.f;
                        }
                        else if( align & LFONT_TEXT_ALIGN_RIGHT )
                        {
                            targetX = area->x + ( area->w - substringWidth( &text.c_str()[ i + 1 ] ) );
                        }
                    }

                    //Move to target point
					mFontProgram2D->leftMultModelView( glm::translate<GLfloat>( glm::mat4(), glm::vec3( targetX - dX, mNewLine, 0.f ) ) );
					mFontProgram2D->updateModelView();

                    dY += mNewLine;
                    dX += targetX - dX;
                }
                //Character
                else
                {
                    //Get ASCII
                    GLuint ascii = (unsigned char)text[ i ];

					//Update position matrix in program
					mFontProgram2D->updateModelView();

                    //Draw quad using vertex data and index data
                    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[ ascii ] );
                    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

                    //Move over
					mFontProgram2D->leftMultModelView( glm::translate<GLfloat>( glm::mat4(), glm::vec3( mClips[ ascii ].w, 0.f, 0.f ) ) );
					mFontProgram2D->updateModelView();
					dX += mClips[ ascii ].w;
                }
            }

        //Disable vertex and texture coordinate arrays
		mFontProgram2D->disableVertexPointer();
		mFontProgram2D->disableTexCoordPointer();
    }
}
*/