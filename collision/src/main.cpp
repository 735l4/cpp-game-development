#include<SFML/Graphics.hpp>
#include <memory>
#include<fstream>
#include<iostream>


class SharedShape {
public:
  std::shared_ptr<sf::Shape> shape;
  float vx, vy;
  std::string name;


  SharedShape(std::shared_ptr<sf::Shape> shape, float vx, float vy, std::string name) 
  : shape(shape)
  , vx(vx)
  , vy (vy)
  , name(name) {}

  // Method to update position and handle DVD-style bouncing
  void update(sf::RenderWindow& window) {
    sf::Vector2f pos = shape->getPosition();

    sf::FloatRect bounds = shape->getLocalBounds(); // Get bounding box of the shape

    // Collision detection with the left side of the window
    if (pos.x < 0) {
      vx = -vx;
    }

    // Collision detection with the top of the window
    if (pos.y < 0) {
      vy = -vy;
    }
    // Collision detection with the right side of the window
    if (pos.x + bounds.size.x > window.getSize().x) {
      vx = -vx;
    }


    // Collision detection with the bottom of the window
    if (pos.y + bounds.size.y > window.getSize().y) {
      vy = -vy; // Reverse vertical velocity if touching the bottom wall
    }

    shape->setPosition({pos.x + vx, pos.y + vy});
  }


};

int main(int argc, char * argv[])
{
  std::ifstream fin("bin/config");
  std::string type;
  std::string fontFile;
  uint fontSize, fR, fG, fB;
  sf::Color textColor;

  uint wWidth, wHeight;
  sf::Font font;


  sf::Text text(font);
  std::vector<std::shared_ptr<SharedShape>> shapes;
  std::string configLine;

  if (!fin.is_open()) {
    std::cerr << "❌ Could not open hello.txt for reading!" << std::endl;
    return 1;
  }

  std::cout << "✅ File opened successfully!\n";

  while (fin >> type) {
    if(type == "Window") {
      fin >> wWidth >> wHeight;
    } else if (type == "Font") {
      fin >> fontFile >> fontSize >> fR >> fG >> fB;

    } else if (type == "Circle") {
      std::string name;
      float x, y , vx, vy;
      int r, g, b;
      float radius;

      fin >> name >> x >> y >> vx >> vy >> r >> g >> b >> radius;

      auto circle = std::make_shared<sf::CircleShape>(radius);
      circle->setPosition({x, y});
      circle->setFillColor(sf::Color(r,g,b));

      shapes.push_back(std::make_shared<SharedShape>(circle, vx, vy, name));

    } else if (type == "Rectangle") {
      std::string name;
      float x, y , vx, vy;
      int r, g, b;
      float width, height;

      fin >> name >> x >> y >> vx >> vy >> r >> g >> b >> width >> height;

      auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2(width, height));
      rect->setPosition({x, y});
      rect->setFillColor(sf::Color(r,g,b));

      shapes.push_back(std::make_shared<SharedShape>(rect, vx, vy, name));
    }
  }

  if(!font.openFromFile(fontFile)) {
    std::cout << "Error opening font file " << std::endl;
  }


  sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "SFML Project");

  window.setFramerateLimit(120.f);

  while(window.isOpen())
  {
    while(const std::optional event = window.pollEvent()) 
    {
      if(event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);


    for(auto& dShape : shapes)
    {
      sf::Text text(font);

      float shapeX = dShape->shape->getPosition().x;
      float shapeY = dShape->shape->getPosition().y;

      float shapeWidth = dShape->shape->getLocalBounds().size.x;
      float shapeHeight = dShape->shape->getLocalBounds().size.y;


      text.setCharacterSize(fontSize);

      text.setString(dShape->name);

      text.setOrigin(text.getGlobalBounds().size / 2.f + text.getLocalBounds().position);
      // text.setPosition(shape.shape->getPosition() + (shape.shape->getLocalBounds().size / 2.f));
      text.setPosition({shapeX + (shapeWidth / 2.f), shapeY + (shapeHeight / 2.f)});

      dShape->update(window);
      window.draw(*dShape->shape);
      window.draw(text);
    }

    window.display();

  }

  return 0;
}
