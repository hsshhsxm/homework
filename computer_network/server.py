# -*- coding: utf-8 -*-

import socket
import time 
import os 
from threading import Thread
import select
import threading
import json
import shutil
import sys
import hashlib
from signal import signal, SIGPIPE, SIG_DFL, SIG_IGN
signal(SIGPIPE, SIG_IGN)
import shutil

IP = '192.168.0.6'
SERVER_PORT = 12306
LISTEN_QUENE = 20
BUFFER_SIZE = 1024

#服务器端文件存储路径，根据环境改变
USER_PATH = '/home/pu/Documents/CloudDisk/drive/'

#传输控制信号
USER_REGISTER = 1
USER_LOGIN = 2
FILE_UPLOAD = 3
FILE_DOWNLOAD = 4
FILE_VERSION_LIST = 5
FILE_SHARE = 6
FILE_GET = 7
FILE_DELETE = 8
CLOSE = 9

'''
User_Dict存储用户信息，key为username，value为password
File_Version为文件历史版本索引，key为path+filename，value为列表[file_version,...]
'''
User_Dict = {}
File_Version = {}

class File:
    def __init__(self):
        self.username = ''
        self.filename = ''
        self.md5 = ''

class File_list:
    def __init__(self):
        self.cnt = ''


server_socket = None  # 负责监听的socket
client_pool = []  # 连接池


"""接收新连接"""
def accept_client():
    while True:
        client_socket, addr = server_socket.accept()  # 阻塞，等待客户端连接
        client_pool.append([client_socket,addr])# 加入连接池
        thread = Thread(target=message_handle, args=(client_socket,addr))# 给每个客户端创建一个独立的线程进行管理
        thread.setDaemon(True)# 设置成守护线程
        thread.start()

"""keep alive"""
def keep_alive(client_socket):
    sum = 0   # 无回应次数
    while True:
        time.sleep(10)
        if sum<5:
            try:
                client_socket.sendall("HeartBeat".encode(encoding='utf8'))
                sum=0
            except socket.error:
                sum = sum + 1
                continue
        else:
            client_socket.close()# 删除连接
            client_pool.remove(client_socket)

def md5check(filename):
    fp = open(filename,'r')
    fcont = fp.read()
    fp.close()
    fmd5 = hashlib.md5(fcont)
    return fmd5

#0表示注册成功，1表示已有用户名存在
def user_register(name,password):
    if name in User_Dict:
        return 1
    else:
        User_Dict[name] = password
        '''为用户创建文件夹'''
        path = USER_PATH + name
        file_path = path + '/' + name#用户文件夹,目录/drive/name/name
        ver_path = path + '/' + name + '_ver'#存储历史版本的文件夹/drive/name/name_ver
        os.makedirs(file_path)
        os.makedirs(ver_path)
        return 0

#0表示登陆成功，1表示密码错误，2表示无此用户名
def user_login(name,password):
    if name in User_Dict:
        if User_Dict[name] == password:
            return 0
        else:
            return 1
    else:
        return 2

def file_download(username,path,filename,client_socket):
    filepath = USER_PATH+username+path+filename
    print("download at ", filepath)
    if os.path.exists(filepath):
        fp =open(filepath,'r')
        fc = fp.read()
        fp.close()
        client_socket.sendall(fc.encode('utf8'))
        time.sleep(1)
        client_socket.sendall("_EXIT_".encode('utf8'))
    else:
        client_socket.sendall("_DELETE_".encode('utf8'))#表示想要获取的文件已被删除
        
    


"""消息处理"""
def message_handle(client_socket,addr):
    print("地址为",addr,"的客户端连接成功")
    while True:
        control = client_socket.recv(1).decode(encoding='utf8')#首先接收控制信号，命令为int
        print("地址为",addr,"的客户端使用命令",control)
        if control != '':
            control = int(control)
        if control == USER_REGISTER:#注册，假定发过来的信号格式为name password
            user_temp = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            user= str(user_temp).split()
            judge = user_register(user[0],user[1])
            print("地址为",addr,"的客户端注册使用的用户名是",user[0],"密码是",user[1])
            if judge == 1:#用户名已存在，注册失败
                client_socket.sendall("1\n".encode(encoding='utf8'))
                print("地址为",addr,"的客户端注册失败")
            else:#注册成功
                client_socket.sendall("0\n".encode(encoding='utf8'))
                print("地址为",addr,"的客户端注册成功")
            continue

        elif control == USER_LOGIN:#登陆,假定发过来的信号格式为name password
            user_temp = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            print(user_temp)
            user= str(user_temp).split()
            judge = user_login(user[0],user[1])
            if judge == 0:#登陆成功
                client_socket.sendall("0\n".encode(encoding='utf8'))
                print("地址为",addr,"的客户端登陆成功")
            elif judge == 1:#密码错误
                client_socket.sendall("1\n".encode(encoding='utf8'))
                print("地址为",addr,"的客户端登陆密码错误")
            else:#此用户名不存在
                client_socket.sendall("2\n".encode(encoding='utf8'))
                print("地址为",addr,"的客户端输入用户名不存在")
            continue
        

        elif control == FILE_UPLOAD:#上传文件，假定收到的信号为username path filename；返回确认后再上传文件
            print("地址为",addr,"的客户端上传文件")
            info = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            info_list = str(info).split()
            file_path = USER_PATH + info_list[0] + '/' + info_list[0] + info_list[1] 
            #创建路径
            if not os.path.exists(file_path):
                os.makedirs(file_path)
            exist_file_list = os.listdir(file_path)
            #版本管理
            if info_list[2] in exist_file_list:
                version_path = USER_PATH +info_list[0]+'/'+info_list[0]+ '_ver'
                shutil.move(file_path+'/'+info_list[2],version_path+'/'+info_list[2])
                file_ver = version_path +'/'+ info_list[2]
                (v_filepath, temp_ver_filename) = os.path.split(file_ver)
                (filename_ver, extension) = os.path.splitext(temp_ver_filename)
                t = time.strftime('%Y-%m-%d_%H:%M:%S',time.localtime(time.time()))
                os.rename(version_path +'/'+ info_list[2],version_path +'/'+filename_ver + t + extension)#给文件名加上时间表示版本
                File_Version[file_path+'/'+info_list[2]].append(filename_ver + t + extension)
                #如果旧版本超过十个就删除
                if len(File_Version[file_path+'/'+info_list[2]]) > 10:
                    dele_file_name = USER_PATH + info_list[0] + '/' + info_list[0]+ '_ver'+'/'+File_Version[file_path+'/'+info_list[2]][0]
                    File_Version[file_path+'/'+info_list[2]].pop(0)
                    os.remove(dele_file_name)
            else:
                File_Version[file_path+'/'+info_list[2]] = []
            #发送确认，表示可以接收文件
            client_socket.sendall("0\n".encode(encoding='utf8'))
            print("send ack\n")
            #接收文件
            fp = open(file_path+'/'+info_list[2],'a')
            size = 0
            while True:
                data = client_socket.recv(BUFFER_SIZE)
                print(data.decode('utf8'), "END_OF_LINE")
                if not data:
                    break
                if data.decode('utf8') == "_EXIT_":
                    break
                size = size + 1
                if size == 1:
                    print("正在接收来自",addr,"的文件")
                else:
                    print(".")
                #写入文件
                fp.write(data.decode(encoding = 'utf8'))
            if size > 0:
                print("来自",addr,"的",info_list[2],"文件传送完毕")
                client_socket.sendall("0\n".encode(encoding='utf8'))#返回确认
            else:
                print("来自",addr,"的",info_list[2],"文件传送失败")
                client_socket.sendall("1\n".encode(encoding='utf8'))#返回接收失败
            fp.close()
            continue
            
        elif control == FILE_DOWNLOAD:#下载文件,假定收到的信号为username path filename
            print("地址为",addr,"的客户端正在下载文件")
            info = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            info_list = str(info).split()
            #path = '/'+info_list[0]+info_list[1]
            file_download(info_list[0],info_list[1],info_list[2],client_socket)
            print("地址为",addr,"的客户端下载文件完成")
            continue

        elif control == FILE_VERSION_LIST:#查看文件的历史版本，假定接收到的信号为username path filename，由于直接传list可能出错，先转换成json再发送
            info = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            info_list = str(info).split()
            file_path = USER_PATH + info_list[0] + '/' + info_list[0] + info_list[1]
            filename = info_list[2]
            if file_path+'/'+filename in File_Version:#如无版本列表，返回空列表
                json_string = json.dumps(File_Version[file_path+'/'+filename])
                client_socket.sendall(json_string.encode('utf8'))
                print("地址为",addr,"的客户端所查找的文件的版本列表已返回")
            continue

        elif control == FILE_SHARE:#分享文件，假定收到的信号为username path filename
            file_info = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            file_info_list= str(file_info).split()
            share_link = "share://"+ "." +file_info_list[0] + "." + file_info_list[1] + "." + file_info_list[2]
            client_socket.sendall(share_link.encode(encoding='utf8'))
            print("地址为",addr,"的客户端创建分享链接成功")
            continue

        elif control == FILE_GET:#获取分享的文件,假定收到的信号为share://.username.path.filename
            share_info = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            share_link = share_info.split('.')
            username = share_link[1]#name
            path = '/' + username + share_link[2]#/path
            filename = share_link[3] + '.' + share_link[4]#file
            file_download(username,path,filename,client_socket)
            print("地址为",addr,"的客户端下载分享的文件成功")
            continue

        elif control == FILE_DELETE:#删除服务器端文件，假定收到的消息为username path filename
            info = client_socket.recv(BUFFER_SIZE).decode(encoding='utf8')
            info_list = str(info).split()
            file_path = USER_PATH + info_list[0] + '/' + info_list[0] + info_list[1] + '/' +info_list[2]
            os.remove(file_path)        
            client_socket.sendall("0\n".encode(encoding='utf8'))#返回成功确认
            print("地址为",addr,"的客户端删除文件成功")
            continue
        elif control == CLOSE:
            print(addr,"temp_close")
            #client_socket.close()
            break


if __name__ == '__main__':
    """初始化服务器端"""
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建 socket 对象
    server_socket.bind((IP,SERVER_PORT))
    server_socket.listen(LISTEN_QUENE)  # 最大等待数
    path = USER_PATH
    print("服务端已启动，在端口",SERVER_PORT,"等待客户端连接")
    if os.path.exists(path):
        shutil.rmtree(path)

    # 新开一个线程，用于接收新连接
    thread = Thread(target=accept_client)
    thread.setDaemon(True)
    thread.start()

    # 主线程逻辑
    while True:
        cmd = input()
        if cmd == 'exit':
            exit()