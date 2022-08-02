import numpy
from scipy import ndimage


class Acutance:
    # round
    # 0 1 0
    # 1 0 1
    # 0 1 1
    #
    # cross (default)
    # 0 1 0
    # 1 1 1
    # 0 1 0
    #
    # square
    # 1 1 1
    # 1 1 1
    # 1 1 1

@staticmethod
def _get_acutance_for_pixel(image, x, y, fun, kernel):
    if kernel == 'round':
        return fun([image[x - 1][y], image[x][y - 1], image[x + 1][y], image[x][y + 1]])
    elif kernel == 'cross':
        return fun([image[x][y], image[x - 1][y], image[x][y - 1], image[x + 1][y], image[x][y + 1]])
    elif kernel == 'square':
        return fun([image[x - 1][y - 1], image[x - 1][y], image[x - 1][y + 1],
                    image[x][y - 1], image[x][y], image[x][y + 1],
                    image[x + 1][y - 1], image[x + 1][y], image[x + 1][y + 1]])
    else:
        raise NotImplementedError()

@staticmethod
def difference(image, kernel='cross'):
    return [[abs(Acutance._get_acutance_for_pixel(image.matrix, x, y, numpy.mean, kernel) - image.matrix[x][y])
             for y in range(1, image.matrix.shape[1] - 1)]
            for x in range(1, image.matrix.shape[0] - 1)]

    @staticmethod
    def rmse(image, kernel='cross'):
        """
        Root mean square error
        """
        return [[numpy.sqrt(
            numpy.mean(
                numpy.square(
                    Acutance._get_acutance_for_pixel(image.matrix, x, y, numpy.array, kernel) - image.matrix[x][y])))
            for y in range(1, image.matrix.shape[1] - 1)]
            for x in range(1, image.matrix.shape[0] - 1)]

    @staticmethod
    def gaussian_laplace(image, kernel_size=3):
        return ndimage.gaussian_laplace(image, kernel_size)

    @staticmethod
    def gaussian_gradient_magnitude(image, kernel_size=4):
        return ndimage.gaussian_gradient_magnitude(image, kernel_size)

    @staticmethod
    def prewitt(image):
        return ndimage.prewitt(image, cval=1)

    @staticmethod
    def sobel(image):
        return ndimage.sobel(image)

    @staticmethod
    def convolve(image, kernel):
        return ndimage.convolve(image, kernel)
