#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);

	int font_size = 170;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", font_size, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0);

	string word = "TRICK";
	font.drawString(word, 0, font_size + 50);

	word = "OR";
	font.drawString(word, ofGetWidth() * 0.5 - font.stringWidth(word) * 0.5, ofGetHeight() * 0.5 + font_size * 0.5);

	word = "TREAT";
	font.drawString(word, ofGetWidth() - font.stringWidth(word), ofGetHeight() - 55);

	fbo.end();

	ofPixels pixels;
	fbo.readToPixels(pixels);

	font_size = 20;
	for (int x = 0; x < fbo.getWidth(); x += font_size) {

		for (int y = 0; y < fbo.getHeight(); y += font_size) {

			if (pixels.getColor(x, y) != ofColor(0, 0)) {

				this->locations.push_back(ofPoint(x, y));

				ofColor color;
				color.setHsb(ofRandom(255), 255, 255);
				
				this->colors.push_back(color);
			}
		}
	}

	ofTrueTypeFontSettings font_settings("fonts/EmojiSymbols-Regular.ttf", font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Emoji);
	this->font.load(font_settings);	
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<string> words = {
		u8"🎃", u8"🍭", u8"👻",
	};

	for (int i = 0; i < this->locations.size(); i++) {

		ofPoint point = this->locations[i];
		int words_index = ofNoise(point.x * 0.003, point.y * 0.003, ofGetFrameNum() * 0.005) * words.size();
		std::string moji = words[words_index];

		if (words_index == 0) {

			ofSetColor(229, 163, 35);
		}
		else if(words_index == 1) {

			ofSetColor(this->colors[i]);
		}
		else {

			ofSetColor(239);
		}

		this->font.drawString(moji, point.x, point.y);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}