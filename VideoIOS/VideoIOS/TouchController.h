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

#import <UIKit/UIKit.h>
#include "render/inputSystem/Input.h"
#include "render/globalData/GlobalData.h"
#include "render/log/Log.h"

@interface TouchController : UIView
-(void)dispatchTouchEvent:(CGPoint)position;
@end

@implementation TouchController

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint position;
    
    for (UITouch *touch in touches) {
        position = [touch locationInView:self];
        if(GlobalData::getInstance()->screenMode == GlobalData::HORIZONTAL_SCREEN){
            float aux = position.x;
            position.x = position.y;
            position.y = aux;
        }else{
            position.y = (float)GlobalData::getInstance()->screenHeight - position.y;
        }
        Input::getInstance()->newEvent(position.x, position.y);
        [self dispatchTouchEvent:position];
	}
}
-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint position, lastPosition;
    
    for (UITouch *touch in touches) {
        position = [touch locationInView:self];
        lastPosition = [touch previousLocationInView:self];
        if(GlobalData::getInstance()->screenMode == GlobalData::HORIZONTAL_SCREEN){
            float aux = position.x;
            position.x = position.y;
            position.y = aux;
            aux = lastPosition.x;
            lastPosition.x = lastPosition.y;
            lastPosition.y = aux;
        }else{
            position.y = (float)GlobalData::getInstance()->screenHeight - position.y;
            lastPosition.y = (float)GlobalData::getInstance()->screenHeight - lastPosition.y;
        }
        [self dispatchTouchEvent:lastPosition];
        [self dispatchTouchEvent:position];
        if(!Input::getInstance()->updateEvent(lastPosition.x, lastPosition.y, position.x, position.y))
            logErr("touch moved update event failed");
	}
}
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    CGPoint position, lastPosition;
    
    for (UITouch *touch in touches) {
        position = [touch locationInView:self];
        lastPosition = [touch previousLocationInView:self];
        if(GlobalData::getInstance()->screenMode == GlobalData::HORIZONTAL_SCREEN){
            float aux = position.x;
            position.x = position.y;
            position.y = aux;
            aux = lastPosition.x;
            lastPosition.x = lastPosition.y;
            lastPosition.y = aux;
        }else{
            position.y = (float)GlobalData::getInstance()->screenHeight - position.y;
            lastPosition.y = (float)GlobalData::getInstance()->screenHeight - lastPosition.y;
        }
        [self dispatchTouchEvent:position];
        if(!Input::getInstance()->updateEventToEnd(position.x, position.y))
            if(!Input::getInstance()->updateEventToEnd(lastPosition.x, lastPosition.y))
                logErr("touch ended update event failed");
	}
}
-(void)dispatchTouchEvent:(CGPoint)position
{
    //logInf("dispatchTouchEvent x: %f y: %f",position.x, position.y);
}
@end
