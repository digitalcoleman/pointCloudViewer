#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setDistance(600);
    ofEnableDepthTest();
    light.setPosition(-300, 400, 600);
    
    
    gui.setup();
    gui.add(scaler.setup("cloud scale", 100, 1, 200));
    gui.add(pointSize.setup("vertex size", 1, 1, 20));
    gui.add(focusDist.setup("DOF focus", 600, 10, 1000));
    gui.add(focalLength.setup("DOF width", 5, 0, 100));
    gui.add(blur.setup("DOF blur", 3, 0, 10));
    gui.add(meshOn.setup("mesh On", false));
    
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    glEnable(GL_POINT_SMOOTH);// use circular points instead of square points
    glPointSize(1); // make the points bigger
    //ofBuffer myPoints = ofBufferFromFile("rafTest2.txt");
    //Path to the comma delimited file
    string filePath = "rafTest2.txt";
    
    loadPoints(filePath);
    
    depthOfField.setup(ofGetWidth(), ofGetHeight());
    

}

//--------------------------------------------------------------
void ofApp::update(){
    if(meshOn) {
        mesh.setMode(OF_PRIMITIVE_TRIANGLES_ADJACENCY);
    }else{
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    glPointSize(pointSize);
    depthOfField.setFocalDistance(focusDist);
    depthOfField.setBlurAmount(blur);
    depthOfField.setFocalRange(focalLength);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    //glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();
    ofSetColor(255);

    depthOfField.begin();
    cam.begin(depthOfField.getDimensions());

    ofPushMatrix();
    ofPoint center = mesh.getCentroid();

    //ofScale(500.0/model.getSceneMax().x, 500.0/model.getSceneMax().x);
    ofScale(scaler, scaler, scaler);
    //ofTranslate(center*scaler);
    ofTranslate(center);
    ofTranslate(0, 0, 4.5);
        ofRotate(-90, 1, 0, 0);
    //ofScale(scaler, scaler, scaler);


    mesh.draw();
    ofPopMatrix();
    ofDrawAxis(100);
    
    cam.end();
    depthOfField.end();
    
    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();
    
    if(ofGetKeyPressed('f')){
        depthOfField.drawFocusAssist(0, 0);
    }
    else{
        depthOfField.getFbo().draw(0, 0);
    }
    
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
    if( dragInfo.files.size() > 0 ){
        loadPoints(dragInfo.files[0]);
    }
    
}

//---------------------------------------------------------

void ofApp::loadPoints(string fileName) {
    //Load file placed in bin/data
    mesh.clear();
    ofFile file(fileName);
    
    if(!file.exists()){
        ofLogError("The file " + fileName + " is missing");
    }
    ofBuffer buffer(file);
    int i=0;
    //Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        //Split line into strings
        vector<string> words = ofSplitString(line, " ");
        //Store strings into a custom container
        if (words.size()>=9) {
            ofPoint newPoint;
            newPoint.x = ofToFloat(words[0]);
            newPoint.y = ofToFloat(words[1]);
            newPoint.z = ofToFloat(words[2]);
            
            ofColor newColor;
            newColor.r = ofToFloat(words[3]);
            newColor.g = ofToFloat(words[4]);
            newColor.b = ofToFloat(words[5]);
            
            ofVec3f newNorm;
            newNorm.x = ofToFloat(words[6]);
            newNorm.y = ofToFloat(words[7]);
            newNorm.z = ofToFloat(words[8]);
            
            mesh.addVertex(newPoint);
            mesh.addColor(newColor);
            mesh.addNormal(newNorm);
            mesh.addIndex(i);
            i++;
        }
    }
}