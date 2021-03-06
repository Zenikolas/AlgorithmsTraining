#include <string>
#include <list>

#include <gtest/gtest.h>
// An animal shelter can only holds dogs and cats, and operates in a strictly "first on, first out" basis.
// People must adopt either an older(based on arrival time) animal or they can select whether they would
// prefer a cat or a dog. They cannot select specific animal which they would like. Create the data
// structures to maintain such system and implement such methods like enqueue, dequeueDog,
// dequeueCat, dequeue. You mau use built-in List data structure.

struct Animal {
    enum Type {
        e_unknown,
        e_cat,
        e_dog
    };

    std::string name;
    Type        type;
};

class Queue {
    struct AnimalOrdered : public Animal {
        size_t order;

        AnimalOrdered(const Animal& animal, size_t _order) : Animal(animal), order(_order) {}
    };

    size_t            m_order = 0;
    std::list<AnimalOrdered> m_cats;
    std::list<AnimalOrdered> m_dogs;

public:
    void enqueue(const Animal& animal) {
        switch (animal.type) {
            case Animal::Type::e_cat:
                m_cats.emplace_back(animal, m_order++);
                break;
            case Animal::Type::e_dog:
                m_dogs.emplace_back(animal, m_order++);
                break;
            default:
                throw std::runtime_error("unknown animal type!");
        }
    }

    Animal dequeue() {
        if (empty()) {
            return Animal();
        }

        if (m_cats.empty()) {
            Animal dog = m_dogs.front();
            m_dogs.pop_front();
            return dog;
        }

        if (m_dogs.empty()) {
            Animal cat = m_cats.front();
            m_cats.pop_front();
            return cat;
        }

        const AnimalOrdered& catRef = m_cats.front();
        const AnimalOrdered& dogRef = m_dogs.front();

        if (catRef.order < dogRef.order) {
            Animal cat = catRef;
            m_cats.pop_front();
            return cat;
        }

        Animal dog = dogRef;
        m_dogs.pop_front();
        return dog;
    }

    Animal dequeueCat() {
        if (m_cats.empty()) {
            return Animal();
        }

        Animal cat = m_cats.front();
        m_cats.pop_front();
        return cat;
    }

    Animal dequeueDog() {
        if (m_dogs.empty()) {
            return Animal();
        }

        Animal dog = m_dogs.front();
        m_dogs.pop_front();
        return dog;
    }

    bool empty() const { return m_cats.empty() && m_dogs.empty(); }
};


TEST(queueAnimalTimeStampTest, SmokeTest) {
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
