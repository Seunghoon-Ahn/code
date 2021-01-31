#include <iostream>
#include <climits>
#include <cstdlib>
using namespace std;

void path(int n);

typedef struct node {
    int x;
    int y;
    int length;
    int bound;
}NODE;

/*
bool operator < (node t, node u) {
    return t.bound > u.bound;
}
priority_queue< node > q;

NODE N[11];
int Field[21][21];
//bool Bcheck[11] = { 0 };

int main(void) {
    int fieldx, fieldy;
    int sx, sy;
    int nodecnt;
    int i = 1;
    int tmp1, tmp2;
    int res = 0;

    cin >> fieldx >> fieldy;
    cin >> sx >> sy;
    cin >> nodecnt; // 점의 갯수 (시작점 제외)
    N[0] = NODE{ sx, sy, 0 , 0 };
    while (i <= nodecnt) {
        cin >> tmp1 >> tmp2;
        N[i] = NODE{ tmp1, tmp2, 0,  INT_MAX };
        i++;
    }

    i = 1;
    while (i <= nodecnt) {   // 시작점에서 다른 점으로의 bound를 계산해서 큐에 넣음
        N[i].bound = abs(N[i].lx - sx) + abs(N[i].ly - sy);
        q.push(N[i]);
        i++;
    }
    bool Bcheck[11] = { 0 };
    i = 1;
    int lastnum = 0;
    while (i <= nodecnt) {
        int nodenum;
        int checknum = 0;

        NODE point = q.top();
        q.pop();
        for (int i = 1; i <= nodenum; i++) {
            if (point.lx == N[i].lx && point.ly == N[i].ly)
                nodenum = i;
        }
        //if (nodenum == 0) {
            for (int i = 1; i <= nodecnt; i++)
                if (Bcheck[i] == false)
                    checknum++;
            if (!checknum) {
                lastnum = i;
                res = N[nodenum].bound;
                break;
            }
        //}
    }
    return 0;
}

*/


int nodenum;  //점 개수 - 시작점
NODE Find[100000];
NODE arr[100];
NODE B[100];
int cnt = 1;
int in = 1;

int main(void) {
    int n, m;    // 좌표 크기
    int sx, sy; //시작점
    int res = INT_MAX; //최종 경로 길이 업데이트
    int tmp1, tmp2;

    cin >> n >> m;
    cin >> sx >> sy;
    arr[0].x = sx;
    arr[0].y = sy;
    cin >> nodenum;
    for (int i = 1; i <= nodenum; i++) {
        cin >> tmp1 >> tmp2;
        B[i].x = tmp1;
        B[i].y = tmp2;
    }

    path(1);

    for (int i = 1; i <= cnt - 1; i++)
        if (Find[i].length + abs(Find[i].x - sx) + abs(Find[i].y - sy) < res)
            res = Find[i].length + abs(Find[i].x - sx) + abs(Find[i].y - sy);

    cout << "The shortest path has length " << res;
    return 0;
}

void path(int n) {
    if (n == nodenum + 1) {
        for (int i = 1; i <= n-1; i++) {
            Find[cnt].length += arr[i].length;
        }
        Find[cnt].x = arr[n - 1].x;
        Find[cnt].y = arr[n - 1].y;
        cnt++;
    }

    for (int i = 1; i <= nodenum; i++) {
        if (!B[i].bound) {
            B[i].bound = 1;
            arr[in].length = abs(B[i].x - arr[in - 1].x) + abs(B[i].y - arr[in - 1].y);
            arr[in].x = B[i].x;
            arr[in].y = B[i].y;
            in++;
            path(n + 1);
            B[i].bound = 0;
            in--;
        }
    }
}