#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofNoFill();
	ofSetCircleResolution(36);

	this->random_seed = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	//if (ofGetFrameNum() % 180 < 5) {

	//	this->random_seed = ofRandom(1000);
	//}

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	//// Day 228 Zenith Blue 
	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(134, 179, 224));
	color_palette.push_back(ofColor(251, 218, 205));
	color_palette.push_back(ofColor(234, 96, 148));

	this->draw_circle_packing(glm::vec2(), 340, color_palette);

	this->cam.end();

}

//--------------------------------------------------------------
void ofApp::draw_circle_packing(glm::vec2 location, float radius, vector<ofColor> color_palette) {

	auto number_of_sphere = radius * 0.8;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto tmp_deg = ofRandom(0, 360);
		auto noise_radius = ofMap(ofNoise(radius * cos(tmp_deg * DEG_TO_RAD) * 0.005, radius * sin(tmp_deg * DEG_TO_RAD) * 0.005, ofGetFrameNum() * 0.01), 0, 1, radius * 0.5, radius * 1.2);
		auto tmp_location_radius = ofRandom(1, noise_radius);
		
		auto tmp_location = glm::vec2(location.x + tmp_location_radius * cos(tmp_deg * DEG_TO_RAD), location.y + tmp_location_radius * sin(tmp_deg * DEG_TO_RAD));
		auto tmp_radius = ofRandom(radius * 0.003, radius * 0.22);

		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(tmp_location, location_list[i]) < tmp_radius + radius_list[i] + 1) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(tmp_location);
			radius_list.push_back(tmp_radius);

			ofPushMatrix();
			ofTranslate(tmp_location);

			int color_index = ofRandom(color_palette.size());

			ofFill();
			ofSetColor(color_palette[color_index], 100);
			ofBeginShape();
			for (int deg = 0; deg < 360; deg += 1) {

				auto noise_value = ofNoise(tmp_location.x + tmp_radius * cos(deg * DEG_TO_RAD) * 0.05, tmp_location.y + tmp_radius * sin(deg * DEG_TO_RAD) * 0.05);
				ofVertex(tmp_radius * noise_value * cos(deg * DEG_TO_RAD), tmp_radius * noise_value * sin(deg * DEG_TO_RAD));
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(color_palette[color_index]);
			ofBeginShape();
			for (int deg = 0; deg < 360; deg += 1) {

				auto noise_value = ofNoise(tmp_location.x + tmp_radius * cos(deg * DEG_TO_RAD) * 0.05, tmp_location.y + tmp_radius * sin(deg * DEG_TO_RAD) * 0.05);
				ofVertex(tmp_radius * noise_value * cos(deg * DEG_TO_RAD), tmp_radius * noise_value * sin(deg * DEG_TO_RAD));
			}
			ofEndShape(true);

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}