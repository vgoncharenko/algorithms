//
// Created by Vitaliy on 2019-09-23.
//

class DangerousClassInheritance
{
private:
    int privateProperty;

    void dddPrivate() {
      cout << "dddPrivate" << endl;
    }
public:
    DangerousClassInheritance(int _p) {
      privateProperty = _p;
    }

    void dddPublic(DangerousClassInheritance *a) {
      a->dddPrivate();
      cout << "Private property: " << a->privateProperty << endl;
    }
};

void testClassInheritance()
{
  DangerousClassInheritance *d1 = new DangerousClassInheritance(10);
  DangerousClassInheritance *d2 = new DangerousClassInheritance(20);

  d1->dddPublic(d2);
}
