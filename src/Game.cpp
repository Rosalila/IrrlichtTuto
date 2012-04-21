#include "../include/Game.h"

Game::Game()
{
    receiver=new InputReceiver();
    painter=new Painter(receiver);

    entidades.push_back((Entity*)new EntityBackground("images/bg.png",painter,receiver));

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
    vector<stringw>fly;
    fly.push_back("images/char/fly/1.png");
    fly.push_back("images/char/fly/2.png");
    entidades.push_back((Entity*)new EntityChar(50,300,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(250,300,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(200,350,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(200,470,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(500,440,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(450,400,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(900,350,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(70,370,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(700,440,3,up,down,left,right,fly,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(150,450,3,up,down,left,right,fly,painter,receiver));

    vector<stringw>up_chuy;
    up_chuy.push_back("images/chuy/up/1.png");
    up_chuy.push_back("images/chuy/up/2.png");
    up_chuy.push_back("images/chuy/up/3.png");
    vector<stringw>down_chuy;
    down_chuy.push_back("images/chuy/down/1.png");
    down_chuy.push_back("images/chuy/down/2.png");
    down_chuy.push_back("images/chuy/down/3.png");
    vector<stringw>left_chuy;
    left_chuy.push_back("images/chuy/left/1.png");
    left_chuy.push_back("images/chuy/left/2.png");
    left_chuy.push_back("images/chuy/left/3.png");
    vector<stringw>right_chuy;
    right_chuy.push_back("images/chuy/right/1.png");
    right_chuy.push_back("images/chuy/right/2.png");
    right_chuy.push_back("images/chuy/right/3.png");
    vector<stringw>fly_chuy;
    fly_chuy.push_back("images/chuy/fly/1.png");
    fly_chuy.push_back("images/chuy/fly/2.png");
    fly_chuy.push_back("images/chuy/fly/3.png");
    fly_chuy.push_back("images/chuy/fly/4.png");
    fly_chuy.push_back("images/chuy/fly/5.png");
    fly_chuy.push_back("images/chuy/fly/6.png");
    entidades.push_back((Entity*)new EntityChuy(460,300,up_chuy,down_chuy,left_chuy,right_chuy,fly_chuy,painter,receiver));

    vector<stringw>vaca;
    vaca.push_back("images/vaca/1.png");
    vaca.push_back("images/vaca/2.png");
    vaca.push_back("images/vaca/3.png");
    entidades.push_back((Entity*)new EntityChar(50,300,1,vaca,vaca,vaca,vaca,vaca,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(750,440,1,vaca,vaca,vaca,vaca,vaca,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(350,400,1,vaca,vaca,vaca,vaca,vaca,painter,receiver));
    entidades.push_back((Entity*)new EntityChar(50,370,1,vaca,vaca,vaca,vaca,vaca,painter,receiver));

    vector<stringw>arboles;
    arboles.push_back("images/arbol/1.png");
    arboles.push_back("images/arbol/2.png");
    arboles.push_back("images/arbol/3.png");
    arboles.push_back("images/arbol/4.png");
    entidades.push_back((Entity*)new EntityArbol(400,200,arboles,painter,receiver));

    entidades.push_back((Entity*)new EntityArbol(450,300,arboles,painter,receiver));

    entidades.push_back((Entity*)new EntityArbol(900,350,arboles,painter,receiver));

    entidades.push_back((Entity*)new EntityArbol(700,50,arboles,painter,receiver));
}

void Game::intro()
{
    int img_actual=0;
    anterior=painter->device->getTimer()->getTime();
    for(;;)
    {
        receiver->startEventProcess();
        if(receiver->IsKeyDown(irr::KEY_ESCAPE))
            break;
        do
        {
            painter->device->run();
        }while(painter->device->getTimer()->getTime()<anterior+16);
        anterior=painter->device->getTimer()->getTime();


        vector<irr::video::ITexture*>images;
        images.push_back(painter->getTexture("images/intro/1.png"));
        images.push_back(painter->getTexture("images/intro/2.png"));
        images.push_back(painter->getTexture("images/intro/3.png"));
        images.push_back(painter->getTexture("images/intro/4.png"));
        images.push_back(painter->getTexture("images/intro/5.png"));
        images.push_back(painter->getTexture("images/intro/6.png"));
        if (painter->isWindowActive())//Paja
        {
            irr::video::ITexture*image=images[img_actual];

            if(receiver->IsKeyPressed(irr::KEY_RETURN))
                img_actual++;
            if(img_actual>=(int)images.size())
                break;

            painter->beginScene();//Paja
            painter->draw2DImage
            (   image,
                irr::core::dimension2d<irr::f32> (image->getOriginalSize().Width,image->getOriginalSize().Height), //tamaño de la imagen
                irr::core::rect<irr::f32>(0,0,image->getOriginalSize().Width,image->getOriginalSize().Height), //Rectangulo de recorte de imagen
                irr::core::position2d<irr::f32>(0,0), //Posicion x y en la pantalla
                irr::core::position2d<irr::f32>(0,0), //Centro de rotacion de la imagen
                irr::f32(0),//rotacion
                irr::core::vector2df (0.5,0.5), //escala x y
                true,// Acepta canal alpha (transparencia del color)
                irr::video::SColor(255,255,255,255),//Color de.. ehh no se d q :s
                false,//Flip horizontal
                false);//Flip vertical

            painter->endScene();//Paja
        }
        painter->run();//Paja
    }
}

void Game::gameLoop()
{
    anterior=painter->device->getTimer()->getTime();
    for(;;)
    {
        logic();
        waitSync();
        render();
    }
}

void Game::logic()
{
    if(receiver->IsKeyDown(irr::KEY_ESCAPE))
        exit(0);
    for(int i=0;i<(int)entidades.size();i++)
        entidades[i]->logic();
}

void Game::render()
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

void Game::waitSync()
{
    do
    {
        painter->device->run();
    }while(painter->device->getTimer()->getTime()<anterior+16);
    anterior=painter->device->getTimer()->getTime();
}
