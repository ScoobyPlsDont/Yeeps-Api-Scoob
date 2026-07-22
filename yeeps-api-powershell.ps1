$body = @{oculusID   = "USERNAME" mobileCode = "0000"} | ConvertTo-Json -Compress

try {
    $response = Invoke-RestMethod `
        -Uri "https://yeeps-proxy.onrender.com/yeeps" `
        -Method POST `
        -ContentType "application/json" `
        -Body $body `
        -TimeoutSec 120 `
        -ErrorAction Stop

    $response | ConvertTo-Json -Depth 10
}
catch {
    if ($_.ErrorDetails.Message) {
        try {$_.ErrorDetails.Message | ConvertFrom-Json | ConvertTo-Json -Depth 10}
        catch {$_.ErrorDetails.Message}
    }
    else {
        $_.Exception.Message
    }
}
