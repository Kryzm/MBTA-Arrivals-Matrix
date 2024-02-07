import requests

BASE_URL = "https://api-v3.mbta.com/"
STOP_ID = "place-cntsq" # See stops-list.txt
ROUTE_TYPE = "1" # 1 - Subway, 2 - Light Rail
API_KEY = ""
URL = f"{BASE_URL}predictions?filter[stop]={STOP_ID}&filter[route_type]={ROUTE_TYPE}&page[limit]=2"

def Get_Requests():
    data = requests.get(URL)
    if data.status_code == 200:
        data_json = data.json()
        route_0 = data_json["data"][0]["relationships"]["route"]["data"]["id"]
        depart_0 = data_json["data"][0]["attributes"]["departure_time"]
        route_1 = data_json["data"][1]["relationships"]["route"]["data"]["id"]
        depart_1 = data_json["data"][1]["attributes"]["departure_time"]
        print(URL)
        print(data_json["data"][0])
        print(f"{route_0} {depart_0}")
        print(f"{route_1} {depart_1}")
        print(URL)

    else:
        print("Failed to retrieve data")

Get_Requests()


# for range in data.json()['data'][n]:
#    description = data.json()['data'][n]['attributes']['description']