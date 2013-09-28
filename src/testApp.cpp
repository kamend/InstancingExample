#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	noiseZ = ofRandom(10,20);
	
	gui.setup();
	gui.add(guiZIncr.setup("Z Inrc", 0.01, 0.001, 0.05));
	
	guiVisible = false;
	
	generateLandscape();


	
	shader.load("shader");
	
	

	glGenBuffers(1,&vboid);
	
	
	int pos = glGetAttribLocation(shader.getProgram(), "transformmatrix");
	int pos1 = pos+0;
	int pos2 = pos+1;
	int pos3 = pos+2;
	int pos4 = pos+3;
	
	glEnableVertexAttribArray(pos1);
	glEnableVertexAttribArray(pos2);
	glEnableVertexAttribArray(pos3);
	glEnableVertexAttribArray(pos4);
	glBindBuffer(GL_ARRAY_BUFFER,vboid);
	glVertexAttribPointer(pos1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(0));
	glVertexAttribPointer(pos2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 4));
	glVertexAttribPointer(pos3, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 8));
	glVertexAttribPointer(pos4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4 * 4, (void*)(sizeof(float) * 12));
	glVertexAttribDivisor(pos1, 1);
	glVertexAttribDivisor(pos2, 1);
	glVertexAttribDivisor(pos3, 1);
	glVertexAttribDivisor(pos4, 1);
	
	
	ofSpherePrimitive sphere;
	sphere.set(10,16);
	
	
	ofBoxPrimitive box;
	box.set(10, 10, 10, 5, 5, 10);
	
	ofCylinderPrimitive cyl;
	cyl.set(6, 30, 32, 8);
	
	vboMesh = sphere.getMesh();
	
	

	postFx.init(ofGetWidth(), ofGetHeight());

	postFx.createPass<SSAOPass>()->setEnabled(true);
	postFx.createPass<LUTPass>()->setEnabled(true);
	//postFx.createPass<HorizontalTiltShifPass>()->setEnabled(true);
	//postFx.createPass<LimbDarkeningPass>()->setEnabled(true);

	
	RenderPass::Ptr fake = postFx.getPasses()[0];
	SSAOPass::Ptr ssa = dynamic_pointer_cast<SSAOPass>(fake);
	ssa->setOnlyAO(false);
	ssa->setFogEnabled(false);
	
	RenderPass::Ptr ptrLut = postFx.getPasses()[1];
	LUTPass::Ptr Lut = dynamic_pointer_cast<LUTPass>(ptrLut);
	
	Lut->loadLUT("Gotham.cube");

}

void testApp::generateLandscape() {
	
	int i = 50;
	int j = 50;
	
	float width = 600;
	float height = 600;
	float depth = 200;
	
	float noiseX = 0;
	float noiseY = 0;


	float incr=0.05;

	
	landscape.clear();
	
	noiseX = 0;
	for(int ii=0;ii<i;ii++) {
		noiseX += incr;
		noiseY = 0;
		for(int jj=0;jj<j;jj++) {
			
			float x = -width/2 + ii*(width/i);
			float z = -height/2 + jj*(height/j);
			
			float nx = ofNoise(noiseX, noiseY, noiseZ);
			
			ofVec3f p = ofVec3f(x, nx * depth,z);
			landscape.push_back(p);
		
			noiseY += incr;
	
		}

	}
		
	matricesData.clear();
	for(int i=0;i<landscape.size();i++) {
		ofMatrix4x4 m;
		m.setTranslation(landscape[i].x, landscape[i].y, landscape[i].z);
		
		for(int j=0;j<16;j++) {
			matricesData.push_back(m.getPtr()[j]);
		}
		
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vboid);
	glBufferData(GL_ARRAY_BUFFER, matricesData.size()*sizeof(float), &matricesData[0], GL_DYNAMIC_DRAW);

}



//--------------------------------------------------------------
void testApp::update(){
		generateLandscape();
	
	zincr = guiZIncr;
	noiseZ += zincr;

}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableSmoothing();
	glEnable(GL_DEPTH_TEST);
	
	
	postFx.begin(cam);
	shader.begin();
	vboMesh.drawInstanced(OF_MESH_FILL, landscape.size());
	shader.end();
	postFx.end(false);

	//ofBackgroundGradient(ofColor(30,30,30), ofColor(0,0,0));
	ofBackground(0, 0, 0);
	postFx.draw();
	
	glDisable(GL_DEPTH_TEST);
	
	if(guiVisible) {
		gui.draw();
	}
	
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' ') {
		guiVisible = !guiVisible;
	}
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
