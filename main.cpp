#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
public:
    int hp = 100, damage = 10, ki = 20;
    float speed=3;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::IntRect frameRect;
    int frameWidth = 48;
    int frameHeight = 48;
    int frameCount = 8;
    int currentFrame = 0;
    sf::Clock animationClock;
    float frameDuration = 0.1f;
    bool isRunning = false;

    Player() {
        playerTexture.loadFromFile("assets/player/run/playerrun.png");
        playerSprite.setTexture(playerTexture);
        frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
        playerSprite.setTextureRect(frameRect);
        playerSprite.setPosition(100, 100);
    }

    void startRunning() {
        isRunning = true;
    }

    void stopRunning() {
        isRunning = false;
        currentFrame = 0;
        frameRect.left = 0;
        playerSprite.setTextureRect(frameRect);
        if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
                animationClock.restart();
                currentFrame = (currentFrame + 1) % frameCount;
                frameRect.left = currentFrame * frameWidth;
                playerSprite.setTextureRect(frameRect);
            }
    }

    void playershot()
    {
        if (isRunning==false){
            playerTexture.loadFromFile("assets/player/run/playershot.png");
        }
        else{
            playerTexture.loadFromFile("assets/player/run/playershotrun.png");
            speed=2;
        }
        if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
                animationClock.restart();
                currentFrame = (currentFrame + 1) % frameCount;
                frameRect.left = currentFrame * frameWidth;
                playerSprite.setTextureRect(frameRect);
            }
    }

    void run() {
        if (isRunning) {
            playerTexture.loadFromFile("assets/player/run/playerrun.png");
            if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
                animationClock.restart();
                currentFrame = (currentFrame + 1) % frameCount;
                frameRect.left = currentFrame * frameWidth;
                playerSprite.setTextureRect(frameRect);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.setScale(-2.0f, 2.0f);
            playerSprite.move(-speed, 0);
            startRunning();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.setScale(2.0f, 2.0f);
            playerSprite.move(speed, 0);
            startRunning();
        }
        else {
            playerTexture.loadFromFile("assets/player/run/playeridle.png");
            stopRunning();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            playershot();
        }
        else speed=3;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(playerSprite);
    }
};

int main() {
    int height=540,width=990;
    sf::RenderWindow window(sf::VideoMode(width,height), "Run Animation");

    Player player;

    sf::Texture wallpaper;
    if (!wallpaper.loadFromFile("assets/wallpaper.jpg")) {
        return -1;
    }
    sf::Sprite wallpapersprite;
    wallpapersprite.setTexture(wallpaper);


    wallpapersprite.setScale(990.0f / 7760.0f,540.0f / 4751.0f);


    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }


        player.run();

        window.clear();
        window.draw(wallpapersprite);
        player.draw(window);

        window.display();
    }

    return 0;
}
