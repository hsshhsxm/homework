import tkinter
import tkinter.messagebox as messagebox
import pymysql

class MySQL:
    def __init__(self):
        self.db = pymysql.connect(host = "localhost", user = "usr", password = "usr", db = "STU", charset = "utf8")
        self.cursor = self.db.cursor()

class Application:
    def __init__(self):
        self.mysql = MySQL()
        self.window = tkinter.Tk()
        self.window.title("Project2")
        self.window.geometry('600x300')
        self.b1 = tkinter.Button(self.window, text = "检索刘老师所授课程的课程号、课程名", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB1())
        self.b2 = tkinter.Button(self.window, text = "检索年龄大于20岁的男同学的学号和姓名", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB2())
        self.b3 = tkinter.Button(self.window, text = "检索至少选修刘老师所授课程中一门课的学生姓名", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB3())
        self.b4 = tkinter.Button(self.window, text = "检索王同学不学的课程的课程号", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB4())
        self.b5 = tkinter.Button(self.window, text = "检索至少选修两门课的学生学号", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB5())
        self.b6 = tkinter.Button(self.window, text = "检索全部学生都选修的课程号与课程名", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB6())
        self.b7 = tkinter.Button(self.window, text = "检索选修课程包括刘老师所授课程的学生学号", highlightbackground='#3E4149', width = 40, command = lambda: self.executeB7())
        self.b8 = tkinter.Button(self.window, text = "退出", highlightbackground='#3E4149', command=self.window.quit)
        self.b1.pack()
        self.b2.pack()
        self.b3.pack()
        self.b4.pack()
        self.b5.pack()
        self.b6.pack()
        self.b7.pack()
        self.b8.pack()
        self.window.mainloop()

    def printInfo(self,str):
        messagebox.showinfo(str)
    
    def executeB1(self):
        sql = "select 课程号,课程名称 from 课程 where 教师 = '刘老师';"
        try:
            lst = []
            lst.append("检索刘老师所授课程的课程号、课程名")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("课程号：" + row[0] + "，课程名称：" + row[1])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")
        
    def executeB2(self):
        sql = "select 学号,姓名 from 学生 where 年龄 > 20 and 性别 = '男';"
        try:
            lst = []
            lst.append("检索年龄大于20岁的男同学的学号和姓名")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("学号：" + row[0] + "，姓名：" + row[1])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")

    def executeB3(self):
        sql = """select distinct 姓名 from 学生,选课,课程 
                where 学生.学号 = 选课.学号 and 选课.课程号 in (select 课程号 from 课程
                                                            where 教师 = '刘老师');
            """
        try:
            lst = []
            lst.append("检索至少选修刘老师所授课程中一门课的学生姓名")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("姓名：" + row[0])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")

    def executeB4(self):
        sql = """select 课程号 from 课程 
                where 课程号 not in ( select 课程号 from 学生,选课
                                    where 姓名 = '王同学' and 学生.学号 = 选课.学号);
            """
        try:
            lst = []
            lst.append("检索王同学不学的课程的课程号")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("课程号：" + row[0])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")

    def executeB5(self):
        sql = """select 学号 from 学生
                where 学号 in (select 学号 from 选课 
                                group by 学号 having count(*) >=2
                                );
            """
        try:
            lst = []
            lst.append("检索至少选修两门课的学生学号")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("学号：" + row[0])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")

    def executeB6(self):
        sql = """select distinct 课程.课程号, 课程.课程名称 from 学生,选课,课程
                where 选课.学号 = 学生.学号 and 选课.课程号 = 课程.课程号
                group by 选课.课程号, 课程名称 having count(*) = (select count(*) from 学生);
            """
        try:
            lst = []
            lst.append("检索全部学生都选修的课程号与课程名")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("课程号：" + row[0] + "，课程名称：" + row[1])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")

    def executeB7(self):
        sql = """select 学号 from 学生
                where 学号 in ( select 学号 from 选课,课程
                                where 课程.教师 = '刘老师' and 课程.课程号 = 选课.课程号
                                );
            """
        try:
            lst = []
            lst.append("检索选修课程包括刘老师所授课程的学生学号")
            lst.append("检索语句为：")
            lst.append(sql)
            lst.append("检索结果为：")
            rowsCount = self.mysql.cursor.execute(sql)
            if rowsCount > 0:
                results = self.mysql.cursor.fetchall()
                for row in results:
                    lst.append("学号：" + row[0])
            else:
                lst.append("空集")
            tmp = tkinter.Tk()
            tmp.title("检索结果")
            ex = tkinter.Button(tmp, text = "退出", highlightbackground='#3E4149', command=tmp.destroy)
            textLst = []
            for item in lst:
                textLst.append(tkinter.Label(tmp, text = item))
            for item in textLst:
                item.pack()
            ex.pack()
        except:
            self.printInfo("错误，无法获取数据")
    


app = Application()


