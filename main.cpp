
#include <iostream>
#include "CharSequence/CharSequence.hpp"

using std::cout;
using std::cin;
using std::endl;

int main() {
    CharSequence *cs = new CharSequence("This This This This This");
    cout << *cs << endl;
    cs->replace("This", "News");
    cs->append("Success");
    cout << cs->getLength() << endl;
    cout << cs->find('N', 11) << endl;
    cout << cs->find("News", 11) << endl;
    cout << *cs << endl;
    cs->replace('N', 'M');
    cout << *cs << endl;
    delete(cs);
    return 0;
}