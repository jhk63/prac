
# pip install opencv-python

import cv2
import numpy as np

img = cv2.imread("lenna.png")
image2 = img.copy()
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

gray2 = cv2.GaussianBlur(gray, (5, 5), 0)
gray2 = cv2.bitwise_not(gray2)

blurring_mask1 = np.array([[1 / 9, 1 / 9, 1 / 9], [1 / 9, 1 / 9, 1 / 9], [1 / 9, 1 / 9, 1 / 9]])
blurring_mask2 = np.array([[1 / 25, 1 / 25, 1 / 25, 1 / 25, 1 / 25], [1 / 25, 1 / 25, 1 / 25, 1 / 25, 1 / 25],
                           [1 / 25, 1 / 25, 1 / 25, 1 / 25, 1 / 25], [1 / 25, 1 / 25, 1 / 25, 1 / 25, 1 / 25],
                           [1 / 25, 1 / 25, 1 / 25, 1 / 25, 1 / 25]])

smoothing_mask = np.array([[1 / 16, 1 / 8, 1 / 16], [1 / 8, 1 / 4, 1 / 8], [1 / 16, 1 / 8, 1 / 16]])

sharpening_mask1 = np.array([[-1, -1, -1], [-1, 9, -1], [-1, -1, -1]])
sharpening_mask2 = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])

bs_mask = np.array([[-1/9, -1/9, -1/9], [-1/9, 1, -1/9], [-1/9, -1/9, -1/9]])

blurring_out1 = cv2.filter2D(gray, -1, blurring_mask1)
blurring_out2 = cv2.filter2D(gray, -1, blurring_mask2)

smoothing_out = cv2.filter2D(gray, -1, smoothing_mask)

sharpening_out1 = cv2.filter2D(gray, -1, sharpening_mask1)
sharpening_out2 = cv2.filter2D(gray, -1, sharpening_mask2)

blurringAndsharpening_out1 = cv2.filter2D(blurring_out1, -1, sharpening_mask1)
blurringAndsharpening_out2 = cv2.filter2D(blurring_out1, -1, bs_mask)

# cv2.imshow('blurring(3X3)', blurring_out1)
# cv2.imshow('blurring(5X5)', blurring_out2)

# cv2.imshow('smoothing', smoothing_out)

# cv2.imshow('sharpening1', sharpening_out1)
# cv2.imshow('sharpening2', sharpening_out2)

# cv2.imshow('test', blurringAndsharpening_out1)
cv2.imshow('test1', blurringAndsharpening_out2)


# -TEST2-----------------------------------------------------------------------------------------
# 아웃라인 필터
edge = cv2.Canny(gray2, 100, 100)
_, thresh = cv2.threshold(gray2, 127, 255, cv2.THRESH_BINARY)
adaptive_threshold= cv2.adaptiveThreshold(gray2, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)

thresh = cv2.erode(thresh, None, iterations=2)
thresh = cv2.dilate(thresh, None, iterations=2)

contours, hierachy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

sorted_contours = sorted(contours, key=cv2.contourArea, reverse=True)

for i in range(len(sorted_contours)):
    contour = sorted_contours[i]
    
    epsilon = 0.01 * cv2.arcLength(contour, True)
    approx = cv2.approxPolyDP(contour, epsilon, True)

    cv2.drawContours(img, [contour], -1, (0,255,0), 3)
    cv2.drawContours(image2, [approx], -1, (0,255,0), 3)

    extLeft = tuple(contour[contour[:, :, 0].argmin()][0])
    extRight = tuple(contour[contour[:, :, 0].argmax()][0])
    extTop = tuple(contour[contour[:, :, 1].argmin()][0])
    extBot = tuple(contour[contour[:, :, 1].argmax()][0])

    cv2.circle(img, extLeft, 8, (0, 0, 255), -1)
    cv2.circle(img, extRight, 8, (0, 255, 0), -1)
    cv2.circle(img, extTop, 8, (255, 0, 0), -1)
    cv2.circle(img, extBot, 8, (255, 255, 0), -1)


# cv2.imshow('contour', img)
cv2.imshow('approx', image2)
# -----------------------------------------------------------------------------------------------

# -TEST3-----------------------------------------------------------------------------------------
# Kenny 필터
src = cv2.imread("lenna.png")

med_val = np.median(src)
lower = int(max(0, 0.7 * med_val))

upper = int(min(255,1.3*med_val))

dst = cv2.GaussianBlur(src, (3,3), 0,0)
dst = cv2.Canny(dst,lower, upper,3)

cv2.imshow('dst', dst)
# -----------------------------------------------------------------------------------------------

cv2.imshow("original", gray)

cv2.waitKey(0)
cv2.destroyAllWindows()
