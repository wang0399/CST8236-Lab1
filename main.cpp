#include <SFML/Graphics.hpp>
#include "TransformNode.h"

/*CST8236 Lab1 */

int main(int argc, char* argv) 
{
  sf::RenderWindow window(sf::VideoMode(600, 600), "Purple");
  
  //define body components
  sf::CircleShape headCircle(12);
  sf::RectangleShape neckRect(sf::Vector2<float>(15.0f, 5.0f));
  sf::RectangleShape bodyRect(sf::Vector2<float>(90.0f, 13.0f));
  sf::RectangleShape lowerRightArmRect(sf::Vector2<float>(35.0f, 6.0f));
  sf::RectangleShape upperRightArmRect(sf::Vector2<float>(40.0f, 6.0f));
  sf::RectangleShape lowerLeftArmRect(sf::Vector2<float>(35.0f, 6.0f));
  sf::RectangleShape upperLeftArmRect(sf::Vector2<float>(40.0f, 6.0f));

  //set componment color
  headCircle.setFillColor(sf::Color::Magenta);
  neckRect.setFillColor(sf::Color::Cyan);
  lowerRightArmRect.setFillColor(sf::Color::Red);
  upperRightArmRect.setFillColor(sf::Color::Blue);
  lowerLeftArmRect.setFillColor(sf::Color::Yellow);
  upperLeftArmRect.setFillColor(sf::Color::Green);
  bodyRect.setFillColor(sf::Color::White);


  bool keyHeld = false;
  bool growing = true;
  int rorateLimit = 1200; //for body rotation range
  int roateCounter = 0;  //for body roatation direction switching
  int roateDirection = 0; //0 for going right, -1 for going left

  //set body's location
  bodyRect.setOrigin(20.0f, 20.0f);
  bodyRect.setPosition(350, 430);
  bodyRect.setScale(3, 3);
  bodyRect.setRotation(-90);

  //define body component position
  sf::Vector2<float> rightArmPosition((bodyRect.getLocalBounds().width), (bodyRect.getLocalBounds().height));
  sf::Vector2<float> leftArmPosition((bodyRect.getLocalBounds().width-4.0f), (bodyRect.getLocalBounds().height)* -1 + 12.0f);
  sf::Vector2<float> headPosition((neckRect.getLocalBounds().width), -8.0f);
  sf::Vector2<float> neckPosition((bodyRect.getLocalBounds().width), (bodyRect.getLocalBounds().height)/2.7);

  //define body component origin
  sf::Vector2<float> rightArmOrigin(2.0f, 1.0f);
  sf::Vector2<float> leftArmOrigin(1.0f, 1.0f);
  sf::Vector2<float> headOrigin(1.0f, 1.0f);
  sf::Vector2<float> defaultArmOrigin(0.0f, 1.0f);

  //set body component origin
  upperRightArmRect.setOrigin(rightArmOrigin);
  lowerRightArmRect.setOrigin(defaultArmOrigin);
  upperLeftArmRect.setOrigin(leftArmOrigin);
  lowerLeftArmRect.setOrigin(defaultArmOrigin);
  neckRect.setOrigin(defaultArmOrigin);
  headCircle.setOrigin(headOrigin);

  //set body components' default angle
  neckRect.setRotation(0);
  upperRightArmRect.setRotation(80);
  lowerRightArmRect.setRotation(35);
  upperLeftArmRect.setRotation(-80);
  lowerLeftArmRect.setRotation(-35);
  
  //set body components' default position 
  neckRect.setPosition(neckPosition);
  headCircle.setPosition(headPosition);
  upperRightArmRect.setPosition(rightArmPosition);
  lowerRightArmRect.setPosition(upperRightArmRect.getLocalBounds().width, 1.0f);
  upperLeftArmRect.setPosition(leftArmPosition);
  lowerLeftArmRect.setPosition(upperLeftArmRect.getLocalBounds().width, 1.0f);

  //transform body components
  TransformNode head(&headCircle);
  TransformNode neck(&neckRect);
  TransformNode body(&bodyRect);
  TransformNode upperLeftArm(&upperLeftArmRect);
  TransformNode lowerLeftArm(&lowerLeftArmRect);
  TransformNode upperRightArm(&upperRightArmRect);
  TransformNode lowerRightArm(&lowerRightArmRect);
 
  //add child to parent component
  body.AddChild(&upperLeftArm);
  body.AddChild(&upperRightArm);
  body.AddChild(&neck);
  neck.AddChild(&head);
  upperLeftArm.AddChild(&lowerLeftArm);
  upperRightArm.AddChild(&lowerRightArm);
  

  sf::Clock deltaTime;
  while (window.isOpen())
  {
    float elaspedTime = deltaTime.restart().asSeconds();
	
    sf::Event sfEvent;
    while (window.pollEvent(sfEvent))
    {
      if (sfEvent.type == sf::Event::Closed)
      {
        window.close();
      }
      else if (sfEvent.type == sf::Event::KeyReleased)
      {
        keyHeld = false;
      }
      else if (sfEvent.type == sf::Event::KeyPressed)
      {
        keyHeld = true;
      }
    }

    if (keyHeld)
    {
		float angleAmount = 90.0f;
		float defaultAngle = angleAmount * elaspedTime;
		float bodyAngle = defaultAngle;

		//evaluates rotation to the "right", when counter limit is reached, it would "switch" rotation direction 
		if (roateCounter < rorateLimit && roateDirection == 0)
		{	
			if (bodyAngle < 0)
				bodyAngle *= -1;

			roateCounter++;

			if (roateCounter == rorateLimit)			
				roateDirection = -1;													
		}
		//evaluates rotation to the "left", switch direction when negativve counter limit is reached 
	   else if (roateCounter > -rorateLimit && roateDirection == -1)
	   {
		   if (bodyAngle > 0)
			   bodyAngle *= -1;

		  roateCounter--;

		 if (roateCounter == -rorateLimit)	 
			 roateDirection = 0;			 				 
	   }     
	 
	    bodyRect.rotate(bodyAngle);
		upperLeftArmRect.rotate(defaultAngle * -1);
		lowerLeftArmRect.rotate(defaultAngle * -1);
		upperRightArmRect.rotate(defaultAngle);
		lowerRightArmRect.rotate(defaultAngle);
		neckRect.rotate(defaultAngle);
	  
    }

    window.clear(); // draw fullscreen graphic
	body.Draw(&window);		
    window.display();
  }

  return 0;
}