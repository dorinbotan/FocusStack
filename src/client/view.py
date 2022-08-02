import numpy
from matplotlib import pyplot


class View:

    @staticmethod
    def plot(depth_map):
        min_h = min(min(depth_map, key=min))
        max_h = max(max(depth_map, key=max))

        fig, axes = pyplot.subplots(2, sharex='all')

        im = axes[0].pcolor(depth_map, cmap='jet', vmin=min_h, vmax=max_h)
        fig.colorbar(im, ax=axes.ravel().tolist(), ticks=numpy.linspace(min_h, max_h, 15, endpoint=True))

        axes[1].plot(depth_map[540])
        pyplot.show()
