import requests

url = 'http://service-oracle-tnsnames.web.cern.ch/service-oracle-tnsnames/tnsnames.ora'
r = requests.get(url,allow_redirects=True)
tnsnames_content = r.content

#open('mytnsnames.ora','wb').write(r.content)
