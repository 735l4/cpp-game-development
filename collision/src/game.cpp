#include<SFML/Graphics.hpp>


int main()
{
  sf::RenderWindow window(sf::VideoMode({500, 500}), "SFML WINDOW");
  sf::CircleShape c(20.f);
  c.setPosition({200, 200});

  sf::Vector2f pos = sf::Vector2f({0.1f, 0.15f});

  c.setFillColor(sf::Color::Cyan);

  window.setFramerateLimit(60.f);


  while(window.isOpen())
  {

    while(const std::optional event = window.pollEvent())
    {
      if(event->is<sf::Event::Closed>())
      {
        window.close();
      }
    }

    // Top
    if(c.getPosition().y < 0)
    {
      pos.y = -pos.y;
    }

    //Left
    if(c.getPosition().x < 0)
    {
      pos.x = -pos.x;
    }

    // Bottom
    if((c.getPosition().y + c.getLocalBounds().size.y) > window.getSize().y)
    {
      pos.y = -pos.y;
    }

    // Right
    if((c.getPosition().x + c.getLocalBounds().size.x) > window.getSize().x)
    {
      pos.x = -pos.x;
    }

    c.move(pos);

    window.clear(sf::Color::Black);

    window.draw(c);
    window.display();
  }

  return 0;
}
