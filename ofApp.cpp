/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("Peep:Table");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	ofSeedRandom();
	
	ofEnableAntiAliasing();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD
	
	/********************
	********************/
	gui.setup();
	
	gui.add(gui__dAngle_Down.setup("dAngle_Down", 14, 0, 90));
	gui.add(gui__dAngle_Up.setup("dAngle_Up", 17, 0, 90));
	gui.add(gui__PushTime_ms.setup("PushTime_ms", 700, 100, 2000));
	gui.add(gui__ReverseDirection.setup("ReverseDirection", false));
	
	/********************
	********************/
	setup_udp();
}

/******************************
******************************/
void ofApp::setup_udp(){
	/********************
	********************/
	{
		ofxUDPSettings settings;
		// settings.sendTo("127.0.0.1", 12345);
		settings.sendTo("10.0.0.7", 12345);
		settings.blocking = false;
		
		udp_Send.Setup(settings);
	}
	
	/********************
	********************/
	{
		ofxUDPSettings settings;
		settings.receiveOn(12346);
		settings.blocking = false;
		
		udp_Receive.Setup(settings);
	}
}

/******************************
******************************/
void ofApp::update(){
	char udpMessage[UDP_BUF_SIZE];
	udp_Receive.Receive(udpMessage, UDP_BUF_SIZE);
	string message=udpMessage;
	
	if(message!=""){
		int counter = 0;
		do{
			/********************
			********************/
			// printf("%s\n", message.c_str());
			// printf("> %d th message\n", counter);
			counter++;
			
			vector<string> strMessages = ofSplitString(message, "[p]");
			/*
			for(int i = 0; i < strMessages.size(); i++){
				printf("%s\n", strMessages[i].c_str());
			}
			*/
			
			if(strMessages.size() == 2){
				if( (strMessages[0] == "Table") && (strMessages[1] == "Beat") )	c_Beat++;
			}
			
			/********************
			********************/
			udp_Receive.Receive(udpMessage, UDP_BUF_SIZE);
			message=udpMessage;
		}while(message!="");
	}
}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(40);
	
	gui.draw();
	
	/*
	printf("c_Beats = %d\r", c_Beat);
	fflush(stdout);
	*/
}

/******************************
******************************/
void ofApp::sendUdpTo_Table__PushUp(){
	/********************
	********************/
	int dAngle = int(gui__dAngle_Up);
	int PushTime_ms = int(gui__PushTime_ms);
	
	char buf[100];
	if(!gui__ReverseDirection)	sprintf(buf, "%d|%d", -dAngle, PushTime_ms);
	else						sprintf(buf, "%d|%d", dAngle, PushTime_ms);
	
	/********************
	********************/
	string message="";
	message += "oF|set_dAngle|";
	message += buf;
	
	udp_Send.Send(message.c_str(),message.length());
}

/******************************
******************************/
void ofApp::sendUdpTo_Table__PushDown(){
	/********************
	********************/
	int dAngle = int(gui__dAngle_Down);
	int PushTime_ms = int(gui__PushTime_ms);
	
	char buf[100];
	if(!gui__ReverseDirection)	sprintf(buf, "%d|%d", dAngle, PushTime_ms);
	else						sprintf(buf, "%d|%d", -dAngle, PushTime_ms);
	
	/********************
	********************/
	string message="";
	message += "oF|set_dAngle|";
	message += buf;
	
	udp_Send.Send(message.c_str(),message.length());
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case '1':
			sendUdpTo_Table__PushDown();
			break;
		case '3':
			sendUdpTo_Table__PushUp();
			break;
			
		case 'd':
			printf("c_Beat = %d\n", c_Beat);
			fflush(stdout);
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
