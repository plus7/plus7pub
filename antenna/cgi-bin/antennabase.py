class NotImplementedException(Exception):
    pass

class MustBeOverridenException(Exception):
    pass

class Crawler:
    def __init__(self, config):
        self.config = config
        loadConfig(config)
    def loadConfig(self, fileName):
        raise NotImplementedException
    def type(self):
        raise MustBeOverridenException
    def run(self):
        raise MustBeOverridenException

class FeedModel:
    def __init__(self, feed):
        self.feed = feed
        loadFeed(feed)
    def type():
        raise MustBeOverridenException
    def items():
        raise NotImplementedException

class FeedItem:
    def __init__(self):
        a
    def name(self):
        return _name
    def uri(self):
        return _uri
    def mail(self):
        return _mail
    def content(self):
        return _content
    def date(self):
        return _date

class FeedView:
    def __init__(self, model):
        self.model = model
    def output(itemlen, length):
        raise MustBeOverridenException
