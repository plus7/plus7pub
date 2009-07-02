#!/usr/bin/python
# -*- coding:utf-8 -*-

import twitter
import datetime

today = datetime.date.today()

deadline = datetime.date(2009, 8, 24)

delta = deadline - today

api = twitter.Api("cs2010_exam", "wani.1951.hakase")

if today == datetime.date(2009, 8, 24):
    msg = u"本日は入試1日目(数学)です。がんばってください。"
elif today == datetime.date(2009,8,25):
    msg = u"本日は入試2日目(専門科目)です。気を引き締めて逝きましょう。"
elif today == datetime.date(2009,8,26):
    msg = u"明日は口述試験です。体調を整えて。"
elif today == datetime.date(2009,8,27):
    msg = u"本日は口述試験です。リラックスリラックス。"
else:
    if delta.days > 0:
        msg = u"コンピュータ科学専攻 入試まであと%d日" % delta.days
    else:
        quit()

#print msg
api.PostUpdate(msg)
