#include "testApp.h"

extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){
	
	//faceWidth = 200;
	//faceHeight = 200;

	finder.setup("haarcascade_frontalface_default.xml");
	//CGContextRef cgctx = NULL;
	//ofSetVerticalSync(true);
	//tex.allocate(300,300, GL_RGBA);
	image.allocate(300, 300, OF_IMAGE_COLOR);
	//pixels.allocate(300, 300, OF_IMAGE_COLOR);
	//imageFace = image;
	
	ofSetFrameRate(30);

}

//--------------------------------------------------------------
void testApp::update(){
	
	int w = 300;
	int h = 300;
	
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	
	// now, let's get the R and B data swapped, so that it's all OK:
	for (int i = 0; i < w*h; i++){
		
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
		image.setFromPixels(data, 300, 300, OF_IMAGE_COLOR_ALPHA, true);
		image.setImageType(OF_IMAGE_COLOR);
		image.update();
		
		//do Face Detection
		finder.findHaarObjects(image.getPixelsRef());
		
		//make sure that OpenCV can find a face
		if (finder.blobs.size() > 0) {
			
			//then make a new image that is the width and height of the face bounding box
			imageFace.allocate(finder.blobs[0].boundingRect.x, finder.blobs[0].boundingRect.y, OF_IMAGE_COLOR_ALPHA);
			
			//unsigned char * origPixels = image.getPixels();
		
			//make a new data type for the new image's pixels
			unsigned char * copyPixels = imageFace.getPixels();
		
			//declare an index to keep track of the new image's pixels that are within the bounding box
			int imageFaceIndex = 0;

			//loop through the first image's cols and rows
			for(int row = 0; row < image.getHeight(); row++) {
				for(int col = 0; col < image.getWidth(); col++) {
				
					//keep track of index
					int offset = row * image.getWidth() + col;
				
					//check to see if "pixel" is within bounds of face detected Rect
					if (row > finder.blobs[0].boundingRect.x && 
						row < (finder.blobs[0].boundingRect.x + finder.blobs[0].boundingRect.width) && 
						col < finder.blobs[0].boundingRect.y && 
						col > (finder.blobs[0].boundingRect.y + finder.blobs[0].boundingRect.height)) {
					
						//if so, then copy the RGBA pixels from the original data to new image pixels
						data[offset*4] = copyPixels[imageFaceIndex*4];
						data[offset*4 + 1] = copyPixels[imageFaceIndex*4 + 1];
						data[offset*4 + 2] = copyPixels[imageFaceIndex*4 + 2];
						data[offset*4 + 3] = copyPixels[imageFaceIndex*4 + 3];
					
						//increment to the next pixel that satisfies the bounding box
						imageFaceIndex++;
						
							}
					
						}
					}
			imageFace.update();

					
				}
				
			}

	//cout << imageBelowWindow()[0] << endl;

	

}

//--------------------------------------------------------------
void testApp::draw(){
	image.draw(0,0, ofGetWidth(), ofGetHeight());
	
	
	ofNoFill();
	
	//for each face "blob" we found, draw a rectangle around the face
    //#2
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRect(finder.blobs[i].boundingRect);
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