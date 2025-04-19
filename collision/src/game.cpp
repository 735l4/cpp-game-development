#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<memory>

int main()
{
  float radius = 25.f;
  uint wWidth = 800;
  uint wHeight = 800;
  float diameter = 2 * radius;

  sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "Game Programming");
  // sf::CircleShape circle(radius);
  // sf::RectangleShape rect({100, 100});
  //
  // circle.setFillColor(sf::Color::Yellow);
  // circle.setPosition({0.f, 0.f}); // Start from top-left

  float movementSpeed = .05f;

  float xSpeed = movementSpeed;
  float ySpeed = movementSpeed;

  while (window.isOpen())
  {
    while (std::optional event = window.pollEvent())
    {
      if(event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    std::vector<std::shared_ptr<sf::Shape>> shapes;
    std::shared_ptr<sf::Shape> shape = std::make_shared<sf::CircleShape>(20.f);
    std::shared_ptr<sf::Shape> shape1 = std::make_shared<sf::CircleShape>(20.f);
    std::shared_ptr<sf::Shape> rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));

    shape1->setPosition({100.f, 100.f});
    rect->setPosition({130.f, 140.f});

    shapes.push_back(shape);
    shapes.push_back(shape1);
    shapes.push_back(rect);


    //
    // std::vector<sf::Shape*> shapes;
    // sf::Shape* shape = new sf::CircleShape(20.f);
    //
    //
    // shapes.push_back(shape);
    // sh


    for(auto& shape : shapes)
    {
      window.draw(*shape);
    }


    // Cool Trick
    // std::vector<sf::RectangleShape> rectangles;
    //
    // for(float i =0; i<25; i++)
    // {
    //   for (float j = 0; j < 10; j++)
    //   {
    //     sf::RectangleShape rect(sf::Vector2f({15, 15}));
    //     rect.setPosition({i * 20, j * 20});
    //     rect.setFillColor(sf::Color(i * 10, j *10, 0));
    //
    //     rectangles.push_back(rect);
    //
    //   }
    // }

    // for(auto& rect: rectangles)
    // {
    //   window.draw(rect);
    // }
    window.display();
  }

  return 0;
}

