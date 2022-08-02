import os
import time

from PIL import Image

from acutance import Acutance
from depthmap import DepthMap
from microscope import MicroscopeClient
from microscope import MicroscopeImage
from view import View


def load(path):
    with open(os.path.join(path, 'meta.txt')) as f:
        meta = f.read().split('\n')[:-1]
    zoom = int(meta.pop(0))
    return [
        MicroscopeImage(Image.open(os.path.join(path, name)).convert('L'), zoom=zoom, focus=focus, led=bool(int(led)))
        for name, focus, led in map(str.split, meta)]


tt = time.monotonic()
c = MicroscopeClient('192.168.1.222')
img = c.get_focus_stack(16384, 30000, 36000, 256)
# here = os.path.dirname(os.path.realpath(__file__))
# img = load(os.path.join(here, 'stack_old'))
print('Images loaded in {} seconds'.format(time.monotonic() - tt))

tt = time.monotonic()
for i, image in enumerate(img):
    t = time.monotonic()
    image.acutance = Acutance.ptp(image)
    print('Acutance for image {} made in {} seconds'.format(i, time.monotonic() - t))
print('Acutance for all images calculated in {} seconds'.format(time.monotonic() - tt))

tt = time.monotonic()
depth_map = DepthMap.get_depth_map(img)
print('Depth map calculated in {} seconds'.format(time.monotonic() - tt))

View.plot(depth_map)
