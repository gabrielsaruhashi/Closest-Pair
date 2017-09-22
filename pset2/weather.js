var Client = require('node-rest-client').Client;
 
var client = new Client();
 

 var args = {
    data: { test: "hello" },
    headers: { "Content-Type": "application/json" }
};

// direct way 
client.get("http://samples.openweathermap.org/data/2.5/weather?zip=94040,us&appid=b1b15e88fa797225412429c1c50c122a1", function (data, response) {
    // parsed response body as js object 
    console.log(data);
    // raw response 
    console.log(response);
});
 
// registering remote methods 
client.registerMethod("jsonMethod", "http://remote.site/rest/json/method", "GET");
 
client.methods.jsonMethod(function (data, response) {
    // parsed response body as js object 
    console.log(data);
    // raw response 
    console.log(response);
});