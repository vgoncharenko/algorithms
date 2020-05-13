//
// Created by Vitaliy on 2019-09-26.
//

class CAnimal {
public:
    CAnimal(string &_name, int _order): name(_name), order(_order) {};
    int setOrder(int _order)
    {
      order = _order;
    }

    int getOrder()
    {
      return order;
    }
    bool operator>(CAnimal a)
    {
      return order > a.getOrder();
    }
private:
    string name {""};
    int order {0};
};

class CCat : public CAnimal{};
class CDog : public CAnimal{};

class Shelter {
    void enq(CCat *cat) {
      enq(cat, cats);
    }
    void enq(CDog *dog) {
      enq(dog, dogs);
    }

    void enq(CAnimal *animal, queue<CAnimal*> q)
    {
      animal->setOrder(this->order++);
      q.push(animal);
    }

    CCat* deqCat()
    {
      return (CCat*)deq(cats);
    }

    CDog* deqDog()
    {
      return (CDog*)deq(dogs);
    }

    CAnimal* deq(queue<CAnimal*> q)
    {
      CAnimal *animal = q.front();
      q.pop();
      return animal;
    }

    CAnimal* deqAny()
    {
      if (dogs.front() > cats.front()) {
        return deq(dogs);
      } else {
        return deq(cats);
      }
    }

private:
    queue<CAnimal*> cats, dogs;
    int order = 0;
};

