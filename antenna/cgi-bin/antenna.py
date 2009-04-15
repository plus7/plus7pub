#!/usr/bin/python

import antennabase

import textview, htmlview, rss1view, rss2view, atomview, jsonview
import bbs2chmodel, rssmodel, atommodel, compositemodel
import bbs2chcrawler, rsscrawler, atomcrawler

class Antenna:
    def loadConfig(self, fileName):
        #raise NotImplementedException
        pass
    def run(self):
        try:
            self.crawl()
            self.output(options)
        except Exception as exp:
            print "Content-Type: text/plain"
            print
            print "Error while running.\n"
            print "details:\n"
            print exp
    def crawl(self):
        # 設定ファイルに基づき、Crawlerを生成
        for each target in crawl_list do
            crawler = NewCrawler(target)
            crawler_list.append(crawler)
        # crawler_listの各Crawlerをマルチスレッドまたはforkして実行
    def output(self, format, itemlen, length):
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
    def __init__(self, config):
        self.config = config
        self.loadConfig(config)

configfile = "antenna.conf"
antenna = Antenna(configfile)
antenna.run()
