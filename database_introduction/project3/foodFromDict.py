#!/usr/bin/env python
# coding=utf-8

'''
添加food列，用于存储饮食的结果，不包含饮食内容时，为空
食物名字从饮食词库food.txt中查找，判断分词的结果是否在词库中
食物名字之间空空格分隔

ALTER TABLE project.travel_poi_checkin_weibos_suzhou ADD food_from_dict varchar(512) DEFAULT NULL;
'''

import pymysql
import time
import os
from ltp import LTP

class food:
    def __init__(self, url, usrname, usrpwd, dbname):
        try:
            self.db = pymysql.connect(host = url, user = usrname, password = usrpwd, database = dbname)
            self.cursor = self.db.cursor()
            self.foodSet = set()
            path = os.getcwd()
            folder = os.path.join(path, "log")
            if not os.path.exists(folder):
                os.makedirs(folder)
            fileName = "log/findFoodFromDictLog.log"
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
    
    def readFromFile(self):
        f = open("foodDict.txt", "r")
        for line in f.readlines():
            line = line.strip()
            self.foodSet.add(line)
        f.close()

    def executeCmd(self, No):
        cmd = "SELECT id, word_split FROM project.travel_poi_checkin_weibos_suzhou LIMIT " + str(No-1) + ",1;"
        self.cursor.execute(cmd)
        self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd + "\n", time.localtime()))
        print(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd, time.localtime()))
        row = self.cursor.fetchone()
        if not row:
            return
        id = row[0]
        splitedWord = row[1]
        if len(splitedWord) == 0:
            return
        wordList = splitedWord.split()
        string = ''
        for word in wordList:
            if word in self.foodSet:
                string += word
                string += ' '
        if len(string) == 0:
            return
        if string == ' ':
            return
        cmd = "UPDATE project.travel_poi_checkin_weibos_suzhou SET food_from_dict=\'" + string + "\' WHERE id=" + str(id) + ";"
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
    db = food("localhost", "hs", "hs", "project")
    num =db.getNum()
    db.readFromFile()
    #已进行至50000
    for i in range(1, num + 1):
        try:
            db.executeCmd(i)
        except:
            pass
            continue
        if i % 50 == 0:
            db.commit()