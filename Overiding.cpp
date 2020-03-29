
//
// Created by Vitaliy on 2019-09-25.
//

class Animal {
private:
    string my_private_string = "animal";
public:
    virtual void myF()
    {
      cout << "Animal class: " << this->my_private_string << endl;
    }
};

class Animal2 : public Animal {
protected:
    string my_private_string = "animal2";
public:
    void myF() override
    {
      cout << "Animal2 class: " << this->my_private_string << endl;
    }
};

class Animal3 : public Animal2 {
public:
    void myF()
    {
      cout << "Animal3 class: " << this->my_private_string << endl;
    }
};


void testOveriding()
{
  Animal *a = new Animal3();
  a->myF();
}

