# -*- coding: cp936 -*-
import sys,os,codecs,urllib2
from HTMLParser import HTMLParser

class MyHTMLParser(HTMLParser):
    def __init__(self, filepath):
        self.fp = open(filepath, "w")
        HTMLParser.__init__(self)
        
    def handle_starttag(self, tag, attrs):
        print "Start tag:", tag
        for attr in attrs:
            print "     attr:", attr
            
    def handle_endtag(self, tag):
        print "End tag  :", tag
        
    def handle_data(self, data):
        print "Data     :", data
        try:
            utf8_data =  unicode(data,'gbk').encode('utf-8')
            print "Unicode Data:", utf8_data
            if not utf8_data.startswith(unicode('笔画数','cp936').encode('utf-8')):
                self.fp.write(utf8_data)
        except UnicodeDecodeError:
            print "Exception raise"
        
if __name__ == "__main__":
    helpStr = "url output"
    if len(sys.argv) != 3:
        print "useage: %s %s"%(sys.argv[0],helpStr)
    else :
        u = urllib2.urlopen(sys.argv[1])
        p = MyHTMLParser(sys.argv[2])
        p.feed(u.read())
        p.close()
        u.close()
                
