#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

#include "Ducks.h"

using namespace std;

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck & duck)
{
	duck.Quack();
	duck.Dance();
	duck.Fly();
	DrawDuck(duck);

	// Divider
	std::cout << "==================" << std::endl;
}


void main()
{
	CMallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	CRedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	CRubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	CDeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	CModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyBehaviorTypes::FlyWithWings);
	PlayWithDuck(modelDuck);
	PlayWithDuck(modelDuck);
	PlayWithDuck(mallarDuck);
}