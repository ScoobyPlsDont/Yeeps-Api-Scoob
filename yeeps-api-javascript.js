async function apiCall(oculusID, mobileCode) {
    const url = "https://yeeps-proxy.onrender.com/yeeps";
    const body = {oculusID, mobileCode};
    try {
        const response = await fetch(url, {
            method: "POST",
            headers: {"Content-Type": "application/json"},
            body: JSON.stringify(body)
        });
        if (!response.ok) {throw new Error(`HTTP ${response.status}: ${response.statusText}`);}
        return await response.json();
    }
    catch (e) {return {error: e.message};}
}
