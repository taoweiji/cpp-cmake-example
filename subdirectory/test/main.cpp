#include <iostream>
#include "project1.h"
#include "project2.h"
#include "project3.h"

using namespace std;

int main() {
    cout << "project1:" << Project1().GetName() << endl;
    cout << "project2:" << Project2().GetName() << endl;
    cout << "project3:" << Project3().GetName() << endl;
    return 0;
}
