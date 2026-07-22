<?php

function apiCall($oculusID, $mobileCode)
{
    $url = "https://yeeps-proxy.onrender.com/yeeps";
    $body = ["oculusID" => $oculusID, "mobileCode" => $mobileCode];
    $ch = curl_init($url);
    curl_setopt_array($ch, [
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_POST => true,
        CURLOPT_POSTFIELDS => json_encode($body),
        CURLOPT_HTTPHEADER => [
            "Content-Type: application/json"
        ],
        CURLOPT_TIMEOUT => 120,
    ]);
  
    $response = curl_exec($ch);
  
    if (curl_errno($ch)) {$error = curl_error($ch); curl_close($ch); return ["error" => $error];
                         }
    $httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);
  
    if ($httpCode >= 400) {return ["error" => "HTTP Error $httpCode", "response" => $response];
                          }
    $decoded = json_decode($response, true);
  
    if (json_last_error() !== JSON_ERROR_NONE) {return ["error" => "Invalid JSON response", "response" => $response];}
    return $decoded;
}
?>
