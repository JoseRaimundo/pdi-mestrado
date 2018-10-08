
import numpy
import re
import sys
import scipy.misc
import subprocess
import os.path
from scipy.ndimage import gaussian_filter

from numpy.lib.stride_tricks import as_strided as ast

import math
import cv2

ref_file = "Janela8.jpeg"
dist_file = "Janela0.jpeg"

ref = scipy.misc.imread(ref_file, flatten=True).astype(numpy.float32)
dist = scipy.misc.imread(dist_file, flatten=True).astype(numpy.float32)
ssim_values = []

original = cv2.imread(ref_file)
contrast = cv2.imread(dist_file,1)

def psnr(img1, img2):
    mse = numpy.mean( (img1 - img2) ** 2 )
    if mse == 0:
        return 100
    PIXEL_MAX = 255.0
    return 20 * math.log10(PIXEL_MAX / math.sqrt(mse))



def ssim_exact(img1, img2, sd=1.5, C1=0.01**2, C2=0.03**2):
    mu1 = gaussian_filter(img1, sd)
    mu2 = gaussian_filter(img2, sd)
    mu1_sq = mu1 * mu1
    mu2_sq = mu2 * mu2
    mu1_mu2 = mu1 * mu2
    sigma1_sq = gaussian_filter(img1 * img1, sd) - mu1_sq
    sigma2_sq = gaussian_filter(img2 * img2, sd) - mu2_sq
    sigma12 = gaussian_filter(img1 * img2, sd) - mu1_mu2

    ssim_num = ((2 * mu1_mu2 + C1) * (2 * sigma12 + C2))

    ssim_den = ((mu1_sq + mu2_sq + C1) * (sigma1_sq + sigma2_sq + C2))

    ssim_map = ssim_num / ssim_den
    return numpy.mean(ssim_map)


d=psnr(original,contrast)
print('{:.3f}'.format(d))
ss = ssim_exact(ref/255, dist/255)
print('{:.3f}'.format(ss))