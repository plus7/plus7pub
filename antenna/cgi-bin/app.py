class App:
    def __init__(self, config):
        self.config = config
    def loadConfig:
        raise NotImplementedException
    def crawl:
        raise NotImplementedException
    def print(self, format, itemlen, length):
        if format == "text":
            printText(itemlen, length)
        elif format == "html":
            printHtml(itemlen, length)
        elif format == "rss1":
            printRss1(itemlen, length)
        elif format == "rss2":
            printRss2(itemlen, length)
        elif format == "atom":
            printAtom(itemlen, length)
        elif format == "json":
            printJson(itemlen, length)
        else:
            raise Exception("invalid format specification")
