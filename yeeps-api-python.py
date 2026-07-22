def api_call(oculusID, mobileCode):
    url = "https://yeeps-proxy.onrender.com/yeeps"
    body = {"oculusID": oculusID, "mobileCode": mobileCode}
    try:
        response = requests.post(url, json=body, timeout=120)
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        return {"error": str(e)}
