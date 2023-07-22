#include "CStack.h"
#include "Factory.h"
#include "Functions.h"

int main() {

    CData0 a(7);

    Factory* f[] = {new FactoryCData0, new FactoryCData1};
    CStack** arr = nullptr;
    size_t n = 0;
    size_t LMax = 2;

    FILE *in = fopen("input.txt", "r");
    char* str = nullptr;

    try {
        while (mygets(str, LMax, in)) {
            CStack** tmp = new CStack*[n + 1];
            if (arr) {
                memmove(tmp, arr, sizeof(void *) * n);
                delete [] arr;
            }
            arr = tmp;
            arr[++n - 1] = CStack::create_by_Factory(str, f);
        }
        cout << "--------------------" << endl;
        for (size_t i = 0; i < n; ++i)
            arr[i]->output();

        cout << "The output to output-files was made" << endl;
        // cyclic shift testing
        cout << "--------------------" << endl;
        cout << "Cyclic shift testing" << endl;
        cout << "Before cyclic shift:" << endl;
        for (size_t i = 0; i < n; ++i)
            cout << *arr[i] << endl;

        // cyclic shift
        CData0 tmpCDataObj(*arr[0]);
        for (size_t i = 0; i < n - 1; ++i)
            *arr[i] = *arr[i + 1];
        *arr[n - 1] = tmpCDataObj;

        cout << "After:" << endl;
        for (size_t i = 0; i < n; ++i)
            cout << *arr[i] << endl;
        cout << "--------------------" << endl;

        for (size_t i = 0; i < n; ++i)
            arr[i]->output();
        cout << "The output to output-files was made" << endl;
        cout << "--------------------" << endl;

        // Decrementing testing
        cout << "Decrementing testing" << endl;
        cout << "Original object: " << *arr[4] << endl;
        cout << "Object after prefix decrementing: " << --(*arr[4]) << endl;

        cout << "Original object: " << (*arr[4])-- << endl;
        cout << "Object after postfix decrementing: " << *arr[4] << endl;

        // Incrementing testing
        cout << "\nIncrementing testing" << endl;
        cout << "Original object: " << *arr[4] << endl;
        cout << "Object after prefix incrementing: " << ++(*arr[4]) << endl;

        cout << "Original object: " << (*arr[4])++ << endl;
        cout << "Object after postfix incrementing: " << *arr[4] << endl;

        // operator + testing
        cout << "--------------------" << endl;
        cout << "Operator + testing" << endl;
        cout << (*arr[4]) << " + " <<  (*arr[1]) << " = ";
        cout << (*arr[4]) + (*arr[1]) << endl;
        cout << (*arr[0]) << " + " <<  (*arr[2]) << " = ";
        cout << (*arr[0]) + (*arr[2]) << endl;
        cout << (*arr[3]) << " + " <<  (*arr[4]) << " = ";
        cout << (*arr[3]) + (*arr[4]) << endl;
        cout << "--------------------" << endl;

        // adding objects in sum
        CData0 sum(0);
        for (size_t i = 0; i < n; ++i)
            sum = sum + *arr[i];

        cout << "sum = " << sum << endl;
        cout << "--------------------" << endl;

    }
    catch (int i) {
        if (i == -1) {
            cout << "Incorrect type(string " << n << ")\n";
        }
        if (i == -2) {
            cout << "Incorrect data(string " << n << ")\n";
        }
        arr[n - 1] = nullptr;
        delete [] str;
    }

    for (size_t i = 0; i < n; ++i)
        delete arr[i];
    delete [] arr;
    for (size_t i = 0; i < 2; ++i)
        delete f[i];

    fclose(in);
    return 0;
}