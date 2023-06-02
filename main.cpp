/*** 
 * @Author: Jacob-biu 2777245228@qq.com
 * @Date: 2023-05-21 00:38:57
 * @LastEditors: Jacob-biu 2777245228@qq.com
 * @LastEditTime: 2023-05-21 09:43:01
 * @FilePath: /WebFileServer/main.cpp
 * @Description: 
 * @Copyright (c) 2023 by Jacob John, All Rights Reserved. 
 */

#include "server.h"

int main(void){
    WebServer webserver;

    // 创建线程池
    int ret = webserver.createThreadPool(4);
    if(ret != 0){
        std::cout << outHead("error") << "创建线程池失败" << std::endl;
        return -1;
    }

    // 初始化用于监听的套接字
    int port = 8888;
    ret = webserver.createListenFd(port);
    if(ret != 0){
        std::cout << outHead("error") << "创建并初始化监听套接字失败" << std::endl;
        return -2;
    }

    // 初始化监听的epoll例程
    ret = webserver.createEpoll();
    if(ret != 0){
        std::cout << outHead("error") << "初始化监听的epoll例程失败" << std::endl;
        return -3;
    }
    // 向 epoll 中添加监听套接字
    ret = webserver.epollAddListenFd();
    if(ret != 0){
        std::cout << outHead("error") << "epoll 添加监听套接字失败" << std::endl;
        return -4;
    }

    // 开启监听并处理请求
    ret = webserver.waitEpoll();
    if(ret != 0){
        std::cout << outHead("error") << "epoll 例程监听失败" << std::endl;
        return -5;
    }
    
    return 0;
}
