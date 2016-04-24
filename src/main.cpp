#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
    //    settings.setGLVersion(2, 1);
    settings.width = 1500;
    settings.height = 1500;
    ofCreateWindow(settings);
    ofRunApp(new ofApp()); // start the app

}
