#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 980, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
