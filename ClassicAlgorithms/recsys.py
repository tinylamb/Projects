# coding: utf-8
from math import sqrt

users = {"Angelica": {"Blues Traveler": 3.5, "Broken Bells": 2.0, "Norah Jones": 4.5, "Phoenix": 5.0, "Slightly Stoopid": 1.5, "The Strokes": 2.5, "Vampire Weekend": 2.0},
         "Bill":{"Blues Traveler": 2.0, "Broken Bells": 3.5, "Deadmau5": 4.0, "Phoenix": 2.0, "Slightly Stoopid": 3.5, "Vampire Weekend": 3.0},
         "Chan": {"Blues Traveler": 5.0, "Broken Bells": 1.0, "Deadmau5": 1.0, "Norah Jones": 3.0, "Phoenix": 5, "Slightly Stoopid": 1.0},
         "Dan": {"Blues Traveler": 3.0, "Broken Bells": 4.0, "Deadmau5": 4.5, "Phoenix": 3.0, "Slightly Stoopid": 4.5, "The Strokes": 4.0, "Vampire Weekend": 2.0},
         "Hailey": {"Broken Bells": 4.0, "Deadmau5": 1.0, "Norah Jones": 4.0, "The Strokes": 4.0, "Vampire Weekend": 1.0},
         "Jordyn":  {"Broken Bells": 4.5, "Deadmau5": 4.0, "Norah Jones": 5.0, "Phoenix": 5.0, "Slightly Stoopid": 4.5, "The Strokes": 4.0, "Vampire Weekend": 4.0},
         "Sam": {"Blues Traveler": 5.0, "Broken Bells": 2.0, "Norah Jones": 3.0, "Phoenix": 5.0, "Slightly Stoopid": 4.0, "The Strokes": 5.0},
         "Veronica": {"Blues Traveler": 3.0, "Norah Jones": 5.0, "Phoenix": 4.0, "Slightly Stoopid": 2.5, "The Strokes": 3.0}
        }

def cosine(varX, varY):
    """计算向量的cos值
    varX = [x1 ... xn]
    varY = [y1 ... yn]
    """
    f = lambda x, y: x*y
    sum_xy = sum(map(f, varX, varY))
    sum_x2 = sum(map(f, varX, varX))
    sum_y2 = sum(map(f, varY , varY))
    try:
        return sum_xy /(sqrt(sum_x2 * sum_y2))
    except ZeroDivisionError:
        pass

def cosDis(rate1, rate2):
    """计算cos距离
    rate = {movie_i:score_i ... }
    """
    varX = []
    varY = []
    for key in rate1:
        if key in rate2:
            varX.append(rate1[key])
            varY.append(rate2[key])
    return cosine(varX, varY)


def pearsonDis(rate1, rate2):
    """计算pearson 距离
    rate = {movie_i:score_i ...}
    """
    varX = []
    varY = []
    for key in rate1:
        if key in rate2:
            varX.append(rate1[key])
            varY.append(rate2[key])
    try:
        #pearson 其实是 中心化后的向量余弦
        meanX = (sum(varX) + 0.0) / len(varX)
        meanY = (sum(varY) + 0.0) / len(varY)
        varX = [i - meanX for i in varX]
        varY = [i -meanY for i in varY]
        return cosine(varX, varY)
    except ZeroDivisionError:
        pass



def computeNeighbor(username, users ,simi=pearsonDis):
    """creates a sorted list of users based on their distance to username"""
    distances = []
    for user in users:
        if user != username:
            distance = simi(users[user], users[username])
            distances.append((distance, user)) # if nothing in common distance.append((None,userName))
    # sort based on distance --  最相似的优先
    distances.sort(reverse = True)
    return distances

def recommend(username, users):
    """Give list of recommendations"""
    # 计算username与其他用户的相似度
    neighbor = computeNeighbor(username, users) # [ (distance, user) ...]

    # 选择较为相似的用户
    simiusers = [i for i in neighbor if i[0] > 0.75] # 标准是相关系数 > 0.75
    if simiusers != []:
        #compute contribution
        sum_dis = sum([i[0] for i in simiusers])
        simiusers = [(i[0] / sum_dis, i[1]) for i in simiusers] # simiusers = [(simi,userID) ...]
        #compute recommendation items
        recItems = {}
        for u in simiusers:
            coeff = u[0] # u[0] = simi
            for item in users[u[1]]: # u[1] = userID
                recItems[item] = recItems.get(item, 0) + coeff * users[u[1]][item]
        Items = sorted(recItems.items(), key = lambda k: k[1], reverse = True)
        Items = [i[0] for i in Items if i[0] not in users[username]]
        return Items
    else:
        return []

if __name__ == '__main__':
    for u in users:
        print u,"\n",recommend(u,users),"\n\n"

