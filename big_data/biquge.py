import requests
from bs4 import BeautifulSoup
import time
import os
import sys

class spider():
    def __init__(self, No1, No2):
        self.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:52.0) Gecko/20100101 Firefox/52.0",
            "Accept": "*/*",
            "Accept-Language": "zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3",
            "Accept-Encoding": "",
            "Connection": "keep-alive",
        }
        self.path = os.path.abspath(os.path.dirname(__file__)) + os.sep + "novel_result" + os.sep
        self.url = "https://www.biquge5200.cc/" + str(No1) + "_" + str(No2) + "/"
        self.No = "/" + str(No1) + "_" + str(No2) + "/"
        self.urlSet = set()
        self.urlList = []
        self.title = ""
    
    def mkdir(self):
        folder = os.path.exists(self.path)
        if not folder:
            os.makedirs(self.path) 
            print("makedir : novel_result")
    
    def getKey(self, myUrl):
        myUrl = myUrl.replace(self.url,"")
        myUrl = myUrl.replace(".html","")
        return int(myUrl)

    def getList(self):
        try:
            req = requests.get(self.url, headers = self.headers)
            req.raise_for_status()
            #req.encoding = 'utf8'
            html = BeautifulSoup(req.text, "html.parser")
            self.title = html.find('div',id = 'info').h1.get_text()
            #print(self.title)
            nurl = html.findAll('a')
            for i in nurl:
                #print(i.get('href'))
                #print(tmp)
                if not str(i.get('href')).find(self.url) :
                    self.urlSet.add(str(i.get('href')))
            self.urlList = list(self.urlSet)
            self.urlList.sort(key = self.getKey)
            #for i in self.urlList:
            #    print(i)
            print("小说《%s》有 %d 章" %(self.title, len(self.urlList)))  
        except:
            s = sys.exc_info()
            print("Error '%s' happened on line %d" % (s[1], s[2].tb_lineno))
            print("Getting url list failed")
    
    def writeToFile(self, chapterName, content):
        filePath = self.path + self.title + ".txt"
        with open(filePath, 'a', encoding='utf8') as f:
            f.write("KEY:" + chapterName + '\n')
            f.writelines("\n".join(content.split())+'\n')
            f.write('\n\n')

    def getContent(self):
        try:
            count = 0
            l = len(self.urlList)
            for url in self.urlList:
                count += 1 
                req = requests.get(url = url, headers = self.headers)
                req.raise_for_status()
                html = BeautifulSoup(req.text, "html.parser")
                chapterName = html.find('div',class_ = 'bookname').h1.get_text()
                content = html.find('div', id = 'content').get_text()
                chapterName = str(chapterName)
                chapterName.strip()
                self.writeToFile(chapterName, content)
                tmp = float(count)/l
                print("《%s》写入完成，当前进度%.2f%%"%(chapterName,tmp))
                time.sleep(1)
        except:
            s = sys.exc_info()
            print("Error '%s' happened on line %d" % (s[1], s[2].tb_lineno))
            print("Getting content failed")

if __name__ == "__main__":
    print("input url:")
    tmp = input()
    tmp = tmp.replace("https://www.biquge5200.cc/", "")
    tmp = tmp.replace("/", "")
    no = tmp.split('_', 1)
    sp = spider(no[0],no[1])
    sp.mkdir()
    sp.getList()
    sp.getContent()