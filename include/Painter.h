#ifndef PAINTER_H
#define PAINTER_H

#include <stdlib.h>	// for itoa() call
#include <irrlicht.h>
using namespace irr;
#include "Input.h"


class Painter
{
    video::IVideoDriver* driver;
    gui::IGUIFont* font;

    public:
    int ventana_x,ventana_y;
    IrrlichtDevice *device;
    Painter(InputReceiver* receiver);
    bool isWindowActive();
    void beginScene();
    void endScene();
    bool run();
    irr::video::ITexture* getTexture(irr::core::stringw archivo);
    void drawText(core::stringw texto,core::rect<s32> posicion,video::SColor color);
    void draw2DRectangle(irr::video::SColor color,core::rect<s32> posicion);
    void draw2DImage	(
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation , irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color ,
				 bool flipHorizontally,
				 bool flipVertically 	);
};


#endif // Painter_H
