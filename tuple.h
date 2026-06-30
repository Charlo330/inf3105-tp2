using namespace std;

template <class I, class J>
class Tuple
{
public:
  Tuple();
  Tuple(I i, J j);
  I &getI();
  J &getJ();

  Tuple<I, J>& operator=(const Tuple<I, J> &autre);

private:
  I i;
  J j;
};

template <class I, class J>
Tuple<I, J>::Tuple() : i(), j() {};

template <class I, class J>
Tuple<I, J>::Tuple(I i, J j) : i(i), j(j) {};

template <class I, class J>
I &Tuple<I, J>::getI()
{
  return i;
}

template <class I, class J>
J &Tuple<I, J>::getJ()
{
  return j;
}

template <class I, class J>
Tuple<I, J> &Tuple<I, J>::operator=(const Tuple<I, J> &autre)
{
  if (this != &autre)
  {
    i = autre.i;
    j = autre.j;
  }
  return *this;
}