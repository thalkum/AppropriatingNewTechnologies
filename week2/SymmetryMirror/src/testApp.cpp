#include "testApp.h"

using namespace ofxCv;


void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	tracker.setup();
	//pigface.loadImage("pigface.png");
	faceFbo.allocate(512,512, GL_RGBA);
	ofEnableAlphaBlending();
	inRightState = true;
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), 10, 20);
	
	if(tracker.getFound()) {
		//tracker.draw();
		ofMesh objectMesh = tracker.getObjectMesh();
		ofMesh imageMesh = tracker.getImageMesh();
		ofMesh meanMesh = tracker.getMeanObjectMesh();


		
		faceFbo.begin();
			ofClear(0, 0);
			cam.getTextureReference().bind();
			ofSetupScreenOrtho(640, 480, OF_ORIENTATION_DEFAULT, false, -1000, 1000);
			ofTranslate(256, 256);
			ofScale(8,8);
			//ofRotate(3, 0, 0, 0);
			meanMesh.draw();
			cam.getTextureReference().unbind();
		faceFbo.end();
		//faceFbo.clear();
		
		//draw a second time using FBO as image object
		if (inRightState) {
		faceFbo.begin();
			faceFbo.getTextureReference().bind();
			ofMesh mesh;
			//draw vertex coords for right side and tex coords for left side (but flipped)
			mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
				mesh.addVertex(ofVec2f(256, 0));
				mesh.addVertex(ofVec2f(512, 0));	
				mesh.addVertex(ofVec2f(512, 512));				
				mesh.addVertex(ofVec2f(256, 512));
		
				mesh.addTexCoord(ofVec2f(256,0));
				mesh.addTexCoord(ofVec2f(0,0));
				mesh.addTexCoord(ofVec2f(0,512));
				mesh.addTexCoord(ofVec2f(256,512));
		
			mesh.draw();
			faceFbo.getTextureReference().unbind();
		faceFbo.end();
		} else {
			faceFbo.begin();
			faceFbo.getTextureReference().bind();
			ofMesh mesh;
			//draw vertex coords for right side and tex coords for left side (but flipped)
			mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
			mesh.addVertex(ofVec2f(256, 0));
			mesh.addVertex(ofVec2f(0,0));	
			mesh.addVertex(ofVec2f(0,512));				
			mesh.addVertex(ofVec2f(256, 512));
			
			mesh.addTexCoord(ofVec2f(256,0));
			mesh.addTexCoord(ofVec2f(512, 0));
			mesh.addTexCoord(ofVec2f(512, 512));
			mesh.addTexCoord(ofVec2f(256,512));
			
			mesh.draw();
			faceFbo.getTextureReference().unbind();
			faceFbo.end();
		}
		
		ofMesh combo;
		combo = imageMesh;
		//now step through tracker vertices, and make a combo mesh that takes the meshVertex of the cam and the texCoords of the meanObjectMesh
		for (int i = 0; i < tracker.size(); i++) {
			
		
			ofVec2f cur = meanMesh.getVertex(i);
			//cur.rotate(3);
			cur*=ofVec2f (8,8);
			cur+=ofVec2f (256, 256);
			combo.setTexCoord(i, cur);
			
	
		}
							
							
		
		faceFbo.getTextureReference().bind();
		combo.draw();
		faceFbo.getTextureReference().unbind();
		
				

		
		//ofSetupScreenOrtho(640, 480, OF_ORIENTATION_DEFAULT, true, -1000, 1000);
		
		//ofTranslate(100, 100);
		//ofScale(5,5,5);

		//ofRect(silhouette.getBoundingBox());
		//faceFbo.draw(0, 0);
		
		//cam.getTextureReference().bind();
		
		//pigface.getTextureReference().bind();
		//imageMesh.draw();
		//objectMesh.draw();
		//cam.getTextureReference().unbind();
		//pigface.getTextureReference().unbind();
	}
}

void testApp::keyPressed(int key) {
	if(key == 'r') {
		//tracker.reset();
		inRightState = true;
	} else if (key == 'l') {
		inRightState = false;
	}
	
}

