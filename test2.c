void main() {
    int a;
    int b;
    int c;
    a = 1;
    b = 2;
    c = 3;

    cout << 1 + 5;
    cout << 5 - 1;
    cout << 5 * 1;
    cout << 5 / 1;
    // cout << b << c;
    if(a == 1) {
        cout << 1;
    }
    if(a != 1) {
        cout << 0;
    }
    if(a != 2) {
        cout << 1;
    }

    while(a < 10) {
        cout << a;
        a = a + 1;
    }

    while(a > 0) {
        cout << a;
        a = a - 1;
    }

    while(a > 10) {
        cout << a;
        a = a + 1;
    }

    cout << 1 == 1;
    cout << 1 == 2;
    cout << 1 != 1;
    cout << 1 != 2;
    cout << 1 < 2;
    cout << 1 < 1;
    cout << 1 > 2;
    cout << 1 > 1;
    cout << 1 <= 2;
    cout << 1 <= 1;
    cout << 1 >= 2;
    cout << 1 >= 1;

    cout << 1 && 1;
    cout << 1 && 0;
    cout << 0 && 1;
    cout << 0 && 0;
    cout << 1 || 1;
    cout << 1 || 0;
    cout << 0 || 1;
    cout << 0 || 0;


    // catch bad things
}