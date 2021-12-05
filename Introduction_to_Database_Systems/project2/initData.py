import pymysql

class MySQL:
    def __init__(self):
        self.db = pymysql.connect(host = "localhost", user = "usr", password = "usr", db = "STU", charset = "utf8")
        self.cursor = self.db.cursor()
    
    def createtable(self):
        createStudentTable = """CREATE TABLE 学生(
                                学号 CHAR(10) NOT NULL,
                                姓名 VARCHAR(20),
                                年龄 INT, 
                                性别 CHAR(1),
                                PRIMARY KEY(学号)
                                )CHARSET=utf8;"""
        createScoreTable = """CREATE TABLE 选课(
                                学号 CHAR(10) NOT NULL,
                                课程号 CHAR(4) NOT NULL,
                                成绩 INT,
                                PRIMARY KEY(学号, 课程号)
                                )CHARSET=utf8;"""
        createCourseTable = """CREATE TABLE 课程(
                                课程号 CHAR(4) NOT NULL,
                                课程名称 VARCHAR(20),
                                教师 VARCHAR(10),
                                PRIMARY KEY(课程号)
                                )CHARSET=utf8;"""
        self.cursor.execute(createStudentTable)
        self.cursor.execute(createScoreTable)
        self.cursor.execute(createCourseTable)
    
    def initData(self):
        insertDataIntoStu = """INSERT INTO 学生 (学号,姓名,年龄,性别)
                                VALUES
                                (1700011111, '张同学', 22, '男'),
                                (1800012222, '李同学', 21, '女'),
                                (1700012343, '王同学', 22, '男'),
                                (1900013333, '赵同学', 20, '女'),
                                (1900014213, '吴同学', 20, '女');
                                """ 
        insertDataIntoSco = """INSERT INTO 选课 (学号,课程号,成绩)
                                VALUES
                                (1700011111, 00001, 91),
                                (1700011111, 00002, 89),
                                (1700011111, 00003, 95),
                                (1700012343, 00001, 86),
                                (1700012343, 00002, 85),
                                (1700012343, 00003, 89),
                                (1800012222, 00001, 88),
                                (1800012222, 00002, 84),
                                (1900013333, 00001, 92),
                                (1900014213, 00001, 93);
                                """
        insertDataIntoCou = """INSERT INTO 课程 (课程号, 课程名称, 教师)
                                VALUES
                                (00001, '高等数学1', '刘老师'),
                                (00002, '高等数学2', '刘老师'),
                                (00003, '线性代数', '张老师');
                                """
        self.cursor.execute(insertDataIntoStu)
        self.cursor.execute(insertDataIntoSco)
        self.cursor.execute(insertDataIntoCou)
        self.db.commit()
        

a = MySQL()
a.createtable()
a.initData()

