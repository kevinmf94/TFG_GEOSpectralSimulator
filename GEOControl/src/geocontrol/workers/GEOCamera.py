from .GEOWorker import GEOWorker
import os


class GEOCamera(GEOWorker):

    def __init__(self, client, csv_file, generate_images=False, filename="Output", path="outputs/"):
        GEOWorker.__init__(self, client, csv_file)
        self.index = 0
        self.item = self.data.loc[self.index]
        self.generate_images = generate_images
        self.filename = filename
        self.path = path

    def notify(self, time):

        if not self.is_finish() and int(self.data.loc[self.index][0]) == time:

            self.item = self.data.loc[self.index]

            # Call client
            self.client.set_camera_lookat(int(self.item[1]), self.item[2], self.item[3], self.item[4])

            if self.item[5] == 1:
                try:
                    os.mkdir(self.path)
                except FileExistsError:
                    pass

                channels = self.item[6].split("|")

                for channel in channels:
                    file_path = os.path.abspath(self.path + self.filename + str(self.index) + channel + ".png")
                    self.client.get_image(int(self.item[1]), file_path, channel)

            self.index = self.index + 1

    def is_finish(self):
        return self.index >= self.data.shape[0]
