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
#import "ViewController.h"

#include "iOSUtils.h"
#include "render/fileSystem/FileSystem.h"
#include "render/globalData/GlobalData.h"
#include "render/controllerEGL/ContextControllerEAGL.h"
#include "render/scene/BasicSceneManager.h"
#include "render/scene/Node.h"
#include "render/sceneObjects/mesh/Mesh.h"
#include "render/sceneObjects/mesh/MeshManager.h"
#include "render/sceneObjects/camera/Camera.h"
#include "render/globalData/GlobalData.h"


#include "render/texture/TextureManager.h"
#include "render/utils/Timer.h"
#include "render/GUI/Rect.h"
#include "render/GUI/TextManager.h"

#include "logic/SceneSystem/SceneStateMachine.h"
#include "logic/SceneSystem/Scenes/VideoScene.h"

SceneStateMachine* ssm;

//BasicSceneManager* scene = 0;
//Node* cameraParentNode = 0;

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    TextureManager::freeInstance();
    MeshManager::freeInstance();
    GlobalData::getInstance()->screenMode = GlobalData::HORIZONTAL_SCREEN;
    GLKView *view = (GLKView *)self.view;
    GlobalData::getInstance()->iOSPath = iOSUtils::getiOSPath();

    ContextControllerEAGL::getInstance()->startDisplay(view);
    
    logInf("creating new instance of scene manager");
    GlobalData::getInstance()->scene = new BasicSceneManager();
    
    ssm = new SceneStateMachine(new VideoScene());
}

- (void)dealloc
{
    if(GlobalData::getInstance()->scene != 0)
        delete GlobalData::getInstance()->scene;
    GlobalData::getInstance()->scene = 0;
    TextureManager::freeInstance();
    MeshManager::freeInstance();
    TextManager::freeInstance();
    ContextControllerEAGL::getInstance()->endDisplay();

    delete ssm;
    ssm = 0;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if(GlobalData::getInstance()->scene != 0)
        delete GlobalData::getInstance()->scene;
    GlobalData::getInstance()->scene = 0;
    TextureManager::freeInstance();
    TextManager::freeInstance();
    MeshManager::freeInstance();
    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        ContextControllerEAGL::getInstance()->endDisplay();
    }
    
    delete ssm;
    ssm = 0;
    // Dispose of any resources that can be recreated.
}


- (void)update
{
    Timer::getInstance()->calculeCurrentTime();
    GlobalData::getInstance()->scene->updateVariables();
    GlobalData::getInstance()->scene->createShadowMap();
    ssm->updateMachine();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    GlobalData::getInstance()->scene->cleanBuffers();
    GlobalData::getInstance()->scene->render();
    GlobalData::getInstance()->scene->renderBackground();//to avoid so much fragment shader executions but maybe will cause problems with alpha objects...
    GlobalData::getInstance()->scene->renderGUI();
}
@end