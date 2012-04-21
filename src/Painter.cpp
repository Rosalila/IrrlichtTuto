#include "../include/Painter.h"

Painter::Painter(InputReceiver* receiver)
{
    ventana_x=1024;
    ventana_y=600;
    video::E_DRIVER_TYPE driverType;
    driverType = video::EDT_OPENGL;
    //driverType = video::EDT_SOFTWARE;
    device = createDevice(driverType,core::dimension2d<u32>(ventana_x,ventana_y),true ,false, false, false,receiver);
    if (device == 0)
        return; // could not create selected driver.
    core::array<SJoystickInfo> joystickInfo;
    device->activateJoysticks(joystickInfo);
    device->setWindowCaption(L"Fighter");
    driver = device->getVideoDriver();

    //init fonts
    font = device->getGUIEnvironment()->getFont("menu/font.png");
}

bool Painter::isWindowActive()
{
    return device->isWindowActive();
}

void Painter::beginScene()
{
    driver->beginScene(true, true, video::SColor(255,255,255,255));
}

void Painter::endScene()
{
    //FPS
    int lastFPS=-1;
    int fps = driver->getFPS();
    if (lastFPS != fps)
    {
        core::stringw str = L"Rosalila Fighter  [";
        str += driver->getName();
        str += "] FPSS:";
        str += fps;
        str += " ";
        str += driver->getCurrentRenderTargetSize().Width;
        str += ",";
        str += driver->getCurrentRenderTargetSize().Height;
        str += "  ==>  ";
        str += (float)ventana_y/(float)driver->getCurrentRenderTargetSize().Height;
        device->setWindowCaption(str.c_str());
        lastFPS = fps;
    }
    driver->endScene();
}

bool Painter::run()
{
    return device->run() && driver;
}

irr::video::ITexture* Painter::getTexture(irr::core::stringw archivo)
{
    return driver->getTexture(irr::io::path(archivo));
}

void Painter::drawText(core::stringw texto,core::rect<s32> posicion,video::SColor color)
{
    font->draw(texto,posicion,color);
}

void Painter::draw2DRectangle(irr::video::SColor color,core::rect<s32> posicion)
{
    float escala_x=(float)driver->getCurrentRenderTargetSize().Width/(float)ventana_x;
    float escala_y=(float)driver->getCurrentRenderTargetSize().Height/(float)ventana_y;
    posicion=core::rect<s32>(posicion.UpperLeftCorner.X*escala_x,posicion.UpperLeftCorner.Y*escala_y,posicion.LowerRightCorner.X*escala_x,posicion.LowerRightCorner.Y*escala_y);
    driver->draw2DRectangle(color,posicion);
}

void Painter::draw2DImage
                (
	             irr::video::ITexture* texture,
				 irr::core::dimension2d<irr::f32> size,
				 irr::core::rect<irr::f32> sourceRect,
				 irr::core::position2d<irr::f32> position,
				 irr::core::position2d<irr::f32> rotationPoint,
				 irr::f32 rotation , irr::core::vector2df scale,
				 bool useAlphaChannel,
				 irr::video::SColor color ,
				 bool flipHorizontally,
				 bool flipVertically 	)
{
   //inicio escala

   float escala_x,escala_y;
   if(scale.X!=0 && scale.Y!=0)
   {
       escala_x=(float)(driver->getCurrentRenderTargetSize().Width/(float)ventana_x)*scale.X;
       escala_y=(float)(driver->getCurrentRenderTargetSize().Height/(float)ventana_y)*scale.Y;
   }else
   {
       escala_x=(float)driver->getCurrentRenderTargetSize().Width/(float)ventana_x;
       escala_y=(float)driver->getCurrentRenderTargetSize().Height/(float)ventana_y;
   }

   scale=irr::core::vector2df (escala_x,escala_y);

   //fin escala
   if(!texture)
	   return;

   irr::video::SMaterial material;

   irr::core::vector2df corner[4];

   corner[0] = irr::core::vector2df(position.X,position.Y);
   corner[1] = irr::core::vector2df(position.X+size.Width*scale.X,position.Y);
   corner[2] = irr::core::vector2df(position.X,position.Y+size.Height*scale.Y);
   corner[3] = irr::core::vector2df(position.X+size.Width*scale.X,position.Y+size.Height*scale.Y);


   if (rotation != 0.0f)
      for (int x = 0; x < 4; x++)
         corner[x].rotateBy(rotation,irr::core::vector2df(rotationPoint.X, rotationPoint.Y));


   //TODO: ver como mejorar esto
   irr::core::vector2df uvCorner[4];

   if(!flipVertically && !flipHorizontally)
   {
	   uvCorner[0] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[1] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[2] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[3] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }
   else if(!flipVertically && flipHorizontally)
   {
	   uvCorner[1] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[0] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[3] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[2] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }
   else if(flipVertically && !flipHorizontally)
   {
	   uvCorner[2] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[3] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[0] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[1] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }
   else
   {
	   uvCorner[3] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[2] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.UpperLeftCorner.Y);
	   uvCorner[1] = irr::core::vector2df(sourceRect.UpperLeftCorner.X,sourceRect.LowerRightCorner.Y);
	   uvCorner[0] = irr::core::vector2df(sourceRect.LowerRightCorner.X,sourceRect.LowerRightCorner.Y);
   }


   for (int x = 0; x < 4; x++) {
      float uvX = uvCorner[x].X/(float)texture->getSize().Width;
      float uvY = uvCorner[x].Y/(float)texture->getSize().Height;
      uvCorner[x] = irr::core::vector2df(uvX,uvY);
   }


   irr::video::S3DVertex vertices[4];
   irr::u16 indices[6] = { 0, 1, 2, 3 ,2 ,1 };


   float screenWidth = (float)driver->getScreenSize().Width;
   float screenHeight = (float)driver->getScreenSize().Height;
   for (int x = 0; x < 4; x++) {
      float screenPosX = ((corner[x].X/screenWidth)-0.5f)*2.0f;
      float screenPosY = ((corner[x].Y/screenHeight)-0.5f)*-2.0f;
      vertices[x].Pos = irr::core::vector3df(screenPosX,screenPosY,1);
      vertices[x].TCoords = uvCorner[x];
      vertices[x].Color = color;
   }
   material.Lighting = false;
   material.ZWriteEnable = false;
   material.TextureLayer[0].Texture = texture;

   if (useAlphaChannel)
      material.MaterialType = irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL;
   else
      material.MaterialType = irr::video::EMT_SOLID;


   driver->setMaterial(material);
   driver->drawIndexedTriangleList(&vertices[0],4,&indices[0],2);
   //driver->drawPixel(100,100,color);
}
