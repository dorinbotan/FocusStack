import time
from io import BytesIO

import requests
from PIL import Image

from .microscopeimage import MicroscopeImage


class MicroscopeClientException(Exception):
    pass


class MicroscopeClientValueError(MicroscopeClientException):
    pass


class MicroscopeClient:
    def __init__(self, hostname, protocol='http'):
        self._hostname = hostname
        self._protocol = protocol
        self._host = "{}://{}".format(self._protocol, self._hostname)

    def _get(self, path):
        ans = requests.get("{}/{}".format(self._host, path))
        if not ans.ok:
            raise MicroscopeClientException('Get method - HTTP error, code {}'.format(ans.status_code))
        return ans

    def _put(self, path, json=None):
        ans = requests.put("{}/{}".format(self._host, path), json=json)
        if not ans.ok:
            raise MicroscopeClientException('Put method - HTTP error, code {}'.format(ans.status_code))

    def _post(self, path, json=None):
        ans = requests.post("{}/{}".format(self._host, path), json=json)
        if not ans.ok:
            raise MicroscopeClientException('Post method - HTTP error, code {}'.format(ans.status_code))

    def _delete(self, path):
        ans = requests.delete("{}/{}".format(self._host, path))
        if not ans.ok:
            raise MicroscopeClientException('Delete method - HTTP error, code {}'.format(ans.status_code))

    @property
    def zoom(self):
        ans = self._get('zoom')
        return ans.json()

    @zoom.setter
    def zoom(self, zoom_value):
        if not 0 <= zoom_value <= 16384:
            raise MicroscopeClientValueError('Zoom value outside range of 0..16384')
        self._put('zoom', json={'value': zoom_value})
        while self.zoom != zoom_value:
            time.sleep(0.1)

    @property
    def zoom_locked(self):
        ans = self._get('zoom/lock')
        return bool(ans.json())

    @zoom_locked.setter
    def zoom_locked(self, lock_value):
        if lock_value:
            self._post('zoom/lock')
        else:
            self._delete('zoom/lock')
        while self.zoom_locked != bool(lock_value):
            time.sleep(0.1)

    def toggle_zoom_lock(self):
        self._put('zoom/lock')

    @property
    def magnification(self):
        ans = self._get('magnification')
        return ans.json()

    @magnification.setter
    def magnification(self, magnification_value):
        if not 1 <= magnification_value <= 33:
            raise MicroscopeClientValueError('Magnification value outside range of 1..33')
        self._put('magnification', json={'value': magnification_value})
        while self.magnification != magnification_value:
            time.sleep(0.1)

    @property
    def focus(self):
        ans = self._get('focus')
        return ans.json()

    @focus.setter
    def focus(self, focus_value):
        if not 0 <= focus_value <= 59392:
            raise MicroscopeClientValueError('Zoom value outside range of 0..16384')
        self._put('focus', json={'value': focus_value})
        while self.focus != focus_value:
            time.sleep(0.1)

    @property
    def autofocus(self):
        ans = self._get('focus/auto')
        return bool(ans.json())

    @autofocus.setter
    def autofocus(self, autofocus_value):
        if autofocus_value:
            self._post('focus/auto')
        else:
            self._delete('focus/auto')
        while self.autofocus != bool(autofocus_value):
            time.sleep(0.1)

    def toggle_autofocus(self):
        self._put('focus/auto')

    @property
    def led(self):
        ans = self._get('led')
        return bool(ans.json())

    @led.setter
    def led(self, led_value):
        if led_value:
            self._post('led')
        else:
            self._delete('led')
        while self.led != bool(led_value):
            time.sleep(0.1)

    def toggle_led(self):
        self._put('led')

    @property
    def laser(self):
        ans = self._get('laser')
        return bool(ans.json())

    @laser.setter
    def laser(self, laser_value):
        if laser_value:
            self._post('laser')
        else:
            self._delete('laser')
        while self.laser != bool(laser_value):
            time.sleep(0.1)

    def toggle_laser(self):
        self._put('laser')

    def enable_ir(self):
        self._post('ir')

    def disable_ir(self):
        self._delete('ir')

    def enable_flip(self):
        self._post('flip')

    def disable_flip(self):
        self._delete('flip')

    def get_image_from_camera(self, **kwargs):
        ans = self._get('image')
        return MicroscopeImage(Image.open(BytesIO(ans.content)), **kwargs)

    def get_image_from_memory(self, image_name, **kwargs):
        ans = self._get('image/{}'.format(image_name))
        return MicroscopeImage(Image.open(BytesIO(ans.content)), **kwargs)

    def take_image_store_im_memory(self, image_name):
        self._post('image/{}'.format(image_name))

    def delete_image_form_memory(self, image_name):
        self._delete('image/{}'.format(image_name))

    def meta(self):
        return self._get("meta").text

    def get_focus_stack(self, zoom, minfoxus, maxfocus, steps):
        self._post('focusstack', json={'zoom': zoom, 'minfocus': minfoxus, 'maxfocus': maxfocus, 'steps': steps})
        meta = self.meta().split('\n')[:-1]
        zoom = int(meta.pop(0))
        focus_stack = [self.get_image_from_memory(name, zoom=zoom, focus=focus, led=bool(int(led)))
                       for name, focus, led in map(str.split, meta)]
        return focus_stack
