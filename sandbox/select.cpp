#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define MAX_CHILD 1024

void accept_loop(int soc)
{
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    int child[MAX_CHILD];
    struct timeval timeout;
    struct sockaddr_storage from;
    int acc, child_no, width, i, count, pos, ret;
    socklen_t len;
    fd_set mask;

    /* child配列の初期化 */
    for (i = 0; i < MAX_CHILD; i++) {
        child[i] = -1;
    }
    child_no = 0;
    for (;;) {
        /* select()用マスクの作成 */
        FD_ZERO(&mask);
        FD_SET(soc, &mask);
        width = soc + 1;
        count = 0;
        for (i = 0; i < child_no; i++) {
            if (child[i] != -1) {
                FD_SET(child[i], &mask);
                if (child[i] + 1 > width) {
                    width = child[i] + 1;
                    count++;
                }
            }
        }
        (void) fprintf(stderr, "<<child count:%d>>\n", count);
        /* select()用タイムアウト値のセット */
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        switch (select(width, (fd_set *) &mask, NULL, NULL, &timeout)) {
        case -1:
            /* エラー */
            perror("select");
            break;
        case 0:
            /* タイムアウト */
            break;
        default:
            /* レディ有り */
            if (FD_ISSET(soc, &mask)) {
                /* サーバソケットレディ */
                len = (socklen_t) sizeof(from);
                /* 接続受付 */
                if ((acc = accept(soc, (struct sockaddr *)&from, &len)) == -1) {
                    if(errno!=EINTR){
                        perror("accept");
                    }
                } else {
                    (void) getnameinfo((struct sockaddr *) &from, len,
                               hbuf, sizeof(hbuf),
                               sbuf, sizeof(sbuf),
                               NI_NUMERICHOST | NI_NUMERICSERV);
                    (void) fprintf(stderr, "accept:%s:%s\n", hbuf, sbuf);
                    /* childの空きを検索 */
                    pos = -1;
                    for (i = 0; i < child_no; i++) {
                        if (child[i] == -1) {
                            pos = i;
                            break;
                        }
                    }
                    if (pos == -1) {
                        /* 空きが無い */
                        if (child_no + 1 >= MAX_CHILD) {
                            /* childにこれ以上格納できない */
                            (void) fprintf(stderr,
					   "child is full : cannot accept\n");
                            /* クローズしてしまう */
                            (void) close(acc);
                        } else {
                            child_no++;
                            pos = child_no - 1;
                        }
                    }
                    if (pos != -1) {
                        /* childに格納 */
                        child[pos] = acc;
                    }
                }
            }
/* 準備が完了しているファイルディスクプタを調べる= 計算量:O(n) */            
            for (i = 0; i < child_no; i++) {
                if (child[i] != -1) {
                    if (FD_ISSET(child[i], &mask)) {
                        /* 送受信 */
                        // if ((ret = send(child[i],)) == -1) {
                        //     /* エラーまたは切断 */
                        //     /* クローズ */
                        //     (void) close(child[i]);
                        //     /* childを空きに */
                        //     child[i] = -1;
                        // }
                    }
                }
            }
	    break;
        }
    }
}
