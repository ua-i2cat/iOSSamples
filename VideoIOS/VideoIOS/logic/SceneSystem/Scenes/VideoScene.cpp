/*
 *  thin render - Mobile render engine based on OpenGL ES 2.0
 *  Copyright (C) 2013  Fundació i2CAT, Internet i Innovació digital a Catalunya
 *
 *  This file is part of thin render.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author:         Marc Fernandez Vanaclocha <marc.fernandez@i2cat.net>
 */

#include "VideoScene.h"
#include "../../../render/GUI/Rect.h"
#include "../../../render/GUI/TextManager.h"
#include "../../../render/inputSystem/Input.h"
#include <vector>

VideoScene::VideoScene(){
    stateName = "VideoScene";
    GlobalData::getInstance()->scene->closeScene();
    TextureManager::freeInstance();
    MeshManager::freeInstance();
    TextManager::freeInstance();
    FileSystem::freeInstance();
    Input::getInstance()->clearEvents();

    
    float w = GlobalData::getInstance()->screenWidth;
    float h = GlobalData::getInstance()->screenHeight;
    float proportionText = h/1280.0f;
    
    RectGUI* rect = GlobalData::getInstance()->scene->createRectangleGUI(0.0f, h, w, h);
    startVideo();
    rect->setShader(new VideoPlaneShader());
    rect->setTexture(TextureManager::getInstance()->getTexture("XAxisButton.png"));//current trick to get a Texture class inside the rect...
    
    
    playButton = GlobalData::getInstance()->scene->createRectangleGUI(w*(0.5f-0.125f), w*0.125f , w*0.1f, 0.1f*w);
    playButton->setTexture(TextureManager::getInstance()->getTexture("XAxisButton.png"));
    playButton->setText("PLAY", "FreeSans.ttf", proportionText*24);
    playButton->setEnabled(false);
    playButton->setClickable(true);
    
    pauseButton = GlobalData::getInstance()->scene->createRectangleGUI(w*(0.5f-0.125f), w*0.125f , w*0.1f, 0.1f*w);
    pauseButton->setTexture(TextureManager::getInstance()->getTexture("XAxisButton.png"));
    pauseButton->setText("PAUSE", "FreeSans.ttf", proportionText*24);
    pauseButton->setClickable(true);
    
    stopButton = GlobalData::getInstance()->scene->createRectangleGUI(w*(0.5f+0.025f), w*0.125f , w*0.1f, 0.1f*w);
    stopButton->setTexture(TextureManager::getInstance()->getTexture("XAxisButton.png"));
    stopButton->setText("STOP", "FreeSans.ttf", proportionText*24);
    stopButton->setClickable(true);
}

VideoScene::~VideoScene(){
    
}

int VideoScene::update(SceneStateMachine *machine){
    std::vector<event> events = Input::getInstance()->getEventsNotLooked();
    if(events.size() == 0  || events.at(0).state != Input::BEGIN_INPUT) return NOTHING;
    
    RectGUI* rect = GlobalData::getInstance()->scene->getRectTouch(events.at(0).x, events.at(0).y);
    if(rect == playButton){
        playAction();
        playButton->setEnabled(false);
        pauseButton->setEnabled(true);
    }else if(rect == pauseButton){
        if(pauseAction()){
            playButton->setEnabled(true);
            pauseButton->setEnabled(false);
        }
    }else if(rect == stopButton){
        stopAction();
        playButton->setEnabled(true);
        pauseButton->setEnabled(false);
    }
    return NOTHING;
}
