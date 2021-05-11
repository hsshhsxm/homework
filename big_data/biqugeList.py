import requests
from bs4 import BeautifulSoup
import time
import os
import sys
import csv

class spiderForList():
    def __init__(self,No1, No2):
        self.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:52.0) Gecko/20100101 Firefox/52.0",
            "Accept": "*/*",
            "Accept-Language": "zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3",
            "Accept-Encoding": "",
            "Connection": "keep-alive",
        }
        self.path = os.path.abspath(os.path.dirname(__file__)) + os.sep + "result" + os.sep
        self.url = "https://www.biquge5200.cc/" + str(No1) + "_" + str(No2) + "/"
        self.No = int(No2)
        self.resList = []
        self.name = ""
        self.author = ""
        self.bookClass = ""
        self.intro = ""
    
    def mkdir(self):
        folder = os.path.exists(self.path)
        if not folder:
            os.makedirs(self.path) 
            print("makedir : result")
    
    def createCSV(self):
        filePath = self.path + "res" + ".csv"
        with open(filePath, 'w', encoding='utf8') as f:
            csvWrite = csv.writer(f)
            dataRow = ["编号", "类别", "书名", "作者", "简介"]
            csvWrite.writerow(dataRow)

    def writeToFile(self):
        filePath = self.path + "res" + ".csv"
        with open(filePath, 'a', encoding='utf8') as f:
            csvWrite = csv.writer(f)
            dataRow = [self.No, self.bookClass, self.name, self.author, self.intro]
            csvWrite.writerow(dataRow)
    
    def getContent(self):
        try:
            req = requests.get(url = self.url, headers = self.headers)
            req.raise_for_status()
            html = BeautifulSoup(req.text, "html.parser")
            self.name = html.find('div',id = 'info').h1.get_text()
            author = html.find('div',id = 'info').p.get_text()
            self.author = author.split("：")[1]
            self.bookClass = html.find('div', class_ = "con_top").findAll('a')[-1].get_text()
            self.intro = html.find('div',id = 'intro').p.get_text()
            #dataRow = [self.No, self.bookClass, self.name, self.author, self.intro]
            #print(dataRow)
            self.writeToFile()
            print("正在获取编号为" + str(self.No) + ",书名为《" + self.name + "》的信息")
            time.sleep(1)
        except:
            s = sys.exc_info()
            print("Error '%s' happened on line %d" % (s[1], s[2].tb_lineno))
            print("Getting " + self.No + "content failed")
            pass 

if __name__ == "__main__":
    No1 = 0
    No2  = 147747
    for i in range(1, No2 + 1):
        sp = spiderForList(No1, i)
        sp.mkdir()
        if i == 1:
            sp.createCSV()
        try:
            sp.getContent()
        except:
            pass 
            continue
    
