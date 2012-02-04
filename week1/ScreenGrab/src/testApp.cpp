#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){
	
	
	captureWidth = ofGetWidth();
    captureHeight = ofGetHeight();

	finder.setup("haarcascade_frontalface_default.xml");
	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
	//tex.allocate(300,300, GL_RGBA);
	image.allocate(captureWidth, captureHeight, OF_IMAGE_COLOR);
	//pixels.allocate(300, 300, OF_IMAGE_COLOR);
	//imageFace = image;
	
	ofSetFrameRate(30);

}

//--------------------------------------------------------------
void testApp::update(){
	
	captureWidth = ofGetWidth();
    captureHeight = ofGetHeight();
	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),captureWidth,captureHeight);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < captureWidth*captureHeight; i++){
		
		unsigned char r = data[i*4]; // mem A  
		
		data[i*4]   = data[i*4+1];   
		data[i*4+1] = data[i*4+2];   
		data[i*4+2] = data[i*4+3];   
		data[i*4+3] = r; 
	}
	
	
	if (data!= NULL) {
		//tex.loadData(data, 300, 300, GL_RGBA);
		//tex.readToPixels(pixels);
		//image = pixels;
		image.setFromPixels(data, captureWidth, captureHeight, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();
		
		//do Face Detection
		finder.findHaarObjects(image.getPixelsRef());
		
		//make sure that OpenCV can find a face

	    if (finder.blobs.size() > 0) {
			
			//then make a new image that is the width and height of the face bounding box
			imageFace.allocate(finder.blobs[0].boundingRect.width, finder.blobs[0].boundingRect.height, OF_IMAGE_COLOR);
			
			unsigned char * origPixels = image.getPixels();
			
	//cout << imageBelowWindow()[0] << endl;

	}

}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	image.draw(0,0, ofGetWidth(), ofGetHeight());
	
		
	
	ofNoFill();
	
	//for each face "blob" we found, draw a rectangle around the face
    //#2
	/*for(int i = 0; i < finder.blobs.size(); i++) {
		
		ofRect(finder.blobs[i].boundingRect);
<<<<<<< HEAD
		imageFace.rotate90(90);
		imageFace.draw(finder.blobs[0].boundingRect.x, finder.blobs[0].boundingRect.y, finder.blobs[0].boundingRect.width, finder.blobs[0].boundingRect.width);
	}
=======
	//	imageFace.draw(finder.blobs[0].boundingRect.x, finder.blobs[0].boundingRect.y, finder.blobs[0].boundingRect.width, finder.blobs[0].boundingRect.width);
	}*/
    
    if (finder.blobs.size() > 1) {
        
        //then make a new image that is the width and height of the face bounding box
        imageFace.allocate(finder.blobs[0].boundingRect.width, finder.blobs[0].boundingRect.height, OF_IMAGE_COLOR);
        

        
        unsigned char * origPixels = image.getPixels();
        //make a new data type for the new image's pixels
        unsigned char * copyPixels = imageFace.getPixels();
		
        //declare an index to keep track of the new image's pixels that are within the bounding box
        int imageFaceIndex = 0;
        
		ofRectangle box = finder.blobs[0].boundingRect;
		imageFace.cropFrom(image, box.x, box.y, box.width, box.height);        
    
        imageFace.update();
		ofNoFill();
		ofPushMatrix();
		ofPushStyle();
		ofSetColor(ofColor::red);
		ofRect(0, 0, 10, 10);
		ofTranslate(finder.blobs[0].centroid.x, finder.blobs[0].centroid.y, 0);
		ofSetColor(ofColor::green);
		ofRect(0, 0, 10, 10);
		ofRotate(ofGetElapsedTimef()*ofGetElapsedTimef());
		ofSetColor(ofColor::blue);
		ofRect(0, 0, 10, 10);
		ofPopStyle();
		imageFace.setAnchorPercent(0.5, 0.5);
		ofNoFill();
        imageFace.draw(0, 0, box.width, box.height);
		ofPopMatrix();
	}

	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}