# coding: utf-8
IRC_SERVER = "irc.mozilla.gr.jp" #chat1.ustream.tv"
IRC_PORT = 6667
IRC_NICK = "chikabot"

import re
import DNS
from irclib import nm_to_n
from irclib import nm_to_h
from ircbot import SingleServerIRCBot
	
class IRCBot(SingleServerIRCBot):
    def __init__(self):
        print ("connecting.")
        SingleServerIRCBot.__init__(self, [(IRC_SERVER, IRC_PORT)], IRC_NICK, IRC_NICK)
        self.channel = u"#moz-otaku".encode("utf-8")

    def on_welcome(self, irc, e):
        print ("on_welcome")
        irc.join(self.channel)

    def on_privmsg(self, irc, e):
        try:
            nick = nm_to_n(e.source())
            host = nm_to_h(e.source())
            msg = unicode(e.arguments()[0], "utf-8")
        except Exception, e:
            print(str(e))
            return

        e.nick = nick
        e.host = host
        e.msg = msg
        
        if re.match("^[1-9]\d{3,4}$", msg):
            self.on_gameoffer(e)
        elif re.match("^good night, jewel.$", msg):
            self.on_queryquit(e)

    def on_pubmsg(self, irc, e):
        pass

    def on_gameoffer(self, e):
        addr = self.dns_lookup(e.host)
        if addr:
            msg = e.nick + u"が" + addr + u":" + e.msg + u"で募集中だよ。"
            self.connection.notice(self.channel, msg.encode("utf-8"))

    def on_queryquit(self, e):
        self.connection.quit("good bye.")

    def dns_lookup(self, host):
        DNS.DiscoverNameServers()
        ans = DNS.Request(host).req().answers
        for rec in ans:
            if rec['typename'] == 'A':
                return rec['data']
        return null		

	#on_pubmsg = on_privmsg

bot = IRCBot()
bot.start()
