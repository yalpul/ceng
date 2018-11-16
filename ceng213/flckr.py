import os
os.system("curl -s https://www.flickr.com -o index.html")
fp = open("index.html", "r")

s = fp.read()

index = s.find(".main-bucket")

fin = s[index:].find(")")

s = s[index:fin+index]
url = s[s.find("(")+1:]
os.system("curl -s %s -o bg.png" % url)
fp.close()
os.remove("index.html")
