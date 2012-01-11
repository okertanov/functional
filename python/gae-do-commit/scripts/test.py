import sys

class RouteDef(object):
    @classmethod
    def __repr__(cls):
        return cls.route


class MainRoute(RouteDef):
    route = '/'
    def get(self, *args):
        self.response.out.write('It works (wsgi main)!')



if __name__ == "__main__":
    print(repr(MainRoute()))

