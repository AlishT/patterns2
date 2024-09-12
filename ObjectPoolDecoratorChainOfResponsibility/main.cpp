// ObjectPoolDecoratorChainOfResponsibility.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "ObjectPool.h";
#include "Decorator.h"
#include "ChainOfResponsibility.h"

using namespace std;

int main()
{
    //Object Pool
    RoundMag* pool = new RoundMag(10);
    
    Bullet* thirtyRoundMag = new Bullet();
    Bullet* sixtyRoundMag = new Bullet();

    thirtyRoundMag->setValue(10);

    pool->GetFreeBullets(thirtyRoundMag->getValue());
    pool->ReleaseBullet(thirtyRoundMag);
  
    
    sixtyRoundMag->setValue(60);
    pool->GetFreeBullets(sixtyRoundMag->getValue());
    pool->ReleaseBullet(sixtyRoundMag);

    //Decorator
    shared_ptr<Weapon> rifle = make_shared<Rifle>();

    shared_ptr<Weapon> stock = make_shared<StockComponent>(rifle);
    cout << "Weapon control with stock: " << stock->recoilControl() << endl;

    shared_ptr<Weapon> underbarrel = make_shared<UnderbarrelComponent>(rifle);
    cout << "Weapon control with stock and underbarrel: " << underbarrel->recoilControl() << endl;
    
    //Chain Of Responsibility
    shared_ptr<Dollar10Handler> s10 = make_shared<Dollar10Handler>();
    shared_ptr<Dollar20Handler> s20 = make_shared<Dollar20Handler>(s10);
    shared_ptr<Dollar50Handler> s50 = make_shared<Dollar50Handler>(s20);
    shared_ptr<Dollar100Handler> s100 = make_shared<Dollar100Handler>(s50);

    shared_ptr<AtmHandler> atm = make_shared<AtmHandler>(s100);
    atm->HandleRequest(770);
}

