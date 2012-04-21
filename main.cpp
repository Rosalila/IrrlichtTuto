#include <iostream>
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

class EntityChuy:Entity
{
public:
    int pos_x;
    int pos_y;
    int current_image;
    int elapsed_time;
    stringw orientation;
    vector<irr::video::ITexture*>up;
    vector<irr::video::ITexture*>down;
    vector<irr::video::ITexture*>left;
    vector<irr::video::ITexture*>right;
    EntityChuy(int pos_x,int  pos_y,
               vector<stringw>up,vector<stringw>down,vector<stringw>left,vector<stringw>right,
               Painter*painter,InputReceiver*receiver)
    {
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
            irr::core::vector2df (1,1), //escala x y
            true,// Acepta canal alpha (transparencia del color)
            irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
            false,//Flip horizontal
            false);//Flip vertical
    }

    void logic()
    {
        elapsed_time++;
        if(elapsed_time<50)
            return;
        elapsed_time=0;

        current_image++;
        if(current_image>=(int)images.size())
            current_image=0;
    }
};

class Game
{
public:
    InputReceiver *receiver;
    Painter *painter;
    u32 anterior;
    vector<Entity*>entidades;

    Game()
    {
        receiver=new InputReceiver();
        painter=new Painter(receiver);

        vector<stringw>up;
        up.push_back("images/char/up/1.png");
        up.push_back("images/char/up/2.png");
        vector<stringw>down;
        down.push_back("images/char/down/1.png");
        down.push_back("images/char/down/2.png");
        vector<stringw>left;
        left.push_back("images/char/left/1.png");
        left.push_back("images/char/left/2.png");
        vector<stringw>right;
        right.push_back("images/char/right/1.png");
        right.push_back("images/char/right/2.png");
        entidades.push_back((Entity*)new EntityChuy(200,200,up,down,left,right,painter,receiver));

        vector<stringw>arboles;
        arboles.push_back("images/arbol/1.png");
        arboles.push_back("images/arbol/2.png");
        entidades.push_back((Entity*)new EntityArbol(400,200,arboles,painter,receiver));

        entidades.push_back((Entity*)new EntityArbol(450,300,arboles,painter,receiver));

        entidades.push_back((Entity*)new EntityArbol(900,350,arboles,painter,receiver));

        entidades.push_back((Entity*)new EntityArbol(700,50,arboles,painter,receiver));
    }

    void gameLoop()
    {
        anterior=painter->device->getTimer()->getTime();
        for(;;)
        {
            logic();
            waitSync();
            render();
        }
    }

    void logic()
    {
        if(receiver->IsKeyDown(irr::KEY_ESCAPE))
            exit(0);
        for(int i=0;i<(int)entidades.size();i++)
            entidades[i]->logic();
    }
    void render()
    {
        if (painter->isWindowActive())//Paja
        {
            painter->beginScene();//Paja

            for(int i=0;i<(int)entidades.size();i++)
                entidades[i]->draw();

            painter->endScene();//Paja
        }
        painter->run();//Paja
    }
    void waitSync()
    {
        do
        {
            painter->device->run();
        }while(painter->device->getTimer()->getTime()<anterior+16);
        anterior=painter->device->getTimer()->getTime();
    }
};

int main()
{
    Game game;
    game.gameLoop();

    return 0;
}
