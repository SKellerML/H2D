#include "FontObject.h"

Font2D *FontObject::font;

void FontObject::setFont2D(Font2D *f)
{
	font=f;
}

FontObject::FontObject(void)
{
	fontSize=0;
	posX=0.f;
	posY=0.f;
	length=0.f;
	height=0.f;
}


FontObject::~FontObject(void)
{
}

GLshort FontObject::initFitToRect(std::string t,Rect size,GLfloat padding,GLuint alignmentH,GLuint alignmentV,GLshort maxFontSize)
{
	if(length==0.f)
	{

		position=size;
		pad=padding;
		alignH=alignmentH;
		alignV=alignmentV;
		maxSize=maxFontSize;


		text=t;	
		height=font->getNewLineHeight();
		//Calculate Width
        GLfloat currentLength = 0.f;
		//GLfloat currentWord=0.f; // Für Zeilenumbruch

            //Go through string
            for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
				{
					currentLength += font->getSpace()/2;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
					if(currentLength>length)
					{
						length=currentLength;
					}
					currentLength=0.f;
                   
					height+=font->getNewLineHeight();
                }
                //Character
                else
				{
					currentLength+=font->getLetterWidth(text[i]);
                }
			}

			if(currentLength>length)
			{
				length=currentLength;
			}

		//size/mLineHeight*1.2
		GLfloat faktor=(size.w-2*padding)/length;

		//fontSize=(font->getLineHeight()*((size.w-2*padding)/length));
		
		fontSize=font->getLineHeight()*faktor;
		//fontSize=faktor;

		// Maximum Fontsize
		if(maxFontSize != -1.f && fontSize > maxFontSize)
		{
			fontSize=maxFontSize;
			faktor=fontSize/font->getLineHeight();
		}
		if(fontSize>(size.h-padding*2))
		{
			fontSize=size.h-padding*2;
			faktor=fontSize/font->getLineHeight();
		}
		
		//Check font alignment

		switch(alignmentH)
		{
		case FONT_TEXT_ALIGNMENT_LEFT:
			posX=padding;
			break;
		case FONT_TEXT_ALIGNMENT_CENTERED_H:
			posX=-1*(size.w-length*faktor)/2.f+padding;
			break;
		case FONT_TEXT_ALIGNMENT_RIGHT:
			posX=size.w-padding;
			break;
		default:
			posX=padding;
		}

		switch(alignmentV)
		{
		case FONT_TEXT_ALIGNMENT_TOP:
			posY=padding;
			break;
		case FONT_TEXT_ALIGNMENT_CENTERED_V:
			posY=0.f;//(size.h-font->getLineHeight()*faktor)/2;
			break;
		case FONT_TEXT_ALIGNMENT_BOTTOM:
			posY=size.h-padding-font->getLineHeight();
			break;
		default:
			posY=padding;
			break;
		}

		textType=TEXT_FIT_TO_RECT;

		return fontSize;
	}
	return -1;
}

Rect FontObject::init(std::string t,GLshort fs,GLfloat padding)
{
	fontSize=fs;

	Rect size(0.f,0.f,0.f,0.f);

	position=size;
	pad=padding;
	//alignH=alignmentH;
	//alignV=alignmentV;
	maxSize=fs;

	if(length==0.f)
	{
		float s=fontSize/font->getLineHeight();
		text=t;	
		height=font->getNewLineHeight();
		//Calculate Width
        GLfloat currentLength = 0.f;
		//GLfloat currentWord=0.f; // Für Zeilenumbruch

		for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
				{
                    currentLength += font->getSpace()*s/2;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
					if(currentLength>length)
					{
						length=currentLength;
					}
					currentLength=0.f;
                   
					height+=font->getNewLineHeight()*s;
                }
                //Character
                else
                {
					currentLength+=font->getLetterWidth(text[i])*s;
                }
			}

			if(currentLength>length)
			{
				length=currentLength;
			}

		size.h=height;
		size.w=length;

		// Position (No Special Alignment Options aviable, always Upper Left)

		posX=padding;
		posY=padding;

		textType=TEXT_NORMAL;

		return size;
	}
	return size;
}

GLfloat FontObject::initWrap(std::string t,GLshort fontSize,GLfloat width,GLfloat padding,GLuint alignmentH,GLuint alignmentV)
{
	/*
	if(length==0.f)
	{
		Rect size(0.f,0.f,0.f,0.f);

		position=size;
		pad=padding;
		alignH=alignmentH;
		alignV=alignmentV;
		maxSize=fontSize;


		text=t;	
		height=font->getNewLineHeight();
		//Calculate Width
        GLfloat currentLength = 0.f;
		GLfloat currentWord=0.f; // Für Zeilenumbruch
		GLint currentWordChars;
		GLint currentChars;

            //Go through string
            for( int i = 0; i < text.length(); i++ )
            {
                //Space
                if( text[ i ] == ' ' )
				{
					currentLength += font->getSpace()/2;
					currentLength += currentWord;
					currentChars+=currentWordChars+1;
					currentWordChars=0;
                }
                //Newline
                else if( text[ i ] == '\n' )
                {
					if(currentLength>length)
					{
						length=currentLength;
					}
					currentLength=0.f;
                   
					height+=font->getNewLineHeight();

					currentChars=0;
					currentWordChars=0;

                }
                //Character
                else
				{
					currentLength+=font->getLetterWidth(text[i]);
					currentWordChars++;
                }

				if((currentLength+currentWord) >= width)
				{
					text.insert(currentChars+1,"/n");
				}

			}

			if(currentLength>length)
			{
				length=currentLength;
			}*/


		/*
		//size/mLineHeight*1.2
		GLfloat faktor=(size.w-2*padding)/length;

		//fontSize=(font->getLineHeight()*((size.w-2*padding)/length));
		
		fontSize=font->getLineHeight()*faktor;
		//fontSize=faktor;

		// Maximum Fontsize
		if(maxFontSize != -1.f && fontSize > maxFontSize)
		{
			fontSize=maxFontSize;
			faktor=fontSize/font->getLineHeight();
		}
		if(fontSize>(size.h-padding*2))
		{
			fontSize=size.h-padding*2;
			faktor=fontSize/font->getLineHeight();
		}
		*/
		//Check font alignment
			/*
		switch(alignmentH)
		{
		case FONT_TEXT_ALIGNMENT_LEFT:
			posX=padding;
			break;
		case FONT_TEXT_ALIGNMENT_CENTERED_H:
			posX=(size.w/2)-length*faktor/2+1.5f;
			break;
		case FONT_TEXT_ALIGNMENT_RIGHT:
			posX=size.w-padding;
			break;
		default:
			posX=padding;
		}

		switch(alignmentV)
		{
		case FONT_TEXT_ALIGNMENT_TOP:
			posY=padding;
			break;
		case FONT_TEXT_ALIGNMENT_CENTERED_V:
			posY=(size.h-font->getLineHeight()*faktor)/2;
			break;
		case FONT_TEXT_ALIGNMENT_BOTTOM:
			posY=size.h-padding-font->getLineHeight();
			break;
		default:
			posY=padding;
			break;
		}
		*/
		
/*textType=TEXT_WRAP;

		return fontSize;
	}
	*/
	return -1;
}

void FontObject::setTextColor(Color4f col)
{
	textColor=col;
}

void FontObject::render(GLfloat x,GLfloat y)
{
	Engine::fontProgram.bind();
	Engine::fontProgram.setTextColor(textColor);
	//font->renderText(posX+x,posY+y,text,fontSize);
	font->renderText(x+posX,y+posY,text,fontSize);
}


void FontObject::updateText(std::string t)
{
	length=0;

	switch(textType)
	{
	case TEXT_FIT_TO_RECT:
		FontObject::initFitToRect(t,position,pad,alignH,alignV,maxSize);
		break;
	case TEXT_NORMAL:
		init(t,fontSize);
		break;
	default:
		init(t,fontSize);
		break;
	}

}
std::string *FontObject::getText()
{
	return &text;
}