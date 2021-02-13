#include <string>
#include <list>

#include <gtest/gtest.h>
// An animal shelter can only holds dogs and cats, and operates in a strictly "first on, first out" basis.
// People must adopt either an older(based on arrival time) animal or they can select whether they would
// prefer a cat or a dog. They cannot select specific animal which they would like. Create the data
// structures to maintain such system and implement such methods like enqueue, dequeueDog,
// dequeueCat, dequeue. You mau use built-in List data structure.

struct Animal {
    enum class Type {
        e_unknown,
        e_cat,
        e_dog
    };

    std::string name;
    Type        type;
};

class Queue {
    std::list<Animal> m_animals;

    Animal dequeueSpecific(Animal::Type type) {
            if (m_animals.empty()) {
                throw std::runtime_error("dequeue on an empty queue");
            }

            auto end = std::end(m_animals);
            auto rit = std::begin(m_animals);
            for (; rit != end; ++rit) {
                if (rit->type == type) {
                    break;
                }
            }

            if (rit == end) {
                return Animal();
            }

            Animal returnAnimal = *rit;
            m_animals.erase(rit);
            return returnAnimal;
    }
public:
    void enqueue(const Animal& animal) {
        if (animal.type == Animal::Type::e_unknown) {
            throw std::runtime_error("trying to enqueue unknown animal");
        }

        m_animals.push_back(animal);
    }

    Animal dequeue() {
        if (m_animals.empty()) {
            throw std::runtime_error("dequeue on an empty queue");
        }
        Animal ret = m_animals.front();
        m_animals.pop_front();

        return ret;
    }

    Animal dequeueCat() {
        return dequeueSpecific(Animal::Type::e_cat);
    }

    Animal dequeueDog() {
        return dequeueSpecific(Animal::Type::e_dog);
    }

    bool empty() const { return m_animals.empty(); }
};


TEST(queueAnimalTest, SmokeTest) {
    Queue qq;

    qq.enqueue(Animal{.name = "Marsik", .type = Animal::Type::e_cat});
    qq.enqueue(Animal{.name = "Mana", .type = Animal::Type::e_dog});
    qq.enqueue(Animal{.name = "Lana", .type = Animal::Type::e_dog});
    qq.enqueue(Animal{.name = "Barsik", .type = Animal::Type::e_cat});
    qq.enqueue(Animal{.name = "Lansik", .type = Animal::Type::e_cat});
    qq.enqueue(Animal{.name = "Barni", .type = Animal::Type::e_dog});

    {
        Animal ret = qq.dequeueDog();
        ASSERT_EQ(std::string("Mana"), ret.name);
        ASSERT_EQ(Animal::Type::e_dog, ret.type);
    }

    {
        Animal ret = qq.dequeue();
        ASSERT_EQ(std::string("Marsik"), ret.name);
        ASSERT_EQ(Animal::Type::e_cat, ret.type);
    }

    {
        Animal ret = qq.dequeueCat();
        ASSERT_EQ(std::string("Barsik"), ret.name);
        ASSERT_EQ(Animal::Type::e_cat, ret.type);
    }

    {
        Animal ret = qq.dequeue();
        ASSERT_EQ(std::string("Lana"), ret.name);
        ASSERT_EQ(Animal::Type::e_dog, ret.type);
    }

    {
        Animal ret = qq.dequeueDog();
        ASSERT_EQ(std::string("Barni"), ret.name);
        ASSERT_EQ(Animal::Type::e_dog, ret.type);
    }

    {
        Animal ret = qq.dequeueCat();
        ASSERT_EQ(std::string("Lansik"), ret.name);
        ASSERT_EQ(Animal::Type::e_cat, ret.type);
    }

    ASSERT_TRUE(qq.empty());
}
