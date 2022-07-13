#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    for (float i = 0; i < 1; i += 0.01)
    {
        cout << "cos(" << i << ") : " << cos(i) << " \t sin(" << i << ") : " << sin(i) << endl;
    }

    return 0;
}
