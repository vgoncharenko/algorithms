
//
// Created by Vitaliy on 2019-09-25.
//
#include <string>
#include <iostream>



class Animal {
private:
    std::string my_private_string = "animal";
public:
    virtual void myF()
    {
        std::cout << "Animal class: " << this->my_private_string << std::endl;
    }
};

class Animal2 : public Animal {
protected:
    std::string my_private_string = "animal2";
public:
    void myF() override
    {
        std::cout << "Animal2 class: " << this->my_private_string << std::endl;
    }
};

class Animal3 : public Animal2 {
public:
    void myF()
    {
      std::cout << "Animal3 class: " << this->my_private_string << std::endl;
    }
};


void testOveriding()
{
  Animal *a = new Animal3();
  a->myF();
}

