class RSSCrawler:
    def __init__(self, config):
        self.urllist = []
        self.config = config
        loadConfig(config)
    def loadConfig(self, fileName):
        raise NotImplementedException
    def type(self):
        raise MustBeOverridenException
    def run(self):
        raise MustBeOverridenException
