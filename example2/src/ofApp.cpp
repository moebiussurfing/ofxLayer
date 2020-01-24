#include "ofMain.h"

#include "ofxLayer.h"
#include "ofxGui.h"

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
        name =_name;
        setup();
    }

    ofParameter<string> name{"name","name"};
    ofParameter<bool> enable{"enable", false};
    ofParameter<float> alpha{"alpha", 1.0f, 0.0f, 1.0f};
    ofParameter<ofColor> color{"color",ofColor(255),ofColor(0),ofColor(255)};
    ofParameter<int> blend{"blend", 0, 0, 5};
    ofParameter<string> blendName{"blendName",""};
    ofParameter<bool> enableBg{"enableBg", false};
    ofParameter<ofColor> bgColor{"bgColor",ofColor(128),ofColor(0),ofColor(255)};
    ofParameter<float> bgAlpha{"bgAlpha", 1.0f, 0.0f, 1.0f};
    ofParameter<glm::vec2> pos{"pos",
        glm::vec2(10,10),glm::vec2(0,0),glm::vec2(1440,900)};

    ofParameterGroup params{"MyLayer"};
    ofBlendMode OF_BlendMode;

    void Changed_params(ofAbstractParameter &e)
    {
        string name = e.getName();
        ofLogNotice("MyLayer") << "name: " << name << " : " << e;

        if (name == "enable")
        {
            if  (layerPtr != nullptr)
            {
                layerPtr->setAlpha(enable?alpha.get():0.0f);
            }
        }
        else if (name == "alpha")
        {
            if  (layerPtr != nullptr)
            {
                layerPtr->setAlpha(alpha.get());
            }
        }
        else if (name == "blend")
        {
            switch (blend) {
                case 0:
                    layerPtr->setBlendMode(OF_BLENDMODE_DISABLED);
                    cout <<"OF_BLENDMODE_DISABLED"<<endl;
                    blendName = "DISABLED";
                    break;
                case 1:
                    layerPtr->setBlendMode(OF_BLENDMODE_ALPHA);
                    cout <<"OF_BLENDMODE_ALPHA"<<endl;
                    blendName = "ALPHA";
                    break;
                case 2:
                    layerPtr->setBlendMode(OF_BLENDMODE_ADD);
                    cout <<"OF_BLENDMODE_ADD"<<endl;
                    blendName = "ADD";
                    break;
                case 3:
                    layerPtr->setBlendMode(OF_BLENDMODE_SUBTRACT);
                    cout <<"OF_BLENDMODE_SUBTRACT"<<endl;
                    blendName = "SUBTRACT";
                    break;
                case 4:
                    layerPtr->setBlendMode(OF_BLENDMODE_MULTIPLY);
                    cout <<"OF_BLENDMODE_MULTIPLY"<<endl;
                    blendName = "MULTIPLY";
                    break;
                case 5:
                    layerPtr->setBlendMode(OF_BLENDMODE_SCREEN);
                    cout <<"OF_BLENDMODE_SCREEN"<<endl;
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
        //params.setName("settings");
        params.add(name);
        params.add(enable);
        params.add(alpha);
        params.add(color);
        params.add(blend);
        params.add(blendName);
        params.add(enableBg);
        params.add(bgColor);
        params.add(bgAlpha);
        params.add(pos);
    }

    void setup()
    {
        params.setName(name);
        ofAddListener(params.parameterChangedE(), this, &MyLayer::Changed_params);
        string str = name.get() + ".xml";
        load(str);
    }

    ~MyLayer()
    {
        cout<< "DESTRUCT starts"<<endl;

        ofRemoveListener(params.parameterChangedE(), this, &MyLayer::Changed_params);
        string str = name.get() + ".xml";
        save(str);

        cout<< "DESTRUCT finish"<<endl;
    }

    void load(string path)
    {
//        path = "path.xml";
        load_GroupSettings(params, path);
    }

    void save(string path)
    {
        //        path = "path.xml";
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
        if (myLayer.enableBg.get())
        {
            int a = ofMap(myLayer.bgAlpha,0,1,0,255);
            ofColor c = myLayer.bgColor.get();
            ofBackground(c.r, c.g, c.b, a);
        }
    }

    void draw()
    {
        ofSetColor(myLayer.color.get());
        img.draw(myLayer.pos.get().x, myLayer.pos.get().y);
    }

    ~TestLayer1()
    {
        cout <<"~TestLayer1()"<<endl;
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
        if (myLayer.enableBg.get())
        {
            int a = ofMap(myLayer.bgAlpha,0,1,0,255);
            ofColor c = myLayer.bgColor.get();
            ofBackground(c.r, c.g, c.b, a);
        }
    }

    void draw()
    {
        ofSetColor(myLayer.color.get());
        img.draw(myLayer.pos.get().x, myLayer.pos.get().y);
    }

    ~TestLayer2()
    {
        cout <<"~TestLayer2()"<<endl;
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
        if (myLayer.enableBg.get())
        {
            int a = ofMap(myLayer.bgAlpha,0,1,0,255);
            ofColor c = myLayer.bgColor.get();
            ofBackground(c.r, c.g, c.b, a);
        }
    }

    void draw()
    {
        ofSetColor(myLayer.color.get());
        img.draw(myLayer.pos.get().x, myLayer.pos.get().y);}

    ~TestLayer3()
    {
        cout <<"~TestLayer3()"<<endl;
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
    int NUM_LAYERS = 3;
    ofParameterGroup paramsControl{"MANAGER"};
    ofParameter<int> selected{"LAYER", 1, 1, NUM_LAYERS};
    ofParameter<bool> moveUp{"UP", false};
    ofParameter<bool> moveDown{"DOWN", false};
    ofxPanel guiControl;

    void Changed_params(ofAbstractParameter &e)
    {
        string name = e.getName();
        ofLogNotice("ofApp") << "name: " << name << " : " << e;

        if (name == "UP")
        {
            moveUp = false;
            switch (selected) {
                case 1:
                    layer1->moveUp();
                    break;
                case 2:
                    layer2->moveUp();
                    break;
                case 3:
                    layer3->moveUp();
                    break;
                default:
                    ofLogError("ofApp")<<"selected layer not exist";
                    break;
            }
        }
        else if (name == "DOWN")
        {
            moveDown = false;
            switch (selected) {
                case 1:
                    layer1->moveDown();
                    break;
                case 2:
                    layer2->moveDown();
                    break;
                case 3:
                    layer3->moveDown();
                    break;
                default:
                    ofLogError("ofApp")<<"selected layer not exist";
                    break;
            }
        }
    }

    void setup()
    {
        //control
        paramsControl.add(selected);
        paramsControl.add(moveUp);
        paramsControl.add(moveDown);
        ofAddListener(paramsControl.parameterChangedE(), this, &ofApp::Changed_params);

        guiControl.setup("CONTROL");
        guiControl.add(paramsControl);
        guiControl.setPosition(300,5);

        //-

        ofSetLogLevel(OF_LOG_VERBOSE);

        ofSetFrameRate(30);
        ofBackground(30);

        mng.setup(1280, 720);

        layer1 = mng.createLayer<TestLayer1>(1);
        layer2 = mng.createLayer<TestLayer2>(1);
        layer3 = mng.createLayer<TestLayer3>(1);

        layer1->setAlpha(1);
        layer2->setAlpha(1);
        layer3->setAlpha(1);

        //layer1->setLayerIndex(2);

        //params
        layer1->myLayer.setName("layer1");
        layer2->myLayer.setName("layer2");
        layer3->myLayer.setName("layer3");

        //ptr
        layer1->myLayer.passLayer(layer1);
        layer2->myLayer.passLayer(layer2);
        layer3->myLayer.passLayer(layer3);

        //TODO:
        //layers sorting...drag system, ImGui/ImNode... should be nice

        //gui
        gui.setup("gui");
        gui.add(layer1->myLayer.params);
        gui.add(layer2->myLayer.params);
        gui.add(layer3->myLayer.params);
        gui.setPosition(5, 5);
    }

    void update()
    {
        mng.update();
        ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    }

    void draw()
    {
        ofEnableAlphaBlending();
        mng.draw();

        guiControl.draw();
        gui.draw();

        string str;
        int index = -1;
        switch (selected) {
            case 1:
                index = layer1->getLayerIndex();
                break;
            case 2:
                index = layer2->getLayerIndex();
                break;
            case 3:
                index = layer3->getLayerIndex();
                break;
                //            default:
                //                ofLogError("ofApp")<<"selected layer not exist";
                //                break;
        }
        if (index == -1)
        {
            ofLogError("ofApp")<<"layer index unknown";
        }
        str = "LAYER: "+ofToString(selected);
        str += " POS: "+ofToString(index);
        ofDrawBitmapStringHighlight(str, 0, ofGetHeight()-7);
    }

    void keyPressed(int key)
    {
        if (key == OF_KEY_UP)
        {
            moveUp = true;
        }
        else if (key == OF_KEY_DOWN)
        {
            moveDown = true;
        }

        //            if (key == '1') layer3->moveUp();
        //            if (key == '2') layer3->moveDown();
        //            if (key == '3') layer3->moveFront();
        //            if (key == '4') layer3->moveBack();
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
};


int main(int argc, const char** argv)
{
    ofSetupOpenGL(1280, 720, OF_WINDOW);
    ofRunApp(new ofApp);
    return 0;
}
