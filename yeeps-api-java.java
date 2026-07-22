import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import org.json.JSONObject;

public class Api {
    public static JSONObject apiCall(String oculusID, String mobileCode) {
        String url = "https://yeeps-proxy.onrender.com/yeeps";
        JSONObject body = new JSONObject();
        body.put("oculusID", oculusID);
        body.put("mobileCode", mobileCode);

        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(url))
                .timeout(java.time.Duration.ofSeconds(120))
                .header("Content-Type", "application/json")
                .POST(HttpRequest.BodyPublishers.ofString(body.toString()))
                .build();

        try {
            HttpResponse<String> response = client.send(
                    request,
                    HttpResponse.BodyHandlers.ofString()
            );

            if (response.statusCode() >= 200 && response.statusCode() < 300) {
                return new JSONObject(response.body());
            } else {
                return new JSONObject()
                        .put("error", "HTTP " + response.statusCode() + ": " + response.body());
            }

        } catch (Exception e) {
            return new JSONObject()
                    .put("error", e.getMessage());
        }
    }
}
