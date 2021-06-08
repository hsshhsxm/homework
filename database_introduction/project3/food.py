#!/usr/bin/env python
# coding=utf-8

'''
引用：
在微博饮食分析中，我们需要用到分词、词性标注和依存句法分析。
当研究一条微博判断是否发生饮食行为时，我们可以对微博内容的分词结果用这样一条规则：
用含词语“吃”+与“吃”相关的句法关系为VOB（动宾关系）+“吃”的宾语为名词这三个条件来过滤。
如果符合这个有三个条件的规则，则可以判定为发生了饮食行为，且提取出来的“吃”的宾语就是饮食行为涉及的食品。

添加food列，用于存储饮食的结果，不包含饮食内容时，为空
食物的名称按照上述规则来，其他情况太多，暂不考虑
食物名字之间空空格分隔

ALTER TABLE project.travel_poi_checkin_weibos_suzhou ADD food varchar(512) DEFAULT NULL;
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

    def findFood(self,sentence):
        ltp = LTP()
        words, hidden = ltp.seg([sentence])
        posTags = ltp.pos(hidden)
        words = words[0] #分词结果list
        posTags = posTags[0] #词性标注结果list
        dep = ltp.dep(hidden)[0] #依存句法分析结果list
        relyId = [d[1] for d in dep] #父节点id list
        relation = [d[2] for d in dep] #关系结果 list
        heads = ['Root' if id == 0 else words[id - 1] for id in relyId] #父节点内容
        string = ''
        for i in range(len(words)):
            if 'n' in posTags[i] and heads[i] == '吃' and relation[i] == 'VOB':
                string += words[i]
                string += ' '
        return string
    
    def executeCmd(self, No):
        cmd = "SELECT id,cleaned_text FROM project.travel_poi_checkin_weibos_suzhou LIMIT " + str(No-1) + ",1;"
        self.cursor.execute(cmd)
        self.logFile.write(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd + "\n", time.localtime()))
        print(time.strftime("%Y-%m-%d %H:%M:%S 执行命令" + cmd, time.localtime()))
        row = self.cursor.fetchone()
        if not row:
            return
        id = row[0]
        text = row[1]
        string = self.findFood(text)
        if len(string) == 0:
            return
        cmd = "UPDATE project.travel_poi_checkin_weibos_suzhou SET food=\'" + string + "\' WHERE id=" + str(id) + ";"
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
    #已进行至1000
    for i in range(1, num + 1):
        db.executeCmd(i)
        if i % 50 == 0:
            db.commit()

