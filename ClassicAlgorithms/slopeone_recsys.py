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


def transpose(users):
    """转置users 使其为items的表达方式 items = {itemID:{userID:score ...} ... }
    """
    items ={}
    for u in users:
        for i in users[u]:
            items.setdefault(i,{})
            items[i][u] = users[u][i]
    return items

def devij(items):
    """计算item_i item_j 的差
       结果的上三角矩阵用字典表示{item1:{item2:dev ...} ...}
    """
    item = items.keys()
    dev = {}
    for i in range(len(item) - 1):
        dev.setdefault(item[i], {})
        for j in range(i+1,len(item)):
            dev[item[i]][item[j]] = diff(items[item[i]], items[item[j]])
    return dev

def diff(item1, item2):
    """compute difference of two items
       item = {user:score ...}
    """
    count = 0.0
    sum_diff = 0
    for k in item1:
        if k in item2:
            count += 1
            sum_diff += (item1[k] - item2[k])
    if count != 0:
        return (sum_diff / count, count )  # count 就是diff 的权重
    else:
        return None

def userrate(userID , itemID, users, dev):
    """userID rate itemID
    """
    if (itemID not in users[userID]):
        sum_count = 0.0
        sum_score = 0.0
        for j in users[userID]:
            if itemID in dev: # 由于dev 是上三角矩阵 所以需要判断
                if j in dev[itemID]:
                    dev_ij = dev[itemID][j][0] # dev_ij 意思就是 i - j
                    count = dev[itemID][j][1]
                else:
                    dev_ij = -dev[j][itemID][0]
                    count = dev[j][itemID][1]
            else:
                dev_ij = -dev[j][itemID][0]
                count = dev[j][itemID][1]
            sum_score += (dev_ij + users[userID][j]) * count
            sum_count += count
        return sum_score / sum_count

if __name__ == '__main__':
    items = transpose(users)
    dev = devij(items)
    #for k in dev:
    #    print k ,dev[k]
    #    print("\n")
    userID = "Veronica"
    itemID = "Vampire Weekend"
    print userID, itemID,userrate(userID, itemID, users, dev)
