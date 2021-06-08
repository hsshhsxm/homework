#!/usr/bin/env python
# coding=utf-8

'''
添加cleanedText列，用于文本清洗的结果，去除url、tag等
ALTER TABLE project.travel_poi_checkin_weibos_suzhou ADD cleanedText varchar(512) DEFAULT NULL;
'''

import pymysql
import time
import threading
import os
from weibo_preprocess_toolkit import WeiboPreprocess

class cleanText:
    def __init__(self, url, usrname, usrpwd, dbname):
        try:
            self.db = pymysql.connect(host = url, user = usrname, password = usrpwd, database = dbname)
            self.cursor = self.db.cursor()
            self.preprocess = WeiboPreprocess()
            path = os.getcwd()
            folder = os.path.join(path, "log")
            if not os.path.exists(folder):
                os.makedirs(folder)
            fileName = "log/cleanTextLog.log"
            full = os.path.join(path, fileName)
            self.logFile = open(fileName, mode = 'a+')
            self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 打开数据库成功\n", time.localtime()))
            print(time.strftime("%Y-%m-%d %H:%M:%S 打开数据库成功", time.localtime()))
        except:
            self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 打开数据库失败\n", time.localtime()))
            print(time.strftime("%Y-%m-%d %H:%M:%S 打开数据库失败", time.localtime()))
    
    def __del__(self):
        self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 关闭数据库\n", time.localtime()))
        print(time.strftime("%Y-%m-%d %H:%M:%S 关闭数据库", time.localtime()))
        self.db.close()
    
    #获得总条数
    def getNum(self):
        cmd = "SELECT COUNT(*) FROM project.travel_poi_checkin_weibos_suzhou;"
        self.cursor.execute(cmd)
        num = self.cursor.fetchone()[0]
        self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 数据共" + str(num) + "行\n", time.localtime()))
        print(time.strftime("%Y-%m-%d %H:%M:%S 数据共" + str(num) + "行", time.localtime()))
        return num
    
    #第n行分词
    def clean(self, No):
        cmd = "SELECT id,text FROM project.travel_poi_checkin_weibos_suzhou LIMIT " + str(No-1) + ",1;"
        self.cursor.execute(cmd)
        self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd + "\n", time.localtime()))
        print(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd, time.localtime()))
        row = self.cursor.fetchone()
        if not row:
            return
        id = row[0]
        text = row[1]
        #print(str(id) + " " + text)
        wordSplited = self.preprocess.clean(text, simplified=False)
        cmd = "UPDATE project.travel_poi_checkin_weibos_suzhou SET cleanedText=\'" + wordSplited + "\' WHERE id=" + str(id) + ";"
        #print(cmd)
        try:
            self.cursor.execute(cmd)
            self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd + "\n", time.localtime()))
            print(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd, time.localtime()))
        except:
            self.db.rollback()
            self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 执行失败，回滚\n", time.localtime()))
            print(time.strftime("%Y-%m-%d %H:%M:%S 执行失败，回滚", time.localtime()))
    
    def commit(self):
        self.db.commit()
        self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 向数据库提交\n", time.localtime()))
        print(time.strftime("%Y-%m-%d %H:%M:%S 向数据库提交", time.localtime()))

if __name__ == "__main__":
    db = cleanText("localhost", "hs", "hs", "project")
    num =db.getNum()
    #已进行至26900
    for i in range(1, num + 1):
        db.clean(i)
        if i % 50 == 0:
            db.commit()

