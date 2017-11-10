# -*- coding: utf-8 -*- 
from collections import defaultdict
import cv2
import numpy as np
from skimage.segmentation import slic
from skimage.segmentation import mark_boundaries
from skimage.util import img_as_float
import matplotlib.pyplot as plt

def diff(p1,p2):
	weight = abs(np.int(p1) - np.int(p2))
	return weight

#Class to represent a graph
class Graph:

	def __init__(self,vertices,supern):
		self.V= vertices #No. of vertices
		self.supern = supern
		self.graph = {} # default dictionary to store graph
		self.cheapest = {}
		self.set = {}
		#self.get = {}

	def merge(self,father,son):
		for value in self.set[son]:
			self.set[father].append(value)
		del self.set[son]

	# function to add an edge to graph
	def addEdge(self,u,v,w):
		(u_x,u_y) = (u[0],u[1])
		(v_x,v_y) = (v[0],v[1])
		self.graph[((u_x,u_y),(v_x,v_y))] = [u,v,w]

	# A utility function to find set of an element i
	# (uses path compression technique)
	#一直往上会找到子集父点
	def find(self, parent, i):
		# if parent[i[0]][i[1]] == (i[0],i[1]):
		# 	return (i[0],i[1])
		# return self.find(parent, parent[i[0]][i[1]]) #传入本顶点的父点

		if parent.get((i[0],i[1])) == (i[0],i[1]):
			return (i[0],i[1])
		return self.find(parent, parent.get((i[0],i[1]))) #传入本顶点的父点

	# A function that does union of two sets of x and y
	# (uses union by rank)
	def union(self, parent, rank, x, y, u, v):
		xroot = self.find(parent, x)
		yroot = self.find(parent, y)
		# Attach smaller rank tree under root of high rank tree
		# (Union by Rank)
		# 哪个子集的等级大，谁做父集,找父集只是为了知道谁是谁的子集,与update edge无关
		if rank[xroot] < rank[yroot]:
			parent[xroot] = yroot #yroot is father
			bigroot = yroot
			smallroot = xroot
			self.merge(yroot,xroot)
		elif rank[xroot] > rank[yroot]:
			parent[yroot] = xroot
			bigroot = xroot
			smallroot = yroot
			self.merge(xroot,yroot)
		#If ranks are same, then make one as root and increment
		# its rank by one
		#如果等级一样, 随便选一个做集合parent顶点, 然后rank+1, rank形容子集的大小
		else :
			parent[yroot] = xroot
			bigroot = xroot
			smallroot = yroot
			self.merge(xroot,yroot)
			rank[xroot] += 1
		###### who is first node #####
		if (xroot[0] < yroot[0]) or (xroot[1] < yroot[1]):
			f_root = (xroot[0],xroot[1])
			s_root = (yroot[0],yroot[1])
		elif (yroot[0] < xroot[0]) or (yroot[1] < xroot[1]):
			f_root = (yroot[0],yroot[1])
			s_root = (xroot[0],xroot[1])

		# delete set's intrinic edges 
		for element1 in self.set[bigroot]:
			for element2 in self.set[bigroot]:
				if (element1 != element2) and ( self.graph.get(( (element1[0],element1[1]), (element2[0],element2[1]) )) != None ):
					#self.get[( (element1[0],element1[1]), (element2[0],element2[1]) )] = self.graph[( (element1[0],element1[1]), (element2[0],element2[1]) )]
					del self.graph[( (element1[0],element1[1]), (element2[0],element2[1]) )]
		####### update merged set #######
		(L,A,B) = (0,0,0) ; length = len(self.set[bigroot])
		for element in self.set[bigroot]:
			#print element
			L += element[2] ; A += element[3]; B += element[4]
		L /= length ; A /= length; B /= length
		for element in self.set[bigroot]:
			element[2] = L ; element[3] = A; element[4] = B
		#update average
		for element in self.set[bigroot]:
			u_x = element[0] ; u_y = element[1]
			d1 = self.graph.get(  (  (u_x-1,u_y),(u_x,u_y) )  ) #up
			d2 = self.graph.get(  (  (u_x,u_y-1),(u_x,u_y) )  ) #left
			d3 = self.graph.get(  (  (u_x,u_y),(u_x+1,u_y) )  ) #down
			d4 = self.graph.get(  (  (u_x,u_y),(u_x,u_y+1) )  ) #right
			if d1 != None:
				weight = diff(element[2],d1[1][2])
				self.graph[ (  (u_x-1,u_y),(u_x,u_y) ) ][1] = element
				self.graph[ (  (u_x-1,u_y),(u_x,u_y) ) ][2] = weight				
			if d2 != None:
				weight = diff(element[2],d2[1][2])
				self.graph[ (  (u_x,u_y-1),(u_x,u_y) ) ][1] = element
				self.graph[ (  (u_x,u_y-1),(u_x,u_y) ) ][2] = weight	
			if d3 != None:
				weight = diff(element[2],d3[1][2])
				self.graph[ (  (u_x,u_y),(u_x+1,u_y) ) ][0] = element
				self.graph[ (  (u_x,u_y),(u_x+1,u_y) ) ][2] = weight				
			if d4 != None:
				weight = diff(element[2],d4[1][2])
				self.graph[ (  (u_x,u_y),(u_x,u_y+1) ) ][0] = element
				self.graph[ (  (u_x,u_y),(u_x,u_y+1) ) ][2] = weight
		# print "update: " + str(new_edge)
		# print self.graph

	# The main function to construct MST using Kruskal's algorithm
	def boruvkaMST(self):
		# An array to store index of the cheapest edge of
		# subset. It store [u,v,w] for each component

		# Initially there are V different trees.
		# Finally there will be one tree that will be MST
		numTrees = self.V * self.V
		MSTweight = 0
		parent = {};rank={}
		for node_x in range(self.V):
			for node_y in range(self.V):
				parent[(node_x,node_y)] = (node_x,node_y)
				self.cheapest[(node_x,node_y)] = -1
				rank[(node_x,node_y)] = 0

		# Keep combining components (or sets) until all
		# compnentes are not combined into single MST
		round = 0
		while numTrees > 3000:
			# Traverse through all edges and update
			# cheapest of every component
			#for i in range(len(self.graph)):
			for value in self.graph.values():
				# Find components (or sets) of two corners
				# of current edge
				#u,v,w = self.graph[i]
				u,v,w = value
				if w == -1:
					continue
				#print value
				set1 = self.find(parent, u)
				set2 = self.find(parent ,v)

				# If two corners of current edge belong to
				# same set, ignore current edge. Else check if 
				# current edge is closer to previous
				# cheapest edges of set1 and set2
				#如果这一条边的两个顶点在同一个子集上则跳过，如果不在，
				#判断这条边是不是这两个顶点的比之前选择的权重最小边的权重更小的边，是则更新权重最小边
				if set1 != set2:
					if self.cheapest[set1] == -1 or self.cheapest[set1][2] > w : #complier will not check cheapest[set1][2], if cheaspest[set1] == -1 is true.
						self.cheapest[set1] = [u,v,w] #update set's new cheapest edges

					if self.cheapest[set2] == -1 or self.cheapest[set2][2] > w :
						self.cheapest[set2] = [u,v,w]

			# Consider the above picked cheapest edges and add them
			# to MST
			for node_x in range(self.V):
				for node_y in range(self.V):
					#Check if cheapest for current set exists
					#cheapest永远有vertice那么多个顶点，子集融合后的元素变-1
					#历遍整一个最小权重边集合，-1表示已经融合掉了（不存在），不处理
					if self.cheapest[(node_x,node_y)] != -1:
						if self.cheapest[(node_x,node_y)][2] != -1:
							#print cheapest[(node_x,node_y)]
							if numTrees < 2000  and numTrees % 100 == 0:
								print numTrees
							if numTrees == 3000:
								break
							u,v,w = self.cheapest[(node_x,node_y)]
							set1 = self.find(parent, u)
							set2 = self.find(parent ,v)
							if set1 != set2 : # 
								MSTweight += w
								self.union(parent, rank, set1, set2,u,v)
								#print ("Edge %d-%d with weight %d included in MST" % (u,v,w))
								#每次融合的时候，选一次权重最小边
								numTrees = numTrees - 1 #如果只剩下最后一棵树则停止
							else:
								self.cheapest[(node_x,node_y)] = -1

			#reset cheapest array
			#cheapest =[-1] * self.V
			for node_x in range(self.V):
				for node_y in range(self.V):
					self.cheapest[(node_x,node_y)] = -1


		myImg = [[0] * self.V] * self.V
		print len(self.set)
		for value in self.set.values():
			while(len(value)):
				item = value.pop()
				x = item[0]; y = item[1]; l = item[2]; a = item[3]; b = item[4]
				myImg[x][y] = [l,a,b]
		myImg = np.array(myImg)
		myImg = myImg.astype(np.uint8)
		myImg = cv2.cvtColor(myImg, cv2.COLOR_LAB2BGR)
		cv2.imwrite("test.png", myImg)
		show_myImg = cv2.imread("test.png")
		cv2.imshow("Image", show_myImg)   
		cv2.waitKey(0)  
		print ("Weight of MST is %d" % MSTweight)


#img = cv2.imread("all/flownet2prediction/flownet2_00018_pre.flo.png")
img = cv2.imread("all/alley_1/frame_0001.png")
segments = slic(img_as_float(img), n_segments = 300, sigma = 5)
print segments
print segments.shape
plt.imshow(mark_boundaries(img_as_float(cv2.cvtColor(img, cv2.COLOR_BGR2RGB)), segments))
#plt.imshow(img_as_float(cv2.cvtColor(img, cv2.COLOR_BGR2RGB), segments))
plt.show()
exit(3)
width = img.shape[0]
g = Graph(width,10)
sets = {}
img1 = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
print img1.shape
for i in range(0,width):
	for j in range(0,width):  # 512 * 511 * 2
		sets[(i,j)] = []
		sets[(i,j)].append([i,j,int(img1[i][j][0]),int(img1[i][j][1]),int(img1[i][j][2])])
		if i< width-1 and j < width-1:
			inten1 = img1[i][j][0]
			inten2 = img1[i][j+1][0]
			weight_right = diff(inten1,inten2)
			g.addEdge([i,j,inten1,img1[i][j][1],img1[i][j][2]],[i,j+1,inten2,img1[i][j+1][1],img1[i][j+1][2]],weight_right)

			inten1 = img1[i][j][0]
			inten2 = img1[i+1][j][0]
			weight_down = diff(inten1,inten2)
			g.addEdge([i,j,inten1,img1[i][j][1],img1[i][j][2]],[i+1,j,inten2,img1[i+1][j][1],img1[i+1][j][2]],weight_down)
		elif i<width-1 and j == width-1:
			inten1 = img1[i][j][0]
			inten2 = img1[i+1][j][0]
			weight_down = diff(inten1,inten2)
			g.addEdge([i,j,inten1,img1[i][j][1],img1[i][j][2]],[i+1,j,inten2,img1[i+1][j][1],img1[i+1][j][2]],weight_down)
		elif i==width-1 and j<width-1:
			inten1 = img1[i][j][0]
			inten2 = img1[i][j+1][0]
			weight_right = diff(inten1,inten2)
			g.addEdge([i,j,inten1,img1[i][j][1],img1[i][j][2]],[i,j+1,inten2,img1[i][j+1][1],img1[i][j+1][2]],weight_right)
g.set = sets
g.boruvkaMST()

#This code is contributed by Neelam Yadav

