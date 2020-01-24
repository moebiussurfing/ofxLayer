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
        layerPtr = _layer;
    }

    void setName(string _name)
    {
        name =_name;
        setup();
    }

    ofParameter<string> name{"name","name"};
    ofParameter<bool> enable{"enable", false};
    ofParameter<float> alpha{"alpha", 1.0f, 0.0f, 1.0f};
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
                layerPtr->setAlpha(enable?1.0f:0.0f);
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
        else if (name == "enableBg")
        {

        }
        else if (name == "bgColor")
        {

        }else if (name == "pos")
        {

        }
    }

    MyLayer()
    {
//        params.setName("settings");
        params.add(name);
        params.add(enable);
        params.add(alpha);
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
        path = "path.xml";
        load_GroupSettings(params, path);
    }
    void save(string path)
    {
//        save_GroupSettings(params, path);
        save_GroupSettings(params, "path.xml");
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


class TestLayer1 : public ofxLayer::Layer
{
public:

    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer1);

    ofImage img;
    int x, y;

    MyLayer myLayer;

    void setup()
    {
        x = 100;
        y = 100;
        img.load("images/bikers.jpg");

    }
    void update()
    {
        int a = ofMap(myLayer.bgAlpha,0,1,0,255);
        ofColor c = myLayer.bgColor.get();
        ofBackground(c.r, c.g, c.b, a);
    }

    void draw()
    {
        ofSetColor(255);
        img.draw(x, y);
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
    int x, y;

    MyLayer myLayer;

    void setup()
    {
        x = 100;
        y = 100;
        img.load("images/tdf_1972_poster.jpg");
    }

    void update()
    {
        int a = ofMap(myLayer.bgAlpha,0,1,0,255);
        ofColor c = myLayer.bgColor.get();
        ofBackground(c.r, c.g, c.b, a);
    }

    void draw()
    {
        ofSetColor(255);
        img.draw(x, y);
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
    int x, y;

    MyLayer myLayer;

    void setup()
    {
        MyLayer myLayer;

        x = 100;
        y = 100;
        img.load("images/gears.gif");
    }

    void update()
    {
        int a = ofMap(myLayer.bgAlpha,0,1,0,255);
        ofColor c = myLayer.bgColor.get();
        ofBackground(c.r, c.g, c.b, a);
    }

    void draw()
    {
        ofSetColor(255);
        img.draw(x, y);
    }

    ~TestLayer3()
    {
        cout <<"~TestLayer3()"<<endl;
    }
};

TestLayer1 *layer1;
TestLayer2 *layer2;
TestLayer3 *layer3;

ofxLayer::Manager mng;


//bool b1 = false;
//bool b2 = false;
//bool b3 = false;
//int  last = 0;

ofxPanel gui;

class ofApp : public ofBaseApp
{
public:
    void setup()
    {
        ofSetLogLevel(OF_LOG_VERBOSE);

//        b1 = false;
//        b2 = false;
//        b3 = false;
//        last = 0;

        ofSetFrameRate(30);
        //ofSetVerticalSync(true);
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

        //        int t1 = ofGetFrameNum()%30;
        //        int t2 = ofGetFrameNum()%70;
        //        int t3 = ofGetFrameNum()%100;
        //        int i;

        // layer3->setAlpha(ofMap(ofGetMouseY(), 0, 900, 0.0f, 1.0f));


        //if (t2 == 0)
        //{
        //    ofBlendMode bl = layer2->getBlendMode();
        //    i = (int)bl;
        //    i++;
        //    i = i % 6;
        //    cout <<"i:"<<i<<"  bl:"<<ofBlendMode(i)<<endl;
        //    layer3->setBlendMode(ofBlendMode(i));
        //}

        //layer2->setAlpha(t3/70.f);
        //layer2->x +=1;
        //if(layer2->x >= 1280-layer2->img.getWidth())
        //    layer2->x = 0;

        //layer3->setAlpha(t3/90.0);
        //layer3->setBlendMode(ofBlendMode(i));
    }

    void draw()
    {
        ofEnableAlphaBlending();
        mng.draw();

        //        ofDrawBitmapStringHighlight(ofToString(last), 0, 10);
        //        ofDrawBitmapStringHighlight(ofToString(last), 0, 20);

        gui.draw();
    }

    void keyPressed(int key)
    {
//        //hide any layer
//        if (key == 'z')
//        {
//            b1 = !b1;
//            if (b1)
//                layer1->setAlpha(1);
//            else
//                layer1->setAlpha(0);
//
//            cout <<"b1:"<<b1<<endl;
//            last = 1;
//        }
//        if (key == 'x')
//        {
//            b2 = !b2;
//            if (b2)
//                layer2->setAlpha(1);
//            else
//                layer2->setAlpha(0);
//
//            cout <<"b2:"<<b2<<endl;
//            last = 2;
//        }
//        if (key == 'c')
//        {
//            b3 = !b3;
//            if (b3)
//                layer3->setAlpha(1);
//            else
//                layer3->setAlpha(0);
//
//            cout <<"b3:"<<b3<<endl;
//            last = 3;
//        }
//
//        //browse layers
//        if (key == OF_KEY_LEFT)
//        {
//            last--;
//            if (last<1) last = 1;
//        }
//        if (key == OF_KEY_RIGHT)
//        {
//            last++;
//            if (last>3) last = 3;
//        }
//
//        //alpha tune
//        if (key == OF_KEY_UP)
//        {
//            float a;
//
//            if (last == 1)
//                a = layer1->getAlpha();
//            if (last == 2)
//                a = layer2->getAlpha();
//            if (last == 3)
//                a = layer3->getAlpha();
//
//            cout << "a"<<last<<":"<<a<<endl;
//            a = a + 0.1f;
//            if (a>1.0) a = 1.0;
//            cout << ">a"<<last<<":"<<a<<endl;
//
//            if (last == 1)
//                layer1->setAlpha(a);
//            if (last == 2)
//                layer2->setAlpha(a);
//            if (last == 3)
//                layer3->setAlpha(a);
//        }
//
//        if (key == OF_KEY_DOWN)
//        {
//            float a;
//
//            if (last == 1)
//                a = layer1->getAlpha();
//            if (last == 2)
//                a = layer2->getAlpha();
//            if (last == 3)
//                a = layer3->getAlpha();
//
//            cout << "a"<<last<<":"<<a<<endl;
//            a = a - 0.1f;
//            if (a<0.0) a = 0.0;
//            cout << ">a"<<last<<":"<<a<<endl;
//
//            if (last == 1)
//                layer1->setAlpha(a);
//            if (last == 2)
//                layer2->setAlpha(a);
//            if (last == 3)
//                layer3->setAlpha(a);
//        }
//
//        //sorting
//        if (last == 1)
//        {
//            if (key == '1') layer1->moveUp();
//            if (key == '2') layer1->moveDown();
//            if (key == '3') layer1->moveFront();
//            if (key == '4') layer1->moveBack();
//        }
//        if (last == 2)
//        {
//            if (key == '1') layer2->moveUp();
//            if (key == '2') layer2->moveDown();
//            if (key == '3') layer2->moveFront();
//            if (key == '4') layer2->moveBack();
//        }
//        if (last == 3)
//        {
//            if (key == '1') layer3->moveUp();
//            if (key == '2') layer3->moveDown();
//            if (key == '3') layer3->moveFront();
//            if (key == '4') layer3->moveBack();
//        }
//
//        //OF_BLENDMODE_DISABLED = 0,
//        ///// \brief Blend mode used for alpha blending.
//        //OF_BLENDMODE_ALPHA       = 1,
//        ///// \brief Blend mode used for additive blending.
//        //OF_BLENDMODE_ADD       = 2,
//        ///// \brief Blend mode used for subtractive blending.
//        //OF_BLENDMODE_SUBTRACT = 3,
//        ///// \brief Blend mode used for multiplicative blending.
//        //OF_BLENDMODE_MULTIPLY = 4,
//        ///// \brief Blend mode used for screen blending.
//        //OF_BLENDMODE_SCREEN   = 5
//
//        //blend mode
//        if (key == ' ')
//        {
//            int bl_1;
//            int bl_2;
//            int bl_3;
//
//            if (last == 1)
//            {
//                bl_1 = layer1->getBlendMode();
//                bl_1++;
//                if (bl_1>4)
//                    bl_1 = 0;
//
//                switch (bl_1) {
//                    case 0:
//                        layer1->setBlendMode(OF_BLENDMODE_DISABLED);
//                        cout <<"1_OF_BLENDMODE_DISABLED"<<endl;
//                        break;
//                    case 1:
//                        layer1->setBlendMode(OF_BLENDMODE_ALPHA);
//                        cout <<"1_OF_BLENDMODE_ALPHA"<<endl;
//                        break;
//                    case 2:
//                        layer1->setBlendMode(OF_BLENDMODE_ADD);
//                        cout <<"1_OF_BLENDMODE_ADD"<<endl;
//                        break;
//                    case 3:
//                        layer1->setBlendMode(OF_BLENDMODE_SUBTRACT);
//                        cout <<"1_OF_BLENDMODE_SUBTRACT"<<endl;
//                        break;
//                    case 4:
//                        layer1->setBlendMode(OF_BLENDMODE_MULTIPLY);
//                        cout <<"1_OF_BLENDMODE_MULTIPLY"<<endl;
//                        break;
//                    case 5:
//                        layer1->setBlendMode(OF_BLENDMODE_SCREEN);
//                        cout <<"1_OF_BLENDMODE_SCREEN"<<endl;
//                        break;
//                }
//            }
//            if (last == 2)
//            {
//                bl_2 = layer2->getBlendMode();
//                bl_2++;
//                if (bl_2>4)
//                    bl_2 = 0;
//
//                switch (bl_2) {
//                    case 0:
//                        layer2->setBlendMode(OF_BLENDMODE_DISABLED);
//                        cout <<"2_OF_BLENDMODE_DISABLED"<<endl;
//                        break;
//                    case 1:
//                        layer2->setBlendMode(OF_BLENDMODE_ALPHA);
//                        cout <<"2_OF_BLENDMODE_ALPHA"<<endl;
//                        break;
//                    case 2:
//                        layer2->setBlendMode(OF_BLENDMODE_ADD);
//                        cout <<"2_OF_BLENDMODE_ADD"<<endl;
//                        break;
//                    case 3:
//                        layer2->setBlendMode(OF_BLENDMODE_SUBTRACT);
//                        cout <<"2_OF_BLENDMODE_SUBTRACT"<<endl;
//                        break;
//                    case 4:
//                        layer2->setBlendMode(OF_BLENDMODE_MULTIPLY);
//                        cout <<"2_OF_BLENDMODE_MULTIPLY"<<endl;
//                        break;
//                    case 5:
//                        layer2->setBlendMode(OF_BLENDMODE_SCREEN);
//                        cout <<"2_OF_BLENDMODE_SCREEN"<<endl;
//                        break;
//                }
//            }
//            if (last == 3)
//            {
//                bl_3 = layer3->getBlendMode();
//                bl_3++;
//                if (bl_3>4)
//                    bl_3 = 0;
//
//                switch (bl_3) {
//                    case 0:
//                        layer3->setBlendMode(OF_BLENDMODE_DISABLED);
//                        cout <<"3_OF_BLENDMODE_DISABLED"<<endl;
//                        break;
//                    case 1:
//                        layer3->setBlendMode(OF_BLENDMODE_ALPHA);
//                        cout <<"3_OF_BLENDMODE_ALPHA"<<endl;
//                        break;
//                    case 2:
//                        layer3->setBlendMode(OF_BLENDMODE_ADD);
//                        cout <<"3_OF_BLENDMODE_ADD"<<endl;
//                        break;
//                    case 3:
//                        layer3->setBlendMode(OF_BLENDMODE_SUBTRACT);
//                        cout <<"3_OF_BLENDMODE_SUBTRACT"<<endl;
//                        break;
//                    case 4:
//                        layer3->setBlendMode(OF_BLENDMODE_MULTIPLY);
//                        cout <<"3_OF_BLENDMODE_MULTIPLY"<<endl;
//                        break;
//                    case 5:
//                        layer3->setBlendMode(OF_BLENDMODE_SCREEN);
//                        cout <<"3_OF_BLENDMODE_SCREEN"<<endl;
//                        break;
//                }
//            }
//        }
    }

    void keyReleased(int key)
    {
    }

    void mouseMoved(int x, int y)
    {
//        switch (last) {
//            case 1:
//                layer1->x=x;
//                layer1->y=y;
//                break;
//            case 2:
//                layer2->x=x;
//                layer2->y=y;
//                break;
//            case 3:
//                layer3->x=x;
//                layer3->y=y;
//                break;
//        }
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
