import numpy as np
import cv2
from matplotlib import pyplot as plt
from find_obj import filter_matches, explore_match

img1 = cv2.imread('res/facetemplate.jpg',0) #query Image
img2 = cv2.imread('res/facetest.jpg',0) #train Image

# Initiate SIFT detector
orb = cv2.ORB()

# find the keypoints and descriptors with SIFT
kp1, des1 = orb.detectAndCompute(img1,None)
kp2, des2 = orb.detectAndCompute(img2,None)

# create a BFMatcher object
bf = cv2.BFMatcher(cv2.NORM_HAMMING)#, crossCheck=True)

# Match descriptors
matches = bf.knnMatch(des1, trainDescriptors = des2, k=2)

p1, p2, kp_pairs = filter_matches(kp1, kp2, matches)

res = p1/p2
#print p1

i = 0
m1 = np.array([])
m2 = np.array([])
mp_pairs = np.array([])

print p1
print p2

#Filter through the matches, out of bounds matches removed
for p in p1:
	if(p[0]>600 and p[0]<700 and p[1]>300 and p[1]<500):
		m1 = np.append(m1,p1[i] - np.array([420,0]), axis=0)
		m2 = np.append(m2,p2[i], axis=0)
		mp_pairs = np.append(mp_pairs,kp_pairs[i], axis=0)
	i+=1

m1 = np.reshape(m1,(-1,2))
m2 = np.reshape(m2,(-1,2))

stackSize = m1.size / 2
ratio = np.sum(m1/m2, axis=0)

print stackSize
print ratio

print "Similarity"
xSim = abs(((stackSize - ratio[0]) / stackSize) * 100)
ySim = abs(((stackSize - ratio[1]) / stackSize) * 100)

print xSim
print ySim

if (((xSim + ySim)/2) > 40):
	print "Match"
else:
	print "Not Similar"

#print m2
#print mp_pairs

#myMatch1 = filter(lambda x: x[0]>200 and x[1]>150,p1)
#myMatch2 = filter(lambda x: x[0]>200 and x[1]>150,p2)
#myPairs = filter(lambda x: x[0]>50 and x[1]>50,kp_pairs)

#print myMatch1
#print myMatch2
#print myPairs

explore_match('find_obj', img1, img2, kp_pairs) # cv2 shows images

# Sort them in the order of their distance
#matches = sorted(matches, key = lambda x:x.distance)

# Draw first 10 matches
#img3 = cv2.drawMatches(img1,p1,img2,p2,kp_pairs[:10], flags=2)

#plt.imshow(img3),plt.show()

cv2.waitKey()
cv2.destroyAllWindows()

