class DepthMap:

    @staticmethod
    def __get_height(x):
        return 0.00116 * x - 36.888

    @staticmethod
    def _get_pos_of_most_focused(images, x, y):
        points = [image.acutance[x][y] for image in images]
        most_focused_index = points.index(max(points))
        return DepthMap.__get_height(images[most_focused_index].focus)

    @staticmethod
    def get_depth_map(images):
        return [[DepthMap._get_pos_of_most_focused(images, x, y)
                 for y in range(len(images[0].acutance[0]))]
                for x in range(len(images[0].acutance))]
