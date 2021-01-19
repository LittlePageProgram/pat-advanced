#include <iostream>
using namespace std;
const int N = 100010;
int e[N], l[N], r[N], idx;
void init() {
    // 0 表示左端点， 1表示右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}
void add(int k, int x) {
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
    idx++;
}
void remove(int k) {
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}
int main() {
    init();
    int M, k, x; string op;
    cin >> M;
    while(M--) {
        cin >> op;
        if(op == "L") cin >> x, add(0, x);
        else if(op == "R") cin >> x, add(l[1], x);
        else if(op == "D") cin >> k, remove(k + 1);
        else if(op == "IL") cin >> k >> x, add(l[k + 1], x);
        else cin >> k >> x, add(k + 1, x);
    }
    for(int i = r[0]; i != 1; i = r[i])
        cout << e[i] << " ";
    cout << endl;
    return 0;
}