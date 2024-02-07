import requests
import time

API_KEY = "44f1957459334329bcc9e46f9d227281"
BASE_URL = "https://api-v3.mbta.com/"
PAGELIM = 2
ROUTE_TYPE = 1 # 1 Subway

def get_arrivals(station):
    url = f"{BASE_URL}predictions?filter[stop]={station}&page[limit]={PAGELIM}&fields[prediction]=status,departure_time&sort[-departure_time]&filter[route_type]={ROUTE_TYPE}"
    try:
        response = requests.get(url)
        data = response.json()
        return data["data"]
    except:
        print("Invalid Station Code")
        return None

while True:
    station = input("Enter Station Code: ").lower()
    data = get_arrivals(station)
    if not data:
        continue

    print(data)
    break
    