#include <iostream>
#include <vector>

class Plant
{
public:
    Plant(int hp, int damage) : hp(hp), damage(damage) {}

    virtual void attack() = 0;
    bool isAlive() const { return hp > 0; }
    void takeDamage(int dmg) { hp -= dmg; }

protected:
    int hp;
    int damage;
};

class Peashooter : public Plant
{
public:
    Peashooter() : Plant(100, 20) {}
    void attack() override { std::cout << "Peashooter attacks with " << damage << " damage.\n"; }
};

class Zombie
{
public:
    Zombie(int hp, int damage) : hp(hp), damage(damage) {}

    void attack() { std::cout << "Zombie attacks with " << damage << " damage.\n"; }
    bool isAlive() const { return hp > 0; }
    void takeDamage(int dmg) { hp -= dmg; }

private:
    int hp;
    int damage;
};

class Game
{
public:
    Game()
    {
        plants.push_back(new Peashooter());
        zombies.push_back(new Zombie(150, 10));
    }

    ~Game()
    {
        for (auto plant : plants)
            delete plant;
        for (auto zombie : zombies)
            delete zombie;
    }

    void start()
    {
        while (true)
        {
            if (plants.empty() || zombies.empty())
            {
                break;
            }

            Plant *plant = plants[0];
            Zombie *zombie = zombies[0];

            plant->attack();
            zombie->takeDamage(plant->damage);

            if (!zombie->isAlive())
            {
                delete zombie;
                zombies.erase(zombies.begin());
                if (zombies.empty())
                {
                    std::cout << "All zombies are defeated! Plants win!\n";
                    break;
                }
            }

            zombie->attack();
            plant->takeDamage(zombie->damage);

            if (!plant->isAlive())
            {
                delete plant;
                plants.erase(plants.begin());
                if (plants.empty())
                {
                    std::cout << "All plants are defeated! Zombies win!\n";
                    break;
                }
            }
        }
    }

private:
    std::vector<Plant *> plants;
    std::vector<Zombie *> zombies;
};

int main()
{
    Game game;
    game.start();
    return 0;
}
