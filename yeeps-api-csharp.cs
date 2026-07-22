using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

public class Api
{
    private static readonly HttpClient client = new HttpClient{Timeout = TimeSpan.FromSeconds(120)};
    public static async Task<JsonElement> ApiCall(string oculusID, string mobileCode)
    {
        var url = "https://yeeps-proxy.onrender.com/yeeps";
        var body = new {oculusID, mobileCode};
        try
        {
            var json = JsonSerializer.Serialize(body);
            var content = new StringContent(json, Encoding.UTF8, "application/json");
            var response = await client.PostAsync(url, content);
            response.EnsureSuccessStatusCode();
            var responseText = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<JsonElement>(responseText);
        }
        catch (Exception e)
        {
            return JsonSerializer.SerializeToElement(new
            {
                error = e.Message
            });
        }
    }
}
