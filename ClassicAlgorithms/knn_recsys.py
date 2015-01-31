# coding=utf-8
# 
#  Nearest Neighbor Classifier for Pima dataset
#
#  Code file for the book Programmer's Guide to Data Mining
#  http://guidetodatamining.com
import heapq
import random
import os

class Classifier:
    def __init__(self, bucketPrefix, testBucketNumber, dataFormat, k, metric):

        """ a classifier will be built from files with the bucketPrefix
        excluding the file with textBucketNumber. dataFormat is a string that
        describes how to interpret each line of the data files. 
        """
   
        self.medianAndDeviation = [] # 训练的结果
        self.k = k # k-NN
        self.p = metric # Minkowski 距离中的 p

        # reading the data in from the file
 
        self.format = dataFormat.strip().split('\t')
        self.data = [] #每一行用tuple保存，作为 data list中的一条
        # for each of the buckets numbered 1 through 10:
        for i in range(1, 11):
            # if it is not the bucket we should ignore, read in the data
            if i != testBucketNumber:
                filename = "%s-%02i" % (bucketPrefix, i)
                #f = open(filename)
                #lines = f.readlines()
                #f.close()
                with open(filename) as f:
                    lines = f.readlines()
                #print(lines[0])
                for line in lines:
                    fields = line.strip().split('\t')
                    ignore = []
                    vector = []
                    classification = ''
                    for i in range(len(fields)):
                        if self.format[i] == 'num':
                            vector.append(float(fields[i]))
                        elif self.format[i] == 'comment':
                            ignore.append(fields[i])
                        elif self.format[i] == 'class':
                            classification = fields[i]
                    self.data.append((classification, vector, ignore))
        self.rawData = list(self.data)
        # get length of Feature vector  计算特征向量的维度
        self.vlen = len(self.data[0][1])
        # now normalize the data
        for i in range(self.vlen):
            self.normalizeColumn(i)
        
    
    ##################################################
    ###
    ###  CODE TO COMPUTE THE MODIFIED STANDARD SCORE

    def getMedian(self, alist):
        """return median of alist"""
        if alist == []:
            return []
        blist = sorted(alist)
        length = len(alist)
        if length % 2 == 1:
            # length of list is odd so return middle element
            return blist[int(((length + 1) / 2) -  1)]
        else:
            # length of list is even so compute midpoint
            v1 = blist[int(length / 2)]
            v2 =blist[(int(length / 2) - 1)]
            return (v1 + v2) / 2.0
        

    def getAbsoluteStandardDeviation(self, alist, median):
        """given alist and median return absolute standard deviation"""
        sum = 0
        for item in alist:
            sum += abs(item - median)
        return sum / len(alist)


    def normalizeColumn(self, columnNumber):
       """given a column number, normalize that column in self.data"""
       # first extract values to list
       col = [v[1][columnNumber] for v in self.data]
       median = self.getMedian(col)
       asd = self.getAbsoluteStandardDeviation(col, median)
       #print("Median: %f   ASD = %f" % (median, asd))
       self.medianAndDeviation.append((median, asd)) # 训练的结果1.特征normal化  2.保存每个特征的(median, asd)
       for v in self.data:
           v[1][columnNumber] = (v[1][columnNumber] - median) / asd


    def normalizeVector(self, v):
        """We have stored the median and asd for each column.
        We now use them to normalize vector v"""
        vector = list(v)
        for i in range(len(vector)):
            (median, asd) = self.medianAndDeviation[i]
            vector[i] = (vector[i] - median) / asd
        return vector
    ###
    ### END NORMALIZATION
    ##################################################

    def testBucket(self, bucketPrefix, bucketNumber):
        """Evaluate the classifier with data from the file
        bucketPrefix-bucketNumber"""
        
        filename = "%s-%02i" % (bucketPrefix, bucketNumber)
        with open(filename) as f:
            lines = f.readlines()
        #f = open(filename)
        #lines = f.readlines()
        #f.close()
        totals = {}
        for line in lines:
            data = line.strip().split('\t')
            vector = []
            classInColumn = -1
            for i in range(len(self.format)):
                  if self.format[i] == 'num':
                      vector.append(float(data[i]))
                  elif self.format[i] == 'class':
                      classInColumn = i
            theRealClass = data[classInColumn]
            #print("REAL ", theRealClass)
            classifiedAs = self.classify(vector)
            totals.setdefault(theRealClass, {})
            totals[theRealClass].setdefault(classifiedAs, 0)
            totals[theRealClass][classifiedAs] += 1
        # totals = {'1': {'1': 7, '0': 6}, '0': {'1': 4, '0': 23}}
        return totals



    def minkowski(self, vector1, vector2, p):
        func = lambda v1, v2:pow(abs(v1 - v2), p)
        dis = pow(sum(map(func, vector1, vector2)), 1.0/p)
        return dis

    def manhattan(self, vector1, vector2):
        """Computes the Manhattan distance."""
        return self.minkowski(vector1, vector2, 1)
        #return sum(map(lambda v1, v2: abs(v1 - v2), vector1, vector2))

    def euclidean(self, vector1, vector2):
        return self.minkowski(vector1, vector2, 2)


    def nearestNeighbor(self, itemVector):
        """return nearest neighbor to itemVector"""
        return min([ (self.minkowski(itemVector, item[1]), item, self.p) for item in self.data])
    
    def knn(self, itemVector):
        """returns the predicted class of itemVector using k
        Nearest Neighbors"""
        # changed from min to heapq.nsmallest to get the
        # k closest neighbors
        neighbors = heapq.nsmallest(self.k, [(self.minkowski(itemVector, item[1], self.p), item) for item in self.data])
        # heapq.nsmallest() 这里还有默认排序key的
        # each neighbor gets a vote
        #print(neighbors[0]) neighbors = [(distance, (class,normalVector)) ... ]
        results = {}
        for neighbor in neighbors: 
            theClass = neighbor[1][0]
            results[theClass] = results.get(theClass, 0) + 1
            #第二种计数方法
            #results.setdefault(theClass, 0)
            #results[theClass] += 1
        #print(results)
        resultList = sorted(results.items(), key=lambda k:k[1], reverse=True) # 字典结果排序
        # resultList = [(class, votes) ... ]
        #resultList = sorted([(i[1], i[0]) for i in results.items()], reverse=True)

        #get all the classes that have the maximum votes
        maxVotes = resultList[0][1]
        possibleAnswers = [i[0] for i in resultList if i[1] == maxVotes]
        # randomly select one of the classes that received the max votes
        answer = random.choice(possibleAnswers)
        return answer

    def classify(self, itemVector):
        """Return class we think item Vector is in"""
        # k represents how many nearest neighbors to use
        return(self.knn(self.normalizeVector(itemVector)))                             
 

       
def tenfold(bucketPrefix, dataFormat, k, metric):
    results = {}
    for i in range(1, 11):
        c = Classifier(bucketPrefix, i, dataFormat, k, metric)
        t = c.testBucket(bucketPrefix, i)
        for (key, value) in t.items():
            results.setdefault(key, {})
            for (ckey, cvalue) in value.items():
                results[key].setdefault(ckey, 0)
                results[key][ckey] += cvalue
                
    # now print results
    categories = list(results.keys())
    categories.sort()
    print(   "\n       Classified as: ")
    header =    "        "
    subheader = "      +"
    for category in categories:
        header += "% 2s   " % category
        subheader += "-----+"
    print (header)
    print (subheader)
    total = 0.0
    correct = 0.0
    for category in categories:
        row = " %s    |" % category 
        for c2 in categories:
            if c2 in results[category]:
                count = results[category][c2]
            else:
                count = 0
            row += " %3i |" % count
            total += count
            if c2 == category:
                correct += count
        print(row)
    print(subheader)
    print("\n%5.3f percent correct" %((correct * 100) / total))
    print("total of %i instances" % total)

if __name__ == '__main__':

    print("\n\nLARGE DATA SET")
    tenfold(os.getcwd() + "/pima/pima", "num	num	num	num	num	num	num	num	class", 3, 2)

