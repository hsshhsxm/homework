from ltp import LTP

def findFood(sentence):
    ltp = LTP()
    words, hidden = ltp.seg([sentence])
    posTags = ltp.pos(hidden)
    words = words[0] #分词结果list
    print(words)
    posTags = posTags[0] #词性标注结果list
    print(posTags)
    dep = ltp.dep(hidden)[0] #依存句法分析结果list
    for t in dep:
        print(t)
    relyId = [d[1] for d in dep] #父节点id list
    relation = [d[2] for d in dep] #关系结果 list
    heads = ['Root' if id == 0 else words[id - 1] for id in relyId] #父节点内容
    for i in range(len(words)):
        if 'n' in posTags[i] and heads[i] == '吃' and relation[i] == 'VOB':
            print("找到了一种食物：" + words[i])

if __name__ == "__main__":
    str = "我想吃火锅。你吃雪糕。他吃番茄炒鸡蛋。"
    findFood(str)