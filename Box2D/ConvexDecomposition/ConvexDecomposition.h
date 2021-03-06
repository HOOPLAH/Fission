/*
 * Copyright (c) 2007 Erin Catto http://www.gphysics.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef CONVEX_DECOMPOSITION_H
#define CONVEX_DECOMPOSITION_H

#include "b2Polygon.h"

class ConvexDecomposition : public Test
{
public:
	ConvexDecomposition()
{

        // Ground body
        {
            b2FixtureDef sd;
			sd.shape = new b2PolygonShape;
            ((b2PolygonShape*)sd.shape)->SetAsBox(50.0f, 10.0f);
            sd.friction = 0.3f;
			
            b2BodyDef bd;
			bd.type = b2_staticBody;
            bd.position.Set(0.0f, -10.0f);
            b2Body *body = m_world->CreateBody(&bd);
			body->CreateFixture(&sd);
        }
		
		//Create non-convex vertex list (gear shape)
		const int32 nVert = 40;
		float x[nVert];
		float y[nVert];
		float rado = 2.0f;
		float radi = 1.0f;
		
		for (int i=0; i<nVert; i++){
			x[i] = sinf( 6.28f*i/(float)nVert ) * ( (i%2 == 0)?rado:radi );
			y[i] = cosf( 6.28f*i/(float)nVert ) * ( (i%2 == 0)?rado:radi );
		}
		

		{// Convex decomposition test - gear shape
			//Create prototype polydef
			b2FixtureDef polyprot;
			polyprot.density = 1.0f;
			polyprot.friction = 0.3f;
			polyprot.restitution = 0.2f;
		
			b2Polygon pgon(x,y,nVert);
		
			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			bd.angle = 0.0f;
			for (int32 i=0; i<5; ++i) {
				bd.position.Set(0.0f, i*5.0f+5.0f);
				b2Body *body = m_world->CreateBody(&bd);
				b2FixtureDef* deleteMe = DecomposeConvexAndAddTo(&pgon, body, &polyprot);
				delete[] deleteMe;
			}
		}
		
		// Convex hull
		{
			//Create prototype polydef
			b2FixtureDef polyprot;
			polyprot.density = 1.0f;
			polyprot.friction = 0.3f;
			polyprot.restitution = 0.2f;
			
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.angle = 0.0f;
			
			b2Polygon convexHull = ConvexHull(x,y,nVert);

			// Even though the polygon is now convex, we can feed it into the
			// convex decomposition just to make sure it doesn't have too many
			// vertices
			for (int32 i=0; i<5; ++i) {
				bd.position.Set(5.0f, i*5.0f+5.0f);
				b2Body *body = m_world->CreateBody(&bd);
				b2FixtureDef* deleteMe = DecomposeConvexAndAddTo(&convexHull, body, &polyprot);
				delete[] deleteMe;
			}
		}

		{
		// Another convex decomposition - 'E' shape
			//float32 x1[] = { 0.0f, 10.0f, 10.0f, 2.0f, 2.0f, 7.0f, 7.0f, 2.0f, 2.0f, 10.0f, 10.0f, 0.0f };
			//float32 y1[] = { 0.0f, 0.0f,  2.0f,  2.0f, 5.0f, 5.0f, 7.0f, 7.0f, 10.0f, 10.0f, 12.0f, 12.0f };
/*			for (int i=0; i<12; ++i) {
				x1[i] -= 5.0f;
				y1[i] -= 6.0f;
				x1[i] *= .3f;
				y1[i] *= .3f;
			}
//*/
			//*
			float32 x1[] = {-281.395f, -242.967f, -195.818f, -142.336f,
							-110.72f, -64.2768f, -4.57442f, 48.9422f,
							93.0067f, 180.814f, 236.762f, 264.98f,
							272.277f, 262.918f, 224.683f, 178.101f,
							114.358f, 89.0376f, 53.3651f, -0.116635f,
							-45.2516f, -92.5334f, -117.159f, -146.302f,
							-188.774f, -236.76f, -272.267f};
			float32 y1[] = {14.676f, 26.0122f, 33.3497f, 34.6758f,
							32.9536f, 41.9926f, 67.7013f, 83.3058f,
							101.334f, 122.954f, 129.058f, 122.49f,
							108.92f, 93.9747f, 87.6079f, 103.261f,
							55.9573f, 48.7228f, 58.7557f, 44.8463f,
							21.5937f, -8.90518f, -9.14116f, 4.24852f,
							7.52196f, -12.0526f, -14.1282f};//*/
			/*float32 x1[] = {-100.0f, 0.0f, 100.0f};
			float32 y1[] = {0.0f, 5.0f, 0.0f};*/
			int32 thisN = 27;
			float32 buffx[27];
			float32 buffy[27];
			for (int i=0; i<thisN; ++i) {
				x1[i] *= .03f;
				y1[i] *= .03f;
				buffx[i] = x1[i];
				buffy[i] = y1[i];
			}
			int32 shiftBy = 0;
			for (int i=0; i<thisN; ++i) {
				x1[i] = buffx[ remainder(i+shiftBy,thisN) ];
				y1[i] = buffy[ remainder(i+shiftBy,thisN) ];
			}
			b2FixtureDef polyprot;
			polyprot.density = 1.0f;
			polyprot.friction = 0.3f;
			polyprot.restitution = 0.2f;
			
			b2Polygon pgon(x1,y1,thisN);
			
			b2BodyDef bd;
			bd.bullet = true;
			bd.type = b2_dynamicBody;

			for (int32 i=0; i<2; ++i) {
				bd.position.Set(-5.0f, i*5.0f+5.0f);
				b2Body *body = m_world->CreateBody(&bd);
				b2FixtureDef* deleteMe = DecomposeConvexAndAddTo(&pgon, body, &polyprot);
				delete[] deleteMe;
			}

			//Reversed version of same
			ReversePolygon(x1,y1,thisN);
			b2Polygon pgon2(x1,y1,thisN);
			b2BodyDef bd2;
			bd2.type = b2_dynamicBody;
			bd2.bullet = true;
			for (int32 i=0; i<3; ++i){
				bd2.position.Set(-5.0f, i*5.0f+15.0f);
				b2Body *body = m_world->CreateBody(&bd2);
				b2FixtureDef* deleteMe = DecomposeConvexAndAddTo(&pgon, body, &polyprot);
				delete[] deleteMe;
			}

			//Non-simple (self intersecting) polygon - star, specified by 5 vertices
			float32 x3[5];
			float32 y3[5];
			float32 starSize = 2.0f;
			float32 ang = 0.0f;
			for (int32 i=0; i<5; i++){
				x3[i] = sinf( ang ) * starSize;
				y3[i] = cosf( ang ) * starSize;
				ang += 2.0f*3.14f * 2.0f / 5.0f;
			}
			b2Polygon pgon3(x3,y3,5);
			b2BodyDef bd3;
			bd3.type = b2_dynamicBody;
			b2Polygon fixedPgon = TraceEdge(&pgon3);
			for (int32 i=0; i<5; ++i){
				bd3.position.Set(10.0f,i*5.0f+5.0f);
				b2Body *body = m_world->CreateBody(&bd3);
				b2FixtureDef* deleteMe = DecomposeConvexAndAddTo(&fixedPgon, body, &polyprot);
				delete[] deleteMe;
			}

			//Another, now with pinch points
			float32 x4[] = {-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f,0.0f};
			float32 y4[] = {-1.0f, -1.0f,0.0f, 0.0f, 1.0f, 1.0f, 3.0f};
			b2Polygon pgon4(x4,y4,7);
			b2BodyDef bd4;
			bd4.type = b2_dynamicBody;
			fixedPgon.Set(TraceEdge(&pgon4));
			for (int32 i=0; i<5; ++i){
				bd4.position.Set(-10.0f+5.0f*i,30.0f);
				b2Body *body = m_world->CreateBody(&bd4);
				b2FixtureDef* deleteMe = DecomposeConvexAndAddTo(&fixedPgon, body, &polyprot);
				delete[] deleteMe;
			}

			//Randomized for trace edge stress testing
			/*int32 nRand = 30;
			float32* x5 = new float32[nRand];
			float32* y5 = new float32[nRand];

			for (int32 i=0; i<1; ++i){
				for (int32 j=0; j<nRand; ++j){
					x5[j] = b2Random(-6.0f,6.0f);
					y5[j] = b2Random(-6.0f,6.0f);
					if (j%4 == 2) {x5[j] = 0.0f;y5[j] = 0.0f;}
					
				}
				b2Polygon pgon5(x5,y5,nRand);
				b2BodyDef bd5;
				bd5.type = b2_dynamicBody;
				fixedPgon.Set(TraceEdge(&pgon5));
				deleteMe = DecomposeConvexAndAddTo(&fixedPgon,&bd5,&polyprot);
				bd5.position.Set(-10.0f+5.0f*i,39.0f);
				m_world->CreateBody(&bd5);
				delete[] deleteMe;
			}
			delete[] x5;
			delete[] y5;*/

		}
		
}

~ConvexDecomposition()
{
}

static Test* Create()
{
	return new ConvexDecomposition;
}
};

#endif