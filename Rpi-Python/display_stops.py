import requests

BASE_URL = "https://api-v3.mbta.com/"
STOP_ID = "place-davis"

data = requests.get(f"{BASE_URL}predictions?filter[stop]={STOP_ID}&page[limit]=2")
data_json = data.json()
route_0 = data_json["data"][0]["relationships"]["route"]["data"]["id"]
depart_0 = data_json["data"][0]["attributes"]["departure_time"]
route_1 = data_json["data"][1]["relationships"]["route"]["data"]["id"]
depart_1 = data_json["data"][1]["attributes"]["departure_time"]

print(f"{route_0} {depart_0}")
print(f"{route_1} {depart_1}")
print(f"URL: {BASE_URL}predictions?filter[stop]={STOP_ID}&page[limit]=2")



# for range in data.json()['data'][n]:
#    description = data.json()['data'][n]['attributes']['description']

# if data.status_code == 200

# payload = {'key1': 'value1', 'key2': 'value2'}
#r = requests.get('https://httpbin.org/get', params=payload)

