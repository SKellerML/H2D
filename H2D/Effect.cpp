#include "Effect.h"


Effect::Effect(void)
{
	active=false;
	particleEmitter=NULL;
	containsAnimation = false;
}


Effect::~Effect(void)
{
	if(particleEmitter!=NULL)	delete particleEmitter;
	ParticleEmitter* particleEmitter=NULL;
	active=false;
	containsAnimation = false;
}

void Effect::loadEffect(GLuint effectType, b2Body* parentBody, b2Vec2 offset)
{
	loadEffect(effectType, parentBody->GetPosition(), parentBody->GetLinearVelocity(),offset, parentBody->GetWorldVector(b2Vec2(1.f, 1.f)));

	//m_effectPosition=parentBody->GetPosition();


	//switch(effectType)
	//{
	//case EFFECT_EXPLOSION_SMALL:
	//	{
	//		animation.loadAnimation(ANIMATION_EXPLOSION_1);
	//		m_effectDuration=0.25f;//animation.getAnimationDurationInFrames()/TICKS_PER_SECOND;
	//		m_animationSpeed=m_effectDuration/((float)animation.getAnimationDurationInFrames()/TICKS_PER_SECOND);
	//		m_effectDuration=1.f;
	//		ComplexPlainParticleEmitter* particleEm = new ComplexPlainParticleEmitter();
	//		particleEm->createEmitter(m_effectPosition,parentBody->GetLinearVelocity(),50,m_effectDuration,5.f,b2Vec2(2.f,2.f),true,true,false);
	//		particleEmitter = particleEm;
	//	}
	//	break;
	////case EFFECT_ENGINES_SMALL:
	////	{
	////		animation.loadAnimation(ANIMATION_EXPLOSION_1);
	////		m_effectDuration=animation.getAnimationDurationInFrames()/TICKS_PER_SECOND;
	////		m_animationSpeed=m_effectDuration/((float)animation.getAnimationDurationInFrames()/TICKS_PER_SECOND);
	////		SimpleParticleEmitter* particleEm = new SimpleParticleEmitter();
	////		particleEm->createEmitter(m_effectPosition,parentBody->GetLinearVelocity(),50,5.f,5.f,true,true,parentBody->GetWorldVector(b2Vec2(0.f,-1.f)));
	////		particleEmitter = particleEm;
	////	}
	////	break;
	//}
	//m_effectVelocity=parentBody->GetLinearVelocity();
	////m_effectVelocity*=50.f;
	//m_effectVelocity*=(1.f/(TICKS_PER_SECOND*2));

	//m_effectPosition-=m_effectVelocity;	


	//effectTimer.start();

	//active=true;
	//wasRendering=true;
}
void Effect::loadEffect(GLuint effectType, b2Vec2 emitterPosition, b2Vec2 emitterVelocity, b2Vec2 offset, b2Vec2 direction)
{
	resetEffect();

	m_effectPosition = emitterPosition;

	

	switch (effectType)
	{
	case EFFECT_EXPLOSION_SMALL:
	{
								   animation.loadAnimation(ANIMATION_EXPLOSION_1);
								   containsAnimation = true;
								   m_effectDuration = 0.25f;//animation.getAnimationDurationInFrames()/TICKS_PER_SECOND;
								   m_animationSpeed = m_effectDuration / ((float)animation.getAnimationDurationInFrames() / TICKS_PER_SECOND);
								   m_effectDuration = 1.f;
								   ComplexPlainParticleEmitter* particleEm = new ComplexPlainParticleEmitter();
								   particleEm->createEmitter(m_effectPosition, emitterVelocity, 50, m_effectDuration, 5.f, b2Vec2(2.f, 2.f), true, true, false,b2Vec2(0.f,0.f) );
								   particleEmitter = particleEm;
	}
		break;
	case EFFECT_GAUSS_DISCHARGE:{
									
									m_effectDuration = 0.5f;//animation.getAnimationDurationInFrames()/TICKS_PER_SECOND;
									//m_animationSpeed = m_effectDuration / ((float)animation.getAnimationDurationInFrames() / TICKS_PER_SECOND);
									m_effectDuration = 2.f;
									ComplexPlainParticleEmitter* particleEm = new ComplexPlainParticleEmitter();
									direction.x *= 0.1f;
									direction.y *= 1.5f;
									particleEm->createEmitter(m_effectPosition, emitterVelocity, 50, m_effectDuration, .25f, b2Vec2(4.f, 4.f), false,true, false, direction);
									particleEmitter = particleEm;
									particleEmitter->setParticleColor(Color4f(0.1f, 0.1f, 0.7f, 0.7f), Color4f(0.1f, 0.1f, 0.7f, 0.0f));
	}
		break;
	case EFFECT_EXPLOSION_BIG:
	{
								   animation.loadAnimation(ANIMATION_EXPLOSION_1);
								   containsAnimation = true;
								   m_effectDuration = 0.25f;//animation.getAnimationDurationInFrames()/TICKS_PER_SECOND;
								   m_animationSpeed = m_effectDuration / ((float)animation.getAnimationDurationInFrames() / TICKS_PER_SECOND);
								   m_effectDuration = 1.f;
								   ComplexPlainParticleEmitter* particleEm = new ComplexPlainParticleEmitter();
								   particleEm->createEmitter(m_effectPosition, emitterVelocity, 100, m_effectDuration, 5.f, b2Vec2(15.f, 15.f), true, true, false, b2Vec2(0.f, 0.f));
								   particleEm->setParticleColor(Color4f(1.f, 1.f, 0.33f, 0.6f), Color4f(1.f, 0.33f, 0.33f, 0.6f));
								   particleEmitter = particleEm;
	}
		break;
		//case EFFECT_ENGINES_SMALL:
		//	{
		//		animation.loadAnimation(ANIMATION_EXPLOSION_1);
		//		m_effectDuration=animation.getAnimationDurationInFrames()/TICKS_PER_SECOND;
		//		m_animationSpeed=m_effectDuration/((float)animation.getAnimationDurationInFrames()/TICKS_PER_SECOND);
		//		SimpleParticleEmitter* particleEm = new SimpleParticleEmitter();
		//		particleEm->createEmitter(m_effectPosition,parentBody->GetLinearVelocity(),50,5.f,5.f,true,true,parentBody->GetWorldVector(b2Vec2(0.f,-1.f)));
		//		particleEmitter = particleEm;
		//	}
		//	break;
	}
	m_effectVelocity = emitterVelocity;
	//m_effectVelocity*=50.f;
	m_effectVelocity *= (1.f / (TICKS_PER_SECOND * 2));

	m_effectPosition -= m_effectVelocity;


	effectTimer.start();

	active = true;
	wasRendering = true;
}
void Effect::resetEffect()
{
	if (particleEmitter != NULL)
	{
		particleEmitter->deleteEmitter();	
		particleEmitter = NULL;
	}
	active = false;
}


void Effect::updateEffect(bool render)
{
	if(!active) return;
		if(render)
		{
			if(!wasRendering)
			{
				animation.resetAnimation();
				//if(particleEmitter != NULL) particleEmitter->update();
				wasRendering=true;
			}
			else
			{
				animation.updateAnimation(m_animationSpeed, true);
				if(particleEmitter != NULL) particleEmitter->update();

				m_effectPosition+=m_effectVelocity;

				if(effectTimer.hasPassed(m_effectDuration))
				{
					active=false;
				}
			}
		}
		else if(wasRendering)
		{
			wasRendering=false;
			particleEmitter->deleteEmitter();
		}
}
void Effect::renderEffect(b2Vec2 renderPos, GLfloat angle, b2Vec2 rotationOffset)
{
	if(!active)	return;
		if(wasRendering)
		{
			b2Vec2 rp=m_effectPosition;
			rp*=100;
			rp+=BaseObject::getWorldPos();

			//printf("But Y: %f \n",m_animationSpeed);
			animation.renderAnimation(rp);	// Rotation?
			if (particleEmitter != NULL) particleEmitter->renderParticles(renderPos,angle,rotationOffset);
		}
}

/*
	Stationary Effect																																				   StationaryEffect
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

StationaryEffect::StationaryEffect(void)
{
	active=false;
	particleEmitter=NULL;
}


StationaryEffect::~StationaryEffect(void)
{
	ParticleEmitter* particleEmitter=NULL;
	active=false;
}

void StationaryEffect::loadEffect(GLuint effectType, b2Body* parentBody, b2Vec2 offset)
{
	loadEffect(effectType, parentBody->GetPosition(), parentBody->GetLinearVelocity(), offset, parentBody->GetWorldVector(b2Vec2(1.f, 1.f)));

	//m_effectPosition=parentBody->GetPosition();
	//m_emitterOffset = offset;

	//switch(effectType)
	//{
	//case EFFECT_STATIONARY_ENGINES_SMALL:
	//	{
	//		//animation.loadAnimation(ANIMATION_EXPLOSION_1);
	//		
	//		m_animationSpeed=0.5f;//(float)(((float)animation.getAnimationDurationInFrames()/TICKS_PER_SECOND)/m_effectDuration);
	//		std::shared_ptr<ComplexPlainParticleEmitter> particleEm(new ComplexPlainParticleEmitter());
	//		m_particleDirectionAA=b2Vec2(0.f,-1.f);
	//		
	//		particleEm->createEmitter(m_effectPosition+offset,parentBody->GetLinearVelocity(),100,1.f,1.f,b2Vec2(8.f,8.f),false,true,true,parentBody->GetWorldVector(b2Vec2(0.f,-1.f)));
	//		particleEmitter = particleEm;
	//		//particleEmitter->setParticleColor(Color4f(1.f,0.f,0.f,1.f),Color4f(0.f,0.f,1.f,1.f));
	//		particleEmitter->setParticleColor(Color4f(0.f, 1.f, 0.f, 1.f), Color4f(1.f, 1.f, 0.33f, 1.f));
	//	}
	//	break;
	//}
	////printf("Speed: %f ||%f \n",m_animationSpeed,m_effectDuration);

	//active=true;
	//wasRendering=true;
}


void StationaryEffect::loadEffect(GLuint effectType, b2Vec2 emitterPosition, b2Vec2 emitterVelocity, b2Vec2 offset, b2Vec2 direction)
{
	m_effectPosition = emitterPosition;
	m_emitterOffset = offset;

	switch (effectType)
	{
	case EFFECT_STATIONARY_ENGINES_SMALL:
	{
											//animation.loadAnimation(ANIMATION_EXPLOSION_1);

											m_animationSpeed = 0.5f;//(float)(((float)animation.getAnimationDurationInFrames()/TICKS_PER_SECOND)/m_effectDuration);
											std::shared_ptr<ComplexPlainParticleEmitter> particleEm(new ComplexPlainParticleEmitter());
											m_particleDirectionAA = b2Vec2(0.f, -1.f);

											particleEm->createEmitter(m_effectPosition + offset, emitterVelocity, 100, 1.f, 1.f, b2Vec2(8.f, 8.f), false, true, true, direction);
											particleEmitter = particleEm;
											//particleEmitter->setParticleColor(Color4f(1.f,0.f,0.f,1.f),Color4f(0.f,0.f,1.f,1.f));
											particleEmitter->setParticleColor(Color4f(0.f, 1.f, 0.f, 1.f), Color4f(1.f, 1.f, 0.33f, 1.f));
	}
		break;
	}
	//printf("Speed: %f ||%f \n",m_animationSpeed,m_effectDuration);

	active = true;
	wasRendering = true;
}

void StationaryEffect::updateEffect(bool emitting, b2Body* body, GLfloat emittedParticleModifier)
{
	if(!active) return;

	if(!wasRendering)	// Started Rendering?
	{
		animation.resetAnimation();
		if(particleEmitter != NULL) particleEmitter->update();
		wasRendering=true;
	}
	else	// Ongoing rendering?
	{
		animation.updateAnimation(/*m_animationSpeed*/m_animationSpeed,true);
		if(particleEmitter != NULL)
		{
			m_effectPosition=body->GetPosition();
			particleEmitter->setPosition(body, m_emitterOffset, body->GetWorldVector(m_particleDirectionAA));
			particleEmitter->setEmittingData(emitting, emittedParticleModifier);
			particleEmitter->update();
		}
	}

}

void StationaryEffect::renderEffect(b2Vec2 renderPos, GLfloat angle, b2Vec2 rotationOffset)
{
	if(!active)	return;

			b2Vec2 rp=m_effectPosition;
			rp*=100;
			rp+=BaseObject::getWorldPos();
			
			animation.renderAnimation(rp);	// Rotation?
			if (particleEmitter != NULL) particleEmitter->renderParticles(renderPos, angle, rotationOffset);
		
}
