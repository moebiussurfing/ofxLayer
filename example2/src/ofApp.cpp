#include "ofMain.h"

#include "ofxLayer.h"
#include "ofxGui.h"

#define NUM_LAYERS 3

using namespace ofxLayer;

class MyLayer
{

public:

	Layer *layerPtr;


	void passLayer(Layer* _layer)
	{
		ofLogNotice("MyLayer") << "passLayer:" << ofToString(_layer->getClassName());
		layerPtr = _layer;
	}

	void setName(string _name)
	{
		ofLogNotice("MyLayer") << "setName: " << _name;
		name = _name;
		setup();
	}

	ofBlendMode OF_BlendMode;

	ofParameter<string> name{ "name","name" };
	ofParameter<bool> enable{ "enable", false };
	ofParameter<float> alpha{ "alpha", 0.8f, 0.0f, 1.0f };
	ofParameter<ofColor> color{ "color",ofColor(255),ofColor(0),ofColor(255) };
	ofParameter<int> blend{ "blend", 0, 0, 5 };
	ofParameter<string> blendName{ "","" };
	ofParameter<bool> enableBg{ "enableBg", false };
	ofParameter<ofColor> bgColor{ "bgColor",ofColor(128),ofColor(0),ofColor(255) };
	ofParameter<float> bgAlpha{ "bgAlpha", 1.0f, 0.0f, 1.0f };
	ofParameter<glm::vec2> pos{ "pos",
		glm::vec2(10,10),glm::vec2(0,0),glm::vec2(1440,900) };
	ofParameter<int> level{ "level", 1, 1, NUM_LAYERS };

	ofParameterGroup params{ "MyLayer" };
	ofParameterGroup paramsBg{ "background" };

	void Changed_params(ofAbstractParameter &e)
	{
		string name = e.getName();
		ofLogNotice("MyLayer") << "name: " << name << " : " << e;

		if (name == "enable")
		{
			if (layerPtr != nullptr)
			{
				layerPtr->setAlpha(enable ? alpha.get() : 0.0f);
			}
		}
		else if (name == "alpha")
		{
			if (layerPtr != nullptr)
			{
				layerPtr->setAlpha(alpha.get());
			}
		}
		else if (name == "blend")
		{
			switch (blend) {
			case 0:
				layerPtr->setBlendMode(OF_BLENDMODE_DISABLED);
				cout << "OF_BLENDMODE_DISABLED" << endl;
				blendName = "DISABLED";
				break;
			case 1:
				layerPtr->setBlendMode(OF_BLENDMODE_ALPHA);
				cout << "OF_BLENDMODE_ALPHA" << endl;
				blendName = "ALPHA";
				break;
			case 2:
				layerPtr->setBlendMode(OF_BLENDMODE_ADD);
				cout << "OF_BLENDMODE_ADD" << endl;
				blendName = "ADD";
				break;
			case 3:
				layerPtr->setBlendMode(OF_BLENDMODE_SUBTRACT);
				cout << "OF_BLENDMODE_SUBTRACT" << endl;
				blendName = "SUBTRACT";
				break;
			case 4:
				layerPtr->setBlendMode(OF_BLENDMODE_MULTIPLY);
				cout << "OF_BLENDMODE_MULTIPLY" << endl;
				blendName = "MULTIPLY";
				break;
			case 5:
				layerPtr->setBlendMode(OF_BLENDMODE_SCREEN);
				cout << "OF_BLENDMODE_SCREEN" << endl;
				blendName = "SCREEN";
				break;
			}
		}
		//        else if (name == "enableBg")
		//        {
		//
		//        }
		//        else if (name == "bgColor")
		//        {
		//
		//        }else if (name == "pos")
		//        {
		//
		//        }
	}

	MyLayer()
	{
		params.add(name);
		params.add(enable);
		params.add(level);
		params.add(alpha);
		params.add(color);
		params.add(blend);
		params.add(blendName);
		params.add(pos);
		paramsBg.add(enableBg);
		paramsBg.add(bgColor);
		paramsBg.add(bgAlpha);
		params.add(paramsBg);
	}

	void setup()
	{
		name.setSerializable(false);
		level.setSerializable(false);
		blendName.setSerializable(false);
		
		params.setName(name);
		ofAddListener(params.parameterChangedE(), this, &MyLayer::Changed_params);
		//string str = name.get() + ".xml";
		//load(str);
	}

	void reLoad()//to reload after layer construction is done
	{
		string str = name.get() + ".xml";
		load(str);
	}
	void reSave()//to save after layer construction is done
	{
		string str = name.get() + ".xml";
		save(str);
	}

	void exit()
	{
		cout << "DESTRUCT starts" << endl;

		ofRemoveListener(params.parameterChangedE(), this, &MyLayer::Changed_params);

		string str = name.get() + ".xml";
		save(str);

		cout << "DESTRUCT finish" << endl;
	}

	~MyLayer()
	{
		//destructor is not triggered on app quit/exit...?
	}

	void load(string path)
	{
		ofLogNotice("MyLayer") << "load: " << path;
		load_GroupSettings(params, path);
	}

	void save(string path)
	{
		ofLogNotice("MyLayer") << "save: " << path;
		save_GroupSettings(params, path);
	}

	void load_GroupSettings(ofParameterGroup &g, string path)
	{
		ofLogNotice("MyLayer") << "GroupSettings load " << path;
		ofXml settings;
		settings.load(path);
		ofDeserialize(settings, g);
	}

	void save_GroupSettings(ofParameterGroup &g, string path)
	{
		ofLogNotice("MyLayer") << "GroupSettings save " << path;
		ofXml settings;
		ofSerialize(settings, g);
		settings.save(path);
	}
};

//-

class TestLayer1 : public ofxLayer::Layer
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer1);
	ofImage img;
	MyLayer myLayer;

	void setup()
	{
		img.load("images/bikers.jpg");
	}
	void update()
	{
		//ofLogVerbose("TestLayer1") << "update()";
		if (myLayer.enableBg.get())
		{
			int a = ofMap(myLayer.bgAlpha, 0, 1, 0, 255);
			ofColor c = myLayer.bgColor.get();
			ofBackground(c.r, c.g, c.b, a);
		}
		else
		{
			ofBackground(255, 0, 0, 0);
		}
	}

	void draw()
	{
		ofSetColor(myLayer.color.get());
		img.draw(myLayer.pos.get().x, myLayer.pos.get().y);
	}

	~TestLayer1()
	{
		cout << "~TestLayer1()" << endl;
	}
};

class TestLayer2 : public ofxLayer::Layer
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer2);
	ofImage img;
	MyLayer myLayer;

	void setup()
	{
		img.load("images/tdf_1972_poster.jpg");
	}

	void update()
	{
		//ofLogVerbose("TestLayer2") << "update()";
		if (myLayer.enableBg.get())
		{
			int a = ofMap(myLayer.bgAlpha, 0, 1, 0, 255);
			ofColor c = myLayer.bgColor.get();
			ofBackground(c.r, c.g, c.b, a);
		}
		else
		{
			ofBackground(0, 255, 0, 0);
		}
	}

	void draw()
	{
		ofSetColor(myLayer.color.get());
		img.draw(myLayer.pos.get().x, myLayer.pos.get().y);
	}

	~TestLayer2()
	{
		cout << "~TestLayer2()" << endl;
	}
};

class TestLayer3 : public ofxLayer::Layer
{
public:

	OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer3);
	ofImage img;
	MyLayer myLayer;

	void setup()
	{
		img.load("images/gears.gif");
	}

	void update()
	{
		//ofLogVerbose("TestLayer3") << "update()";
		if (myLayer.enableBg.get())
		{
			int a = ofMap(myLayer.bgAlpha, 0, 1, 0, 255);
			ofColor c = myLayer.bgColor.get();
			ofBackground(c.r, c.g, c.b, a);
		}
		else
		{
			ofBackground(0, 0, 255, 0);
		}
	}

	void draw()
	{
		ofSetColor(myLayer.color.get());
		img.draw(myLayer.pos.get().x, myLayer.pos.get().y);
	}

	~TestLayer3()
	{
		cout << "~TestLayer3()" << endl;
	}
};

//-

TestLayer1 *layer1;
TestLayer2 *layer2;
TestLayer3 *layer3;

ofxLayer::Manager mng;

//-

class ofApp : public ofBaseApp
{
public:

	ofxPanel gui;

	//selector
	ofParameterGroup paramsControl{ "MANAGER" };
	ofParameter<int> selectedLayer{ "LAYER", 1, 1, NUM_LAYERS };
	ofParameter<bool> selectedEnable{ "ENABLE", false };
	ofParameter<float> selectedAlpha{ "ALPHA", 0.5f, 0.0f, 1.0f };
	ofParameter<int> selectedLevel{ "LEVEL", 1, 1, NUM_LAYERS };//layer vele/sorting position 1=front
	ofParameter<bool> moveUp{ "UP", false };
	ofParameter<bool> moveDown{ "DOWN", false };
	ofParameter<bool> bSave{ "SAVE", false };
	ofParameter<bool> bLoad{ "LOAD", false };
	ofxPanel guiControl;

	void setup()
	{
		ofSetLogLevel(OF_LOG_VERBOSE);

		ofSetFrameRate(30);
		ofBackground(30);

		//-

		//control
		paramsControl.add(selectedLayer);
		paramsControl.add(selectedEnable);
		paramsControl.add(selectedAlpha);
		paramsControl.add(selectedLevel);
		paramsControl.add(moveUp);
		paramsControl.add(moveDown);
		paramsControl.add(bSave);
		paramsControl.add(bLoad);

		ofAddListener(paramsControl.parameterChangedE(), this, &ofApp::Changed_params);

		guiControl.setup("CONTROL");
		guiControl.add(paramsControl);
		guiControl.setPosition(300, 5);

		//-

		mng.setup(ofGetWindowWidth() - 100, ofGetWindowHeight() - 100);

		layer1 = mng.createLayer<TestLayer1>(1);
		layer2 = mng.createLayer<TestLayer2>(1);
		layer3 = mng.createLayer<TestLayer3>(1);

		layer1->setAlpha(1);
		layer2->setAlpha(1);
		layer3->setAlpha(1);

		//sorting
		//layer1->setLayerIndex(2);

		//params
		layer1->myLayer.setName("layer1");
		layer2->myLayer.setName("layer2");
		layer3->myLayer.setName("layer3");

		//populate default layout (when no xml settings)
		int pad = 100;
		int x = 400;
		int y = 200;
		layer1->myLayer.pos.set((glm::vec2(x + pad, y + pad)));
		layer2->myLayer.pos.set((glm::vec2(x + 2 * pad, y + 2 * pad)));
		layer3->myLayer.pos.set((glm::vec2(x + 3 * pad, y + 3 * pad)));

		//levels
		layer1->myLayer.level = 1;
		layer2->myLayer.level = 2;
		layer3->myLayer.level = 3;

		//ptr
		layer1->myLayer.passLayer(layer1);
		layer2->myLayer.passLayer(layer2);
		layer3->myLayer.passLayer(layer3);

		//TODO:
		//layers sorting...drag system, ImGui/ImNode... should be nice

		//gui
		gui.setup("LAYERS");
		gui.add(layer1->myLayer.params);
		gui.add(layer2->myLayer.params);
		gui.add(layer3->myLayer.params);
		gui.setPosition(5, 5);

		//TODO:
		//mng.setBackgroundAuto(false);

		//-

		//startup

		//load xml settings
		layer1->myLayer.reLoad();
		layer2->myLayer.reLoad();
		layer3->myLayer.reLoad();

		selectedLayer = selectedLayer;//trig callback to refresh 
	}

	void exit()
	{
		ofLogError("ofApp") << "exit()";
		layer1->myLayer.exit();
		layer2->myLayer.exit();
		layer3->myLayer.exit();
	}


	void update()
	{
		ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
		mng.update();

		//TODO:
		////to update bg
		//layer1->update();
		//layer2->update();
		//layer3->update();
	}

	void draw()
	{
		ofEnableAlphaBlending();
		mng.draw();

		guiControl.draw();
		gui.draw();

		//debug
		int y = 70;
		string pad = "  ";
		string str = "";
		str += "MONITOR\n";
		str += "LAYER:" + ofToString(selectedLayer);
		str += pad;
		str += "LEVEL:" + ofToString(selectedLevel);
		str += "\n";
		str += "\n";
		str += "KEYS\n";
		str += "L-R:BROWSE LAYER";
		str += pad;
		str += "UP-DOWN:MOVE LEVEL";
		str += pad;
		str += "RETURN:ENABLE LAYER";
		ofDrawBitmapStringHighlight(str, 0, ofGetHeight() - y);
	}

	void keyPressed(int key)
	{
		//selector controller

		//sort
		if (key == OF_KEY_UP)
		{
			moveUp = true;
		}
		else if (key == OF_KEY_DOWN)
		{
			moveDown = true;
		}
		//select
		else if (key == OF_KEY_LEFT)
		{
			if (selectedLayer > 1)
				selectedLayer--;
		}
		else if (key == OF_KEY_RIGHT)
		{
			if (selectedLayer < 3)
				selectedLayer++;
		}
		//toggle enable
		else if (key == OF_KEY_RETURN)
		{
			selectedEnable = !(selectedEnable.get());
		}
	}

	void keyReleased(int key)
	{
	}

	void mouseMoved(int x, int y)
	{
	}

	void mouseDragged(int x, int y, int button)
	{
	}

	void mousePressed(int x, int y, int button)
	{
	}

	void mouseReleased(int x, int y, int button)
	{
	}

	void windowResized(int w, int h)
	{
	}

	void Changed_params(ofAbstractParameter &e)
	{
		string name = e.getName();
		ofLogNotice("ofApp") << "name: " << name << " : " << e;

		//select layer
		if (name == "LAYER")
		{
			//collapse all
			gui.minimizeAll();

			//expand and get enable and alpha vars from selected
			if (selectedLayer == 1)
			{
				auto &g = gui.getGroup("layer1");
				g.maximize();
				g.getGroup("color").minimize();
				g.getGroup("pos").minimize();
				g.getGroup("background").minimize();
				selectedAlpha = layer1->myLayer.alpha.get();
				selectedEnable = layer1->myLayer.enable.get();
				selectedLevel = layer1->myLayer.level.get();
			}
			else if (selectedLayer == 2)
			{
				auto &g = gui.getGroup("layer2");
				g.maximize();
				g.getGroup("color").minimize();
				g.getGroup("pos").minimize();
				g.getGroup("background").minimize();
				selectedAlpha = layer2->myLayer.alpha.get();
				selectedEnable = layer2->myLayer.enable.get();
				selectedLevel = layer2->myLayer.level.get();
			}
			else if (selectedLayer == 3)
			{
				auto &g = gui.getGroup("layer3");
				g.maximize();
				g.getGroup("color").minimize();
				g.getGroup("pos").minimize();
				g.getGroup("background").minimize();
				selectedAlpha = layer3->myLayer.alpha.get();
				selectedEnable = layer3->myLayer.enable.get();
				selectedLevel = layer3->myLayer.level.get();
			}
		}
		//sort
		//if (key == '1') layer3->moveUp();
		//if (key == '2') layer3->moveDown();
		//if (key == '3') layer3->moveFront();
		//if (key == '4') layer3->moveBack();
		else if (name == "UP")
		{
			moveUp = false;
			switch (selectedLayer) {
			case 1:
				layer1->moveUp();
				selectedLevel = layer1->getLayerIndex() + 1;
				layer1->myLayer.level = selectedLevel;
				break;
			case 2:
				layer2->moveUp();
				selectedLevel = layer2->getLayerIndex() + 1;
				layer2->myLayer.level = selectedLevel;
				break;
			case 3:
				layer3->moveUp();
				selectedLevel = layer3->getLayerIndex() + 1;
				layer3->myLayer.level = selectedLevel;
				break;
			default:
				ofLogError("ofApp") << "selectedLayer layer not exist";
				break;
			}
		}
		else if (name == "DOWN")
		{
			moveDown = false;
			switch (selectedLayer) {
			case 1:
				layer1->moveDown();
				selectedLevel = layer1->getLayerIndex() + 1;
				layer1->myLayer.level = selectedLevel;
				break;
			case 2:
				layer2->moveDown();
				selectedLevel = layer2->getLayerIndex() + 1;
				layer2->myLayer.level = selectedLevel;
				break;
			case 3:
				layer3->moveDown();
				selectedLevel = layer3->getLayerIndex() + 1;
				layer3->myLayer.level = selectedLevel;
				break;
			default:
				ofLogError("ofApp") << "selectedLayer layer not exist";
				break;
			}
		}
		//set enable and alpha from selected to relative layer
		else if (name == "ENABLE")
		{
			if (selectedLayer == 1)
			{
				layer1->myLayer.enable = selectedEnable;
			}
			else if (selectedLayer == 2)
			{
				layer2->myLayer.enable = selectedEnable;
			}
			else if (selectedLayer == 3)
			{
				layer3->myLayer.enable = selectedEnable;
			}
		}
		else if (name == "ALPHA")
		{
			if (selectedLayer == 1)
			{
				layer1->myLayer.alpha = selectedAlpha;
			}
			else if (selectedLayer == 2)
			{
				layer2->myLayer.alpha = selectedAlpha;
			}
			else if (selectedLayer == 3)
			{
				layer3->myLayer.alpha = selectedAlpha;
			}

			if (!selectedEnable)
				selectedEnable = true;
		}
		else if (name == "LEVEL")
		{
			if (selectedLayer == 1)
			{
				layer1->myLayer.level = selectedLevel;//level starts from 1
				layer1->setLayerIndex(layer1->myLayer.level - 1);//layer starts from 0
				//update the other layers level
				layer2->myLayer.level = layer2->getLayerIndex() + 1;
				layer3->myLayer.level = layer3->getLayerIndex() + 1;
			}
			else if (selectedLayer == 2)
			{
				layer2->myLayer.level = selectedLevel;
				layer2->setLayerIndex(layer2->myLayer.level - 1);
				//update the other layers level
				layer1->myLayer.level = layer1->getLayerIndex() + 1;
				layer3->myLayer.level = layer3->getLayerIndex() + 1;
			}
			else if (selectedLayer == 3)
			{
				layer3->myLayer.level = selectedLevel;
				layer3->setLayerIndex(layer3->myLayer.level - 1);
				//update the other layers level
				layer1->myLayer.level = layer1->getLayerIndex() + 1;
				layer2->myLayer.level = layer2->getLayerIndex() + 1;
			}
		}
		else if (name == "SAVE" && bSave)
		{
			bSave = false;
			//save xml settings
			layer1->myLayer.reSave();
			layer2->myLayer.reSave();
			layer3->myLayer.reSave();
		}
		else if (name == "LOAD" && bLoad)
		{
			bLoad = false;
			//load xml settings
			layer1->myLayer.reLoad();
			layer2->myLayer.reLoad();
			layer3->myLayer.reLoad();
		}
	}

};


int main(int argc, const char** argv)
{
	ofSetupOpenGL(1920, 1080, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
