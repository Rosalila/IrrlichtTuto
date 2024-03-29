#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Painter.h"
#include "Input.h"

using namespace std;

class Entity
{
public:
    InputReceiver*receiver;
    Painter*painter;
    Entity(){}
    virtual void draw()=0;
    virtual void logic()=0;
};

class EntityChar:Entity
{
public:
    int pos_x;
    int pos_y;
    int scale;
    int current_image;
    int elapsed_time;
    bool is_flying;
    stringw orientation;
    vector<irr::video::ITexture*>up;
    vector<irr::video::ITexture*>down;
    vector<irr::video::ITexture*>left;
    vector<irr::video::ITexture*>right;
    vector<irr::video::ITexture*>fly;
    EntityChar(int pos_x,int pos_y,int scale,
               vector<stringw>up,vector<stringw>down,vector<stringw>left,vector<stringw>right,vector<stringw>fly,
               Painter*painter,InputReceiver*receiver)
    {
        this->is_flying=false;
        this->orientation="down";
        this->current_image=0;
        this->elapsed_time=0;
        this->pos_x=pos_x;
        this->pos_y=pos_y;
        this->scale=scale;
        this->painter=painter;
        this->receiver=receiver;
        for(int i=0;i<(int)up.size();i++)
            this->up.push_back(painter->getTexture(up[i]));
        for(int i=0;i<(int)down.size();i++)
            this->down.push_back(painter->getTexture(down[i]));
        for(int i=0;i<(int)left.size();i++)
            this->left.push_back(painter->getTexture(left[i]));
        for(int i=0;i<(int)right.size();i++)
            this->right.push_back(painter->getTexture(right[i]));
        for(int i=0;i<(int)fly.size();i++)
            this->fly.push_back(painter->getTexture(fly[i]));
    }

    void draw()
    {
        irr::video::ITexture*image;
        if(orientation=="up")
            image=up[current_image];
        if(orientation=="down")
            image=down[current_image];
        if(orientation=="left")
            image=left[current_image];
        if(orientation=="right")
            image=right[current_image];
        if(is_flying)
            image=fly[current_image];
        painter->draw2DImage
        (   image,
            irr::core::dimension2d<irr::f32> (image->getOriginalSize().Width,image->getOriginalSize().Height), //tamaño de la imagen
            irr::core::rect<irr::f32>(0,0,image->getOriginalSize().Width,image->getOriginalSize().Height), //Rectangulo de recorte de imagen
            irr::core::position2d<irr::f32>(pos_x,pos_y), //Posicion x y en la pantalla
            irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
            irr::f32(0),//rotacion
            irr::core::vector2df (scale,scale), //escala x y
            true,// Acepta canal alpha (transparencia del color)
            irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
            false,//Flip horizontal
            false);//Flip vertical
    }

    void logic()
    {
        if(rand()%4==0)
        {
            orientation="down";
            pos_y++;
        }
        if(rand()%4==1)
        {
            orientation="up";
            pos_y--;
        }
        if(rand()%4==2)
        {
            orientation="right";
            pos_x++;
        }
        if(rand()%4==3)
        {
            orientation="left";
            pos_x--;
        }


        if(receiver->IsKeyDown(irr::KEY_DOWN))
        {
            orientation="down";
            pos_y++;
        }
        if(receiver->IsKeyDown(irr::KEY_UP))
        {
            orientation="up";
            pos_y--;
        }
        if(receiver->IsKeyDown(irr::KEY_RIGHT))
        {
            orientation="right";
            pos_x++;
        }
        if(receiver->IsKeyDown(irr::KEY_LEFT))
        {
            orientation="left";
            pos_x--;
        }
        if(receiver->IsKeyDown(irr::KEY_KEY_F))
        {
            is_flying=true;
        }else
        {
            is_flying=false;
        }

        elapsed_time++;
        if(elapsed_time<30)
            return;
        elapsed_time=0;
        current_image++;
        if(current_image>=(int)up.size() && orientation=="up")
            current_image=0;
        if(current_image>=(int)down.size() && orientation=="down")
            current_image=0;
        if(current_image>=(int)left.size() && orientation=="left")
            current_image=0;
        if(current_image>=(int)right.size() && orientation=="right")
            current_image=0;
        if(current_image>=(int)fly.size() && is_flying)
            current_image=0;
    }

};


class EntityChuy:Entity
{
public:
    int pos_x;
    int pos_y;
    int current_image;
    int elapsed_time;
    bool is_flying;
    stringw orientation;
    vector<irr::video::ITexture*>up;
    vector<irr::video::ITexture*>down;
    vector<irr::video::ITexture*>left;
    vector<irr::video::ITexture*>right;
    vector<irr::video::ITexture*>fly;
    EntityChuy(int pos_x,int  pos_y,
               vector<stringw>up,vector<stringw>down,vector<stringw>left,vector<stringw>right,vector<stringw>fly,
               Painter*painter,InputReceiver*receiver)
    {
        this->is_flying=false;
        this->orientation="down";
        this->current_image=0;
        this->elapsed_time=0;
        this->pos_x=pos_x;
        this->pos_y=pos_y;
        this->painter=painter;
        this->receiver=receiver;
        for(int i=0;i<(int)up.size();i++)
            this->up.push_back(painter->getTexture(up[i]));
        for(int i=0;i<(int)down.size();i++)
            this->down.push_back(painter->getTexture(down[i]));
        for(int i=0;i<(int)left.size();i++)
            this->left.push_back(painter->getTexture(left[i]));
        for(int i=0;i<(int)right.size();i++)
            this->right.push_back(painter->getTexture(right[i]));
        for(int i=0;i<(int)fly.size();i++)
            this->fly.push_back(painter->getTexture(fly[i]));
    }

    void draw()
    {
        irr::video::ITexture*image;
        if(is_flying)
        {
            image=fly[current_image];
        }else
        {
            if(orientation=="up")
                image=up[current_image];
            if(orientation=="down")
                image=down[current_image];
            if(orientation=="left")
                image=left[current_image];
            if(orientation=="right")
                image=right[current_image];
        }

        painter->draw2DImage
        (   image,
            irr::core::dimension2d<irr::f32> (image->getOriginalSize().Width,image->getOriginalSize().Height), //tamaño de la imagen
            irr::core::rect<irr::f32>(0,0,image->getOriginalSize().Width,image->getOriginalSize().Height), //Rectangulo de recorte de imagen
            irr::core::position2d<irr::f32>(pos_x,pos_y), //Posicion x y en la pantalla
            irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
            irr::f32(0),//rotacion
            irr::core::vector2df (1,1), //escala x y
            true,// Acepta canal alpha (transparencia del color)
            irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
            false,//Flip horizontal
            false);//Flip vertical
    }

    void logic()
    {
        if(receiver->IsKeyDown(irr::KEY_DOWN))
        {
            orientation="down";
            pos_y+=4;
        }
        if(receiver->IsKeyDown(irr::KEY_UP))
        {
            orientation="up";
            pos_y-=4;
        }
        if(receiver->IsKeyDown(irr::KEY_RIGHT))
        {
            orientation="right";
            pos_x+=4;
        }
        if(receiver->IsKeyDown(irr::KEY_LEFT))
        {
            orientation="left";
            pos_x-=4;
        }

        elapsed_time++;
        if(elapsed_time<10)
            return;
        elapsed_time=0;
        current_image++;

        if(receiver->IsKeyDown(irr::KEY_KEY_F))
        {
            is_flying=true;
        }else
        {
            is_flying=false;
        }

        if(is_flying)
        {
            if(current_image>=(int)fly.size())
            {
                current_image=2;
            }
        }else
        {
            if(current_image>=(int)up.size() && orientation=="up")
                current_image=0;
            if(current_image>=(int)down.size() && orientation=="down")
                current_image=0;
            if(current_image>=(int)left.size() && orientation=="left")
                current_image=0;
            if(current_image>=(int)right.size() && orientation=="right")
                current_image=0;
        }
    }

};

class EntityArbol:Entity
{
public:
    int pos_x;
    int pos_y;
    int current_image;
    int elapsed_time;
    vector<irr::video::ITexture*>images;
    EntityArbol(int pos_x,int  pos_y,vector<stringw>image_files,Painter*painter,InputReceiver*receiver)
    {
        this->pos_x=pos_x;
        this->pos_y=pos_y;
        this->painter=painter;
        this->receiver=receiver;
        for(int i=0;i<(int)image_files.size();i++)
            images.push_back(painter->getTexture(image_files[i]));
        this->current_image=0;
        this->elapsed_time=0;
    }

    void draw()
    {
        irr::video::ITexture*image=images[current_image];
        painter->draw2DImage
        (   image,
            irr::core::dimension2d<irr::f32> (image->getOriginalSize().Width,image->getOriginalSize().Height), //tamaño de la imagen
            irr::core::rect<irr::f32>(0,0,image->getOriginalSize().Width,image->getOriginalSize().Height), //Rectangulo de recorte de imagen
            irr::core::position2d<irr::f32>(pos_x,pos_y), //Posicion x y en la pantalla
            irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
            irr::f32(0),//rotacion
            irr::core::vector2df (3,3), //escala x y
            true,// Acepta canal alpha (transparencia del color)
            irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
            false,//Flip horizontal
            false);//Flip vertical
    }

    void logic()
    {
        elapsed_time++;
        if(elapsed_time<20)
            return;
        elapsed_time=0;

        current_image++;
        if(current_image>=(int)images.size())
            current_image=0;
    }
};

class EntityBackground:Entity
{
public:
    irr::video::ITexture*image;
    EntityBackground(stringw image_file,Painter*painter,InputReceiver*receiver)
    {
        this->painter=painter;
        this->receiver=receiver;
        this->image=painter->getTexture(image_file);
    }

    void draw()
    {
        painter->draw2DImage
        (   image,
            irr::core::dimension2d<irr::f32> (image->getOriginalSize().Width,image->getOriginalSize().Height), //tamaño de la imagen
            irr::core::rect<irr::f32>(0,0,image->getOriginalSize().Width,image->getOriginalSize().Height), //Rectangulo de recorte de imagen
            irr::core::position2d<irr::f32>(0,0), //Posicion x y en la pantalla
            irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
            irr::f32(0),//rotacion
            irr::core::vector2df (1,1), //escala x y
            true,// Acepta canal alpha (transparencia del color)
            irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
            false,//Flip horizontal
            false);//Flip vertical
    }

    void logic()
    {
    }
};
