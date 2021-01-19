#include <iostream>
using namespace std;
const int N = 100010, INF = 1e8;

int n;
struct node {
  // key 二叉树权值 val 堆权值
  // cnt 本节点个数 size 子树 + 本节点个数
  int l, r, key, val, cnt, size;
}tr[N];

int root, idx;

void pushup(int p) {
  tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + tr[p].cnt;
}

int getNode(int key) {
  tr[++idx].key = key;
  tr[idx].val = rand();
  tr[idx].cnt = tr[idx].size = 1;
  return idx;
}

void build() {
  getNode(-INF), getNode(INF);
  root = 1, tr[1].r = 2;
  pushup(root);
}

void zig(int &p) {
  int q = tr[p].l; tr[p].l = tr[q].r, tr[q].r = p;
  p = q;
  pushup(tr[p].r); pushup(p);
}

void zag(int &p) {
  int q = tr[p].r; tr[p].r = tr[q].l, tr[q].l = p;
  p = q;
  pushup(tr[p].l); pushup(p);
}

int getRankByKey(int &p, int key) {
  if(!p) return 0;
  if(tr[p].key == key) return tr[tr[p].l].size + 1;
  else if(tr[p].key > key) return getRankByKey(tr[p].l, key);
  else return tr[tr[p].l].size + tr[p].cnt + getRankByKey(tr[p].r, key);
}

int getKeyByRank(int &p, int rank) {
  if(!p) return INF;
  if(tr[tr[p].l].size >= rank) return getKeyByRank(tr[p].l, rank);
  else if(tr[tr[p].l].size + tr[p].cnt >= rank) return tr[p].key;
  else return getKeyByRank(tr[p].r, rank - tr[tr[p].l].size - tr[p].cnt);
}

int getPrev(int &p, int key) {
  if(!p) return -INF;
  if(tr[p].key >= key) return getPrev(tr[p].l, key);
  return max(tr[p].key, getPrev(tr[p].r, key));
}

int getNext(int &p, int key) {
  if(!p) return INF;
  if(tr[p].key <= key) return getNext(tr[p].r, key);
  return min(tr[p].key, getNext(tr[p].l, key));
}



void insert(int &p, int key) {
  if(!p) p = getNode(key);
  else if(tr[p].key == key) tr[p].cnt++;
  else if(tr[p].key > key) {
    insert(tr[p].l, key);
    if(tr[tr[p].l].val > tr[p].val) zig(p);
  } else {
    insert(tr[p].r, key);
    if(tr[tr[p].r].val > tr[p].val) zag(p);
  }
  pushup(p);
}

void remove(int &p, int key) {
  if(!p) return;
  if(tr[p].key == key) {
    if(tr[p].cnt > 1) tr[p].cnt--;
    else if(tr[p].l || tr[p].r) {
      if(!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
        zig(p);
        remove(tr[p].r, key);
      } else {
        zag(p);
        remove(tr[p].l, key);
      }
    } else p = 0;
  } else if(tr[p].key > key) remove(tr[p].l, key);
  else remove(tr[p].r, key);
  pushup(p);
}

int main() {
  freopen("pppp.txt", "r", stdin);
  build();
  scanf("%d", &n);
  while(n--) {
    int opt, x;
    scanf("%d%d", &opt, &x);
    if(opt == 1) insert(root, x);
    else if(opt == 2) remove(root, x);
    else if(opt == 3) printf("%d\n", getRankByKey(root, x) - 1);
    else if(opt == 4) printf("%d\n", getKeyByRank(root, x + 1));
    else if(opt == 5) printf("%d\n", getPrev(root, x));
    else printf("%d\n", getNext(root, x));
  }
  return 0;
}