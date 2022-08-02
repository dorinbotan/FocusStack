import numpy

class MicroscopeImage:
    def __init__(self, raw_image, zoom=None, focus=None, led=None):
        self.raw_image = raw_image
        self.matrix = numpy.array(raw_image)
        self._acutance = None
        self.zoom = zoom
        self.focus = focus
        self.led = led

    def __repr__(self):
        to_return = "Image made with "
        to_return += "zoom={}, ".format(self.zoom) if self.zoom else "unknown zoom, "
        to_return += "focus={}, ".format(self.focus) if self.focus else "unknown focus, "
        to_return += "led={}".format(self.led) if self.led is not None else "unknown led state"
        return to_return

    @property
    def acutance(self):
        return self._acutance

    @acutance.setter
    def acutance(self, value):
        self._acutance = value
