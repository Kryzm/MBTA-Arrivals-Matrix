import requests

URL = "https://api-v3.mbta.com/stops?filter[route_type]=0,1&fields[stop]=zone,description"

response = requests.get(URL)
response_json = response.json()
if response.status_code == 200:
    f = open("stops-list.txt", "w")
    n = 0
    stoplist = []
    for range in response_json["data"]:
        description = response.json()['data'][n]['attributes']['description']
        code = response.json()['data'][n]['relationships']['parent_station']['data']['id']
        stoplist.append(f"{description} --- {code}")
        n += 1
stoplist.sort()
for line in stoplist:
    f.write(f"{line}\n")
f.close()